#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char S[100001];
int SA[100001], n;

int SA_cmp(const void *a, const void *b) {
  return strcmp(S + *(int*)a, S + *(int*)b); // compare suffices
}

int main() { // first approach: O(n^2 log n), only for n <= 1000
  n = strlen(gets(S));
  for (int i = 0; i < n; i++) SA[i] = i; // sort       * comparison
  qsort(SA, n, sizeof(int), SA_cmp);     // O(n log n) * O(n) = O(n^2 log n)
  for (int i = 0; i < n; i++) printf("%d %s\n", SA[i], S+SA[i]);
} // return 0;
