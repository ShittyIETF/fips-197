#include <cstdio>
#include <cstring>

#include "Global"

// Values are taken from Appendix C.
template <int N> struct ExampleVector {
  static Byte key[];
  static Byte plaintext[];
  static Byte ciphertext[];
};

// Example vectors for 128-bit key length
template <> Byte ExampleVector<128>::key[] = {
  0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09,
  0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f,
};
template <> Byte ExampleVector<128>::plaintext[] = {
  0x00, 0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77, 0x88, 0x99,
  0xaa, 0xbb, 0xcc, 0xdd, 0xee, 0xff,
};
template <> Byte ExampleVector<128>::ciphertext[] = {
  0x69, 0xc4, 0xe0, 0xd8, 0x6a, 0x7b, 0x04, 0x30, 0xd8, 0xcd,
  0xb7, 0x80, 0x70, 0xb4, 0xc5, 0x5a,
};

// Example vectors for 192-bit key length
template <> Byte ExampleVector<192>::key[] = {
  0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09,
  0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f, 0x10, 0x11, 0x12, 0x13,
  0x14, 0x15, 0x16, 0x17,
};
template <> Byte ExampleVector<192>::plaintext[] = {
  0x00, 0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77, 0x88, 0x99,
  0xaa, 0xbb, 0xcc, 0xdd, 0xee, 0xff,
};
template <> Byte ExampleVector<192>::ciphertext[] = {
  0xdd, 0xa9, 0x7c, 0xa4, 0x86, 0x4c, 0xdf, 0xe0, 0x6e, 0xaf,
  0x70, 0xa0, 0xec, 0x0d, 0x71, 0x91,
};

// Example vectors for 256-bit key length
template <> Byte ExampleVector<256>::key[] = {
  0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09,
  0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f, 0x10, 0x11, 0x12, 0x13,
  0x14, 0x15, 0x16, 0x17, 0x18, 0x19, 0x1a, 0x1b, 0x1c, 0x1d,
  0x1e, 0x1f,
};
template <> Byte ExampleVector<256>::plaintext[] = {
  0x00, 0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77, 0x88, 0x99,
  0xaa, 0xbb, 0xcc, 0xdd, 0xee, 0xff,
};
template <> Byte ExampleVector<256>::ciphertext[] = {
  0x8e, 0xa2, 0xb7, 0xca, 0x51, 0x67, 0x45, 0xbf, 0xea, 0xfc,
  0x49, 0x90, 0x4b, 0x49, 0x60, 0x89,
};

bool anyTestFailed = false;

template <int N>
void testEncryption() {
  typename Cipher<N>::CipherKey key;
  Block in;

  in.read(ExampleVector<N>::plaintext);
  key.read(ExampleVector<N>::key);
  Block out = Cipher<N>::encrypt(Cipher<N>::expandKey(key), in);

  Byte ciphertext[4 * Cipher<N>::block_size];
  out.write(ciphertext);

  if (memcmp(ciphertext, ExampleVector<N>::ciphertext, 4 * Cipher<N>::block_size) != 0) {
    anyTestFailed = true;
    std::printf("%d-bit Encrypt Test -> FAIL\n", N);
    return;
  }
  std::printf("%d-bit Encrypt Test -> PASS\n", N);
}

template <int N>
void testDecryption() {
  typename Cipher<N>::CipherKey key;
  Block in;

  in.read(ExampleVector<N>::ciphertext);
  key.read(ExampleVector<N>::key);
  Block out = Cipher<N>::decrypt(Cipher<N>::expandKey(key), in);

  Byte plaintext[4 * Cipher<N>::block_size];
  out.write(plaintext);

  if (memcmp(plaintext, ExampleVector<N>::plaintext, 4 * Cipher<N>::block_size) != 0) {
    anyTestFailed = true;
    std::printf("%d-bit Decrypt Test -> FAIL\n", N);
    return;
  }
  std::printf("%d-bit Decrypt Test -> PASS\n", N);
}

int main() {
  std::printf("Example Vectors Test\n");
  std::printf("====================\n");

  testEncryption<128>();
  testDecryption<128>();
  testEncryption<192>();
  testDecryption<192>();
  testEncryption<256>();
  testDecryption<256>();

  if (anyTestFailed) {
    std::printf("Status: FAIL\n");
    return -1;
  }

  std::printf("Status: SUCCESS\n");
  return 0;
}
