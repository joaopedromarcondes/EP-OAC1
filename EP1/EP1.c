#include "driverEP1.h"

int processa (short int *M, int memSize) {
  unsigned short int ri, pc, a, b, c, d, r, psw;
  pc=0;
  a = 0;
  r = memSize;
  do {
    ri=M[pc];
    if (ri != 0)
      printf ("Ensine-me a fazer algo com %hx\n", ri);

    switch (ri&0xF000) {
      // NOP
      case 0x0000:
        //printf("NOP\n");
        break;

      // LDA(X)
      case 0x1000:
        printf("LDA\n");
        a = M[ri&0x0FFF];
        //printf("%hx\n", a);
        break;

      // STA(X)
      case 0x2000:
        printf("STA\n");
        M[ri&0x0FFF] = a;
        break;

      // JMP X
      case 0x3000:
        printf("JMP\n");
        r = pc + 1;
        pc = ri&0x0FFF;
        break;

      // JNZ X
      case 0x4000:
        printf("JNZ\n");
        r = pc + 1;
        if (a != 0)
          pc = ri&0x0FFF;
        break;

      // RET
      case 0x5000:
        printf("RET\n");
        pc = r;
        break;

      // ARIT
      case 0x6000:
        printf("ARIT\n");

        switch (ri&0b0000111000000000) {
          case 0b0000000000000000:
            // 0xFFFF
            break;
          case 0b0000001000000000:
            // 0x0000
            break;
          case 0b0000010000000000:
            // not
            break;
          case 0b0000011000000000:
            // and
            break;
          case 0b0000100000000000:
            // or
            break;
          case 0b0000101000000000:
            // xor
            break;
          case 0b0000110000000000:
            // add
            break;
          case 0b0000111000000000:
            // sub
            break;
        }












        break;
    }

    pc++;
    if (pc>=memSize) pc=0;
  } while ((ri&0xF000)!=0xF000);
}
