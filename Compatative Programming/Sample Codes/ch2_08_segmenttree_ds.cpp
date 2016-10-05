#include "competitive.h" // study this header file!

#define MAX_N 7

int main() {
  int A[MAX_N] = { 8, 7, 3, 9, 5, 1, 10 }; // the original array
  init_st(MAX_N);
  build_st(RANGE_MIN, A, 1, 0, MAX_N - 1);

  printf("              A is { 8, 7, 3, 9, 5, 1  , 10 }\n");
  printf("RMQ(1, 3) = %d\n", st_query(RANGE_MIN, A, 1, 0, MAX_N - 1, 1, 3)); // 2
  printf("RMQ(3, 4) = %d\n", st_query(RANGE_MIN, A, 1, 0, MAX_N - 1, 3, 4)); // 4
  printf("RMQ(0, 0) = %d\n", st_query(RANGE_MIN, A, 1, 0, MAX_N - 1, 0, 0)); // 0
  printf("RMQ(0, 6) = %d\n", st_query(RANGE_MIN, A, 1, 0, MAX_N - 1, 0, 6)); // 5
  printf("RMQ(4, 6) = %d\n", st_query(RANGE_MIN, A, 1, 0, MAX_N - 1, 4, 6)); // 5

  printf("Now, modify A into { 8, 7, 3, 9, 5, 100, 10 }\n");
  st_update_point(RANGE_MIN,A, 1, 0, MAX_N - 1, 5, 100);
  // these three values do not change
  printf("RMQ(1, 3) = %d\n", st_query(RANGE_MIN, A, 1, 0, MAX_N - 1, 1, 3)); // 2
  printf("RMQ(3, 4) = %d\n", st_query(RANGE_MIN, A, 1, 0, MAX_N - 1, 3, 4)); // 4
  printf("RMQ(0, 0) = %d\n", st_query(RANGE_MIN, A, 1, 0, MAX_N - 1, 0, 0)); // 0
  // these two values change
  printf("RMQ(0, 6) = %d\n", st_query(RANGE_MIN, A, 1, 0, MAX_N - 1, 0, 6)); // 5->2
  printf("RMQ(4, 6) = %d\n", st_query(RANGE_MIN, A, 1, 0, MAX_N - 1, 4, 6)); // 5->4

  return 0;
}
