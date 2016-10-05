/*
ID: b0002141
PROG: fracdec
LANG: C++
*/

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
#define REPI(i, v)		for (i=v.begin() ; i!=v.end() ; i++)
#define FOR(i, n)		REP (i, 0, n-1)
#define FORD(i, n)		REPD(i, n-1, 0)

#define All(v)			v.begin(),v.end()
#define Resize(v,N)		v.clear(); v.resize(N);

#define IsIn(v,e)		(find(All(v),e) != v.end())
#define Remove(v,e)		v.resize( remove(All(v),e) - v.begin() )

#define VI			vector<int>
#define VVI			vector<VI>

#define VD			vector<double>
#define VVD			vector<VD>

#define x			first
#define y			second
#define II			pair<int,int>
#define VII			vector<II>
#define VVII		vector<VII>

#define VS			vector<string>
#define VC			vector<char>

int main(){
	//ifstream cin("input.txt");
	ifstream cin("fracdec.in");
	ofstream cout("fracdec.out");
	int i,j,k;
	int N,D;
	int cnt = 0;

	cin >> N >> D;

	cout << N/D <<".";

	int n;
	char buf[10];
	sprintf(buf,"%d",N/D);
	string Buf = buf;
	n = Buf.size() + 1;

	N = N%D;
	VI V(D,-1);
	VI v;

	k = 0;
	if(N == 0){
		cout << 0;
		cnt++;
	}
	while(N != 0){
		if(V[N] != -1){
			k = V[N];
			break;
		}
		V[N] = v.size();
		N *= 10;
		v.push_back(N/D);
		N %= D;
		k = v.size();
	}

	FOR(i,v.size()){
		if(n%76 == 0)
			cout << endl;
		if(i == k){
			n++;
			cout <<"(";
			if(n%76 == 0)
				cout << endl;
		}
		n++;
		cout << v[i];
	}
	if(k != v.size())
		cout <<")";
	cout << endl;

	return 0;
}