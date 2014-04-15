#include <cstdio>
#include <iomanip>
#include <string>
#include <sstream>
#include <array>
#include <vector>
using namespace std;

// TODO tidy up those includes
#include "Global"

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

