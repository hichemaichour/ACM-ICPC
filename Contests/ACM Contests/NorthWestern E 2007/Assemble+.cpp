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
typedef pair<int, int>		II;
typedef vector<II>			VII;
typedef vector<VII>			VVII;
typedef vector<string>		VS;
typedef vector<VS>			VVS;

#define Q first
#define P second

VVII v;
int MaxQ;
int MinQ;

bool func(II p1, II p2){
	if(p1.Q != p2.Q)
		return p1.Q > p2.Q;
	return p1.P < p2.P;
}

void pre(){
	MinQ = 0;
	MaxQ = 1000000000;
	int i,j;
	FOR(i,v.size()){
		VII V = v[i];
		if(i == 80)
			i = 80;
		v[i].clear();
		sort(All(V),func);
		v[i].push_back(V.front());
		REP(j,1,V.size()-1)
			if(V[j].P < v[i].back().P)
				v[i].push_back(V[j]);
		sort(All(v[i]));
	}
}

int BS(int b){
	int hi = MaxQ;
	int lo = MinQ;
	while(lo!=hi){
		int mid = (lo+hi)/2 + 1;

		int sum=0;
		for(int i=0 ; i<v.size() ; i++){
			if(lower_bound(All(v[i]),II(mid,0)) == v[i].end()){
				sum = b+1;
				break;
			}
			sum += lower_bound(All(v[i]),II(mid,0))->P;
		}

		if(sum<=b)
			lo = mid;
		else
			hi = mid-1;
	}
	return lo;
}

int main(){
	//ifstream cin("in.h");
	int T;
	cin>>T;
	while(T--){
		v.clear();
		int i;
		map<string,int> m;
		string str,buf;
		II d;
		long long n,b;
		cin>>n>>b;
		int cnt = 0;
		for(i=0 ; i<n ; i++){
			cin>>str>>buf>>d.P>>d.Q;
			if(m[str] == 0){
				v.push_back(VII());
				cnt++;
				m[str]=cnt;
			}
			v[m[str]-1].push_back(d);
		}

		
		pre();

		cout<<BS(b)<<endl;
	}
}