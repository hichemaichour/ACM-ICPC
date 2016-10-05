/*
ID: b0002141
PROG: zerosum
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

#define ADD			1
#define SUB			2
#define CON			0

int N;
VI op;
VS ans;

void Rec(int pos=0){
	int i,j,k;
	if(pos == N-1){
		int sum = 0;
		int cop = ADD;
		int psum = 0;

		REP(i,1,N){
			psum = psum*10 + i;
			if(op[i-1] != CON){
				if(cop == ADD)
					sum += psum;
				else
					sum -= psum;
				cop = op[i-1];
				psum = 0;
			}
		}

		if(cop == ADD)
			sum += psum;
		else
			sum -= psum;

		if(sum != 0)
			return;

		string str = "";
		FOR(i,N){
			if(i){
				if(op[i-1] == ADD)
					str += '+';
				else if(op[i-1] == SUB)
					str += '-';
				else
					str += ' ';
			}
			str += '0' + (i+1);
		}
		ans.push_back(str);

		return;
	}

	FOR(i,3){
		op[pos] = i;
		Rec(pos+1);
	}
}

int main(){
	//ifstream cin("input.txt");
	ifstream cin("zerosum.in");
	ofstream cout("zerosum.out");
	int i;
	cin >> N;
	op.resize(N);
	Rec();
	FOR(i,ans.size())
		cout << ans[i] << endl;
}