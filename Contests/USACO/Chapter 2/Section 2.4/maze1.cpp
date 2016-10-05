/*
ID: b0002141
PROG: maze1
LANG: C++
*/

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

#define VD			vector<double>
#define VVD			vector<VD>

#define x			first
#define y			second
#define II			pair<int,int>
#define VII			vector<II>
#define VVII		vector<VII>

#define VS			vector<string>
#define VC			vector<char>

int main(){
	//ifstream cin("input.txt");
	ifstream cin("maze1.in");
	ofstream cout("maze1.out");
	int i,j,k;
	int C,R;
	string buf;
	VS V;
	int dx[]={1,0};
	int dy[]={0,1};

	cin >> C >> R;
	getline(cin,buf);
	V.clear(); V.resize(2*R+1);
	FOR(i,2*R+1)
		getline(cin,V[i]);

	VVI Adj(R*C);
	FOR(i,R) FOR(j,C){
		int u,v;
		u = i*C + j;
		int x,y;
		FOR(k,2){
			x = i+dx[k];
			y = j+dy[k];
			if(x>=R || y>=C)
				continue;
			if(k==0 && V[2*i+2][2*j+1]=='-')
				continue;
			if(k==1 && V[2*i+1][2*j+2]=='|')
				continue;
			v = x*C + y;
			Adj[u].push_back(v);
			Adj[v].push_back(u);
		}
	}

	VI d(R*C,R*C*10);
	queue<int> Q;
	FOR(i,R){
		if(V[2*i+1][0] == ' '){
			d[i*C + 0] = 0;
			Q.push(i*C + 0);
		}
		if(V[2*i+1][2*C] == ' '){
			d[i*C + C-1] = 0;
			Q.push(i*C + C-1);
		}
	}
	FOR(i,C){
		if(V[0][2*i+1] == ' '){
			d[0*C + i] = 0;
			Q.push(0*C + i);
		}
		if(V[2*R][2*i+1] == ' '){
			d[(R-1)*C + i] = 0;
			Q.push((R-1)*C + i);
		}
	}

	while(!Q.empty()){
		int u,v;
		u = Q.front(); Q.pop();
		FOR(i,Adj[u].size()){
			v = Adj[u][i];
			if(d[v] <= d[u]+1)
				continue;
			d[v] = d[u]+1;
			Q.push(v);
		}
	}

	int ans = 0;
	FOR(i,d.size())
		ans = max(ans,d[i]);

	cout << ans+1 << endl;

	return 0;
}