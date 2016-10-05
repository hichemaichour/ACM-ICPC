#include "competitive.h"

int main() {
  int V, E, a, b, weight;

  /*
  // Graph in Figure 4.19
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

  scanf("%d %d", &V, &E);
  REP (i, 0, V - 1) {
    REP (j, 0, V - 1)
      AdjMat[i][j] = 1000000000; // use 1.10^9 to avoid overflow
    AdjMat[i][i] = 0;
  }

  REP (i, 0, E - 1) {
    scanf("%d %d %d", &a, &b, &weight);
    AdjMat[a][b] = weight; // directed graph
  }

  REP (k, 0, V - 1) // O(V^3) Floyd Warshall's code is here
    REP (i, 0, V - 1)
      REP (j, 0, V - 1)
        AdjMat[i][j] = min(AdjMat[i][j],
          AdjMat[i][k] + AdjMat[k][j]);

  REP (i, 0, V - 1)
    REP (j, 0, V - 1)
      printf("APSP(%d, %d) = %d\n", i, j, AdjMat[i][j]);

  return 0;
}
