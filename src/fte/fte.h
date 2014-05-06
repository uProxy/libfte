#ifndef _LIBFTE_SRC_FTE_ENCRYPTER_H
#define _LIBFTE_SRC_FTE_ENCRYPTER_H

#include <iostream>
#include <string.h>

#include "ffx/ffx.h"

#include "fte/exceptions.h"
#include "fte/ranking/dfa.h"

namespace fte {

const uint32_t kFFXRadix = 2;
const uint32_t kFTEKeyLengthInNibbles = 32;

class Key : public ffx::Key {
 public:
  Key() : ffx::Key() {};
  Key(std::string key) : ffx::Key(key) {};
  Key(const char * key) : ffx::Key(key) {};
};

class FTE {
 private:
  ranking::DFA input_ranker_;
  ranking::DFA output_ranker_;
  Key key_;
  ffx::FFX ffx_;
  uint32_t input_language_capacity_;
  uint32_t output_language_capacity_;

 public:
  FTE(const std::string, const uint32_t,
      const std::string, const uint32_t,
      const Key);


  std::string encrypt(const std::string);
  std::string decrypt(const std::string);

};

} // namespace fte

#endif /* _LIBFTE_SRC_FTE_ENCRYPTER_H */