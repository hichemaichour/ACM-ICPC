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

typedef pair<int,II>		Data;

#define y first
#define x1 second.first
#define x2 second.second

#define X first
#define Y second

const double EPS = 1e-9;

vector<Data> Ret;
VII Po;

void func(){
	int i;
	map<int,int> m;
	Ret.clear();
	FOR(i,Po.size()-1){
		if(Po[i].Y == Po[i+1].Y)
			continue;
		double L = ((Po[i+1].X-Po[i].X)*1.0) / (Po[i+1].Y-Po[i].Y);
		double D = Po[i].X - L*Po[i].Y;
		int j,k;
		if(Po[i].Y < Po[i+1].Y){
			REP(j,Po[i].Y+1,Po[i+1].Y){
				k = ceil(L*j + D + EPS);
				if(m.find(j) != m.end() && k <= m[j])
					Ret.push_back( Data(j , II(k,m[j])) );
				else
					m[j] = k;
			}
		}
		else{
			REPD(j,Po[i].Y-1,Po[i+1].Y){
				k = floor(L*j + D - EPS);
				if(m.find(j) != m.end() && m[j] <= k)
					Ret.push_back( Data(j , II(m[j],k)) );
				else
					m[j] = k;
			}
		}
	}
}

int main(){
	//ifstream cin("Interior.h");
	int P;
	cin>>P;
	int cnt;
	FOR(cnt,P){
		int i;
		Po.clear();

		int buf,N;
		cin >> buf >> N;
		Po.resize(N);
		FOR(i,N)
			cin >> Po[i].X >> Po[i].Y;
		Po.push_back(Po.front());

		func();

		sort(All(Ret),greater<Data>());
		cout << buf <<" "<< Ret.size()<<endl;
		FOR(i,Ret.size())
			cout << Ret[i].y <<" "<< Ret[i].x1 <<" "<< Ret[i].x2<<endl;
	}
}