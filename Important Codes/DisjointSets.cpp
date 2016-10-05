#include <iostream>
#include <fstream>
#include <sstream>

#include <iomanip>

#include <algorithm>

#include <vector>
#include <deque>
#include <list>
#include <stack>
#include <queue>
#include <set>
#include <map>
#include <bitset>
#include <string>

#include <iterator>
#include <functional>
#include <complex>
#include <numeric>
#include <valarray>

#include <cmath>

using namespace std;

#define REP(i, a, b) 		for (i=(int)a ; i<=(int)b ; i++)
#define REPD(i, a, b)		for (i=(int)a ; i>=(int)b ; i--)
#define REPI(i, v)		for (i=v.begin() ; i!=v.end() ; i++)
#define FOR(i, n)		REP (i, 0, n-1)
#define FORD(i, n)		REPD(i, n-1, 0)

#define All(v)			v.begin(),v.end()
#define Resize(v,N)		v.clear(); v.resize(N);

#define IsIn(v,e)		(find(All(v),e) != v.end())
#define Remove(v,e)		v.resize( remove(All(v),e) - v.begin() )

#define VI			vector<int>
#define VVI			vector<VI>

#define x			first
#define y			second
#define II			pair<int,int>
#define VII			vector<II>
#define VVII			vector<VII>

int N;
VI Set;
VI nSet;

void initSet(){
    int i;
    Set.clear(); nSet.clear();
    Set.resize(N); nSet.resize(N);
    FOR(i,N)
        Set[i] = i;
}

int Find(int u){
    if(Set[u] != u)
        Set[u] = Find(Set[u]);
    return Set[u];
}

void Union(int u,int v){
    u = Find(u);
    v = Find(v);
    if(u != v){
        nSet[u] += nSet[v];
        nSet[v] = -1;
    }
    Set[v] = u;
}

