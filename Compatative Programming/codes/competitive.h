// if you are VC++ users, this will suppress some compilation warning messages
#define _CRT_SECURE_NO_DEPRECATE

// Include all headers that you may possibly need
// Note: you can add/reduce these #includes according to your need
#include <algorithm> // sort, lower_bound, min, max, next_permutation
#include <bitset> // for Sieve of Eratosthenes
#include <cmath> // math routines: abs, pow, etc
#include <cstdio> // In case needed
#include <cstdlib>
#include <ctype.h> // character routines: isalpha, etc
#include <deque>
#include <iostream> // I/O routines
//#include <list>
#include <map> // balanced BST (RB Tree) for key-data pairs
#include <queue> // queue and priority_queue
#include <set> // balanced BST (RB Tree) with key only
#include <stack> // stack
#include <string> // C++ class string
#include <vector> // resize-able array
using namespace std;

// Shortcuts for "common" data types in contests
typedef long long             ll;
typedef long double           ld;
typedef vector<int>           vi;
typedef vector<bool>          vb;
typedef pair<int, int>        ii;
typedef vector<ii>            vii;
typedef set<int>              si;
typedef map<string, int>      msi;

// To simplify repetitions/loops
// Note: define your loop style and stick with it!
// a to b, and variable i is local!
#define REP(i, a, b) 	for (int i = int(a); i <= int(b); i++)
// loop from 1 to n, variable i is local
#define REPN(i, n)	  REP (i, 1, int(n))
// loop down from a to b, variable i is local
#define REPD(i, a, b)	for (int i = int(a); i >= int(b); i--)
// These variations are manual at the moment
#define TRvi(c, it)   for (vi::iterator it = (c).begin(); it != (c).end(); it++)
#define TRvii(c, it) \
  for (vii::iterator it = (c).begin(); it != (c).end(); it++)
#define TRmsi(c, it)  for (msi::iterator it = (c).begin(); it != (c).end(); it++)
// only for UNIX
//#define TR(c, it)	for (typeof((c).begin()) it = (c).begin(); it != (c).end(); it++)

// Even more shortcuts
#define PB      	push_back
#define MP      	make_pair
#define SIZE(c) 	(int((c).size()))
#define SHOW(x) 	cerr << #x << " = " << x << endl;

// Avoid re-typing the test cases whenever you want to test your program
// Simply place test data inside "input.txt" and put this line just
// after int main() {
#define REDIRECT_INPUT   freopen("input.txt", "r", stdin)

#define INF 2147483647 // 2^31-1
// If you need to recall how to use memset:
#define MEMSET_INF 127 // about 2B
#define MEMSET_HALF_INF 63 // about 1B
// useful to initialize shortest path distances, set INF to 127!
//memset(dist, MEMSET_INF, sizeof dist);
// useful to initialize DP memoization table
//memset(dp_memo, -1 sizeof dp_memo);
// useful to clear array of integers
//memset(arr, 0, sizeof arr);


// Graph Library
#define MAX_V 100 // Change this to the actual size of |V|
int AdjMat[MAX_V][MAX_V]; // if MAX_V > 100, consider using AdjList
vector<vii> AdjList; // see vii shortcut above for explanation
priority_queue< pair<int, ii> > EdgeList;
// int parent, vector<int> children;

// for DFS
#define DFS_WHITE -1 // normal DFS
#define DFS_BLACK 1
vi dfs_num;
int numComponent;
void initDFS(int V) { // used in normal dfs
  dfs_num.clear(); dfs_num.resize(V, DFS_WHITE);
  numComponent = 0;
}

#define DFS_GRAY 2 // one more color for graph edges property check
vi dfs_parent;
void initGraphCheck(int V) { // used in normal dfs
  initDFS(V);
  dfs_parent.clear(); dfs_parent.resize(V, 0);
}

