#include <stdio.h>
#include <stdint.h>

union msgblock {
  uint8_t e[64];
  uint32_t t[16];
  uint64_t s[8];
};

enum status {READ, PAD0, PAD1, FINISH};

int main(int argc, char *argv[]) {
  
  union msgblock M;        

  uint64_t nobits = 0;
  uint64_t nobytes;

  enum status S = READ;

  int i;

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
      S = FINISH; // Set enum to FINISH
    } else if(nobytes < 64) { // If between 56 and 64 bytes have been read from the file
      S = PAD0; // Set enum to PAD0
      M.e[nobytes] = 0x80; // Write 10000000 into the first position in M that hasn't already been written to
      while (nobytes < 64) { // While between 56 and 64 bytes have been read in from the file
         // Continue to add blocks of 00000000 until 64 bits are left at the end
        nobytes = nobytes + 1;
        M.e[nobytes] = 0x00;
      }
    } else if(feof(f)) { // If exactly 64 bytes have been read in from the file
      S = PAD1; // Set enum to PAD1
    }
  }

  if(S == PAD0 || S == PAD1){ // If enum is PAD0 or PAD1
    // Add a block of padding where the first 448 bits are 0, and the last 8 bytes write in the number of bits in the original message
    for (i=0; i<56; i++){
      M.e[i] = 0x00;
    }
    M.s[7] = nobits;
  }

  if(S == PAD1){ // If enum is PAD1
    M.e[0] = 0x80; // Write 10000000 into the last block
  }

  fclose(f); // Close the file

  // Print out the msgblock
  for(i=0; i<64; i++){
    printf("%x ", M.e[i]);
  }
  printf("\n");
        
  return 0;
}
