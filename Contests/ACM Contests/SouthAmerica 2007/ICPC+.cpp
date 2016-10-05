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

#define IsIn(v,e)			(find(All(v),e) != v.end())
#define Remove(v,e)			v.resize( remove(All(v),e) - v.begin() )

#define VI					vector<int>
#define VVI					vector<VI>

#define x					first
#define y					second
#define II					pair<int,int>
#define VII					vector<II>
#define VVII				vector<VII>

#define St					pair<int,II>
#define s					first
#define t					second.first
#define p					second.second

const int Inf = 1e7;
int N,M;
int outL,outH;
vector<vector<St> > V;
VI index;

int main(){
	ifstream cin("I.h");
	for(int CNT=1 ; true ; CNT++){
		if(CNT == 117)
			CNT = 117;
		int i,j,k;
		cin >> N >> M;
		if(N==0)
			return 0;

		outL = 1;
		outH = Inf;
		V.clear();
		index.clear();
		V.resize(10000);

		cin.ignore(100,'\n');
		FOR(i,N){
			St buf;
			int cnt = 0;
			FOR(j,M){
				k = 0;
				while(cin.peek() != '/'){
					k *= 10;
					k += cin.get() - '0';
				}
				cin.get();

				if(cin.peek() != '-'){
					buf.p += k-1;
					cin >> k;
					buf.t += k;
					cnt++;
				}
				while(!isdigit(cin.peek()) && j!=M-1)
					cin.get();
			}
			buf.s += buf.t + buf.p*20;
			cin.ignore(100,'\n');
			if(cnt != 0){
				V[cnt].push_back(buf);
				index.push_back(cnt);
			}
		}

		sort(All(index));
		index.resize(unique(All(index)) - index.begin());

		FOR(i,index.size()){
			V[i] = V[index[i]];
			sort(All(V[i]));
		}
		V.resize(index.size());

		FOR(i,index.size()){
			k = i;
			FOR(j,V[k].size()-1){
				if(V[k][j].p == V[k][j+1].p)
					continue;
				int n = -1*(V[k][j].t - V[k][j+1].t);
				int d = V[k][j].p - V[k][j+1].p;
				if(n/d < 1)
					continue;
				else if(n%d == 0 && n/d == 20){
					outL = 20;
					outH = 20;
				}
				
				else if(n/d >= 20){
					if(n%d)
						outH = min(outH,n/d);
					else
						outH = min(outH,n/d - 1);
				}
				else
					outL = max(outL , n/d + 1);
			}
		}

		cout << outL <<" ";
		if(outH == Inf)
			cout <<"*"<<endl;
		else
			cout << outH << endl;
	}
}