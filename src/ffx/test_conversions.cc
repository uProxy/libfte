#define __STDC_LIMIT_MACROS
#define __STDC_CONSTANT_MACROS

#include "gtest/gtest.h"

#include "ffx/ffx.h"

const uint32_t FFX_RADIX = 2;

TEST(FFX2, ExtractBits1) {
  // We have the 4-bit X as 0b1000
  mpz_class X = 0x08;
  uint8_t X_len = 4;

  // should return exactly 1000b (bits in index 0 to 3)
  mpz_class retval = ffx::extract_bit_range(X, X_len, 0, 3);

  EXPECT_EQ(retval, 0x8);
}

TEST(FFX2, ExtractBits2) {
  // X is the 8-bit string: 0b10001000
  mpz_class X = 0x88;
  uint8_t X_len = 8;

  // should return exactly 1000b for left/right
  mpz_class retval_left = ffx::extract_bit_range(X, X_len, 0, 3);
  mpz_class retval_right = ffx::extract_bit_range(X, X_len, 4, 7);

  EXPECT_EQ(retval_left, 0x8);
  EXPECT_EQ(retval_right, 0x8);
}

TEST(FFX2, ExtractBits3) {
  // 0b111111111
  mpz_class X = 0xFF;
  uint8_t X_len = 8;

  // should return exactly 1111b for left/right
  mpz_class retval = ffx::extract_bit_range(X, X_len, 0, 7);

  EXPECT_EQ(retval, 0xFF);
}

TEST(FFX2, ExtractBits4) {
  // 0b111111111
  mpz_class X = 0xFF;
  uint8_t X_len = 8;

  // should return exactly 1111b for left/right
  mpz_class retval_left = ffx::extract_bit_range(X, X_len, 0, 3);
  mpz_class retval_right = ffx::extract_bit_range(X, X_len, 4, 7);

  EXPECT_EQ(retval_left, 0xF);
  EXPECT_EQ(retval_right, 0xF);
}

TEST(FFX2, ExtractBits5) {
  // 0b11110000
  mpz_class X = 0xF0;
  uint8_t X_len = 8;

  mpz_class retval_left = ffx::extract_bit_range(X, X_len, 0, 3);
  mpz_class retval_right = ffx::extract_bit_range(X, X_len, 4, 7);

  EXPECT_EQ(retval_left, 0xF);
  EXPECT_EQ(retval_right, 0x0);
}

TEST(FFX2, ExtractBits6) {
  // 0b11110000
  mpz_class X = 0xFFFF0000;
  uint8_t X_len = 32;

  mpz_class retval_left = ffx::extract_bit_range(X, X_len, 0, 15);
  mpz_class retval_right = ffx::extract_bit_range(X, X_len, 16, 31);

  EXPECT_EQ(retval_left, 0xFFFF);
  EXPECT_EQ(retval_right, 0x0000);
}

TEST(FFX2, MpzCharConversion1) {
  uint32_t n = 2;
  mpz_class X = 1024;
  unsigned char * Y = new unsigned char[n];
  mpz_class Z = 0;

  ffx::mpz_to_base256(X, n, Y);

  EXPECT_EQ(n, 2);
  EXPECT_EQ(Y[1], '\00');
  EXPECT_EQ(Y[0], '\04');

  ffx::base256_to_mpz(Y, n, Z);

  EXPECT_EQ(X, Z);

  delete[] Y;
}

TEST(FFX2, MpzCharConversion2) {
  mpz_class X = mpz_class("99999999999999999999");
  uint32_t n = mpz_sizeinbase(X.get_mpz_t(), 256);
  unsigned char * Y = new unsigned char[n];
  mpz_class Z = 0;

  ffx::mpz_to_base256(X, n, Y);
  ffx::base256_to_mpz(Y, n, Z);

  EXPECT_EQ(X, Z);

  delete[] Y;
}

TEST(FFX2, 16to256) {
  std::string X = "00000000000000000000000000000000";
  uint32_t sizeInBase256 = 16;
  unsigned char * Y = new unsigned char[sizeInBase256];

  ffx::base16_to_base256(X, sizeInBase256, Y);
  
  uint32_t i = 0;
  for (;i<sizeInBase256;i++) {
      EXPECT_EQ(Y[i], 0);
  }

  delete[] Y;
}