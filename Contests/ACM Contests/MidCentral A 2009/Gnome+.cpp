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

#define Y "Ordered"
#define N "Unordered"

int main(){
	ifstream cin("Gnome.h");
	int T,i;
	cin >> T;
	VI v(T);
	cout << "Gnomes:" <<endl;
	FOR(i,T){
		int j;
		FOR(j,T)
			cin >> v[j];

		if(T==1){
			cout << Y <<endl;
			continue;
		}

		bool flg = true;
		if(v[0] > v[1]){
			FOR(j,T-1)
				if(v[j] < v[j+1])
					flg = false;
		}
		else{
			FOR(j,T-1)
				if(v[j] > v[j+1])
					flg = false;
		}

		if(flg)
			cout << Y << endl;
		else
			cout << N << endl;

	}
}