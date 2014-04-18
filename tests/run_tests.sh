#! /bin/bash

# Compile & Run KeyExpansionTest
g++ -std=c++11 -I ../ KeyExpansionTest.cpp -o KeyExpansionTest && ./KeyExpansionTest

# TODO this is not part of the test suite
# Compile & Run main
g++ -std=c++11 -I ../ ../aes128.cpp -o aes128 && ./aes128
