#include "competitive.h" // study this header file!

int main() {
  stack<char> s;
  queue<char> q;

  printf("%d\n", s.empty()); // currently s is empty, true (1)
  printf("==================\n");
  s.push('a');
  s.push('b');
  s.push('c');
  // stack is LIFO, thus the content of s is currently like this:
  // c <- top
  // b
  // a
  printf("%c\n", s.top()); // output 'c'
  s.pop(); // pop topmost
  printf("%c\n", s.top()); // output 'b'
  printf("%d\n", s.empty()); // currently s is not empty, false (0)
  printf("==================\n");

  printf("%d\n", q.empty()); // currently q is empty, true (1)
  printf("==================\n");
  while (!s.empty()) { // stack s still has 2 more items
    q.push(s.top()); // enqueue 'b', and then 'a'
    s.pop();
  }

  printf("%c\n", q.front()); // prints 'b'
  printf("%c\n", q.back()); // prints 'a'

  return 0;
}