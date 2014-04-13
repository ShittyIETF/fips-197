#include <cstdio>
#include <iomanip>
#include <string>
#include <sstream>
#include <array>
#include <vector>
using namespace std;

typedef unsigned char   Byte;
typedef vector<Byte>    Bytes;
typedef unsigned int    Word;

// 4-byte vector (for columns of the matrices)
struct Vec4 : public array<Byte, 4> {
  typedef array<Byte, 4> base_type;

  Vec4() : array<Byte, 4>{{0, 0, 0, 0}}
  {
  }
};

// 128-bit block for input/output
struct IOBlock : public array<Byte, 16> {};

// 128-bit block in column-major matrix form
struct Block : public array<Vec4, 4> {
  typedef array<Vec4, 4> base_type;

  Block() {}

  Block& operator<<(const IOBlock &in) {
    for (int r = 0; r < 4; ++r) {
      for (int c = 0; c < 4; ++c) {
        (*this)(r,c) = in[r + 4*c];
      }
    }
    return *this;
  }
  Block& operator>>(IOBlock &in) {
    for (int r = 0; r < 4; ++r) {
      for (int c = 0; c < 4; ++c) {
        in[r + 4*c] = (*this)(r,c);
      }
    }
    return *this;
  }

  // Element accessor style: m(r, c)
  // Indices start from zero
  Byte& operator()(int row, int col) {
    return (*this)[col][row];
  }
};

struct State : public Block {};

#include "GF28"
using namespace gf_2_8;

#include "Transformations"
using namespace Transformations;

#include "Cipher"
using namespace Cipher;


IOBlock aes128(IOBlock input, CipherKey<128> key)
{
  CipherKeyExpansion<128> exp = expandKey(key);

  State st;
  st << input;





  IOBlock r;
  st >> r;
  return r;
}

char digitToHex(int a) {
  if (a < 10) {
    return a + '0';
  } else {
    return a + 'a' - 10;
  }
}
template <int N>
string hexaString(const array<Vec4, N> &a) {
  stringstream ss;
  for (int c = 0; c < N; ++c) {
    for (int r = 0; r < 4; ++r) {
      Byte b = a[c][r];
      ss << digitToHex(b / 16) << digitToHex(b % 16);
    }
  }
  return ss.str();
}

void testExpansions() {
  printf("Testing 128-bit key expansion:\n");

  Byte key128[] = {
    0x2b, 0x7e, 0x15, 0x16, 0x28, 0xae, 0xd2, 0xa6, 0xab, 0xf7, 0x15, 0x88, 0x09, 0xcf, 0x4f, 0x3c
  };

  CipherKey<128> key;
  for (int c = 0; c < ::Cipher::Cipher<128>::key_length; ++c) {
    for (int r = 0; r < 4; ++r) {
      key[c][r] = key128[4*c + r];
    }
  }

  printf("Expanding key: %s\n", hexaString<4>(static_cast<array<Vec4, 4>&>(key)).c_str());

  CipherKeyExpansion<128> exp = expandKey(key);

  string expected128 = "2b7e151628aed2a6abf7158809cf4f3ca0fafe1788542cb123a339392a6c7605f2c295f27a96b9435935807a7359f67f3d80477d4716fe3e1e237e446d7a883bef44a541a8525b7fb671253bdb0bad00d4d1c6f87c839d87caf2b8bc11f915bc6d88a37a110b3efddbf98641ca0093fd4e54f70e5f5fc9f384a64fb24ea6dc4fead27321b58dbad2312bf5607f8d292fac7766f319fadc2128d12941575c006ed014f9a8c9ee2589e13f0cc8b6630ca6";

  printf("Expected: %s\n", expected128.c_str());
  printf("Actual:   %s\n", hexaString<44>(static_cast<array<Vec4, 44>&>(exp)).c_str());

}

int main()
{
  Vec4 v;

  printf("GF(2^8) Tests:\n");
  printf("57 + 83\n");
  printf("Expected: d4\n");
  printf("Actual:   %x\n", gf_2_8::add(0x57u, 0x83u));
  printf("57 x 83\n");
  printf("Expected: c1\n");
  printf("Actual:   %x\n", gf_2_8::mul(0x57u, 0x83u));

  testExpansions();

  return 0;
}
