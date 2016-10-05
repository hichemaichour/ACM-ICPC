/*
ID: b0002141
PROG: castle
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

#define x			first
#define y			second
#define II			pair<int,int>
#define VII			vector<II>
#define VVII		vector<VII>

int M,N;
VVI Adj;
int dx[] = { 0,-1,0,1};
int dy[] = {-1, 0,1,0};
int W[]  = {1,2,4,8};

int main(){
	//ifstream cin("input.txt");
	ifstream cin("castle.in");
	ofstream cout("castle.out");
	int i,j,k;
	int ux,uy;
	int vx,vy;
	int n;
	cin >> M >> N;
	Adj.clear();
	Adj.resize(N*M);
	FOR(ux,N){
		FOR(uy,M){
			cin >> n;
			FOR(i,4){
				vx = ux+dx[i];
				vy = uy+dy[i];
				if(vx<0 || vx>=N || vy<0 || vy>=M || n & W[i])
					continue;
				Adj[ux*M + uy].push_back(vx*M + vy);
			}
		}
	}

	VVI done(N,VI(M));
	VVI G(N,VI(M,-1));
	int C = 0;
	FOR(i,N){
		FOR(j,M){
			if(done[i][j]) continue;
			done[i][j] = 1;
			G[i][j] = C++;
			queue<int> X; queue<int> Y;
			X.push(i); Y.push(j);
			while(!X.empty()){
				ux = X.front(); X.pop();
				uy = Y.front(); Y.pop();
				n = ux*M + uy;
				FOR(k,Adj[n].size()){
					vx = Adj[n][k] / M;
					vy = Adj[n][k] % M;
					if(done[vx][vy]) continue;
					done[vx][vy] = 1;
					G[vx][vy] = G[i][j];
					X.push(vx); Y.push(vy);
				}
			}
		}
	}

	VI NC(C);
	FOR(i,N) FOR(j,M) NC[G[i][j]]++;

	int LRC = -1;
	int px=N,py=M;
	int pos;
	FOR(ux,N){
		FOR(uy,M){
			REP(i,1,2){
				vx = ux+dx[i]; vy = uy+dy[i];
				if(vx<0 || vx>=N || vy<0 || vy>=M || G[ux][uy]==G[vx][vy]) continue;
				n = NC[G[ux][uy]] + NC[G[vx][vy]];
				if(n < LRC) continue;
				if(n > LRC || uy<py) {px=ux; py=uy; LRC=n; pos=i; continue;}
				if(uy>py) continue;
				if(pos==1 && i==2) continue;
				if(pos==2 && i==1) {px=ux; py=uy; LRC=n; pos=i; continue;}
				if(ux>px) {px=ux; py=uy; LRC=n; pos=i; continue;}
			}
		}
	}

	cout << C << endl;
	cout << *max_element(All(NC)) << endl;
	cout << LRC << endl;
	cout << px+1 <<" "<< py+1;
	if(pos==1)cout <<" N"<<endl;
	else	cout <<" E"<<endl;
}