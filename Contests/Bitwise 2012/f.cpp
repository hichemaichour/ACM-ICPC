#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <set>

#define REP(i,a,b)		for(i=(int)a ; i<=(int)b ; i++)
#define FOR(i,N)		REP(i,0,N-1)

#define VI				vector<int>
#define VVI				vector<VI>

#define St				pair<char,int>
#define c				first
#define n				second
#define VSt				vector<St>
#define VVSt			vector<VSt>

using namespace std;

int N,M;
vector<string> Str;

VVI val;

int main(){
	//ifstream cin("f.txt");
	while(cin >> N >> M){
		int i,j,k;

		Str.resize(M);
		FOR(i,M) 
			cin >> Str[i];

		val.clear(); val.resize(M,VI(N));
		FOR(i,M) FOR(j,N){
			FOR(k,N-j)
				if(Str[i][k] != Str[i][k+j])
					break;
			val[i][j] = k;
		}

		VI buf;
		string str = "";
		FOR(i,N){
			set<char> s;
			char c;
			int n=-1;
			FOR(j,M){
				if(val[j][i] > n){
					s.clear();
					c = Str[j][i];
					n = val[j][i];
					s.insert(c);
				}
				else if(val[j][i] == n){
					if(Str[j][i] < c)
						c = Str[j][i];
					s.insert(Str[j][i]);
				}
			}
			buf.push_back(s.size());
			str += c;
		}

		long long ans = 1;
		long long mod = 10000007;
		FOR(i,buf.size())
			ans = (ans*buf[i])%mod;

		cout << ans <<" "<< str << endl;
	}
	return 0;
}