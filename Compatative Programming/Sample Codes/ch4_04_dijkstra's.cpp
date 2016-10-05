#include "competitive.h"

int main() {
  int V, E, a, b, weight;

  /*
  // Graph in Figure 4.16
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
  AdjList.assign(V, vii()); // assign blank vectors of pair<int, int>s to AdjList

  REP (i, 0, E - 1) {
    scanf("%d %d %d", &a, &b, &weight); a--; b--; // decrease index by 1
    AdjList[a].push_back(ii(b, weight)); // first time using weight
  }

  // as an example, we start from this source (see Figure 4.16)
  int s = 2 - 1; // index 2 is decreased by 1

  // Dijkstra routine
  vector<int> dist(V, INF); dist[s] = 0; // INF = 2.10^9 not MAX_INT to avoid overflow
  priority_queue<ii, vector<ii>, greater<ii> > pq; pq.push(ii(0, s)); // sort based on increasing distance

  while (!pq.empty()) { // main loop
    ii top = pq.top(); pq.pop(); // greedy: pick shortest unvisited vertex
    int d = top.first, u = top.second;
    if (d == dist[u]) // This check is important! We want to process vertex u only once but we can
      // actually enqueue u several times in priority_queue... Fortunately, other occurrences of u
      // in priority_queue will have greater distances and can be ignored (the overhead is small) :)
      TRvii (AdjList[u], it) { // all outgoing edges from u
        int v = it->first, weight_u_v = it->second;
        if (dist[u] + weight_u_v < dist[v]) { // if can relax      (note: Record SP spanning tree)
          dist[v] = dist[u] + weight_u_v; // relax                 (here if needed. This is similar)
          pq.push(ii(dist[v], v)); // enqueue this neighbor        (as printpath in BFS)
  }   } }                          // regardless whether it is already in pq or not

  REP (i, 0, V - 1) // index + 1 for final answer
    printf("SSSP(%d, %d) = %d\n", s + 1, i + 1, dist[i]);

  return 0;
}
