/*
ID: b0002141
PROG: runround
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

#define VI			vector<long long>
#define VVI			vector<VI>

#define VD			vector<double>
#define VVD			vector<VD>

#define x			first
#define y			second
#define II			pair<int,int>
#define VII			vector<II>
#define VVII		vector<VII>

#define INT			unsigned long long

INT N;
VI done;
VI Done(10);
INT ret;

bool Is(INT M){
	int i,j,k;
	VI V;
	while(M){V.push_back(M%10); M/=10;}
	reverse(All(V));

	done.clear();
	done.resize(V.size());

	int pos=0;
	FOR(i,V.size()){
		if(done[pos]) return false;
		done[pos] = 1;
		pos += V[pos];
		pos %= V.size();
	}
	return pos == 0;
}

int Rec(int lim,int pos=0,INT n=0){
	INT i,j,k;
	if(pos == lim){
		if(Is(n) && n>N){ret=n; return 1;}
		return 0;
	}
	n*=10;
	REP(i,1,9){
		if(Done[i]) continue;
		Done[i]=1;
		if(Rec(lim,pos+1,n+i)) return 1;
		Done[i]=0;
	}
	return 0;
}

void Rec(){
	int i;
	int j=0;
	INT k = N;
	while(k){j++; k/=10;}
	REP(i,j,10){
		if(Rec(i)) return;
	}
}

int main(){
	ifstream cin("input.txt");
	//ifstream cin("runround.in");
	//ofstream cout("runround.out");
	int i,j,k;

	cin >> N;
	Rec();
	cout << ret << endl;

	return 0;
}