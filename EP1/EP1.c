#include "driverEP1.h"

/// @brief 
/// @param M 
/// @param memSize 
/// @return 
int processa (short int *M, int memSize) {
  unsigned short int ri, pc, a, b, c, d, r, psw;
  unsigned short int* op_1,* op_2,* saida;
  unsigned short int ZERO = 0;
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
        printf("%hx\n", a);
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

        // saida
        switch (ri&0b0000000111000000) {
        case 0b0000000000000000:
          // A
          saida = &a;
          break;
        case 0b0000000001000000:
          // B
          saida = &b;
          break;
        case 0b0000000010000000:
          // C
          saida = &c;
          break;
        case 0b0000000011000000:
          // D
          saida = &d;
          break;
        case 0b0000000110000000:
          // R
          saida = &r;
          break;
        }

        // entrada 1
        switch (ri&0b0000000000111000) {
        case 0b0000000000000000:
          // A
          op_1 = &a;
          break;
        case 0b0000000000001000:
          // B
          op_1 = &b;
          break;
        case 0b0000000000010000:
          // C
          op_1 = &c;
          break;
        case 0b0000000000011000:
          // D
          op_1 = &d;
          break;
        case 0b0000000000110000:
          // R
          op_1 = &r;
          break;
        }

        // entrada 2

        if ((ri&0b0000000000000100) == 0) {
          op_2 = &ZERO;
        }
        switch (ri&0b0000000000000111) {
          case 0b0000000000000100:
            // A
            op_2 = &a;
            break;
          case 0b0000000000000101:
            // B
            op_2 = &b;
            break;
          case 0b0000000000000110:
            // C
            op_2 = &c;
            break;
          case 0b0000000000000111:
            // D
            op_2 = &d;
            break;
        }


        switch (ri&0b0000111000000000) {
          case 0b0000000000000000:
            // 0xFFFF
            *saida = 0xFFFF;
            break;
          case 0b0000001000000000:
            // 0x0000
            *saida = 0x0000;
            break;
          case 0b0000010000000000:
            // not
            *saida = ~(*op_1);
            break;
          case 0b0000011000000000:
            // and
            *saida = (*op_1) & (*op_2);
            break;
          case 0b0000100000000000:
            // or
            *saida = (*op_1) | (*op_2);
            break;
          case 0b0000101000000000:
            // xor
            *saida = (*op_1) ^ (*op_2);
            break;
          case 0b0000110000000000:
            // add
            printf("add\n");
            *saida = (*op_1) + (*op_2);
            break;
          case 0b0000111000000000:
            // sub
            *saida = (*op_1) - (*op_2);
            break;
        }



        break;
    }

    pc++;
    if (pc>=memSize) pc=0;
  } while ((ri&0xF000)!=0xF000);
}
