#include "competitive.h"

void dfs(int u) { // DFS for normal usage
  printf(" %d", u); // this vertex is touched
  dfs_num[u] = DFS_BLACK; // mark as visited
  TRvii (AdjList[u], v) // try all neighbors v of vertex u
    if (dfs_num[v->first] == DFS_WHITE) // avoid cycle
      dfs(v->first); // v is an (edge, weight) pair
}

void floodfill(int u, int color) {
  dfs_num[u] = color; // not just a generic DFS_BLACK
  TRvii (AdjList[u], v) // try all neighbors v of vertex u
    if (dfs_num[v->first] == DFS_WHITE) // avoid cycle
      floodfill(v->first, color); // v is an (edge, weight) pair
}

void graphCheck(int u) { // DFS for checking graph edge properties...
  dfs_num[u] = DFS_GRAY; // color this as grey (temporary)
  TRvii (AdjList[u], v) { // traverse this AdjList
    if (dfs_num[v->first] == DFS_WHITE) { // GRAY to WHITE
      // printf("  Tree Edge (%d, %d)\n", u, v->first);
      dfs_parent[v->first] = u; // parent of this children is me
      graphCheck(v->first);
    }
    else if (dfs_num[v->first] == DFS_GRAY) { // GRAY to GRAY
      if (v->first == dfs_parent[u])
        printf(" Bidirectional (%d, %d) - (%d, %d)\n", u, v->first, v->first, u);
      else
        printf(" Back Edge (%d, %d) (Cycle)\n", u, v->first);
    }
    else if (dfs_num[v->first] == DFS_BLACK) // GRAY to BLACK
      printf(" Forward/Cross Edge (%d, %d)\n", u, v->first);
  }
  dfs_num[u] = DFS_BLACK; // now color this as black (DONE)
}

void articulationPointAndBridge(int u) {
  dfs_low[u] = dfs_num[u] = dfsNumberCounter++; // dfs_low[u] <= dfs_num[u]
  TRvii (AdjList[u], v)
    if (dfs_num[v->first] == DFS_WHITE) { // a tree edge
      dfs_parent[v->first] = u; // parent of this children is me
      if (u == dfsRoot) // special case
        rootChildren++; // count children of root
      articulationPointAndBridge(v->first);
      if (dfs_low[v->first] >= dfs_num[u]) // for articulation point
        articulation_vertex[u] = true; // store this information first
      if (dfs_low[v->first] > dfs_num[u]) // for bridge
        printf(" Edge (%d, %d) is a bridge\n", u, v->first);
      dfs_low[u] = min(dfs_low[u], dfs_low[v->first]); // update dfs_low[u]
    }
    else if (v->first != dfs_parent[u]) // a back edge and not direct cycle
      dfs_low[u] = min(dfs_low[u], dfs_num[v->first]); // update dfs_low[u]
}

void tarjanSCC(int u) {
  dfs_low[u] = dfs_num[u] = dfsNumberCounter++; // dfs_low[u] <= dfs_num[u]
  dfs_scc.push(u); // store u according to order of visitation
  TRvii (AdjList[u], v) {
    if (dfs_num[v->first] == DFS_WHITE) { // a tree edge
      dfs_parent[v->first] = u; // parent of this children is me
      tarjanSCC(v->first);
    }
    dfs_low[u] = min(dfs_low[u], dfs_low[v->first]); // update dfs_low[u]
  }

  if (dfs_low[u] == dfs_num[u]) { // if this is a root of SCC
    printf("SCC: ");
    while (!dfs_scc.empty() && dfs_scc.top() != u) {
      printf("%d ", dfs_scc.top()); dfs_scc.pop();
    }
    printf("%d\n", dfs_scc.top()); dfs_scc.pop();
  }
}

void topoVisit(int u) {
  dfs_num[u] = DFS_BLACK;
  TRvii (AdjList[u], it)
    if (dfs_num[it->first] == DFS_WHITE)
      topoVisit(it->first);
  topologicalSort.push_back(u);
}

