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

bool anyTestFailed = false;

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

template <int N> struct KeyExpansionExample {
  static Byte key[];
  static char expansionStr[];
};

template<>
Byte KeyExpansionExample<128>::key[] = {
  0x2b, 0x7e, 0x15, 0x16, 0x28, 0xae, 0xd2, 0xa6, 0xab, 0xf7,
  0x15, 0x88, 0x09, 0xcf, 0x4f, 0x3c,
};
// TODO make those binary too
template<>
char KeyExpansionExample<128>::expansionStr[] =
  "2b7e151628aed2a6abf7158809cf4f3ca0fafe1788542cb123a339392a6c7605"
  "f2c295f27a96b9435935807a7359f67f3d80477d4716fe3e1e237e446d7a883b"
  "ef44a541a8525b7fb671253bdb0bad00d4d1c6f87c839d87caf2b8bc11f915bc"
  "6d88a37a110b3efddbf98641ca0093fd4e54f70e5f5fc9f384a64fb24ea6dc4f"
  "ead27321b58dbad2312bf5607f8d292fac7766f319fadc2128d12941575c006e"
  "d014f9a8c9ee2589e13f0cc8b6630ca6";

template<>
Byte KeyExpansionExample<192>::key[] = {
  0x8e, 0x73, 0xb0, 0xf7, 0xda, 0x0e, 0x64, 0x52, 0xc8, 0x10, 0xf3, 0x2b,
  0x80, 0x90, 0x79, 0xe5, 0x62, 0xf8, 0xea, 0xd2, 0x52, 0x2c, 0x6b, 0x7b,
};
template<>
char KeyExpansionExample<192>::expansionStr[] =
  "8e73b0f7da0e6452c810f32b809079e562f8ead2522c6b7bfe0c91f72402f5a5"
  "ec12068e6c827f6b0e7a95b95c56fec24db7b4bd69b5411885a74796e92538fd"
  "e75fad44bb095386485af05721efb14fa448f6d94d6dce24aa326360113b30e6"
  "a25e7ed583b1cf9a27f939436a94f767c0a69407d19da4e1ec1786eb6fa64971"
  "485f703222cb8755e26d135233f0b7b340beeb282f18a2596747d26b458c553e"
  "a7e1466c9411f1df821f750aad07d753ca4005388fcc5006282d166abc3ce7b5"
  "e98ba06f448c773c8ecc720401002202";

template<>
Byte KeyExpansionExample<256>::key[] = {
  0x60, 0x3d, 0xeb, 0x10, 0x15, 0xca, 0x71, 0xbe, 0x2b, 0x73, 0xae, 0xf0, 0x85, 0x7d, 0x77, 0x81,
  0x1f, 0x35, 0x2c, 0x07, 0x3b, 0x61, 0x08, 0xd7, 0x2d, 0x98, 0x10, 0xa3, 0x09, 0x14, 0xdf, 0xf4,
};
template<>
char KeyExpansionExample<256>::expansionStr[] =
  "603deb1015ca71be2b73aef0857d77811f352c073b6108d7"
  "2d9810a30914dff49ba354118e6925afa51a8b5f2067fcde"
  "a8b09c1a93d194cdbe49846eb75d5b9ad59aecb85bf3c917"
  "fee94248de8ebe96b5a9328a2678a647983122292f6c79b3"
  "812c81addadf48ba24360af2fab8b46498c5bfc9bebd198e"
  "268c3ba709e0421468007bacb2df331696e939e46c518d80"
  "c814e20476a9fb8a5025c02d59c58239de1369676ccc5a71"
  "fa2563959674ee155886ca5d2e2f31d77e0af1fa27cf73c3"
  "749c47ab18501ddae2757e4f7401905acafaaae3e4d59b34"
  "9adf6acebd10190dfe4890d1e6188d0b046df344706c631e";

template <int N>
void testExpansion() {
  enum {
    key_length =       Cipher<N>::key_length,
    expansion_length = Cipher<N>::expansion_length,
  };

  // Copy data to CipherKey structure
  // TODO remove typename somehow
  typename Cipher<N>::CipherKey key;
  for (int c = 0; c < key_length; ++c) {
    for (int r = 0; r < 4; ++r) {
      key[c][r] = KeyExpansionExample<N>::key[4*c + r];
    }
  }

  // Expand the key into `exp`
  typename Cipher<N>::CipherKeyExpansion exp = expandKey<N>(key);
  string actualExpHex = hexaString<expansion_length>(
    static_cast< array<Vec4, expansion_length >& >(exp)
  ).c_str();

  // Compare expansion with expected value
  if (strcmp(actualExpHex.c_str(), KeyExpansionExample<N>::expansionStr) != 0) {
    // Not-equal, fail
    printf("%d-bit Key Expansion Test -> FAIL\n", N);
    anyTestFailed = true;
    return;
  }

  // if no fails occurred, pass
  printf("%d-bit Key Expansion Test -> PASS\n", N);
}

int main() {
  printf("Key Expansion Test\n");
  printf("==================\n");

  testExpansion<128>();
  testExpansion<192>();
  testExpansion<256>();

  if (anyTestFailed) {
    printf("Status: FAIL\n");
    return -1;
  }

  printf("Status: SUCCESS\n");
  return 0;
}
