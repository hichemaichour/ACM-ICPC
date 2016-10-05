#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <functional>

#define REP(i,a,b)		for(i=(int)a ; i<=(int)b ; i++)
#define FOR(i,N)		REP(i,0,N-1)

#define VI				vector<long long>

#define II				pair<long long,long long>
#define VII				vector<II>
#define VVII			vector<VII>

#define INF				1e9

using namespace std;

int C;
int P;
int S;
int H;

VVII Adj;
VI dis;

void dijkstra(){
	int i,j,k;
	int u,v,d;
	dis.clear(); dis.resize(C,INF);
	priority_queue<II,VII,greater<II> > Q;

	dis[S] = 0;
	Q.push(II(0,S));
	while(!Q.empty()){
		u = Q.top().second;
		d = Q.top().first;
		Q.pop();

		if(d > dis[u])
			continue;

		FOR(i,Adj[u].size()){
			v = Adj[u][i].first;
			if(dis[v] > d + Adj[u][i].second){
				dis[v] = d + Adj[u][i].second;
				Q.push(II(dis[v],v));
			}
		}
	}
}

int main(){
	//ifstream cin("i.txt");
	while(cin >> C >> P >> S){
		S--;
		int i,j,k;
		int u,v,t;
		Adj.clear(); Adj.resize(C);

		FOR(i,P){
			cin >> u >> v >> t;
			u--; v--;
			Adj[u].push_back(II(v,t));
			Adj[v].push_back(II(u,t));
		}

		dijkstra();

		int f,w;
		cin >> H;
		long long ans = 0;
		FOR(i,H){
			cin >> f >> w;
			f--;
			ans += dis[f]*w;
		}

		cout << ans << endl;
	}
	return 0;
}