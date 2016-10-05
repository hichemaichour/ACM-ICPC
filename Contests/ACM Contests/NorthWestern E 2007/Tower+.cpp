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

#define PB					push_back
#define MP					make_pair

#define PQ					priority_queue

#define IsIn(v,e)			(find(All(v),e) != v.end())
#define Remove(v,e)			v.resize( remove(ALL(v),e) - v.begin() )


typedef long long			LL;
typedef long double			LD;
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
typedef pair<int, int>		II;
typedef vector<II>			VII;
typedef vector<VII>			VVII;
typedef vector<string>		VS;
typedef vector<VS>			VVS;

LL h,l;
VLL P;
VLL L;
VLL p;

LL func(int i){
	LL j,k;
	if(P[i] == p[L[i]])
		return 0;
	
	j = max(P[i],p[L[i]]) - min(P[i],p[L[i]]);
	k = l - j;

	p[L[i]] = P[i];
	return min(j,k);
}

int main(){
	//ifstream cin("Tower.h");
	int T;
	cin >> T;
	while(T--){
		int i,j,k;
		P.clear();
		L.clear();
		p.clear();

		cin >> h >> l;
		P.resize(h*l);
		L.resize(h*l);
		p.resize(h);

		int Max = 0;
		FOR(i,h){
			FOR(j,l){
				cin >> k;
				if(k==-1)
					continue;
				Max = max(Max,k);
				L[k-1] = i;
				P[k-1] = j;
			}
		}
		P.resize(Max);
		L.resize(Max);

		LL sum = 0;
		FOR(i,Max)
			sum += L[i]*2*10 + func(i)*5;
		cout<<sum<<endl;
	}
}