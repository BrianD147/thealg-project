// Brian Doyle - G00330969
// The Secure Hash Algorithm, 256 bit version

#include <stdio.h> // Usual input/output header file
#include <stdin.h> // For using fixed bit length integers

void sha256();

// See Sections 4.1.2 and 4.2.2 for definitions
uint32_t sig0(uint32_t x);
uint32_t sig1(uint32_t x);

// See Section 3.2 for definitions
uint32_t rotr(uint32_t n, uint32_t x);
uint32_t shr(uint32_t n, uint32_t x);

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

  // For looping
  int t = 0;

  // From page 22, W[t] = M[t] for 0<= t ,+ 15.
  for (t=0; t<16; t++){
    W[t] = M[t];
  }

  // From page 22, W[t] =  ...
  for (t=16; t<64; t++){
    sig1(W[t-2]) + W[t-7] + sig0(W[t-15]) + W[t-16];
  }
  
  // Initialise a-h as per Step 2, Page 19.
  a = H[0]; b = H[1]; c = H[2]; d = H[3];
  e = H[4]; f = H[5]; g = H[6]; h = H[7]; 

  // Step 3.
  for (t=0; t<64; t++){
    T1 = h + SIG_1(e) + Ch(e, f, g) + K[t] + W[t];
    T2 = SIG_0(a) + Maj(a, b, c);
    h = g;
    g = f;
    f = e;
    e = d + T1;
    d = c;
    c = b;
    b = a;
    a = T1 + T2;
  }
}

// See Section 3.2 for definitions
uint32_t rotr(uint32_t n, uint32_t x){
  return (x >> n) | (x << (32-n));
}

uint32_t shr(uint32_t n, uint32_t x){
  return (x >> n);
}


uint32_t sig0(uint32_t x){
  // See Section 3.2 and 4.1.2 for definitions
  return (rotr(7,x) ^ rotr(18,x) ^ shr(3,x));
}

uint32_t sig1(uint32_t x){
  // See Section 3.2 and 4.1.2 for definitions
  return (rotr(17,x) ^ rotr(19,x) ^ shr(10,x));
}

