#include "competitive.h"

int main() {
  int V, E, a, b, weight;

  /*
  // Graph in Figure 4.17, no negative cycle
  5 5
  0 1 1
  0 2 10
  1 3 2
  2 3 -10
  3 4 3

  // Graph in Figure 4.18, negative cycle exists
  3 3
  0 1 1000
  1 2 15
  2 1 -42
  */

  AdjList.clear();
  scanf("%d %d", &V, &E);
  AdjList.assign(V, vii()); // assign blank vectors of pair<int, int>s to AdjList

  REP (i, 0, E - 1) {
    scanf("%d %d %d", &a, &b, &weight);
    AdjList[a].push_back(ii(b, weight));
  }

  // as an example, we start from this source (see Figure 1.15)
  int s = 0;

  // Bellman Ford routine
  vector<int> dist(V, INF); dist[s] = 0; // INF = 2^31-1
  REP (i, 0, V - 2) // relax all E edges V-1 times, O(V)
    REP (u, 0, V - 1) // these two loops = O(E)
      TRvii (AdjList[u], v) // relax these edges
        dist[v->first] = min(dist[v->first], dist[u] + v->second);

  bool negative_cycle_exist = false;
  REP (u, 0, V - 1) // one more pass to check
    TRvii (AdjList[u], v)
      if (dist[v->first] > dist[u] + v->second) // should be false, but if possible
        negative_cycle_exist = true;            // then negative cycle exists!
  printf("Negative Cycle Exist? %s\n", negative_cycle_exist ? "Yes" : "No");

  if (!negative_cycle_exist)
    REP (i, 0, V - 1)
      printf("SSSP(%d, %d) = %d\n", s, i, dist[i]);

  return 0;
}
