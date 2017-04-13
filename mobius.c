#include <stdio.h>
#include <math.h>
#include <string.h>

#define LEN 5
#define N   8
#define DEBUG 0

/* Distance matrix */
int D[N][N] = {
  {0, 1, 2, 2, 1, 2, 2, 1},
  {1, 0, 1, 2, 2, 1, 2, 2},
  {2, 1, 0, 1, 2, 2, 1, 2},
  {2, 2, 1, 0, 1, 2, 2, 1},
  {1, 2, 2, 1, 0, 1, 2, 2},
  {2, 1, 2, 2, 1, 0, 1, 2},
  {2, 2, 1, 2, 2, 1, 0, 1},
  {1, 2, 2, 1, 2, 2, 1, 0}
};

/* f: {0, 1, 2} -> {'0', '1', '*'} */
inline char addr_char(int n){
  return (n != 2) ? ('0' + n) : '*';
}

/**
 * Determines if two strings are actually dist apart
 */
int valid(char* addr1, char* addr2, int dist){
  int i;

  for (i = 0; i < LEN; ++i)
    if ((addr1[i] + addr2[i]) == ('0' + '1'))
      --dist;

  return !dist;
}

int all_valid_rec(char addr[][LEN + 1], int vtx){
  int temp, max, i, j;

  if (vtx >= N)
    return 1;

  max = (int) pow(3, LEN);
  for (i = 0; i < max; ++i){
    temp = i;
    /* Generate next address */
    for (j = 0; j < LEN; ++j){
      addr[vtx][j] = addr_char(temp % 3);
      temp /= 3;
    }

    /* Check validity with all past */
    for (j = 0; j < vtx; ++j)
      if (!valid(addr[vtx], addr[j], D[vtx][j]))
        break;


    /* If all past are valid, generate another */
    if (j == vtx){

#if DEBUG
      for (j = 0; j < vtx; ++j)
        printf("  ");
      printf("%s\n", addr[vtx]);
#endif

      if (all_valid_rec(addr, vtx + 1))
        return 1;
    }
  }

  return 0;
}

int main(int argc, char* argv[]){
  int vtx;
  int i, j, max;
  int found;
  char addr[N][LEN + 1];

  memset(addr, 0, N * (LEN + 1) * sizeof(char));

  max = 1 << (LEN - 2);
  for (i = 0; i < max; ++i){
    for (j = 0; j < LEN; ++j)
      addr[0][j] = ((i & (1 << j)) ? '*' : '0');

    printf("%s\n", addr[0]);
    if (found = all_valid_rec(addr, 1))
      break;
  }

  if (found){
    printf("Solution found:\n");
    for (vtx = 0; vtx < N; ++vtx)
      printf("%d: %s\n", vtx, addr[vtx]);
  }
  else {
    printf("No possible addressing\n");
  }

  return 0;
}
