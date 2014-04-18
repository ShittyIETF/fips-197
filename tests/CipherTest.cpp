#include <cstdio>
#include <cstring>
#include <iomanip>
#include <string>
#include <sstream>
#include <array>
#include <vector>
using namespace std;

#include "Global"

#include "GF28"
using namespace gf_2_8;

#include "Transformations"
using namespace Transformations;

#include "Cipher"

Byte input[] = {
  0x32, 0x43, 0xf6, 0xa8, 0x88, 0x5a, 0x30, 0x8d, 0x31, 0x31,
  0x98, 0xa2, 0xe0, 0x37, 0x07, 0x34,
};

Byte cipherKey[] = {
  0x2b, 0x7e, 0x15, 0x16, 0x28, 0xae, 0xd2, 0xa6, 0xab, 0xf7,
  0x15, 0x88, 0x09, 0xcf, 0x4f, 0x3c,
};

Byte output[] = {
  0x39, 0x25, 0x84, 0x1d, 0x02, 0xdc, 0x09, 0xfb, 0xdc, 0x11,
  0x85, 0x97, 0x19, 0x6a, 0x0b, 0x32,
};

int main() {
  printf("Cipher Test\n");
  printf("==================\n");

  Cipher<128>::CipherKey key;
  Block inp;
  for (int c = 0; c < 4; ++c) {
    for (int r = 0; r < 4; ++r) {
      key[c][r] = cipherKey[4 * c + r];
      inp[c][r] = input[4 * c + r];
    }
  }

  Block out = Cipher<128>::encrypt(Cipher<128>::expandKey(key), inp);
  bool fail = 0;

  for (int c = 0; c < 4; ++c) {
    for (int r = 0; r < 4; ++r) {
      if (out[c][r] != output[4 * c + r]) {
        fail = true;
      }
    }
  }

  if (fail) {
    printf("128-bit Cipher Test -> FAIL\n");
    printf("Status: FAIL\n");
    return -1;
  }

  printf("128-bit Cipher Test -> PASS\n");
  printf("Status: SUCCESS\n");
  return 0;



  return 0;
}
