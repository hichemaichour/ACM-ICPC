#include <iostream>
#include <fstream>

#include <vector>
#include <queue>
#include <map>
#include <set>
#include <algorithm>
#include <functional>

#define All(v)			v.begin(),v.end()

#define REP(i,a,b)		for(i=(int)a ; i<=(int)b ; i++)
#define FOR(i,N)		REP(i,0,N-1)

#define VI				vector<int>
#define VVI				vector<VI>

#define VD				vector<double>
#define VVD				vector<VD>

#define fst				first
#define scd				second
#define II				pair<int,int>
#define VII				vector<II>
#define VVII			vector<VII>

using namespace std;

int main(){
	ifstream cin("input.txt");
	ofstream cout("p1.out");
	int T;
	cin >> T;
	int cnt;
	REP(cnt,1,T){
		int i,j,k;
		int N,s;
		VII V;

		cin >> N;
		V.resize(N);
		s = 0;
		FOR(i,N){
			cin >> V[i].fst;
			V[i].scd = i+1;
			s += V[i].fst;
		}
		sort(All(V));

		int ans;
		int sum = 0;
		FOR(ans,N){
			sum += V[ans].fst;
			if(sum > s/2)
				break;
		}

		cout << ans;
		FOR(i,ans)
			cout <<" "<<V[i].scd;
		cout << endl;

		cout << N-ans-1;
		REP(i,ans,N-2)
			cout <<" "<<V[i].scd;
		cout << endl;
	}
}