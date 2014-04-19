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

int main() {
  printf("GF(2^8) Tests\n");
  printf("=============\n");

  bool anyTestFailed = false;

  if (gf_2_8::add(0x57u, 0x83u) == 0xd4u) {
    printf("GF(2^8) Addition Test -> PASS\n");
  } else {
    printf("GF(2^8) Addition Test -> FAIL\n");
    anyTestFailed = true;
  }
  if (gf_2_8::mul(0x57u, 0x83u) == 0xc1u) {
    printf("GF(2^8) Multiplication Test -> PASS\n");
  } else {
    printf("GF(2^8) Multiplication Test -> FAIL\n");
    anyTestFailed = true;
  }

  if (anyTestFailed) {
    printf("Status: FAIL\n");
    return -1;
  }

  printf("Status: SUCCESS\n");
  return 0;
}
