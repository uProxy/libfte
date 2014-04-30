#include "exceptions.h"
#include "ranker.h"
#include "encrypter.h"
#include "ffx2.h"

namespace fte {
encrypter::encrypter( std::string input_dfa, uint32_t input_max_len,
                      std::string output_dfa, uint32_t output_max_len,
                      std::string key ) {
    _input_ranker = ranker(input_dfa, input_max_len);
    _output_ranker = ranker(output_dfa, output_max_len);
    _key = key;
    _ffx = fte::ffx2::ffx2();

    // validate that _input/_output rankers are compatible
    mpz_class words_in_input_language = _input_ranker.getNumWordsInLanguage(input_max_len);
    mpz_class words_in_output_language = _output_ranker.getNumWordsInLanguage(output_max_len);
    if ( words_in_input_language > words_in_output_language ) {
        throw fte::FteException();
    }
}

std::string encrypter::encrypt( std::string plaintext ) {
    mpz_class plaintext_rank = _input_ranker.rank(plaintext);
    mpz_class C = _ffx.encrypt( _key, plaintext_rank );
    std::string retval = _output_ranker.unrank(C);
    return retval;
}

std::string encrypter::decrypt( std::string ciphertext ) {
    mpz_class C = _output_ranker.rank(ciphertext);
    mpz_class plaintext_rank = _ffx.decrypt( _key, C );
    std::string retval = _input_ranker.unrank(plaintext_rank);
    return retval;
}
} // namespace fte