vi dfs_low; // additional information for articulation pointersections/bridges
vb articulation_vertex;
int dfsNumberCounter, dfsRoot, rootChildren;
void initArticulationPointBridge(int V) {
  initGraphCheck(V);
  dfs_low.clear(); dfs_low.resize(V, 0);
  articulation_vertex.clear(); articulation_vertex.resize(V, false);
  dfsNumberCounter = 0;
}

stack<int> dfs_scc; // additional information for SCC
void initTarjanSCC(int V) {
  initGraphCheck(V);
  dfs_low.clear(); dfs_low.resize(V, 0);
  dfsNumberCounter = 0;
  while (!dfs_scc.empty())
    dfs_scc.pop();
}

vector<int> topologicalSort; // additional information for toposort
void initTopologicalSort(int V) {
  initDFS(V);
  topologicalSort.clear();
}


// Union-Find Disjoint Sets Library
// PS: This library code does not include the `union by rank' heuristic yet
vector<int> pset(1000); // 1000 is just a rough number, adjustable by user
int disjointSetSize;
void initSet(int _size) { disjointSetSize = _size; pset.resize(_size); REP (i, 0, _size - 1) pset[i] = i; }
int findSet(int i) { return (pset[i] == i) ? i : (pset[i] = findSet(pset[i])); }
void unionSet(int i, int j) { if (pset[findSet(i)] != findSet(j)) { pset[findSet(i)] = findSet(j); disjointSetSize--; } }
bool isSameSet(int i, int j) { return findSet(i) == findSet(j); }


// Segment Tree Library
// The segment tree is stored like a heap array
#define RANGE_SUM 0
#define RANGE_MIN 1
#define RANGE_MAX 2
vi segment_tree;

void init_segment_tree(int N) { // if original array size is N,
  // the required segment_tree array length is 2*2^(floor(log2(N)) + 1);
  int length = (int)(2 * pow(2.0, floor((log((double)N) / log(2.0)) + 1)));
  segment_tree.resize(length, 0); // resize this vector and fill with 0
}

void build_segment_tree(int code, int A[], int node, int b, int e) {
  if (b == e) { // as b == e, either one is fine
    if (code == RANGE_SUM) segment_tree[node] = A[b]; // store value of this cell
    else                   segment_tree[node] = b; // if RANGE_MIN/MAXIMUM, store index
  }
  else { // recursively compute the values in the left and right subtrees
    int leftIdx = 2 * node, rightIdx = 2 * node + 1;
    build_segment_tree(code, A, leftIdx , b              , (b + e) / 2);
    build_segment_tree(code, A, rightIdx, (b + e) / 2 + 1, e          );
    int lContent = segment_tree[leftIdx], rContent = segment_tree[rightIdx];
    
    if (code == RANGE_SUM) // make this segment contains sum of left and right subtree
      segment_tree[node] = lContent + rContent;
    else { // (code == RANGE_MIN/MAXIMUM)
      int lValue = A[lContent], rValue = A[rContent];
      if (code == RANGE_MIN) segment_tree[node] = (lValue <= rValue) ? lContent : rContent;
      else                   segment_tree[node] = (lValue >= rValue) ? lContent : rContent;
} } }

int query(int code, int A[], int node, int b, int e, int i, int j) {
  if (i > e || j < b) return -1; // if current interval outside query interval 
  if (b >= i && e <= j) return segment_tree[node]; // if current interval inside query interval

  // compute the minimum position in the left and right part of the interval
  int p1 = query(code, A, 2 * node    , b              , (b + e) / 2, i, j);
  int p2 = query(code, A, 2 * node + 1, (b + e) / 2 + 1, e          , i, j);

  // return the position where the overall minimum is
  if (p1 == -1) return p2; // can happen if we try to access segment outside query
  if (p2 == -1) return p1; // same as above

  if (code == RANGE_SUM)      return p1 + p2;
  else if (code == RANGE_MIN) return (A[p1] <= A[p2]) ? p1 : p2;
  else                        return (A[p1] >= A[p2]) ? p1 : p2;
}

