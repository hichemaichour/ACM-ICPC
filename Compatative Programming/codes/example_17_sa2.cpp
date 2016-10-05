#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <algorithm>
using namespace std;

#define MAXN 200010
int RA[MAXN], SA[MAXN], LCP[MAXN], *FC, *SC, step;
char S[MAXN], Q[MAXN];

bool cmp(int a, int b) {
  if (step==-1 || FC[a]!=FC[b]) return FC[a] < FC[b];
  return FC[a+(1<<step)] < FC[b+(1<<step)];
}

void suffix_array(char *S, int n) { // O(n log^2(n))
  for (int i=0; i<n; i++) RA[i] = S[SA[i] = i];
  for (FC=RA, SC=LCP, step=-1; (1<<step)<n; step++){
    sort(SA, SA+n, cmp);
    int cnt = 0;
    for (int i=0; i<n; i++){
      if (i>0 && cmp(SA[i-1],SA[i])) cnt++;
      SC[SA[i]] = cnt; 
    }
    if (cnt==n-1) break; // all distinct, no need to continue
    swap(FC,SC);
  }
  for (int i=0; i<n; i++) RA[SA[i]] = i;
}

pair<int, int> range(int n, char *Q) {
  int lo = 1, hi = n, m = strlen(Q), mid = lo; // index 0 - null, valid range = [1..n]
  while (lo <= hi) {
    mid = (lo + hi) / 2;
    int cmp = strncmp(S + SA[mid], Q, m);
    if (cmp == 0) // found
      break;
    else if (cmp > 0)
      hi = mid - 1;
    else
      lo = mid + 1;
  }
  if (lo > hi)
    return make_pair(-1, -1); // not found
  for (lo = mid; lo >= 1 && strncmp(S + SA[lo], Q, m) == 0; lo--);
  lo++;
  for (hi = mid; hi <= n && strncmp(S + SA[hi], Q, m) == 0; hi++);
  hi--;
  return make_pair(lo, hi);
}

int main(){
  int n = strlen(gets(S));
  suffix_array(S, n + 1); // NULL is included!
  for (int i = 1; i <= n; i++) // SA[0] is the NULL
    printf("%d %s\n", SA[i], S + SA[i]);

  gets(Q);
  pair<int, int> pos = range(n, Q);
  if (pos.first != -1 && pos.second != -1) {
    printf("%s is found in index [%d .. %d] in SA of %s\n", Q, pos.first, pos.second, S);
    printf("They are:\n");
    for (int i = pos.first; i <= pos.second; i++)
      printf("  %s\n", S + SA[i]);
  }
  else
    printf("%s is not found in %s\n", Q, S);
} // return 0;
