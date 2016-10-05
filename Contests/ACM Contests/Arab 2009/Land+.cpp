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

const int Inf = 1e7;		// Infinity
const int H = 0;			// Horizantal Direction
const int V = 1;			// Vertical Direction
int N,K;					// # of Cities & # of Children
VVI C(2);					// Cities

double A,B;					// Output

int gcd(int a,int b) {
	if (a%b==0) 
		return b; 
	else 
		return gcd(b,a%b);
}


void Rec(int dir , int pos=1 , int c=0 , int a=0){
	int i,j,k;
	int M = C[dir].size();
	int sum;
	int b = K*K;

	if( (a*1.0)/b > (A*1.0)/B ) // Higher than wht we already got
		return;

	else if(c == K){ // Base Case
		if( (a*1.0)/b < (A*1.0)/B ){
			A = a/gcd(a,b);
			B = b/gcd(a,b);
		}
		return;
	}

	else if(pos >= M){ // Out of cities
		k = N;
		Rec(dir,pos,c+1,a+k);
	}

	else if(c == K-1){ // Last Child
		sum = C[dir][M-1] - C[dir][pos-1];
		k = abs(sum*K - N);
		Rec(dir,M,c+1,a+k);
	}

	else {
		j = (N+K-1)/K + C[dir][pos-1];
		i = lower_bound(All(C[dir]),j) - C[dir].begin();

		i--;

		if(N%K!=0 || !binary_search(All(C[dir]),j)){
			sum = C[dir][i] - C[dir][pos-1];
			k = abs(sum*K - N);
			Rec(dir,i+1,c+1,a+k);
		}

		if(i+1 == M)
			return;

		sum = C[dir][i+1] - C[dir][pos-1];
		k = abs(sum*K - N);
		Rec(dir,i+2,c+1,a+k);

		/*if(N%K==0 && binary_search(All(C[dir]),j) && i+2<M){
			sum = C[dir][i+2] - C[dir][pos-1];
			k = abs(sum*K - N);
			Rec(dir,i+3,c+1,a+k);
		}*/
	}
}

int main(){
	ifstream cin("I.h");
	for(int cnt=1 ; true ; cnt++){
		int i,j,k;

		if(cnt == 8)
			i = 0;

		C[H].clear();
		C[H].push_back(0);
		C[V].clear();
		C[V].push_back(0);
		A = Inf;
		B = 1;

		cin >> N >> K;
		if(N==0)
			return 0;

		VI X(N);
		VI Y(N);
		FOR(i,N)
			cin >> X[i] >> Y[i];
		sort(All(X));
		sort(All(Y));

		j = X[0];
		k = Y[0];
		C[H].push_back(1);
		C[V].push_back(1);
		REP(i,1,N-1){
			if(j == X[i])
				C[H][C[H].size()-1]++;
			else
				C[H].push_back(1);
			if(k == Y[i])
				C[V][C[V].size()-1]++;
			else
				C[V].push_back(1);
			j = X[i];
			k = Y[i];
		}

		partial_sum(All(C[H]),C[H].begin());
		partial_sum(All(C[V]),C[V].begin());

		Rec(H);
		Rec(V);

		cout << cnt <<". "<< A<<"/"<<B <<endl;
	}
}