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

#define REP(i, a, b) 	for (i=(int)a ; i<=(int)b ; i++)
#define REPD(i, a, b)	for (i=(int)a ; i>=(int)b ; i--)
#define REPI(i, v)		for (i=v.begin() ; i!=v.end() ; i++)
#define FOR(i, n)		REP (i, 0, n-1)
#define FORD(i, n)		REPD(i, n-1, 0)

#define All(v)			v.begin(),v.end()
#define Resize(v,N)		v.clear(); v.resize(N);

#define IsIn(v,e)		(find(All(v),e) != v.end())
#define Remove(v,e)		v.resize( remove(All(v),e) - v.begin() )

#define VI				vector<int>
#define VVI				vector<VI>

#define x				first
#define y				second
#define II				pair<int,int>
#define VII				vector<II>
#define VVII			vector<VII>

#define VS				vector<string>
#define VVS				vector<VS>

int main(){
	int n;
	cin >> n;
	while(n--){
		int i,j,k;
		string str;
		cin >> str;
		int cnt = 1;
		char c = str[0];
		REP(i,1,str.size()-1){
			if(str[i] != c){
				cout << cnt << c;
				c = str[i];
				cnt = 1;
			}
			else{
				cnt++;
			}
		}
		cout << cnt << c << endl;
	}
}