#include "competitive.h" // study this header file!

int main() {         //    idx   0 1 2 3 4 5 6 7 8
  vi ft = ft_create(9); // ft = {0,0,0,0,0,0,0,0,0}
  ft_adjust(ft, 2, 1);  // ft = {0,0,1,1,0,0,0,1,0}, index 2,3,7 are affected (all +1)
  ft_adjust(ft, 4, 1);  // ft = {0,0,1,1,1,1,0,2,0}, index 4,5,7 are affected (all +1)
  ft_adjust(ft, 5, 2);  // ft = {0,0,1,1,1,3,0,4,0}, index 5,7 are affected (all +2)
  ft_adjust(ft, 6, 3);  // ft = {0,0,1,1,1,3,3,7,0}, index 6,7 are affected (all +3)
  ft_adjust(ft, 7, 2);  // ft = {0,0,1,1,1,3,3,9,0}, only index 7 is affected (+2)
  ft_adjust(ft, 8, 1);  // ft = {0,0,1,1,1,3,3,9,1}, only index 8 is affected (+1)
  printf("%d\n", ft_rsq(ft, 0, 0)); // returns 0 , ft[0] (idx 0)
  printf("%d\n", ft_rsq(ft, 0, 2)); // returns 1 , ft[2] (idx 2) + ft[1] (idx 0-1)
  printf("%d\n", ft_rsq(ft, 0, 6)); // returns 7 , ft[6] (idx 6) + ft[5] (idx 4-5) + ft[3] (idx 0-3)
  printf("%d\n", ft_rsq(ft, 0, 8)); // returns 10, ft[8] (idx 8) + ft[7] (idx 0-7)
  printf("%d\n", ft_rsq(ft, 3, 6)); // returns 6 , rsq(ft, 0, 6) - rsq(ft, 0, 2) = 7 - 1 = 6.

  return 0;
}
