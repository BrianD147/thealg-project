# SHA-256 Algorithm
A 4th Year Project for Theory Of Algorithms Module

### The Secure Hash Algorithm
The secure hash algorithm is an algorithm which takes an input and produces a hash value known as a message digest, this value is typically represented as a hexidecimal number. The algorithm was designed by the NSA(National Security Agency). The original algorithm has bee nconsidered unsecure by most major companies and organisations since 2010, and in 2017 CWI Amsterdam and Google published two different pdf files which produced the same hash value, thus proving the algorithm to be unsecure. However SHA-2, the algorithms second itteration has yet to be cracked and is still considered secure.

### Running this version of SHA-256
In order to run the program, the following command must be run
```
./sha256 <filename>
```
Please make sure to run the command from the correct directory, and be sure to have the file you with to hash in the same directory

Any readable file can be hashed, try using the text.txt file like so
```
./sha256 test.txt
```
The program will return a hash value like so
```
f681b315, 0ba42833, 4f102eba, 3952d78b, 400ded46, c7d12921, 58db9625, 70ecac68
```
(Note:This has value is currently incorrect due to a problem with converting the hash value to Big Endian.) 

### The basics of the code
The program is ran from the main function, which first reads and checks if the input file is acceptable. If it is then the program runs the 'sha256' method.
```c
int main (int argc, char *argv[]){
FILE *msgf;
msgf = fopen(argv[1], "r"); // Open the file
  if(msgf == NULL){
    fprintf(stderr, "Error opening the file: %s\n", strerror(errno));
  } else {
    sha256(msgf); // Run the secure has algorithm on the file
    fclose(msgf); // Close the file
  } 
   return 0;
}
```
The sha256 method declares a lot of constants to begin with. The entire documentation describing and explaining the algorithm in detail can be found [here]

Basically we have a set of hash values (H) which are reset each time the program starts.
These values are then changed over multiple iterations and this is what is printed to the screen once everything is complete.
```c
uint32_t H[8] = {
  0x6a09e667,
  0xbb67ae85,
  0x3c6ef372,
  0xa54ff53a,
  0x510e527f,
  0x9b05688c,
  0x1f83d9ab,
  0x5be0cd19
};
```
K is a set of constant values that represent the first 32-bits of the fractional parts of the cube roots of the first 64 primes. This are described in the above document.
```c
uint32_t K[] = {
  0x428a2f98, 0x71374491, 0xb5c0fbcf, 0xe9b5dba5,
  0x3956c25b, 0x59f111f1, 0x923f82a4, 0xab1c5ed5,
  0xd807aa98, 0x12835b01, 0x243185be, 0x550c7dc3,
  0x72be5d74, 0x80deb1fe, 0x9bdc06a7, 0xc19bf174,
  0xe49b69c1, 0xefbe4786, 0x0fc19dc6, 0x240ca1cc,
  0x2de92c6f, 0x4a7484aa, 0x5cb0a9dc, 0x76f988da,
  0x983e5152, 0xa831c66d, 0xb00327c8, 0xbf597fc7,
  0xc6e00bf3, 0xd5a79147, 0x06ca6351, 0x14292967,
  0x27b70a85, 0x2e1b2138, 0x4d2c6dfc, 0x53380d13,
  0x650a7354, 0x766a0abb, 0x81c2c92e, 0x92722c85,
  0xa2bfe8a1, 0xa81a664b, 0xc24b8b70, 0xc76c51a3,
  0xd192e819, 0xd6990624, 0xf40e3585, 0x106aa070,
  0x19a4c116, 0x1e376c08, 0x2748774c, 0x34b0bcb5,
  0x391c0cb3, 0x4ed8aa4a, 0x5b9cca4f, 0x682e6ff3,
  0x748f82ee, 0x78a5636f, 0x84c87814, 0x8cc70208,
  0x90befffa, 0xa4506ceb, 0xbef9a3f7, 0xc67178f2
};
```
Each file the program takes in must be padded with extra extra bits in order for the file to be an acceptable size. An acceptable size being a multiple of 64 bytes. Basically 10000000 is written into the first available space at the end of the file. Then 0's are added to the file up until the last 64 bits. Finally the last 64 bits are filled with a value that represents the size of the inital file. This is the most complex part of the entire process, and all the code has been commented to help you understand what is going on.

[here]: https://www.nist.gov/publications/secure-hash-standard
