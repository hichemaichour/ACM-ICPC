#include <iostream>
#include <fstream>
#include <sstream>
#include <stdio.h>

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
#define FOR(i, n)			REP (i, 0, n-1)
#define FORD(i, n)		REPD(i, n-1, 0)

#define All(v)			v.begin(),v.end()
#define Resize(v,N)		v.clear(); v.resize(N);

#define IsIn(v,e)			(find(All(v),e) != v.end())
#define Remove(v,e)		v.resize( remove(All(v),e) - v.begin() )

#define VI				vector<int>
#define VVI				vector<VI>

#define x				first
#define y				second
#define II				pair<int,int>
#define VII				vector<II>
#define VVII			vector<VII>

#define DD				pair<double,double>
#define VDD				vector<DD>
#define VVDD			vector<VDD>

#define VD				vector<double>
#define VVD				vector<VD>

#define St				pair<int,II>
#define NIL				-1

int Hichem;
int N;
int T;
VVI Adj;		// Adjecency of the Graph
VVI G;
VI t;
int NS;
VI pSet;
VI nSet;

void initSet(){
    int i;
    pSet.clear(); nSet.clear();
    pSet.resize(N); nSet.resize(N,1);
    NS = N;
    FOR(i,N)
        pSet[i] = i;
}

int Find(int u){
    if(pSet[u] != u)
        pSet[u] = Find(pSet[u]);
    return pSet[u];
}

bool Union(int u,int v){
	bool ret = false;
	u = Find(u);
	v = Find(v);
	if(u != v){
		nSet[u] += nSet[v];
		nSet[v] = -1;
		NS--;
		ret = true;
	}
	pSet[v] = u;
	return ret;
}


VVI MST_Adj;

int MST(){
	int i,j,k;
	int u,v;

	initSet();

	vector<St> E; // St -> pair<weight , pair<u,v>>
	FOR(i,N){
		FOR(j,Adj[i].size()){
			k = Adj[i][j]; // or k = Adj[i][j].node
			if(k>i)
				E.push_back(St(G[i][k] , II(i,k))); // or Adj[i][j].weight
		}
	}
	sort(All(E));

	int totD = 0;
	MST_Adj.clear(); MST_Adj.resize(N);
	FOR(i,E.size()){
		if(NS == 1)
			break;
		u = E[i].y.x; v = E[i].y.y;
		if(Union(u,v)){
			totD += G[u][v]; // or Adj[u][v].weight
			MST_Adj[u].push_back(v);
			MST_Adj[v].push_back(u);
		}
	}
	return totD;
}

int StoI(string str){
	int i;
	int ret = 0;
	FOR(i,str.size())
		ret = ret*10 + (str[i]-'0');
	return ret;
}

void Modify(string& str){
	int i;
	while(str[str.size()-1] == ' ')
		str.resize(str.size()-1);
	while(str[0] == ' ')
		str = str.substr(1);

	FOR(i,str.size()-1)
		if(str[i]==')' && str[i+1]==')')
			str = str.substr(0,i+1) + ' ' + str.substr(i+1);
	str.push_back(' ');
}

int Build_Graph(string str){
	Modify(str);
	int i,j,k;
	int p = NIL;
	VI P(N);
	int ret = 0;

	VI done(N);

	while(!str.empty()){
		if(ret > Hichem)
			return NIL;
		stringstream s;
		string buf = str.substr(0,str.find(' '));
		if(buf.empty())
			buf = "";
		else if(buf[0] == '('){
			buf = buf.substr(1);
			k = StoI(buf);
			done[k-1] = 1;
			P[k-1] = p;
			if(p != NIL) ret += G[k-1][p];
			p = k-1;
		}
		else if(buf[buf.size()-1] == ')'){
			buf.resize(buf.size()-1);
			if(!buf.empty()){
				k = StoI(buf);
				done[k-1] = 1;
				P[k-1] = p;
				if(p != NIL) ret += G[k-1][p];
			}
			if(p!=-1)
				p = P[p];
		}
		else{
			k = StoI(buf);
			done[k-1] = true;
			P[k-1] = p;
			if(p != NIL) ret += G[k-1][p];
		}
		str = str.substr(str.find(' ')+1);
	}
	bool b = true;
	FOR(i,N) if(!done[i]) b = false;

	if(b)
		return ret;
	return NIL;
}

int main(){
	ifstream cin("input.txt");
	for(int cnt=1 ; true ; cnt++){
		int i,j,k;
		Adj.clear();
		G.clear();

		cin >> N;
		if(N==0)return 0;
		Adj.resize(N);
		G.resize(N,VI(N));
		FOR(i,N){
			REP(j,i+1,N-1){
				cin >> k;
				if(k == 0)
					continue;
				Adj[i].push_back(j);
				Adj[j].push_back(i);
				G[i][j] = k;
				G[j][i] = k;
			}
		}

		Hichem = MST();

		string Tree;
		cin >> T;
		cin.ignore(100,'\n');
		FOR(i,T){
			getline(cin,Tree);

			if(Build_Graph(Tree) == Hichem)
				cout<< cnt <<"."<< i+1 <<" YES"<<endl;
			else
				cout<< cnt <<"."<< i+1 <<" NO"<<endl;
		}
	}
}