int update_point(int code, int A[], int node, int b, int e, int idx, int new_value) {
  // this update code is still preliminary, i == j
  // must be able to update range in the future!
  int i = idx, j = idx;

  // if the current interval does not intersect 
  // the update interval, return this segment_tree node value!
  if (i > e || j < b)
    return segment_tree[node];

  // if the current interval is included in the update range,
  // update that segment_tree[node]
  if (b == i && e == j) {
    A[i] = new_value; // update the underlying array?
    if (code == RANGE_SUM)
      return segment_tree[node] = A[b]; // this new value
    else
      return segment_tree[node] = b; // this index
  }

  // compute the minimum position in the 
  // left and right part of the interval
  int p1, p2;
  p1 = update_point(code, A, 2 * node, b, (b + e) / 2, idx, new_value);
  p2 = update_point(code, A, 2 * node + 1, (b + e) / 2 + 1, e, idx, new_value);

  // return the position where the overall minimum is
  if (code == RANGE_SUM)
    return segment_tree[node] = p1 + p2;
  else if (code == RANGE_MIN)
    return segment_tree[node] = (A[p1] <= A[p2]) ? p1 : p2;
  else // if (code == RANGE_MAX)
    return segment_tree[node] = (A[p1] >= A[p2]) ? p1 : p2;
}



/* Mathematics Library */
ll _sieve_size;
bitset<10000010> bs; // 10^7 should be enough for most cases
vi primes; // compact list of primes in form of vector<int>

void sieve(ll upperbound) { // create list of primes in [0 .. upperbound]
  _sieve_size = upperbound + 1; // add 1 to include upperbound
  bs.reset(); bs.flip(); // set all numbers to 1
  bs.set(0, false); bs.set(1, false); // except index 0 and 1
  for (ll i = 2; i <= _sieve_size; i++) if (bs.test((size_t)i)) {
    // cross out multiples of i starting from i * i!
    for (ll j = i * i; j <= _sieve_size; j += i) bs.set((size_t)j, false);
    primes.push_back((int)i); // simultaneously update this
  }
} // call this method in main method

bool isPrime(ll N) { // a good deterministic prime tester
  if (N < _sieve_size) return bs.test(N); // O(1) for small primes
  REP (i, 0, primes.size() - 1) if (N % primes[i] == 0) return false;
  return true; // it takes longer time if N is a large prime!
} // Note: only work for N <= (last prime in vi "primes")^2

vi primeFactors(int N) {
  vi factors;          // vi "primes" (generated by sieve) is optional
  int PF_idx = 0, PF = primes[PF_idx]; // using PF = 2, 3, 4, ..., is also ok.
  while (N != 1 && (PF * PF <= N)) { // stop at sqrt(N), but N can get smaller
    while (N % PF == 0) { N /= PF; factors.push_back(PF); } // remove this PF
    PF = primes[++PF_idx]; // only consider primes!
  }
  if (N != 1) factors.push_back(N); // special case if N is actually a prime
  return factors;
}

int EulerPhi(int N) {
  vi factors = primeFactors(N);
  vi::iterator new_end = unique(factors.begin(), factors.end()); // only unique ones
  int result = N;
  for (vi::iterator i = factors.begin(); i != new_end; i++)
    result = result - result / *i;
  return result;
}

int gcd(int a, int b) { return (b == 0 ? a : gcd(b, a % b)); }

int lcm(int a, int b) { return (a * b / gcd(a, b)); }

pair<ii, int> extendedEuclid(int a, int b) {
  if (b == 0)
    return make_pair(make_pair(1, 0), a);
  pair<ii, int> result = extendedEuclid(b, a % b);
  int x = result.first.first, y = result.first.second;
  int d = result.second;
  int x1 = y;
  int y1 = x - (a / b) * y;
  x = x1;
  y = y1;
  return make_pair(make_pair(x, y), d);
}
