#include "competitive.h" // study this header file!

int main() {
  int arr[5] = {7,7,7}; // initial size (5) and initial value {7,7,7,0,0}
  vector<int> v(5, 5);  // initial size (5) and initial value {5,5,5,5,5}

  printf("arr[2] = %d and v[2] = %d\n", arr[2], v[2]); // 7 and 5

  REP (i, 0, 4) { // see competitive.h for explanation of this macro 'REP'
    arr[i] = i;
    v[i] = i;
  }

  printf("arr[2] = %d and v[2] = %d\n", arr[2], v[2]); // 2 and 2

  // arr[5] = 5; // static array will generate index out of bound error
  v.PB(5); // but vector will resize itself, PB is shortcut for push_back
  printf("v[5] = %d\n", v[5]); // 5
  
  return 0;
}
