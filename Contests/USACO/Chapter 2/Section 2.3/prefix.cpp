/*
ID: b0002141
PROG: prefix
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

VS words;
string STR;
VI dp;

int DP(){
	int ans;
	queue<int> Q;
	VI done(STR.size()+1,false);

	ans = 0;
	Q.push(0);
	done.front() = true;
	while(!Q.empty()){
		int pos = Q.front(); Q.pop();
		ans = max(ans,pos);
		if(pos == STR.size())
			continue;

		int i;
		FOR(i,words.size()){
			int n = words[i].size();
			if(words[i] == STR.substr(pos,n) && !done[pos+n]){
				Q.push(pos+n);
				done[pos+n] = true;
			}
		}
	}
	return ans;
}

int main(){
	//ifstream cin("input.txt");
	ifstream cin("prefix.in");
	ofstream cout("prefix.out");
	
	string str;
	while(cin >> str && str != ".")
		words.push_back(str);
	STR = "";
	while(cin >> str)
		STR += str;

	dp.clear(); dp.resize(STR.size(),-1);
	cout << DP() << endl;
}