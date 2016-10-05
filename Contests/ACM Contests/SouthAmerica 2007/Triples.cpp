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
#define REPI(i, v)			for (i=v.begin() ; i!=v.end() ; i++)
#define FOR(i, n)			REP (i, 0, n-1)
#define FORD(i, n)			REPD(i, n-1, 0)

#define All(v)				v.begin(),v.end()
#define Resize(v,N)			v.clear(); v.resize(N);

#define PB					push_back
#define MP					make_pair

#define PQ					priority_queue

#define IsIn(v,e)			(find(All(v),e) != v.end())
#define Remove(v,e)			v.resize( remove(All(v),e) - v.begin() )


typedef long long			LL;
typedef long double			LD;
typedef pair<int, int>		II;
typedef vector<int>			VI;
typedef vector<VI>			VVI;
typedef vector<bool>		VB;
typedef vector<VB>			VVB;
typedef vector<double>		VD;
typedef vector<VD>			VVD;
typedef vector<LL>			VLL;
typedef vector<VLL>			VVLL;
typedef vector<LD>			VLD;
typedef vector<VLD>			VVLD;
typedef vector<II>			VII;
typedef vector<VII>			VVII;
typedef vector<string>		VS;
typedef vector<VS>			VVS;

map<int,int> p1,p2;

II func(map<int,int>& m){
	II ret = II(0,0);
	map<int,int>::iterator i,j,k;
	REPI(i,m){
		while(i->second >= 3){
			i->second -= 3;
			ret.first++;
		}
	}

	map<int,int> buf = m;
	m.clear();
	
	REPI(i,buf)
		if(i->second != 0)
			m[i->first] = i->second;

	return ret;
}

int main(){
	ifstream cin("I.h");
	while(true){
		p1.clear();
		p2.clear();

		int i,j;
		int N;
		cin >> N;
		if(N==0)
			return 0;

		FOR(i,N){
			cin >> j;
			if(i%2 == 0)
				p1[j]++;
			else
				p2[j]++;
		}

		II P1 = func(p1);
		II P2 = func(p2);

		if(P1 == P2)
			cout << 0 << endl;
		else if(P1 > P2)
			cout << 1 << endl;
		else
			cout << 2 << endl;
	}
}