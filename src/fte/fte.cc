/*
 * References:
 *   [FTE1] http://eprint.iacr.org/2012/494.pdf
 *   [FTE2] (to appear summer 2014)
 */

#include "fte.h"

#include <math.h>

#include "src/fte/encrypting/ffx/ffx.h"
#include "src/fte/encrypting/rabbit/rabbit.h"

#include "fte/ranking/dfa_ranker.h"
#include "fte/ranking/dot_star_ranker.h"
#include "fte/ranking/dot_plus_ranker.h"

namespace fte {

Fte::Fte() {
  plaintext_ranker_ = NULL;
  ciphertext_ranker_ = NULL;
  encrypter_ = NULL;
  key_is_set_ = false;
  languages_are_set_ = false;
  max_cycles_ = kMaxCycles;
}

Fte::~Fte() {
  if (plaintext_ranker_ != NULL) {
    if (plaintext_ranker_ == ciphertext_ranker_) {
      ciphertext_ranker_ = NULL;
    }
    delete plaintext_ranker_;
  }
  if (ciphertext_ranker_ != NULL) {
    delete ciphertext_ranker_;
  }
  if (encrypter_ != NULL) {
    delete encrypter_;
  }
}

/*
 * Here we set our input/output langauges and verify that the output langauge has
 * capacity at least as large as the input language.
 */
bool Fte::SetLanguages(const std::string & plaintext_dfa,
                       uint32_t plaintext_max_len,
                       const std::string & ciphertext_dfa,
                       uint32_t ciphertext_max_len) {

  if (plaintext_dfa == fte::ranking::DOT_STAR_DFA) {
    plaintext_ranker_ = new ranking::DotStarRanker();
  } else if (plaintext_dfa == fte::ranking::DOT_PLUS_DFA) {
    plaintext_ranker_ = new ranking::DotPlusRanker();
  } else {
    plaintext_ranker_ = new ranking::DfaRanker();
  }
  plaintext_ranker_->SetLanguage(plaintext_dfa, plaintext_max_len);
  plaintext_ranker_->WordsInLanguage(&words_in_plaintext_language_);
  plaintext_language_capacity_in_bits_ = mpz_sizeinbase(words_in_plaintext_language_.get_mpz_t(),
                                         kFfxRadix);

  bool languages_are_the_same = (plaintext_dfa == ciphertext_dfa) && (plaintext_max_len == ciphertext_max_len);
  if (languages_are_the_same) {
    ciphertext_ranker_ = plaintext_ranker_;
  } else {
    if (ciphertext_dfa == fte::ranking::DOT_STAR_DFA) {
      ciphertext_ranker_ = new ranking::DotStarRanker();
    } else if (ciphertext_dfa == fte::ranking::DOT_PLUS_DFA) {
      ciphertext_ranker_ = new ranking::DotPlusRanker();
    } else {
      ciphertext_ranker_ = new ranking::DfaRanker();
    }
    ciphertext_ranker_->SetLanguage(ciphertext_dfa, ciphertext_max_len);
  }

  ciphertext_ranker_->WordsInLanguage(&words_in_ciphertext_language_);
  ciphertext_language_capacity_in_bits_ = mpz_sizeinbase(
      words_in_ciphertext_language_.get_mpz_t(), kFfxRadix);

  if(words_in_plaintext_language_ > words_in_ciphertext_language_) {
    return false;
  }

  languages_are_set_ = true;

  // Automatically determine which encrypter we'll use.
  //   * rabbit is a stream cipher
  //   * ffx is a variable input length blockcipher
  // For rabbit, the encrypt and decrypt functions are the same. So,
  // we can't use it for cycle walking. We only need cycle walking when the
  // plaintext/ciphertext language are the same size. Hence, we can only
  // use rabbit when we know we won't cyclewalk. This positively correlates with
  // the use_rabbit condition.
  bool ptxt_smaller = plaintext_language_capacity_in_bits_ < ciphertext_language_capacity_in_bits_;
  bool dot_star_mode = (ciphertext_dfa == fte::ranking::DOT_STAR_DFA);
  bool dot_plus_mode = (ciphertext_dfa == fte::ranking::DOT_PLUS_DFA);
  bool use_rabbit = ptxt_smaller || dot_star_mode || dot_plus_mode;
  if (use_rabbit) {
    encrypter_ = new fte::encrypting::Rabbit();
  } else {
    encrypter_ = new fte::encrypting::Ffx(kFfxRadix);
  }

  if (key_ != "") {
    encrypter_->SetKey(key_);
    key_is_set_ = true;
  }

  return true;
}

bool Fte::set_key(const std::string & key) {
  key_ = key;

  if (encrypter_ != NULL) {
    bool success = encrypter_->SetKey(key);
    key_is_set_ = true;
  }

  return true;
}

/*
 * This is an implementation of rank-encipher-unrank, as described in [FTE2].
 * We perform cycle walking to ensure that we have a ciphertext in the input
 * domain of the ciphertext ranker.
 */
bool Fte::Encrypt(const std::string & plaintext,
                  std::string * ciphertext) {

  if (!key_is_set_) {
    return false;
  }

  if (!languages_are_set_) {
    return false;
  }

  // ensure ciphertext is initialized to the empty string
  ciphertext->clear();

  // rank
  mpz_class plaintext_rank;
  plaintext_ranker_->Rank(plaintext, &plaintext_rank);

  // encrypt
  mpz_class C = 0;
  encrypter_->Encrypt(plaintext_rank, plaintext_language_capacity_in_bits_, &C);
  while (C >= words_in_ciphertext_language_) {
    encrypter_->Encrypt(C, plaintext_language_capacity_in_bits_, &C);
  }

  // unrank
  ciphertext_ranker_->Unrank(C, ciphertext);

  return true;
}

/*
 * Here we recover a plaintext using rank-decipher-unrank.
 * See [FTE2] for more details.
 */
bool Fte::Decrypt(const std::string & ciphertext,
                  std::string * plaintext) {

  if (!key_is_set_) {
    return false;
  }

  if (!languages_are_set_) {
    return false;
  }

  // ensure plaintext is initialized to the empty string
  plaintext->clear();

  // rank
  mpz_class C;
  ciphertext_ranker_->Rank(ciphertext, &C);

  // encrypt
  mpz_class plaintext_rank = 0;
  encrypter_->Decrypt(C, plaintext_language_capacity_in_bits_, &plaintext_rank);
  while (plaintext_rank >= words_in_plaintext_language_) {
    encrypter_->Decrypt(plaintext_rank, plaintext_language_capacity_in_bits_, &plaintext_rank);
  }

  // unrank
  plaintext_ranker_->Unrank(plaintext_rank, plaintext);

  return true;
}

} // namespace fte
