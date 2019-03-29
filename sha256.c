// Brian Doyle - G00330969
// The Secure Hash Algorithm, 256 bit version

#include <stdio.h> // Usual input/output header file
#include <stdin.h> // For using fixed bit length integers

void sha256();

int main (int argc, char *argv[]){
  
  return 0;
}

void sha256(){

  uint32_t W[64]; // Message schedule (Section 6.2).
  uint32_t a, b, c, d, e, f, g, h; // Working variables (Section 6.2).
  uint32_t T1, T2; // Two temporary variables (section 6.2).

  // The Hash value (Section 6.2).
  // Values come from Section 5.3.3.
  uint32_t H[8] = {
    0x6a09e667,
    0xbb67ae85,
    0x3c6ef372,
    0xa54ff53a,
    0x510e527f,
    0x9b05688c,
    0x1f83d9ab,
    0x5be0cd19
  }

  // Current message block
  uint32_t M[16];



}
