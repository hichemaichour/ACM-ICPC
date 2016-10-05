#include "competitive.h"

map<int, int> p; // predecessor map to reconstruct path
int f, s, t; // global variables

void augmentPath(int v, int minEdge) {
  if (v == s) { // managed to get back to source
    f = minEdge; // minEdge of the path
    return;
  }
  else if (p.count(v)) { // augment if there is a path
    // we need AdjMat for fast lookup here
    augmentPath(p[v], min(minEdge, AdjMat[p[v]][v]));
    AdjMat[p[v]][v] -= f; // forward edges -> decrease
    AdjMat[v][p[v]] += f; // backward edges -> increase
  } 
} // for more details why we must do that, consult refs!

int main() {
  freopen("a.txt", "r", stdin);
  int V, k, vertex, weight;

  /*
  // Graph in Figure 1.20
  4 1 2
  2 3 70 4 30
  2 3 25 4 70
  3 1 70 4 5 2 25
  3 1 30 3 5 2 70

  5 1 5
  2 2 100 3 50
  3 3 50 4 50 5 50
  1 4 100
  1 5 125
  0

  */

  scanf("%d %d %d", &V, &s, &t);
  s--; t--;

  memset(AdjMat, 0, sizeof AdjMat);
  AdjList.clear();
  REP (i, 0, V - 1) {
    vii Neighbor;
    AdjList.PB(Neighbor);
  }

  REP (i, 0, V - 1) {
    scanf("%d", &k);
    REP (j, 0, k - 1) {
      scanf("%d %d", &vertex, &weight);
      vertex--;
      AdjMat[i][vertex] = weight;
      AdjList[i].PB(MP(vertex, 0)); // we do not store the weight
    }
  }

  // Edmonds Karp's Algorithm
  int max_flow = 0;
  while (1) { // this will be run max O(VE) times
    f = 0;

    // O(E) BFS and record the path p
    queue<int> q; map<int, int> dist;
    q.push(s); dist[s] = 0; // start from source

    while (!q.empty()) {
      int u = q.front(); q.pop(); // queue: layer by layer!
      if (u == t) break; // modif 1: reach sink t, quickly terminate BFS
      TRvii (AdjList[u], v) // for each neighbours of u
        // modif 2: also check AdjMat as edges may disappear
        if (AdjMat[u][v->first] > 0 && !dist.count(v->first)) {
          dist[v->first] = dist[u] + 1; // then v is reachable from u
          q.push(v->first); // enqueue v for next steps
          p[v->first] = u; // modif 3: predecessor of v->first is u
        }
    }

    augmentPath(t, INF); // path augmentation in O(V)
    if (f == 0) break; // seems that we cannot pass any more flow
    max_flow += f;
  }
  printf("Max flow = %d\n", max_flow);

  return 0;
}
