#include <cstdio>
#include <cstring>

#include "Global"

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
  std::printf("Cipher Test\n");
  std::printf("==================\n");
  bool fail = 0;

  Cipher<128>::CipherKey key;
  Block in;

  key.read(cipherKey);
  in.read(input);

  Block out = Cipher<128>::encrypt(Cipher<128>::expandKey(key), in);

  Byte actualOutput[4 * Cipher<128>::block_size];
  out.write(actualOutput);
  if (std::memcmp(output, actualOutput, 4 * Cipher<128>::block_size) != 0) {
    fail = true;
  }

  if (fail) {
    std::printf("128-bit Cipher Test -> FAIL\n");
    std::printf("Status: FAIL\n");
    return -1;
  }

  std::printf("128-bit Cipher Test -> PASS\n");
  std::printf("Status: SUCCESS\n");
  return 0;



  return 0;
}
