#include "competitive.h"

int V, E, a, b, counter, s;
map<int, int> mapper, reverseMapper;
vector<int> p;

void printpath(int u) {
  if (u == s) { printf("%d", reverseMapper[u]); return; }
  printpath(p[u]);
  printf(" %d", reverseMapper[u]);
}

int main() {
  /*
  // Graph in Figure 4.8, format: list of unweighted edges
  // This example shows another form of reading graph input
  13 16
  10 15   15 20   20 25   10 30   30 47   47 50   25 45   45 65
  15 35   35 55   20 40   50 55   35 40   55 60   40 60   60 65
  */

  scanf("%d %d", &V, &E);
  AdjList.assign(V, vii()); // assign blank vectors of pair<int, int>s to AdjList

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
    AdjList[mapper[a]].push_back(ii(mapper[b], 0));
    AdjList[mapper[b]].push_back(ii(mapper[a], 0));
  }

  // as an example, we start from this source
  // see Figure 4.8
  s = mapper[35];

  // BFS routine
  // inside int main() -- we do not use recursion, thus we do not need to create separate function!
  int layer = -1; // for our output printing purpose
  p.assign(V, 0); // to store parent information (p must be a global variable!)
  queue<int> q; map<int, int> dist;
  q.push(s); dist[s] = 0; // start from source

  while (!q.empty()) {
    int u = q.front(); q.pop(); // queue: layer by layer!
    if (dist[u] != layer) printf("\nLayer %d:", dist[u]);
    layer = dist[u];
    printf(", visit %d", reverseMapper[u]); // reverseMapper maps index to actual vertex label
    TRvii (AdjList[u], v) // for each neighbours of u
      if (!dist.count(v->first)) { // if v not visited before
        dist[v->first] = dist[u] + 1; // then v is reachable from u
        q.push(v->first); // enqueue v for next steps
        p[v->first] = u; // parent of v is u
      }
  }

  printf("\nShortest path: ");
  printpath(mapper[30]);
  printf("\n");

  return 0;
}
