#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cards.h"

#define INBUFLEN 20
#define PLAYAGAINANSWERLEN 4 // should prob be 4

// To copy the RND in ms visual basic. Returns a float
// in the range [0,1) since rand() is in range [0, RAND_MAX)
// NOTE: rand() in C uses the same seed every time,
// sequence will always be the same
float RND() {
  return (float)rand()/(float)(RAND_MAX);
}

void printCardsTest(char** cards) {
  // Print shuffled cards test
  for (int N = 0; N < NUMCARDS; N++) {
    if (N % 13 == 0)
      printf("\n");
    printf("%s  ", cards[N]);
  }
  printf("\n");
  return;
}

// Safe alternative to scanf("%d", &typedNum)
int my_scanf_int(int* typedNum) {
  char my_inStr[INBUFLEN];
  int retInt;
  fgets(my_inStr, INBUFLEN, stdin);
  retInt = sscanf(my_inStr, "%d", typedNum);
  // Clear rest of stdin buffer if my_inStr
  // doesn't contain \n
  if (!strchr(my_inStr, '\n')) {
    while(getchar() != '\n');
  }
  return retInt;
}

int main() {
  char playAgain[PLAYAGAINANSWERLEN];
  int U, W, S, S1;
  int X, Z, N, I;
  char *C[NUMCARDS];
  char *K;
  int L;
  char matchedPtr[2];
  matchedPtr[0] = ' ';
  matchedPtr[1] = 0;
  S = 0;
  printf("                         ");
  printf("CONCENTRATION\n");
  printf("               ");
  printf("CREATIVE COMPUTING   MORRISON NEW JERSEY\n");
  printf("\n\n\n");

  // Loop forever until user chooses to not play again
  // after a game
  while (1) {
    // Instead of filling arr C with strings, let's fill
    // it with char pointers and shuffle those
    for (X = 0; X < NUMCARDS; X++) {
      C[X] = (char *)cards[X];
    }

    /* No shuffling for testing purposes
    // The original BASIC code only iterates Z as 1 thru 51
    for (Z=0; Z < NUMCARDS-1; Z++) {
      K = C[Z];
      L = (int)((float)(NUMCARDS - 1 - Z) * RND());
      C[Z] = C[L+1+Z];
      // Originally said we write to C[L] but that seems sus
      // wouldn't we lose the value at C[L]?
      C[L+1+Z] = K;
    }
      */

    printCardsTest(C);

    for (N=0; N<(NUMCARDS/2); N++) {
      U = -1;
      while (1) {
        printf("FIRST CARD\n");
        if (my_scanf_int(&U) == 1) {
          U = U - 1; // Make U zero-indexed
          if ((U >= 0) && (U < NUMCARDS)) {
            if (C[U][0] == ' ') {
              printf("YOU HAVE ALREADY MATCHED THAT CARD.\n");
              continue;
            }
            break;
          }
          printf("THERE ARE ONLY 52 CARDS IN THE DECK, NOT %d\n", U + 1);
          continue;
        }
        printf("ONLY ENTER A SINGLE INTEGER\n");
      }

      W = -1;
      while (1) {
        printf("SECOND CARD\n");
        if (my_scanf_int(&W) == 1) {
          W = W - 1; // Make W zero-indexed
          if ((W >= 0) && (W < NUMCARDS)) {
            if (C[W][0] == ' ') {
              printf("YOU HAVE ALREADY MATCHED THAT CARD.\n");
              continue;
            }
            if (U != W) {
              break;
            } else {
              printf("YOU CAN'T PICK THE SAME CARD TWICE!\n");
              continue;
            }
          }
          printf("THERE ARE ONLY 52 CARDS IN THE DECK, NOT %d\n", W + 1);
          continue;
        }
        printf("ONLY ENTER A SINGLE INTEGER\n");
      }
      
      // Check for 10 and 10 or two non-10s - '0' = 0x20, A-Z are in [0x40, 0x5A]
      if ((C[U][0] == C[W][0]) && (C[U][1] & 0x20) == (C[W][1] & 0x20)) {
        if (C[U][2] == 0) // Check that the 2-char-long strings include EOL null
          printf("CU2null\n");
        if (C[W][2] == 0)
          printf("CW2null\n");
        printf("THAT'S A MATCH -- %s %s\n", C[U], C[W]);
        C[U] = matchedPtr;
        C[W] = matchedPtr;
        S++;
        printf("YOUR SCORE IS NOW %d YOU HAVE HAD %d PICKS\n", S, N + 1);
      } else {
        printf("#%i is %s, #%i is %s", U + 1, C[U], W + 1, C[W]);
        printf("\r");
        for (I = 0; I < 50; I++) {
          printf(" ");
        }
        printf("\rHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH");
        printf("\rIIIIIIIIIIIIIIIIIIIIIIIIIIIIII");
        printf("\rXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX");
        printCardsTest(C);
        printf("\n\n");
      }
    }
    S1 = S / (N / 4);
    printf("YOU JUST SCORED %d OUT OF %d THAT IS ", S, NUMCARDS);
    printf("test S1: %d\n", S1);
    // Line 670 lists the last option instead 
    // of the second-to-last (typo by author?)
    switch (S1) {
      case 0:
        printf("POOR.\n");
        break;
      case 1:
        printf("FAIR.\n");
        break;
      case 2:
        printf("GOOD.\n");
        break;
      case 3:
        printf("EXCELLENT ! ! !\n");
        break;
      default:
        printf(". . . AAAH . . . UHH....YOU MUST HAVE CHEATED!\n");
    }

    printf("\nDO YOU WANT TO PLAY AGAIN\n");
    fgets(playAgain, PLAYAGAINANSWERLEN, stdin); 
    // Clear rest of stdin buffer if my_inStr
    // doesn't contain \n
    if (!strchr(playAgain, '\n')) {
      while(getchar() != '\n');
    }
    if (!strstr(playAgain, "YES")) {
      break;
    }
  }

  printf("\nCOME BACK AGAIN!!\n");  
  return 0;
}
