import java.util.*;

public class ch4_01_dfs {
  private static final int DFS_WHITE = -1; // normal DFS
  private static final int DFS_BLACK = 1;
  private static final int DFS_GRAY = 2;
  private static Vector < Vector < pair < Integer, Integer > > > AdjList = 
    new Vector < Vector < pair < Integer, Integer > > >();
  private static Vector < Integer > dfs_num, dfs_low, dfs_parent;
  private static Vector < Boolean > articulation_vertex;
  private static Stack < Integer > dfs_scc; // additional information for SCC
  private static Vector < Integer > topologicalSort; // additional information for toposort
  private static int numComp, dfsNumberCounter, dfsRoot, rootChildren;

  private static void initDFS(int V) { // used in normal DFS
    dfs_num = new Vector < Integer > ();
    dfs_num.addAll(Collections.nCopies(V, DFS_WHITE));
    numComp = 0;
  }

  private static void initGraphCheck(int V) {
    initDFS(V);
    dfs_parent = new Vector < Integer > ();
    dfs_parent.addAll(Collections.nCopies(V, 0));
  }

  private static void initArticulationPointBridge(int V) {
    initGraphCheck(V);
    dfs_low = new Vector < Integer > ();
    dfs_low.addAll(Collections.nCopies(V, 0));
    articulation_vertex = new Vector < Boolean > ();
    articulation_vertex.addAll(Collections.nCopies(V, false));
    dfsNumberCounter = 0;
  }

  private static void initTarjanSCC(int V) {
    initGraphCheck(V);
    dfs_low = new Vector < Integer > ();
    dfs_low.addAll(Collections.nCopies(V, 0));
    dfsNumberCounter = 0;
    numComp = 0;
    dfs_scc = new Stack < Integer > ();
  }

  private static void initTopologicalSort(int V) {
    initDFS(V);
    topologicalSort = new Vector < Integer > ();
  }

  private static void dfs(int u) { // DFS for normal usage
    System.out.printf(" %d", u); // this vertex is visited
    dfs_num.set(u, DFS_BLACK); // mark as visited
    Iterator it = AdjList.get(u).iterator();
    while (it.hasNext()) { // try all neighbors v of vertex u
      pair < Integer, Integer > v = (pair < Integer, Integer > )it.next();
      if (dfs_num.get(v.first()) == DFS_WHITE) // avoid cycle
        dfs(v.first()); // v is a (neighbor, weight) pair
    }
  }

  private static void floodfill(int u, int color) {
    dfs_num.set(u, color); // not just a generic DFS_BLACK
    Iterator it = AdjList.get(u).iterator();
    while (it.hasNext()) { // try all neighbors v of vertex u
      pair < Integer, Integer > v = (pair < Integer, Integer > )it.next();
      if (dfs_num.get(v.first()) == DFS_WHITE) // avoid cycle
        floodfill(v.first(), color); // v is a (edge, weight) pair
    }
  }

  private static void graphCheck(int u) { // DFS for checking graph edge properties...
    dfs_num.set(u, DFS_GRAY); // color this as DFS_GRAY (temporary)
    Iterator it = AdjList.get(u).iterator();
    while (it.hasNext()) { // traverse this AdjList
      pair < Integer, Integer > v = (pair < Integer, Integer > )it.next();
      if (dfs_num.get(v.first()) == DFS_WHITE) { // DFS_GRAY to DFS_WHITE
        // System.out.printf("  Tree Edge (%d, %d)\n", u, v.first());
        dfs_parent.set(v.first(), u); // parent of this children is me
        graphCheck(v.first());
      }
      else if (dfs_num.get(v.first()) == DFS_GRAY) { // DFS_GRAY to DFS_GRAY
        if (v.first() == dfs_parent.get(u))
          System.out.printf(" Bidirectional Edge (%d, %d) - (%d, %d)\n", u, v.first(), v.first(), u);
        else
          System.out.printf(" Back Edge (%d, %d) (Cycle)\n", u, v.first());
      }
      else if (dfs_num.get(v.first()) == DFS_BLACK) // DFS_GRAY to DFS_BLACK
        System.out.printf(" Forward/Cross Edge (%d, %d)\n", u, v.first());
    }
    dfs_num.set(u, DFS_BLACK); // now color this as DFS_BLACK (DONE)
  }

  private static void articulationPointAndBridge(int u) {
    dfs_low.set(u, dfsNumberCounter);
    dfs_num.set(u, dfsNumberCounter++); // dfs_low[u] <= dfs_num[u]
    Iterator it = AdjList.get(u).iterator();
    while (it.hasNext()) { // try all neighbors v of vertex u
      pair < Integer, Integer > v = (pair < Integer, Integer > )it.next();
      if (dfs_num.get(v.first()) == DFS_WHITE) { // a tree edge
        dfs_parent.set(v.first(), u); // parent of this children is me
        if (u == dfsRoot) // special case
          rootChildren++; // count children of root
        articulationPointAndBridge(v.first());
        if (dfs_low.get(v.first()) >= dfs_num.get(u)) // for articulation point
          articulation_vertex.set(u, true); // store this information first
        if (dfs_low.get(v.first()) > dfs_num.get(u)) // for bridge
          System.out.printf(" Edge (%d, %d) is a bridge\n", u, v.first());
        dfs_low.set(u, Math.min(dfs_low.get(u), dfs_low.get(v.first()))); // update dfs_low[u]
      }
      else if (v.first() != dfs_parent.get(u)) // a back edge and not direct cycle
        dfs_low.set(u, Math.min(dfs_low.get(u), dfs_num.get(v.first()))); // update dfs_low[u]
    }
  }

