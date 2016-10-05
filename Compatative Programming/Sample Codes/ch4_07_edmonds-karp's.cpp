#include "competitive.h"

#define MAX_V 10 // enough for sample graph in Figure 4.22/4.23

// we need these global variables
int res[MAX_V][MAX_V], max_flow, f, s, t; // define MAX_V appropriately
vi p; // note that vi is our shortcut for vector<int>

void augment(int v, int minEdge) { // traverse the BFS spanning tree as in print_path (section 4.3)
  if (v == s) { f = minEdge; return; } // reach the source, record minEdge in a global variable `f'
  else if (p[v] != -1) { augment(p[v], min(minEdge, res[p[v]][v])); // recursive call
                         res[p[v]][v] -= f; res[v][p[v]] += f; } // alter residual capacities
}

int main() {
  int V, k, vertex, weight;

  /*
  // Graph in Figure 4.22
  4 1 2
  2 3 70 4 30
  2 3 25 4 70
  3 1 70 4 5 2 25
  3 1 30 3 5 2 70

  // Graph in Figure 4.23
  4 1 4
  2 2 100 4 100
  2 3 1 4 100
  1 4 100
  0
  */

  scanf("%d %d %d", &V, &s, &t);
  s--; t--;

  memset(res, 0, sizeof res);
  REP (i, 0, V - 1) {
    scanf("%d", &k);
    REP (j, 0, k - 1) {
      scanf("%d %d", &vertex, &weight); vertex--;
      res[i][vertex] = weight;
    }
  }

  max_flow = 0;
  while (1) { // run O(VE^2) Edmonds Karp to solve the Max Flow problem
    f = 0;

    // run BFS, please examine parts of the BFS code that is different than in Section 4.3
    queue<int> q; vi dist(MAX_V, INF); // #define INF 2000000000
    q.push(s); dist[s] = 0;
    p.assign(MAX_V, -1); // (we have to record the BFS spanning tree)
    while (!q.empty()) { // (we need the shortest path from s to t!)
      int u = q.front(); q.pop();
      if (u == t) break; // immediately stop BFS if we already reach sink t
      for (int v = 0; v < MAX_V; v++) // note: enumerating neighbors with AdjMatrix is `slow'
        if (res[u][v] > 0 && dist[v] == INF) { // res[u][v] can change!
          dist[v] = dist[u] + 1;
          q.push(v);
          p[v] = u; // parent of vertex v is vertex u
    }   }

    augment(t, INF); // find the min edge weight `f' along this path, if any
    if (f == 0) break; // if we cannot send any more flow (`f' = 0), terminate the loop
    max_flow += f; // we can still send a flow, increase the max flow!
  }

  printf("%d\n", max_flow); // this is the max flow value of this flow graph

  return 0;
}