void printThis(char* message) {
  printf("==================================\n");
  printf("%s\n", message);
  printf("==================================\n");
}

int main() {
  int V, total_neighbors, id, weight;

  /*
  // Use the following input:
  // Graph in Figure 4.1/4.2
  8
  1 1 0
  3 0 0 2 0 4 0
  2 1 0 3 0
  3 1 0 2 0 4 0
  1 3 0
  0
  1 7 0
  1 6 0

  // Left graph in Figure 4.3/4.4/4.5
  6
  1 1 0
  3 0 0 2 0 4 0
  1 1 0
  1 4 0
  3 1 0 3 0 5 0
  1 4 0

  // Right graph in Figure 4.3/4.4/4.5
  6
  1 1 0
  5 0 0 2 0 3 0 4 0 5 0
  1 1 0
  1 1 0
  2 1 0 5 0
  2 1 0 4 0

  // Directed graph in Figure 4.6
  8
  1 1 0
  1 3 0
  1 1 0
  2 2 0 4 0
  1 5 0
  1 7 0
  1 4 0
  1 6 0

  // Example of directed graph with back edges
  3
  1 1 0
  2 0 0 2 0
  1 1 0

  // Example of directed acyclic graph (for toposort)
  4
  2 1 0 2 0
  2 2 0 3 0
  1 3 0
  0
  */

  scanf("%d", &V);
  REP (i, 0, V - 1) {
    vii Neighbor; // create vector of pair<int, int>
    AdjList.PB(Neighbor); // store blank vector first
  }

  REP (i, 0, V - 1) {
    scanf("%d", &total_neighbors);
    REPN (j, total_neighbors) {
      scanf("%d %d", &id, &weight);
      AdjList[i].PB(MP(id, weight)); // some index adjustment
    }
  }

  initDFS(V); // call this first before running DFS
  printThis("Standard DFS Demo");
  REP (i, 0, V - 1) // for each vertex u in [0..V-1]
    if (dfs_num[i] == DFS_WHITE) { // if not touched
      printf("Component %d, visit:", ++numComponent);
      dfs(i);
      printf("\n");
    }
  printf("There are %d connected components\n", numComponent);

  initDFS(V); // call this first before running DFS
  printThis("Flood Fill Demo");
  REP (i, 0, V - 1) // for each vertex u in [0..V-1]
    if (dfs_num[i] == DFS_WHITE) // if not touched
      floodfill(i, ++numComponent);
  REP (i, 0, V - 1)
    printf("Vertex %d has color %d\n", i, dfs_num[i]);

  initGraphCheck(V);
  printThis("Graph Edges Property Check");
  REP (i, 0, V - 1)
    if (dfs_num[i] == DFS_WHITE) {
      printf("Component %d:\n", ++numComponent);
      graphCheck(i);
    }

  initArticulationPointBridge(V);
  printThis("Articulation Points & Bridges");
  printf("Bridges:\n");
  REP (i, 0, V - 1)
    if (dfs_num[i] == DFS_WHITE) {
      dfsRoot = i;
      rootChildren = 0;
      articulationPointAndBridge(i);
      articulation_vertex[dfsRoot] = (rootChildren > 1); // special case
    }
  printf("Articulation Points:\n");
  REP (i, 0, V - 1)
    if (articulation_vertex[i])
      printf(" Vertex %d\n", i);

  initTarjanSCC(V);
  printThis("Strongly Connected Components");
  REP (i, 0, V - 1)
    if (dfs_num[i] == DFS_WHITE)
      tarjanSCC(i);

  // make sure that the given graph is DAG
  initTopologicalSort(V);
  printThis("Topological Sort");
  REP (i, 0, V - 1)
    if (dfs_num[i] == DFS_WHITE)
      topoVisit(i);

  reverse(topologicalSort.begin(), topologicalSort.end());
  REP (i, 0, topologicalSort.size() - 1)
    printf(" %d", topologicalSort[i]);
  printf("\n");

  return 0;
}
