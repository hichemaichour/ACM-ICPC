#include "competitive.h" // study this header file!

typedef struct {
  int id;
  int solved;
  int penalty;
} team;

bool icpc_cmp(team a, team b) {
  if (a.solved != b.solved) // can use this primary field to decide sorted order
    return a.solved > b.solved; // ICPC rule: sort by number of problem solved
  else if (a.penalty != b.penalty) // a.solved == b.solved, but we can use
                                   // secondary field to decide sorted order
    return a.penalty < b.penalty; // ICPC rule: sort by descending penalty
  else // a.solved == b.solved AND a.penalty == b.penalty
    return a.id < b.id; // sort based on increasing team ID
}

int main() {
  int *pos, arr[] = {10, 7, 2, 15, 4};
  vector<int> v(arr, arr + 5); // another way to initialize vector
  vector<int>::iterator j;

  // sort descending with vector
  sort(v.rbegin(), v.rend()); // use 'reverse iterator'
  TRvi (v, it) // iterator example, with shortcuts
    printf("%d ", *it); // access value of iterator
  printf("\n");
  printf("==================\n");

  random_shuffle(v.begin(), v.end()); // shuffle content again
  TRvi (v, it)
    printf("%d ", *it);
  printf("\n");
  printf("==================\n");
  partial_sort(v.begin(), v.begin() + 2, v.end()); // partial_sort demo
  TRvi (v, it)
    printf("%d ", *it);
  printf("\n");
  printf("==================\n");

  // sort ascending
  sort(arr, arr + 5); // arr should be sorted now
  REP (i, 0, 4) // 2, 4, 7, 10, 15
    printf("%d ", arr[i]);
  printf("\n");
  sort(v.begin(), v.end()); // sorting a vector, same output
  TRvi (v, it)
    printf("%d ", *it);
  printf("\n");
  printf("==================\n");

  // multi-field sorting example
  // suppose we have 4 ICPC teams
  team nus[4] = { {1, 1, 10}, 
                  {2, 3, 60},
                  {3, 1, 20},
                  {4, 3, 60} };

  // without sorting, they will be ranked like this:
  REP (i, 0, 3)
    printf("id: %d, solved:%d, penalty: %d\n",
           nus[i].id, nus[i].solved, nus[i].penalty);

  sort(nus, nus + 4, icpc_cmp);
  printf("==================\n");
  // after sorting using ICPC rule, they will be ranked like this:
  REP (i, 0, 3)
    printf("id: %d, solved:%d, penalty: %d\n",
           nus[i].id, nus[i].solved, nus[i].penalty);
  printf("==================\n");

  // binary search using lower bound
  pos = lower_bound(arr, arr + 5, 7); // found
  printf("%d\n", *pos);
  j = lower_bound(v.begin(), v.end(), 7);
  printf("%d\n", *j);

  pos = lower_bound(arr, arr + 5, 77); // not found
  if (pos - arr == 5) // arr is of size 5 -> 
                      //    arr[0], arr[1], arr[2], arr[3], arr[4]
                      // if lower_bound cannot find the required value,
                      //   it will set return arr index +1 of arr size, i.e.
                      //   the 'non existent' arr[5]
                      // thus, testing whether pos - arr == 5 blocks 
                      //   can detect this "not found" issue
    printf("77 not found\n");
  j = lower_bound(v.begin(), v.end(), 77);
  if (j == v.end()) // with vector, lower_bound will do the same:
                    //   return vector index +1 of vector size
                    // but this is exactly the position of vector.end()
                    //   so we can test "not found" this way
    printf("77 not found\n");
  printf("==================\n");

  // useful if you want to generate permutations of set
  next_permutation(arr, arr + 5); // 2, 4, 7, 10, 15 -> 2, 4, 7, 15, 10
  next_permutation(arr, arr + 5); // 2, 4, 7, 15, 10 -> 2, 4, 10, 7, 15
  REP (i, 0, 4)
    printf("%d ", arr[i]);
  printf("\n");

  next_permutation(v.begin(), v.end());
  next_permutation(v.begin(), v.end());
  TRvi (v, it)
    printf("%d ", *it);
  printf("\n");
  printf("==================\n");

  // sometimes these two useful simple macros are used
  printf("min(10, 7) = %d\n", min(10, 7));
  printf("max(10, 7) = %d\n", max(10, 7));

  return 0;
}