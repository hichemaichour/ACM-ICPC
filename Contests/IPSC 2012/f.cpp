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

#define x				first
#define y				second
#define II				pair<int,int>
#define VII				vector<II>
#define VVII			vector<VII>

using namespace std;

int main(){
	ifstream cin("input.txt");
	ofstream cout("f1.out");
	int T;
	cin >> T;
	int cnt;
	REP(cnt,1,T){
		int i,j,k;
		VD p;
		int N;

		cin >> N;
		p.resize(N);
		FOR(i,N) cin >> p[i];

		VI v(1000001);
		VI vv;
		v[0] = 1;
		vv.push_back(0);

		FOR(i,N){
			int n = vv.size();
			VII buf;
			FOR(j,n){
				int pp = vv[j]*(1-p[i]) + (1000000-vv[j])*p[i];
				if(v[pp] == 0)
					vv.push_back(pp);
				//v[pp] += v[vv[j]];
				buf.push_back(II(pp,v[vv[j]]));
			}
			FOR(j,buf.size())
				v[buf[j].x] += buf[j].y;
		}

		int ans = 0;
		REP(i,0,0)
			ans += v[1000000/2 + i];
		cout << ans << endl;
	}
}