#include <iostream>
#include <fstream>

#include <vector>
#include <queue>
#include <map>
#include <set>
#include <string>

#include <algorithm>
#include <functional>

#define All(v)			v.begin(),v.end()

#define REP(i,a,b)		for(i=(int)a ; i<=(int)b ; i++)
#define FOR(i,N)		REP(i,0,N-1)

#define VI				vector<int>
#define VVI				vector<VI>

#define VD				vector<double>
#define VVD				vector<VD>

#define x				first
#define y				second
#define II				pair<int,int>
#define VII				vector<II>
#define VVII			vector<VII>

#define VS				vector<string>

using namespace std;

int R,C;
VS V;

bool check(int i,int j){
	if(i!=0 && i!=R-1 && V[i-1][j]=='v' && V[i+1][j]=='^')
		return true;
	if(j!=0 && j!=C-1 && V[i][j-1]=='>' && V[i][j+1]=='<')
		return true;
	return false;
}

int main(){
	ifstream cin("input.txt");
	ofstream cout("a2.out");
	int T;
	cin >> T;
	int cnt;
	REP(cnt,1,T){
		int i,j,k;
		V.clear();

		cin >> R >> C;
		V.resize(R);
		FOR(i,R) cin >> V[i];

		int sum=0;
		FOR(i,R) FOR(j,C)
			if(V[i][j] == 'o' && check(i,j))
				sum++;

		cout << sum << endl;
	}
}