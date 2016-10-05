/*
ID: b0002141
PROG: preface
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

int N;
int a[] = {1,5,10,50,100,500,1000};
char c[] = "IVXLCDM";
VI ret;

void func(int x){
	int i,j,k;
	for(i=6 ; i>=0 ; i-=2){
		if(x/a[i] == 0) continue;
		if(x/a[i] == 1) ret[i]+=1;
		if(x/a[i] == 2) ret[i]+=2;
		if(x/a[i] == 3) ret[i]+=3;
		if(x/a[i] == 4) {ret[i]+=1; ret[i+1]+=1;}
		if(x/a[i] == 5) ret[i+1]+=1;
		if(x/a[i] == 6) {ret[i]+=1; ret[i+1]+=1;}
		if(x/a[i] == 7) {ret[i]+=2; ret[i+1]+=1;}
		if(x/a[i] == 8) {ret[i]+=3; ret[i+1]+=1;}
		if(x/a[i] == 9) {ret[i]+=1; ret[i+2]+=1;}

		x -= (x/a[i])*a[i];
	}
}

int main(){
	//ifstream cin("input.txt");
	ifstream cin("preface.in");
	ofstream cout("preface.out");
	int i,j,k;

	ret.clear();
	ret.resize(7);
	cin >> N;
	REP(i,1,N) func(i);

	FOR(i,7) if(ret[i]) cout << c[i] << " " << ret[i] << endl;
}