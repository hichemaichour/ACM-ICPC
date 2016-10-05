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

const double EPS = 1e-3;
const int INF = 1<<29;
const double PI = acos(-1);

double m,n,t,c;
double P[5];

void Cal(){
	P[1]=0; P[2]=0; P[3]=0; P[4]=0;

	if(m == 1){
		P[2] = c*t * (n-1);
		P[2]/= (t*t*n);
		P[1] = 1 - P[2];
		return;
	}

	P[1]+= (2*t - c)*(2*t - c); // corner
	P[1]+= ((n-2)*(t-c))*(2*t - c) + ((m-2)*(t-c))*(2*t - c); // sides
	P[1]+= (t-c)*(t-c) * (m-2)*(n-2); // inner
	P[1]/= (t*t*m*n);

	P[2]+= (c)*(2*t - c) * ((m-1)+(n-1)); // sides
	P[2]+= (t-c)*(c) * (((n-2)*(m-1)) + ((m-1)*(n-2))); // inner
	P[2]/= (t*t*m*n);

	P[4]+= (PI*c*c/4) * ((m-1)*(n-1));
	P[4]/= (t*t*m*n);

	P[3]+= (c*c) * ((m-1)*(n-1));
	P[3]/= (t*t*m*n);
	P[3]-= P[4];

	P[2] = 1 - P[1] - P[3] - P[4];
}

int main(){
	ifstream cin("input.txt");
	int T;
	cin >> T;
	for(int cnt=1 ; cnt<=T ; cnt++){
		cin >> m>>n >> t >> c;
		if(m>n)
			swap(m,n);

		char str1[100],str2[100],str3[100],str4[100];
		Cal();
		sprintf(str1,"%.4f%%",P[1]*100);
		sprintf(str2,"%.4f%%",P[2]*100);
		sprintf(str3,"%.4f%%",P[3]*100);
		sprintf(str4,"%.4f%%",P[4]*100);

		cout <<"Case "<<cnt<<":"<<endl;
		cout <<"Probability of covering 1 tile  = " << str1 << endl;
		cout <<"Probability of covering 2 tiles = " << str2 << endl;
		cout <<"Probability of covering 3 tiles = " << str3 << endl;
		cout <<"Probability of covering 4 tiles = " << str4 << endl;

		if(cnt != T) cout << endl;
	}
}