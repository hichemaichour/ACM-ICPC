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

int main(){
	ifstream cin("input.txt");
	//ofstream cout("a.out");
	int T;
	cin >> T;
	int cnt;
	REP(cnt,1,T){
		int i,j,k;
		int N;
		VS V1,V2;

		cin >> N;
		V1.resize(N); V2.resize(N);
		FOR(i,N) cin >> V1[i];
		FOR(i,N) cin >> V2[i];

		VVII v1(26);
		VVII v2(26);
		FOR(i,N){
			FOR(j,V1[i].size())
				v1[V1[i][j]-'a'].push_back(II(j,i));
			FOR(j,V2[i].size())
				v2[V2[i][j]-'a'].push_back(II(j,i));
		}
		FOR(i,26){
			sort(All(v1[i]));
			sort(All(v2[i]));
		}

		VVI p(26);
		FOR(i,26){
			if(v1[i].empty()) continue;

			FOR(j,26){
				if(v2[j].empty() || v1[i].size()!=v2[j].size()) continue;
				bool flg = true;
				FOR(k,v1[i].size()){
					if(v1[i][k].x != v2[j][k].x){
						flg = false;
						break;
					}
				}
				if(flg) p[i].push_back(j);
			}
		}

		string ans;
		ans.resize(26);
		VI done(26);
		bool flg=true;
		FOR(i,26){
			if(p[i].empty()) continue;
			if(p[i].size()>1) {flg = false;break;}
			ans[i] = 'a'+p[i].front();
			done[p[i].front()] = 1;
		}
		if(flg){
			j = 0;
			FOR(i,26){
				if(ans[i] != 0) continue;
				while(done[j]) j++;
				done[j] = 1;
				ans[i] = 'a'+j;
			}
		}

		if(flg)
			cout << ans << endl;
		else
			cout <<"*******************************************************"<<endl;
	}
}