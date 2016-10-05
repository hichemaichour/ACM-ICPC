#include <iostream>
#include <string>
#include <cctype>
#include <algorithm>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <set>
#include <bitset>
#include <cmath>
#include <deque>
#include <cstring>
#include <list>
#include <functional>
#include <queue>
#include <climits>

#define FOR(i,N)		for(i=0 ; i<(long long)N ; i++)
#define REP(i,a,b)		for(i=(long long)a ; i<=(long long)b ; i++)
#define REPD(i,a,b)		for(i=(long long)a ; i>=(long long)b ; i--)
#define FORD(i,N)		REPD(i,N-1,0)

#define II				pair<long long,long long>

#define VI				deque<long long>
#define VVI				vector<VI>

#define VII				vector<II>
#define VVII			vector<VII>

#define VS				deque<string>
#define VVS				vector<VS>

#define VD				deque<double>
#define VVD				deque<VD>

#define All(v)			v.begin(),v.end()

#define DD				pair<double,double>
#define VDD				vector<DD>

#define VC				deque<char>
#define VVC				deque<VC>

using namespace std;

#define x				first
#define y				second

int dx[] = {-1, 1, 0, 0};
int dy[] = { 0, 0,-1, 1};

int N;
int n;
VII s,t;
int B[4][4];
map<II,map<II,bool> > m;

long long encode(VII& v){
	long long ans = 0;
	int i;
	FOR(i,n)
		ans = (ans*10 + v[i].x)*10 + v[i].y;
	return ans;
}

VII decode(long long v){
	VII ans(n);
	int i;
	FORD(i,n){
		ans[i].y = v%10; v/=10;
		ans[i].x = v%10; v/=10;
	}
	return ans;
}

long long BFS(){
	int i,k;
	long long u,v,d;
	VII U,V;
	queue<long long> Q,D;
	map<long long,bool> done;

	u = encode(s);
	Q.push(u); D.push(0); done[u]=true;
	while(!Q.empty()){
		u=Q.front(); Q.pop();
		d=D.front(); D.pop();
		if(u==encode(t)) return d;

		FOR(k,4){
			U = decode(u);
			while(1){
				V = U;
				FOR(i,n){
					if(B[V[i].x][V[i].y]==i) continue;
					II nxt = II(V[i].x+dx[k], V[i].y+dy[k]);
					if(m[V[i]][nxt]) continue;
					if(nxt.x>=N || nxt.y>=N || nxt.x<0 || nxt.y<0) continue;
					if(count(All(V),nxt) > 1) continue;
					if(B[nxt.x][nxt.y]==-1 && find(All(V),nxt)!=V.end()) continue;
					if(B[nxt.x][nxt.y]!=-1 && B[nxt.x][nxt.y]!=i && find(All(V),nxt)==V.end()) break;
					V[i] = nxt;
				}
				if(i!=n || U==V) break;
				U = V;
			}
			if(i!=n) continue;
			v = encode(V);
			if(done[v]) continue;
			done[v] = true;
			Q.push(v); D.push(d+1);
		}
	}
	return -1;
}

int main(){
	ifstream cin("input.txt");
	int W;
	int cnt=1;
	while(cin >> N >> n >> W){
		if(N==0) break;
		int i,u,v,uu,vv;
		m.clear();
		s.resize(n); t.resize(n);
		FOR(u,4) FOR(v,4) B[u][v]=-1;

		FOR(i,n) {cin>>u>>v; s[i]=II(u,v);}
		FOR(i,n) {cin>>u>>v; t[i]=II(u,v); B[u][v]=i;}
		FOR(i,W) {cin>>u>>v>>uu>>vv; m[II(u,v)][II(uu,vv)]=m[II(uu,vv)][II(u,v)]=1;}

		int ans = BFS();
		cout <<"Case "<<cnt++<<": ";
		if(ans==-1) cout <<"impossible"<<endl;
		else cout <<ans <<" moves"<<endl;
		cout << endl;
	}
	return 0;
}
