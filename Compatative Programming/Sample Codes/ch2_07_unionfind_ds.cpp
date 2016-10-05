#include "competitive.h" // study this header file!

int main() {
  printf("Assume that there are 5 disjoint sets initially\n");
  initSet(5); // create 5 disjoint sets
  unionSet('A' - 'A', 'B' - 'A'); // unionSet(A, B)
  unionSet('A' - 'A', 'C' - 'A'); // unionSet(A, C)
  unionSet('D' - 'A', 'B' - 'A'); // unionSet(D, B)
  printf("findSet(A) = %d\n", findSet('A' - 'A')); // will return 2 (the parent ID of 'A', 'B', 'C', 'D')
  printf("findSet(B) = %d\n", findSet('B' - 'A')); // will return 2 (the parent ID of 'A', 'B', 'C', 'D')
  printf("findSet(C) = %d\n", findSet('C' - 'A')); // will return 2 (the parent ID of 'A', 'B', 'C', 'D')
  printf("findSet(D) = %d\n", findSet('D' - 'A')); // will return 2 (the parent ID of 'A', 'B', 'C', 'D')
  printf("findSet(E) = %d\n", findSet('E' - 'A')); // will return 4 (the parent ID of 'E')
  printf("isSameSet(A, E) = %d\n", isSameSet('A' - 'A', 'E' - 'A')); // will return 0 (false)
  printf("isSameSet(A, B) = %d\n", isSameSet('A' - 'A', 'B' - 'A')); // will return 1 (true)

  return 0;
}