  private static void tarjanSCC(int u) {
    dfs_low.set(u, dfsNumberCounter);
    dfs_num.set(u, dfsNumberCounter++); // dfs_low[u] <= dfs_num[u]
    dfs_scc.push(u); // store u according to order of visitation

    Iterator it = AdjList.get(u).iterator();
    while (it.hasNext()) { // try all neighbors v of vertex u
      pair < Integer, Integer > v = (pair < Integer, Integer > )it.next();
      if (dfs_num.get(v.first()) == DFS_WHITE) { // a tree edge
        dfs_parent.set(v.first(), u); // parent of this children is me
        tarjanSCC(v.first());
      }
      dfs_low.set(u, Math.min(dfs_low.get(u), dfs_low.get(v.first()))); // update dfs_low[u]
    }

    if (dfs_low.get(u) == dfs_num.get(u)) { // if this is a root of SCC
      System.out.printf("SCC %d: ", ++numComp);
      while (!dfs_scc.isEmpty() && dfs_scc.peek() != u) {
        System.out.printf("%d ", dfs_scc.peek()); dfs_scc.pop();
      }
      System.out.printf("%d\n", dfs_scc.peek()); dfs_scc.pop();
    }
  }

  private static void topoVisit(int u) {
    dfs_num.set(u, DFS_BLACK);
    Iterator it = AdjList.get(u).iterator();
    while (it.hasNext()) {
      pair < Integer, Integer > v = (pair < Integer, Integer > )it.next();
      if (dfs_num.get(v.first()) == DFS_WHITE)
        topoVisit(v.first());
    }
    topologicalSort.add(u);
  }

  private static void printThis(String message) {
    System.out.printf("==================================\n");
    System.out.printf("%s\n", message);
    System.out.printf("==================================\n");
  }

  public static void main(String[] args) {
    int i, j, V, total_neighbors, id, weight;

    /*
    // Use the following input:
    // Graph in Figure 4.1/4.2
    9
    1 1 0
    3 0 0 2 0 4 0
    2 1 0 3 0
    3 1 0 2 0 4 0
    1 3 0
    0
    2 7 0 8 0
    1 6 0
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

    // Example of directed acyclic graph in Figure 4.7 (for toposort)
    8
    2 1 0 2 0
    2 2 0 3 0
    2 3 0 5 0
    1 4 0
    0
    0
    0
    1 6 0
    */

    Scanner sc = new Scanner(System.in);
    AdjList.clear();
    V = sc.nextInt();
    for (i = 0; i < V; i++) {
      Vector < pair < Integer, Integer > > Neighbor = // create vector of pair<int, int> 
        new Vector < pair < Integer, Integer > >();
      AdjList.add(Neighbor); // store blank vector first
    }

    for (i = 0; i < V; i++) {
      total_neighbors = sc.nextInt();
      for (j = 0; j < total_neighbors; j++) {
        id = sc.nextInt();
        weight = sc.nextInt();
        AdjList.get(i).add(new pair< Integer, Integer >(id, weight));
      }
    }

    initDFS(V); // call this first before running DFS
    printThis("Standard DFS Demo");
    for (i = 0; i < V; i++) // for each vertex i in [0..V-1]
      if (dfs_num.get(i) == DFS_WHITE) { // if not visited yet
        System.out.printf("Component %d, visit:", ++numComp);
        dfs(i);
        System.out.printf("\n");
      }
    System.out.printf("There are %d connected components\n", numComp);

    initDFS(V); // call this first before running DFS
    printThis("Flood Fill Demo");
    for (i = 0; i < V; i++) // for each vertex i in [0..V-1], note that we use our REP macro again
      if (dfs_num.get(i) == DFS_WHITE) // if not visited yet
        floodfill(i, ++numComp);
    for (i = 0; i < V; i++)
      System.out.printf("Vertex %d has color %d\n", i, dfs_num.get(i));

    initGraphCheck(V);
    printThis("Graph Edges Property Check");
    for (i = 0; i < V; i++)
      if (dfs_num.get(i) == DFS_WHITE) {
        System.out.printf("Component %d:\n", ++numComp);
        graphCheck(i);
      }

    initArticulationPointBridge(V);
    printThis("Articulation Points & Bridges");
    System.out.printf("Bridges:\n");
    for (i = 0; i < V; i++)
      if (dfs_num.get(i) == DFS_WHITE) {
        dfsRoot = i; rootChildren = 0;
        articulationPointAndBridge(i);
        articulation_vertex.set(dfsRoot, (rootChildren > 1)); // special case
      }

    System.out.printf("Articulation Points:\n");
    for (i = 0; i < V; i++)
      if (articulation_vertex.get(i))
        System.out.printf(" Vertex %d\n", i);

    initTarjanSCC(V);
    printThis("Strongly Connected Components");
    for (i = 0; i < V; i++)
      if (dfs_num.get(i) == DFS_WHITE)
        tarjanSCC(i);

    // make sure that the given graph is DAG
    initTopologicalSort(V);
    printThis("Topological Sort");
    for (i = 0; i < V; i++)
      if (dfs_num.get(i) == DFS_WHITE)
        topoVisit(i);
    for (i = topologicalSort.size() - 1; i >= 0; i--) // access from back to front
      System.out.printf(" %d", topologicalSort.get(i));
    System.out.printf("\n");
  }
}
