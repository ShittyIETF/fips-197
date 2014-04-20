#include <cstdio>

#include "Global"

int main() {
  std::printf("GF(2^8) Tests\n");
  std::printf("=============\n");

  bool anyTestFailed = false;

  if (gf_2_8::add(0x57u, 0x83u) == 0xd4u) {
    std::printf("GF(2^8) Addition Test -> PASS\n");
  } else {
    std::printf("GF(2^8) Addition Test -> FAIL\n");
    anyTestFailed = true;
  }
  if (gf_2_8::mul(0x57u, 0x83u) == 0xc1u) {
    std::printf("GF(2^8) Multiplication Test -> PASS\n");
  } else {
    std::printf("GF(2^8) Multiplication Test -> FAIL\n");
    anyTestFailed = true;
  }

  if (anyTestFailed) {
    std::printf("Status: FAIL\n");
    return -1;
  }

  std::printf("Status: SUCCESS\n");
  return 0;
}
