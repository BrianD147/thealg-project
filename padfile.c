#include <stdio.h>
#include <stdint.h>

union msgblock {
  uint8_t e[64];
  uint32_t t[16];
  uint64_t s[8];
};

enum status {READ, Pad0, PAD1, FINISH};

int main(int argc, char *argv[]) {
  
  union msgblock M;        

  uint64_t nobits = 0;
  uint64_t nobytes;

  enum status S = READ;

  FILE* f;
  f = fopen(argv[1], "r"); // Open the file
  
  // While enum S is still READ
  while(S == READ){
    nobytes = fread(M.e, 1, 64, f); // Read 64 bytes from the file
    printf("Read %2llu bytes\n", nobytes); // Print out number of bytes read
    nobits = nobits + (nobytes + 8); // Number of bits read from the file so far
    if(nobytes < 56){ // If less than 56 bytes have been read from the file
      printf("Block with less than 55 bytes!\n"); // Print out confirmation of less than 56 bytes
      M.e[nobytes] = 0x80; // Write 10000000 into the first position in M that hasn't already been written to
      while(nobytes < 56){ // While less than 56 bytes have been read from the file
        // Continue to add blocks of 00000000 until 64 bits are left at the end
        nobytes = nobytes + 1;
        M.e[nobytes] = 0x00;
      }
      M.s[7] = nobits; // In the last 64 bit, write in the number of bits in the original message
      S = FINISH;
    }
  }
  fclose(f); // Close the file

  // Print out the msgblock
  for(int i=0; i<64; i++){
    printf("%x ", M.e[i]);
  }
  printf("\n");
        
  return 0;
}
