#include <iostream>
#include <fstream>
#include <sstream>

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

#define All(v)				v.begin(),v.end()

#define PB					push_back
#define MP					make_pair

#define PQ					priority_queue

typedef long long			LL;
typedef long double			LD;
typedef vector<int>			VI;
typedef vector<VI>			VVI;
typedef vector<bool>		VB;
typedef vector<VB>			VVB;
typedef vector<double>		VD;
typedef vector<VD>			VVD;
typedef pair<int, int>		II;
typedef vector<II>			VII;
typedef vector<VII>			VVII;

int T;
int N;
vector<string> U;
VI W;
VVI Adj;
VVI Ret;

bool Space(char c1,char c2){
	return c1==c2 && c1==' ';
}

void Modify(string& s){
	while(s[0] == ' ')
		s = s.substr(1);
	while(s[s.size()-1] == ' ')
		s = s.substr(0,s.size()-1);
	s.push_back(' ');
	s.resize(unique(All(s),Space) - s.begin());
}

void BFS(int w,int k){
	VB done(T);
	queue<int> D;
	queue<int> q;
	
	D.push(0);
	q.push(w);
	done[w] = true;

	int i;
	int u,d;
	while(!q.empty()){
		u = q.front(); q.pop();
		d = D.front(); D.pop();

		FOR(i,Adj[u].size()){
			int v = Adj[u][i];
			if(done[v])
				continue;
			done[v] = true;
			if(d > 0)
				Ret[k].push_back(v);
			q.push(v);
			D.push(d+1);
		}
	}
}

void Recommend(){
	int i;
	FOR(i,N)
		BFS(W[i],i);
}

int main(){
	//ifstream cin("Club.h");
	for(int cnt=1 ; true ; cnt++){
		W.clear();
		U.clear();
		Adj.clear();
		int i,j;
		cin >> T >> N;
		if(T==0)
			return 0;
		map<string,int> u;
		map<string,vector<string> > m;
		vector<string> w;
		string str,s1,s2;

		cin.ignore(100,'\n');
		FOR(i,N){
			getline(cin,str);
			Modify(str);
			s1 = str.substr(0,str.find(' '));
			str = str.substr(str.find(' ')+1);
			u[s1] = 0;
			w.push_back(s1);
			while(str != ""){
				s2 = str.substr(0,str.find(' '));
				str = str.substr(str.find(' ')+1);
				m[s1].push_back(s2);
				u[s2] = 0;
			}
		}

		map<string,int>::iterator it;
		i=0;
		REPI(it,u){
			u[it->first] = i++;
			U.push_back(it->first);
		}
		Adj.resize(T);
		FOR(i,N){
			sort(All(m[w[i]]));
			W.push_back(u[w[i]]);
			FOR(j,m[w[i]].size())
				Adj[u[w[i]]].push_back(u[ m[w[i]][j] ]);
		}

		Ret.clear();
		Ret.resize(N);
		sort(All(W));
		Recommend();
		cout<<"--- CASE "<<cnt<<endl;
		FOR(i,N){
			if(Ret[i].empty())
				continue;
			cout<<U[W[i]];
			sort(All(Ret[i]));
			FOR(j,Ret[i].size())
				cout<<" "<<U[Ret[i][j]];
			cout<<endl;
		}
	}
}