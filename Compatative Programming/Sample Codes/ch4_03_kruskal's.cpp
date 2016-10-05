#include "competitive.h"

int main() {
  int V, E, a, b, weight;

  /*
  // Graph in Figure 4.9 left/4.10, format: list of weighted edges
  // This example shows another form of reading graph input
  5 7
  1 2 5
  1 3 5
  1 4 5
  1 5 5
  2 3 2
  3 4 8
  4 5 8
  */

  scanf("%d %d", &V, &E);

  // another graph data structure: EdgeList
  priority_queue< pair<int, ii> > EdgeList; // sort by edge weight O(E log E)
  // PQ default: sort descending. Trick: use <(negative) weight(i, j), <i, j> >
  REP (i, 0, E - 1) {
    scanf("%d %d %d", &a, &b, &weight);
    EdgeList.push(make_pair(-weight, make_pair(--a, --b)));
  }

  int mst_cost = 0; initSet(V); // all V are disjoint sets at the beginning
  while (!EdgeList.empty()) { // while there exist more edges, O(E)
    pair<int, ii> front = EdgeList.top(); EdgeList.pop();
    if (!isSameSet(front.second.first, front.second.second)) { // if no cycle
      mst_cost += (-front.first); // add (negated) -weight of e to MST
      unionSet(front.second.first, front.second.second); // link these two vertices
    }
  }
  printf("MST cost %d\n", mst_cost);

  return 0;
}
