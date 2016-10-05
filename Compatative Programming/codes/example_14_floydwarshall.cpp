#include "competitive.h"

int main() {
  int V, E, a, b, weight;

  /*
  // Graph in Figure 1.17
  5 9
  0 1 2
  0 2 1
  0 4 3
  1 3 4
  2 1 1
  2 4 1
  3 0 1
  3 2 3
  3 4 5
  */

  memset(AdjMat, MEMSET_HALF_INF, sizeof AdjMat);
  scanf("%d %d", &V, &E);
  REP (i, 0, E - 1) {
    scanf("%d %d %d", &a, &b, &weight);
    AdjMat[a][b] = weight; // directed graph
  }

  REP (i, 0, V - 1)
    AdjMat[i][i] = 0;

  REP (k, 0, V - 1)
    REP (i, 0, V - 1)
      REP (j, 0, V - 1)
        AdjMat[i][j] = min(AdjMat[i][j],
          AdjMat[i][k] + AdjMat[k][j]);

  REP (i, 0, V - 1)
    REP (j, 0, V - 1)
      printf("APSP(%d, %d) = %d\n", i, j, AdjMat[i][j]);

  return 0;
}
