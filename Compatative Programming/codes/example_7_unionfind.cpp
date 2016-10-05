#include "competitive.h" // study this header file!

int main() {
  printf("Assume that there are 5 disjoint sets initially\n");
  initSet(); // create MAX_SETS disjoint sets, we only use first 5
  unionSet('A' - 'A', 'B' - 'A'); // unionSet(A, B)
  unionSet('A' - 'A', 'C' - 'A'); // unionSet(A, C)
  unionSet('D' - 'A', 'B' - 'A'); // unionSet(D, B)
  printf("findSet(A) = %d\n", findSet('A' - 'A'));
  printf("isSameSet(A, E) = %d\n", isSameSet('A' - 'A', 'E' - 'A'));

  return 0;
}
