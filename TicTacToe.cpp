#include <cstdio>
#include <stdlib.h>
#include <time.h>
using namespace std;
char place[9] = {84, 73, 67, 84, 65, 67, 84, 79, 69};
char conf[2] = {88, 0};
int turn = 1;
int win = 0;
int rn = 0;
char pn(int m, int mode){
  if (mode == 0){
    if ((m % 2 == 0 && conf[0] == 79) || (m % 2 != 0 && conf[0] == 88)){
      return 88;
    }else if ((m % 2 != 0 && conf[0] == 79) || (m % 2 == 0 && conf[0] == 88)){
      return 79;
    }
	}else if (mode == 1){
    if (m % 2 == 0){
      return 79;
    }else{
      return 88;
    }
	}else if (mode == 2){
    if (m % 2 == 0){
      return 88;
    }else{
      return 79;
    }
  }
  return 0;
}
void wincheck(int computeMode){
  bool bp = 0;
  for (int c = 0; c <= 6; c += 3){
    const int row[3] = {place[c], place[c + 1], place[c + 2]};
    const int col[3] = {place[(c / 3)], place[(c / 3) + 3], place[(c / 3) + 6]};
    const int chk[4] = {(2 * pn(turn, 1)) + 32, (2 * conf[0]) + 32, (3 * conf[0]), (3 * pn(turn, 1))};
    for (int l = (computeMode * 2); l <= (1 + (computeMode * 2)); l++){
      if (row[0] + row[1] + row[2] == chk[l]){
        if (computeMode == 0){
          int p = 0;
          rn = c + p;
          while (p <= 2 && row[p] != 32){
            rn = c + p + 1;
            p++;
          }
        }else{
          win = pn(turn, 2);
        }
        bp = 1;
        break;
      }else if (col[0] + col[1] + col[2] == chk[l]){
        if (computeMode == 0){
          int p = 0;
          rn = (c / 3) + (p * 3);
          while (p <= 2 && col[p] != 32){
            rn = (c / 3) + ((p + 1) * 3);
            p++;
          }
        }else{
          win = pn(turn, 2);
        }
        bp = 1;
        break;
      }else{
        for (int d = 0; d <= 1; d++){
          const int diag[3] = {place[d * 2], place[4], place[8 - (d * 2)]};
          if (diag[0] + diag[1] + diag[2] == chk[l]){
            int p = 0;
            while (p <= 2){
              switch (p){
              case 0:
                if (diag[0] == 32 && computeMode == 0){
                  rn = d * 2;
                  bp = 1;
                }else if (computeMode == 1){
                  win = pn(turn, 2);
                  bp = 1;
                }
                break;
              case 1:
                if (diag[1] == 32 && computeMode == 0){
                  rn = 4;
                  bp = 1;
                }else if (computeMode == 1){
                  win = pn(turn, 2);
                  bp = 1;
                }
                break;
              case 2:
                if (diag[2] == 32 && computeMode == 0){
                  rn = 8 - (d * 2);
                  bp = 1;
                }else if (computeMode == 1){
                  win = pn(turn, 2);
                  bp = 1;
                }
                break;
              }
              p++;
            }
            break;
          }else{
            while (place[rn] != 32)
            {
              rn = rand() % 9;
              break;
            }
          }
        }
      }
      if (bp == 1){
        break;
      }
    }
  }
}
void drawDisplay(){
  system("CLS");
  printf("+---+---+---+\n| %c | %c | %c |\n+---+---+---+\n| %c | %c | %c |\n+---+---+---+\n| %c | %c | %c |\n+---+---+---+\n", place[0], place[1], place[2], place[3], place[4], place[5], place[6], place[7], place[8]);
  wincheck(1);
}
void mech(){
  for (int clr = 0; clr <= 8; clr++){
    place[clr] = 32;
  }
  drawDisplay();
  printf("\nGame Start!");
  for (turn = 1; turn <= 9; turn++){
    bool mode = 0;
    if (conf[1] == 80){
      printf("\nTurn %d!\nPlayer %c move (Position 1-9): ", turn, pn(turn, 0));
      mode = 0;
    }else{
      printf("\nTurn %d!\nPlayer %c move (Position 1-9): ", turn, pn(turn, 1));
      mode = 1;
    }
    if (pn(turn, mode) == conf[0] || conf[1] == 80){
      char pos=0;
      scanf(" %c", &pos);
      pos = pos - 48;
      while ((pos > 0 || pos < 10) && place[pos - 1] != 32){
        fflush(stdin);
        printf("Invalid Position. Please enter a correct position.\nPlayer %c move (Position 1-9): ", pn(turn, mode));
        scanf(" %c", &pos);
        pos = pos - 48;
      }
      place[pos - 1] = pn(turn, mode);
    }else{
      wincheck(0);
      place[rn] = pn(turn, 1);
    }
    drawDisplay();
    if (win == 88 || win == 79){
      system("Color 0A");
      printf("\nPlayer %c Wins!", pn(turn, 0));
      break;
    }
  }
}
int main(){
  srand(time(0));
  drawDisplay();
  printf("TicTacToe v1.2.1\nGame Start!\nPlay Mode: 2-Player or Computer (P/C): ");
  scanf("%c", &conf[1]);
  while (conf[1] != 80 && conf[1] != 67){
    printf("Invalid Choice. Please enter a correct option.\nPlay conf: 2-Player or Computer (P/C): ");
    scanf(" %c", &conf[1]);
  }
  if (conf[1] == 67){
    printf("Start as (X/O): ");
    scanf(" %c", &conf[0]);
    while (conf[0] != 79 && conf[0] != 88){
      printf("Invalid Choice. Please enter a correct option.\nStart as (X/O): ");
      scanf(" %c", &conf[0]);
    }
  }
  mech();
  if (win == 0){
    system("Color 06");
    printf("\nTie Between both players!");
  }
  printf("\nThank you for playing!\nMade by KosmicDaKerbal.\n");
  system("pause");
}
