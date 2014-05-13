/*
 * FFX is a Format-Preserving block cipher. It can be used to implement a
 * variable-input length blockcipher over an arbitrary radix.
 * 
 * This is an implementation for FFX[radix=2] based on the proposed FFX NIST
 * standard, and the updated FFX specification by Rogaway et al:
 * 
 * - http://csrc.nist.gov/groups/ST/toolkit/BCM/documents/proposedmodes/ffx/ffx-spec2.pdf
 * - http://csrc.nist.gov/groups/ST/toolkit/BCM/documents/proposedmodes/ffx/ffx-spec.pdf
 * 
 * Unfortunately, test vectors for FFX[2] do not exist. In this directory I've
 * included aes-ffx-vectors.txt, which has test vectors for radix=10,36. I've
 * used these test vectors to implement an FFX implementation in Python. (Not
 * yet public.) In turn I used the Python implementation to generate FFX[2]
 * vectors.
 * 
 * TODO: Make Python implementation for FFX[N] public.
 * TODO: This implementation only supports radix=2.
 * TODO: This implementation does not support tweaks.
 * 
 * - Kevin P. Dyer
 */

#ifndef _LIBFTE_SRC_FFX_FFX_H
#define _LIBFTE_SRC_FFX_FFX_H

#include <exception>

#include <gmpxx.h>

#include "ffx/conversions.h"
#include "ffx/encryption.h"
#include "ffx/key.h"

namespace ffx {

const uint32_t DEFAULT_FFX_RADIX = 2;
const uint32_t DEFAULT_FFX_ROUNDS = 10;

class FFX {
 private:
  uint32_t radix_;

 public:
  FFX::FFX()
    : radix_(DEFAULT_FFX_RADIX) {
  }

  FFX::FFX(const uint32_t radix)
    : radix_(radix) {
    if(radix_ != DEFAULT_FFX_RADIX) {
      throw InvalidRadix();
    }
  }

  /*
   * Returns the radix for the current FFX instantiation.
   */
  const uint32_t get_radix() const {
    return radix_;
  }

  /*
   * On input of plaintext, plaintext_len, performs FFX.Encrypt[radix]
   * w.r.t. to the key.
   * 
   * This encrypt function preserves the length of the input plaintext. That is,
   * the resultant ciphertext will be a bitstring of length plaintext_len.
   */
  mpz_class encrypt(const Key key,
                    const mpz_class plaintext,
                    const uint32_t plaintext_len);


  /*
   * Given a ciphertext output from FFX.Encrypt[radix], a ciphertext_len and
   * key, recovers the input plaintext.
   */
  mpz_class decrypt(const Key key,
                    const mpz_class ciphertext,
                    const uint32_t ciphertext_len);

/* TODO: support tweaks

  mpz_class encrypt(const Key,
                    const mpz_class, const uint32_t,
                    const mpz_class, const uint32_t);

  mpz_class decrypt(const Key,
                    const mpz_class, const uint32_t,
                    const mpz_class, const uint32_t); 
*/
};

class FFXException : public std::exception {
  virtual const char* what() const throw() {
    return "FteException";
  }
};

class InvalidKeyLength : public FFXException {
  virtual const char* what() const throw() {
    return "Invalid key length.";
  }
};

class InvalidRadix : public FFXException {
  virtual const char* what() const throw() {
    return "We currently only support radix=2.";
  }
};

}

#endif /* _LIBFTE_SRC_FTE_ENCRYPTER_H */
