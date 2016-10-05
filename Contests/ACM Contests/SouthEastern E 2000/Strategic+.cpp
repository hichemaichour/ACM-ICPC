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

#define NIL -1

VI P;				// Parent
VI NC;				// number of children
VB Not;				// Not in the graph ??
VB Mark;			// In the vertex cover ??
deque<int> L;		// Leafs
int Root;			// Root

void Find_Leafs_and_Root(){
	L.clear();
	int i;
	FOR(i,NC.size()){
		if(NC[i] == 0)
			L.push_back(i);
		if(P[i] == NIL)
			Root = i;
	}
}

int Vertex_Cover(){
	Find_Leafs_and_Root();
	while(!L.empty()){
		int f = L.front(); L.pop_front();
		if(!Not[f]){
			if(!Mark[f] && P[f] == NIL)
				Mark[f] = true;
			else if(!Mark[f] && P[f] != NIL)
				Mark[P[f]] = true;
			Not[f] = true;
			NC[P[f]]--;
			if(P[f] != NIL && P[f] != Root)
				if( NC[P[f]] == 0 )
					L.push_back(P[f]);
		}
	}

	int i;
	int ret=0;
	FOR(i,Mark.size())
		if(Mark[i])
			ret++;
	return ret;
}

int main(){
	//ifstream cin("Strategic.h");
	int N;
	while(cin>>N){
		int i,j,k;
		P.clear();
		NC.clear();
		Not.clear();
		Mark.clear();

		P.resize(N,NIL);
		NC.resize(N);
		Not.resize(N);
		Mark.resize(N);

		FOR(i,N){
			string str;
			cin>>str;
			stringstream s1,s2;
			s1<<str.substr(0,str.find(':'));
			str = str.substr(str.find(':')+2);
			s2<<str.substr(0,str.find(')'));
			int n,M;
			s1>>n;
			s2>>M;
			NC[n] = M;
			FOR(j,M){
				cin >> k;
				P[k] = n;
			}
		}

		cout<<Vertex_Cover()<<endl;
	}
	return 0;
}
