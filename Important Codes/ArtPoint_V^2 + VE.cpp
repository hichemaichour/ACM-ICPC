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
VVI Adj;
VI done;
VI nParts;

void DFS(int u) {
    int i;
    FOR(i,Adj[u].size()){
        int v = Adj[u][i];
        if(!done[v]){
            done[v] = true;
            DFS(v);
        }
    }
}

int ArtPoint(){
    int i,j,k;
    int u,v;
    nParts.clear(); nParts.resize(N);

    FOR(u,N){
        done.clear();
        done.resize(N);
        done[u] = true;
        FOR(v,N){
            if(done[v])
                continue;
            nParts[u]++;
            done[v] = true;
            DFS(v);
        }
    }

    int ret = 0;
    FOR(i,N)
        if(nParts[i] > 1)
            ret++;
    return ret; // number of articulation points
}

int main(){
    int i,j,k;
    ifstream cin("input.txt");
    int M;
    cin >> N;
    Adj.clear();
    Adj.resize(N);
    cin >> M;
    FOR(i,M){
        cin >> j >> k;
        Adj[j-1].push_back(k-1);
        Adj[k-1].push_back(j-1);
    }

    cout << ArtPoint() << endl;
    return 0;
}