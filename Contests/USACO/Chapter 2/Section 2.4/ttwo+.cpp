/*
ID: b0002141
PROG: ttwo
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
	ifstream cin("ttwo.in");
	ofstream cout("ttwo.out");
	int i,j,k;
	char buf;
	VVI V(10,VI(10));

	const int FULL = 1;
	const int EMPTY = 0;
	int xF,yF,xC,yC;

	FOR(i,10) FOR(j,10){
		cin >> buf;
		if(buf == '*') V[i][j] = FULL;
		if(buf == 'F'){xF = i; yF = j;}
		if(buf == 'C'){xC = i; yC = j;}
	}

	int done[10][10][4][10][10][4];
	int ii,jj,kk;
	FOR(i,10) FOR(j,10) FOR(k,4) FOR(ii,10) FOR(jj,10) FOR(kk,4) done[i][j][k][ii][jj][kk] = 0;

	int dirF=0,dirC=0;
	int dx[] = {-1,0,1, 0};
	int dy[] = { 0,1,0,-1};

	bool flg = false;
	done[xF][yF][dirF][xC][yC][dirC] = 1;
	int cnt = 0;
	while(!flg){
		i = xF+dx[dirF]; j = yF+dy[dirF];
		if(i<10 && i>=0 && j<10 && j>=0 && V[i][j]==EMPTY){
			xF=i; yF=j;
		}
		else
			dirF = (dirF+1)%4;

		i = xC+dx[dirC]; j = yC+dy[dirC];
		if(i<10 && i>=0 && j<10 && j>=0 && V[i][j]==EMPTY){
			xC=i; yC=j;
		}
		else
			dirC = (dirC+1)%4;

		if(done[xF][yF][dirF][xC][yC][dirC])
			break;
		done[xF][yF][dirF][xC][yC][dirC] = 1;
		if(xF==xC && yF==yC)
			flg = true;
		cnt++;
	}

	if(flg)
		cout << cnt << endl;
	else
		cout << 0 << endl;

	return 0;
}