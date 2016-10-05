#include "competitive.h"

int main() {
  int V, E, a, b, counter;
  map<int, int> mapper, reverseMapper;

  /*
  // Graph in Figure 1.7, format: list of unweighted edges
  // This example shows another form of reading graph input
  13 16
  10 15   15 20   20 25   10 30   30 47   47 50   25 45   45 65
  15 35   35 55   20 40   50 55   35 40   55 60   40 60   60 65
  */

  scanf("%d %d", &V, &E);
  REP (i, 0, V - 1) {
    vii Neighbor; // create vector of pair<int, int>
    AdjList.PB(Neighbor); // store blank vector first
  }

  counter = 0;
  REP (i, 0, E - 1) {
    scanf("%d %d", &a, &b);
    if (mapper.find(a) == mapper.end()) { // mapping trick
      mapper[a] = counter++;
      reverseMapper[mapper[a]] = a;
    }
    if (mapper.find(b) == mapper.end()) {
      mapper[b] = counter++;
      reverseMapper[mapper[b]] = b;
    }
    AdjList[mapper[a]].PB(MP(mapper[b], 0));
    AdjList[mapper[b]].PB(MP(mapper[a], 0));
  }

  // as an example, we start from this source
  // see Figure 1.7
  int s = mapper[35];

  // BFS routine
  queue<int> q; map<int, int> dist;
  q.push(s); dist[s] = 0; // start from source

  while (!q.empty()) {
    int u = q.front(); q.pop(); // queue: layer by layer!
    printf("Visit %d, Layer %d\n", reverseMapper[u], dist[u]);
    TRvii (AdjList[u], v) // for each neighbours of u
      if (!dist.count(v->first)) { // if v not visited before
        dist[v->first] = dist[u] + 1; // then v is reachable from u
        q.push(v->first); // enqueue v for next steps
      }
  }

  return 0;
}
