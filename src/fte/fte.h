/*
 * This class implements a Format-Transforming Encryption scheme for
 * regular languages. The input plaintext language and output ciphertext
 * language can be specified using DFAs.
 *
 * As example example, say we have:
 *   - DFA M1 that accepts the language generated by regex R1 = "^(a|b)+$"
 *   - DFA M2 that accepts the language generated by regex R2 = "^(x|y)+$"
 *
 * Then the FTE[M1,M2] scheme will accepts plaintexts in the language L(R1)
 * and output ciphertexts in the language of L(R2).
 *
 * In the FTE interface we introduce two additional parameters: input_max_len
 * and output_max_len. These are for efficiency purposes and restrict the max.
 * length for any input/output string, respectively.
 */

#ifndef _FTE_FTE_H
#define _FTE_FTE_H

#include <string>

#include "ffx/ffx.h"
#include "fte/exceptions.h"
#include "fte/ranking/dfa_ranker.h"

namespace fte {

const uint32_t kFfxRadix = 2;
const uint32_t kFteKeyLengthInNibbles = 32;

class Fte {
 private:
  ranking::DfaRanker input_ranker_;
  ranking::DfaRanker output_ranker_;
  std::string key_;
  ffx::Ffx ffx_;
  uint32_t input_language_capacity_;
  uint32_t output_language_capacity_;
  mpz_class words_in_input_language_;
  mpz_class words_in_output_language_;

 public:
  Fte() {};

  /*
   * input_dfa and input_max_len specify the input plaintext language
   * ouput_dfa and out_max_len specificy the output ciphertext language
   * the key is a 32-character hex string string
   */
  Fte(const std::string input_dfa, const uint32_t input_max_len,
      const std::string output_dfa, const uint32_t output_max_len,
      const std::string key);

  /*
   * On input of a string that is accepted by input_dfa (specified in the constructor)
   * the encrypt function outputs a ciphertext that is accepted by output_dfa.
   * The plaintext cannot exceed length input_max_len.
   */
  std::string Encrypt(const std::string plaintext);

  /*
   * On input of a string that is accepted by output_dfa (specified in the constructor)
   * the decrypt function recovers a plaintext.
   */
  std::string Decrypt(const std::string ciphertext);

};

} // namespace fte

#endif /* _FTE_FTE_H */
