#include <iostream>
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
#define REPI(i, v)			for (i=v.begin() ; i!=v.end() ; i++)
#define FOR(i, n)			REP (i, 0, n-1)
#define FORD(i, n)			REPD(i, n-1, 0)

#define All(v)			v.begin(),v.end()
#define Resize(v,N)		v.clear(); v.resize(N);

#define IsIn(v,e)		(find(All(v),e) != v.end())
#define Remove(v,e)		v.resize( remove(All(v),e) - v.begin() )

#define VI			vector<long long>
#define VVI			vector<VI>

#define x			first
#define y			second
#define II			pair<long long,long long>
#define VII			vector<II>
#define VVII		vector<VII>

#define VS			vector<string>
#define VVS			vector<VS>

#define St			pair<string,II>

int N;
int Q;
VS str;
VI pos;
vector<St> V;
VVII Adj;
VVS ans;
VI C;

bool func(St node1 , St node2){
	return (node1.x==node2.x && node1.y.x!=node2.y.x);
}

void Build_V(){
	int i,j,k;
	int u,v;
	char c;
	string s;
	vector<St> buf1;
	vector<St> buf2;
	V.clear();
	pos.clear();

	VVII suf(26);
	VVI pre(26);
	FOR(i,N){
		c = str[i][0];
		pre[c-'a'].push_back(i);
		FOR(j,str[i].size()){
			c = str[i][j];
			suf[c-'a'].push_back(II(i,j));
		}
	}

	FOR(i,26){
		if(suf[i].empty() || pre[i].empty())
			continue;
		FOR(j,pre[i].size()){
			k = pre[i][j];
			s = str[k];
			s = s.substr(0,s.size()-1);
			while(s.size() != 1){
				buf1.push_back(St(s , II(1,k)));
				s = s.substr(0,s.size()-1);
			}
		}

		sort(All(buf1));
		
		FOR(j,suf[i].size()){
			k = suf[i][j].x;
			if(suf[i][j].y == 0)
				continue;
			s = str[k].substr(suf[i][j].y , str[k].size());
			St node = St(s , II(0,k));
			if(binary_search(All(buf1),node,func))
				buf1.push_back(node);
		}

		sort(All(buf1));		

		VI index;
		FOR(j,buf1.size()-1){
			if (buf1[j].x == buf1[j + 1].x) {
				s = buf1[j].x;
				index.push_back(buf2.size());
				while (j < buf1.size() && s == buf1[j].x) {
					buf2.push_back(buf1[j]);
					j++;
				}
				j--;
			}
		}
		index.push_back(buf2.size());

		FOR(j,index.size()-1){
			u = index[j]; v = index[j+1]-1;
			if (buf2[u].y.x == buf2[v].y.x)
				continue;
			pos.push_back(V.size());
			REP(u, u, v) V.push_back(buf2[u]);
		}

		buf1.clear();
		buf2.clear();
	}
	pos.push_back(V.size());
}

void Build_Graph(){
	int i,j,k;
	int u,v;

	Adj.clear();
	Adj.resize(N + 26*2); // 26s - 26t - N

	FOR(i,N){
		string s = str[i];
		u = 26*2 + i;

		v = s[0]-'a';
		Adj[v].push_back(II(u , s.size()));

		v = 26 + s[s.size()-1]-'a';
		Adj[u].push_back(II(v , 0));
	}

	int lo,hi;
	FOR(i,pos.size()-1){
		lo = pos[i]; hi = pos[i+1]-1;
		REP(j,lo,hi){
			if(V[j].y.x == 1)break;
			REPD(k,hi,j){
				if(V[k].y.x == 0)break;
				if(V[k].y.y == V[j].y.y)continue;
				u = V[j].y.y + 26*2; v = V[k].y.y + 26*2;
				int cost = str[v - 26*2].size() - V[k].x.size();
				Adj[u].push_back(II(v , cost));
			}
		}
	}
}

const int inf = 1e9;
VS dijkstra(int s,int t){
	int i,j,k;
	int u,v,cost;
	int n = N + 26*2;

	priority_queue<II , vector<II> , greater<II> > q;
	VI d(n,inf);
	VI p(n,-1);

	d[s] = 0;
	q.push(II(0,s));

	while(!q.empty()){
		II buf = q.top(); q.pop();
		u = buf.y; cost = buf.x;

		if(u == t) break;
		if(cost > d[u]) continue;

		FOR(i,Adj[u].size()){
			buf = Adj[u][i];
			v = buf.x;
			if(d[v] <= cost+buf.y) continue;
			d[v] = cost+buf.y;
			p[v] = u;
			q.push(II(d[v],v));
		}
	}

	u = t;
	VS ret;
	while(u != -1){
		if(u >= 26*2)
			ret.push_back(str[u - 26*2]);
		u = p[u];
	}
	reverse(All(ret));

	k = d[t];
	t -= 26;
	if(k == inf)
		C[s*26 + t] = 0;
	else
		C[s*26 + t] = k;
	return ret;
}

void Pre(){
	int i,j,k;
	int u,v,cost;
	ans.clear(); C.clear();
	ans.resize(26*26); C.resize(26*26);

	Build_V();

//	int i;
//	FOR(i,V.size())	cout << V[i].x <<" "<< V[i].y.x <<" "<< V[i].y.y << endl;

	Build_Graph();

//	FOR(i,Adj.size()){
//		if(Adj[i].empty())
//			continue;
//		FOR(j,Adj[i].size()){
//			u = i; v = Adj[i][j].x; cost = Adj[i][j].y;
//
//			if(u < 26) cout << (char)(u+'a') << " ";
//			else if (u < 26*2) cout <<  (char)(u-26+'a') << " ";
//			else cout << u-26*2+1 << " ";
//
//			u = v;
//			if(u < 26) cout << (char)(u+'a') << " ";
//			else if (u < 26*2) cout <<  (char)(u-26+'a') << " ";
//			else cout << u-26*2+1 << " ";
//
//			cout << cost << endl;
//		}
//		cout << endl;
//	}

	FOR(i,26) FOR(j,26) ans[i*26 + j] = dijkstra(i,j+26);
}

int main(){
	ifstream cin("atoz.in");
	for(int cnt=1 ; true ; cnt++){
		int i,j,k;
		cin >> N;
		if(N == 0)break;
		str.clear(); str.resize(N);
		FOR(i,N) cin >> str[i];

		Pre();

		cin >> Q;
		char s,t;
		FOR(i,Q){
			cin >> s >> t;
			s -= 'a'; t -= 'a';
			k = s*26 + t;

			cout << cnt <<"."<< i+1 <<" "<<C[k];
			FOR(j,ans[k].size()) cout <<" "<<ans[k][j];
			cout << endl;
		}
	}
	return 0;
}