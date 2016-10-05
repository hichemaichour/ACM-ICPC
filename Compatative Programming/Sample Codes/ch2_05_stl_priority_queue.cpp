#include "competitive.h" // study this header file!

int main() {
  int money;
  char name[20];
  priority_queue< pair<int, string> > pq; // introducing 'pair'
  pair<int, string> result;

  // suppose we enter these 7 money-name pairs via keyboard
  /*
  100 john
  10 billy
  20 andy
  100 steven
  70 felix
  2000 grace
  70 martin
  */
  REPN (i, 7) {
    scanf("%d %s", &money, &name);
    pq.push(MP(money, name)); // inserting a pair in O(log n), MP is shortcut
    // priority queue will arrange items in 'heap' based
    // on the first key in pair, which is money (integer), largest first
    // if first keys tied, use second key, which is name, largest first
  }
  
  // the internal content of pq heap MAY be something like this:
  // re-read (max) heap concept if you do not understand this diagram
  // the primary keys are money (integer), secondary keys are names (string)!
  //                        (2000,grace)
  //           (100,steven)               (70,martin)   
  //     (100,john)   (10,billy)     (20,andy)  (70,felix)

  // let's print out the top 3 person with most money
  result = pq.top(); // O(1) to access the top / max element
  pq.pop(); // O(log n) to delete the top and repair the structure
  printf("%s has %d $\n", ((string)result.second).c_str(), result.first);
  result = pq.top(); pq.pop();
  printf("%s has %d $\n", ((string)result.second).c_str(), result.first);
  result = pq.top(); pq.pop();
  printf("%s has %d $\n", ((string)result.second).c_str(), result.first);

  return 0;
}