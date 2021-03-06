#include "gtest/gtest.h"

#include "aes_cbc_mac.h"
#include "conversions.h"

// Test vector from:
//   http://csrc.nist.gov/groups/STM/cavp/documents/aes/KAT_AES.zip

TEST(AES_CBC_MAC, MAC1) {
  std::string key = "80000000000000000000000000000000";
  uint32_t key_length_in_bytes = (key.length() + 1) / 2;
  unsigned char * pKey = new unsigned char[key_length_in_bytes];
  fte::encrypting::Base16ToBase256(key, key_length_in_bytes, pKey);
  uint8_t base = 16;
  mpz_class plaintext = mpz_class("00000000000000000000000000000000", base);
  uint32_t plaintext_len = 128;
  mpz_class ciphertext = 0;
  fte::encrypting::AesCbcSetKey(pKey);
  fte::encrypting::AesCbcMac(plaintext, plaintext_len, &ciphertext);
  EXPECT_EQ(ciphertext.get_str(base), "edd33d3c621e546455bd8ba1418bec8");
}

TEST(AES_CBC_MAC, MAC2) {
  std::string key = "c0000000000000000000000000000000";
  uint32_t key_length_in_bytes = (key.length() + 1) / 2;
  unsigned char * pKey = new unsigned char[key_length_in_bytes];
  fte::encrypting::Base16ToBase256(key, key_length_in_bytes, pKey);
  uint8_t base = 16;
  mpz_class plaintext = mpz_class("00000000000000000000000000000000", base);
  uint32_t plaintext_len = 128;
  mpz_class ciphertext = 0;
  fte::encrypting::AesCbcSetKey(pKey);
  fte::encrypting::AesCbcMac(plaintext, plaintext_len, &ciphertext);
  EXPECT_EQ(ciphertext.get_str(base), "4bc3f883450c113c64ca42e1112a9e87");
}

TEST(AES_CBC_MAC, MAC3) {
  std::string key = "00000000000000000000000000000000";
  uint32_t key_length_in_bytes = (key.length() + 1) / 2;
  unsigned char * pKey = new unsigned char[key_length_in_bytes];
  fte::encrypting::Base16ToBase256(key, key_length_in_bytes, pKey);
  uint8_t base = 16;
  mpz_class plaintext = mpz_class("80000000000000000000000000000000", base);
  uint32_t plaintext_len = 128;
  mpz_class ciphertext = 0;
  fte::encrypting::AesCbcSetKey(pKey);
  fte::encrypting::AesCbcMac(plaintext, plaintext_len, &ciphertext);
  EXPECT_EQ(ciphertext.get_str(base), "3ad78e726c1ec02b7ebfe92b23d9ec34");
}

TEST(AES_CBC_MAC, MAC4) {
  std::string key = "00000000000000000000000000000000";
  uint32_t key_length_in_bytes = (key.length() + 1) / 2;
  unsigned char * pKey = new unsigned char[key_length_in_bytes];
  fte::encrypting::Base16ToBase256(key, key_length_in_bytes, pKey);
  uint8_t base = 16;
  mpz_class plaintext = mpz_class("c0000000000000000000000000000000", base);
  uint32_t plaintext_len = 128;
  mpz_class ciphertext = 0;
  fte::encrypting::AesCbcSetKey(pKey);
  fte::encrypting::AesCbcMac(plaintext, plaintext_len, &ciphertext);
  EXPECT_EQ(ciphertext.get_str(base), "aae5939c8efdf2f04e60b9fe7117b2c2");
}
