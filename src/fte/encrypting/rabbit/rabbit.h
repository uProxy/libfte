#ifndef _RABBIT_ENCRYPTER_H
#define _RABBIT_ENCRYPTER_H

#include "../encrypter.h"

#include "rabbit_impl.h"

#include <gmpxx.h>

namespace fte {

namespace encrypting {

const uint32_t kRabbitKeyLengthInBytes = 16;
const uint32_t kRabbitIvLengthInBytes = 8;
const uint32_t kRabbitKeyLengthInNibbles = kRabbitKeyLengthInBytes * 2;
const uint32_t kRabbitIvLengthInNibbles = kRabbitIvLengthInBytes * 2;

class Rabbit : public Encrypter {

 protected:
  std::string key_;
  std::string init_vector_;
  RabbitCryptor cryptor_;

 public:

  bool SetKey(const std::string & key);

  bool Encrypt(const mpz_class & plaintext,
               uint32_t plaintext_len_in_bits,
               mpz_class * ciphertext);

  bool Encrypt(const mpz_class & tweak,
               uint32_t tweak_len_in_bits,
               const mpz_class & plaintext,
               uint32_t plaintext_len_in_bits,
               mpz_class * ciphertext);


  bool Decrypt(const mpz_class & ciphertext,
               uint32_t ciphertext_len_in_bits,
               mpz_class * plaintext);

  bool Decrypt(const mpz_class & tweak,
               uint32_t tweak_len_in_bits,
               const mpz_class & ciphertext,
               uint32_t ciphertext_len_in_bits,
               mpz_class * plaintext);
};

} // namespace encrypting

} // namespace fte

#endif /* _RABBIT_ENCRYPTER_H */
