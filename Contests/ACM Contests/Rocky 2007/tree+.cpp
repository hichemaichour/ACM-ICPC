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
	int cnt;
	for(cnt=1 ; true ; cnt++){
		int i,j,k;
		string str;

		cin >> str;
		if(str[0] == '#') return 0;
		int max1=0,max2=0;

		int cnt1=0,cnt2=0;
		stack<int> S;
		S.push(0);
		FOR(i,str.size()){
			if(str[i]=='d'){
				cnt1 += 1;
				cnt2 = S.top() + 1;
				S.push(cnt2);
			}
			else{
				cnt1 -= 1;
				S.pop();

				k = S.top();
				S.pop();
				S.push(k+1);
			}
			max1 = max(max1,cnt1);
			max2 = max(max2,cnt2);
		}

		cout <<"Tree "<< cnt <<": "<< max1 <<" => "<< max2 << endl;
	}
}