#include <stdio.h>
#include <stdint.h>

union msgblock {
  uint8_t e[64];
  uint32_t t[16];
  uint64_t s[8];
};

int main(int argc, char *argv[]) {
  
  FILE* f;
  char c;

  f = fopen(argv[1], "r");
  printf("%c\n", fread(&c, 1, 1, f));

  fclose(f);
        
  return 0;
}
