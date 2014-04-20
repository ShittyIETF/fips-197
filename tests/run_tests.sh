#! /bin/bash

# Compile & Run GF(2^8) Test
g++ -std=c++11 -Wall -I ../ GF_2_8_Test.cpp -o GF_2_8_Test && ./GF_2_8_Test

# Compile & Run KeyExpansionTest
g++ -std=c++11 -Wall -I ../ KeyExpansionTest.cpp -o KeyExpansionTest && ./KeyExpansionTest

# Compile & Run CipherTest
g++ -std=c++11 -Wall -I ../ CipherTest.cpp -o CipherTest && ./CipherTest

# Compile & Run ExampleVectorsTest
g++ -std=c++11 -Wall -I ../ ExampleVectorsTest.cpp -o ExampleVectorsTest && ./ExampleVectorsTest
