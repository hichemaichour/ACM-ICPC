#include "competitive.h"

int main() {
  freopen("graphexample.txt", "r", stdin);
  int V, E, a, b, weight;

  /*
  // Graph in Figure 1.14, yet another format of graph input
  5 7
  2 1 2
  2 3 7
  2 5 6
  1 3 3
  1 4 6
  3 4 5
  5 4 1
  */

  AdjList.clear();
  scanf("%d %d", &V, &E);
  REP (i, 0, V - 1) {
    vii Neighbor; // create vector of pair<int, int>
    AdjList.PB(Neighbor); // store blank vector first
  }

  REP (i, 0, E - 1) {
    scanf("%d %d %d", &a, &b, &weight);
    a--; b--; // decrease index by 1
    AdjList[a].PB(MP(b, weight)); // first time using weight
  }

  // as an example, we start from this source
  // see Figure 1.14
  int s = 2-1; // index 2 is decreased by 1

  // Dijkstra routine
  vector<int> dist(V, INF); dist[s] = 0; // INF = 2^31-1
  priority_queue<ii, vector<ii>, greater<ii> > pq;
  pq.push(ii(0, s)); // sort based on increasing distance
  while (!pq.empty()) { // main loop
    ii top = pq.top(); pq.pop(); // greedy: pick shortest unvisited vertex
    int d = top.first, u = top.second;
    if (d <= dist[u]) {
      // The check d <= dist[u] is important! We want to process vertex u only once
      // but we can actually enqueue u several times in priority_queue...
      // Fortunately, other occurrences of u on priority_queue will have
      // greater distance and can be ignored :)
      TRvii (AdjList[u], it) { // all outgoing edges from v
        int v = it->first, weight_u_v = it->second;
        if (dist[u] + weight_u_v < dist[v]) {
          dist[v] = dist[u] + weight_u_v; // relax
          pq.push(ii(dist[v], v)); // enqueue this neighbor
        }                          // regardless it is already in pq or not
      }
    }
  }

  REP (i, 0, V - 1) // index + 1 for final answer
    printf("SSSP(%d, %d) = %d\n", s + 1, i + 1, dist[i]);

  return 0;
}
