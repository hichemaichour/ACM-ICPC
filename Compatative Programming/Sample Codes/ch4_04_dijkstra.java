import java.util.*;

public class ch4_04_dijkstra {
  public static final int INF = 2000000000;
  private static Vector< Vector< pair < Integer, Integer > > > AdjList =
             new Vector< Vector< pair < Integer, Integer > > >();
  
  public static void main(String[] args) {
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

    Scanner sc = new Scanner(System.in);
    V = sc.nextInt();
    E = sc.nextInt();

    AdjList.clear();
    for (int i = 0; i < V; i++) {
      Vector< pair < Integer, Integer > > Neighbor = 
        new Vector < pair < Integer, Integer > >();
      AdjList.add(Neighbor); // add neighbor list to Adjacency List
    }

    for (int i = 0; i < E; i++) {
      a = sc.nextInt(); a--; // decrease index by 1
      b = sc.nextInt(); b--;
      weight = sc.nextInt();
      AdjList.get(a).add(new pair < Integer, Integer > (b, weight)); // first time using weight
    }

    // as an example, we start from this source (see Figure 4.16)
    int s = 2 - 1; // index 2 is decreased by 1

    // Dijkstra routine
    Vector < Integer > dist = new Vector < Integer > ();
    dist.addAll(Collections.nCopies(V, INF)); dist.set(s, 0); // INF = 2.10^9 not MAX_INT to avoid overflow
    PriorityQueue < pair < Integer, Integer > > pq = new PriorityQueue < pair < Integer, Integer > >(1, 
      new Comparator< pair < Integer, Integer > >() { // overriding the compare method 
        public int compare(pair < Integer, Integer > i, pair < Integer, Integer > j) {
          return i.first() - j.first();
        }
      }
    );
    pq.offer(new pair < Integer, Integer > (0, s)); // sort based on increasing distance

    while (!pq.isEmpty()) { // main loop
      pair < Integer, Integer > top = pq.poll(); // greedy: pick shortest unvisited vertex
      int d = top.first(), u = top.second();
      if (d <= dist.get(u)) { // This check is important! We want to process vertex u only once but we can
        // actually enqueue u several times in priority_queue... Fortunately, other occurrences of u
        // in priority_queue will have greater distances and can be ignored (the overhead is small) :)
        Iterator it = AdjList.get(u).iterator();
        while (it.hasNext()) { // all outgoing edges from v
          pair< Integer, Integer > p = (pair< Integer, Integer >) it.next();
          int v = p.first(), weight_u_v = p.second();
          if (dist.get(u) + weight_u_v < dist.get(v)) { // if can relax      (note: Record SP spanning tree)
            dist.set(v, dist.get(u) + weight_u_v); // relax                  (here if needed. This is similar)
            pq.offer(new pair < Integer, Integer >(dist.get(v), v)); //      (as printpath in BFS)
            // enqueue this neighbor regardless whether it is already in pq or not    
    } } } }
  
    for (int i = 0; i < V; i++) // index + 1 for final answer
      System.out.printf("SSSP(%d, %d) = %d\n", s + 1, i + 1, dist.get(i));
  }
}
