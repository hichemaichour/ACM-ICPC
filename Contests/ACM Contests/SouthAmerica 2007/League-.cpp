#include <iostream>
#include <fstream>
#include <sstream>

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

#define REP(i, a, b) 		for (i=a ; i<=b ; i++)
#define REPD(i, a, b)		for (i=a ; i>=b ; i--)
#define REPI(i, v)			for (i=v.begin() ; i!=v.end() ; i++)
#define FOR(i, n)			REP (i, 0, n-1)
#define FORD(i, n)			REPD(i, n-1, 0)

#define All(v)				v.begin(),v.end()

#define PB					push_back
#define MP					make_pair

#define PQ					priority_queue

typedef long long			LL;
typedef long double			LD;
typedef vector<int>			VI;
typedef vector<VI>			VVI;
typedef vector<bool>		VB;
typedef vector<VB>			VVB;
typedef vector<double>		VD;
typedef vector<VD>			VVD;
typedef pair<int, int>		II;
typedef vector<II>			VII;
typedef vector<VII>			VVII;

#define Link deque<int>

int H,R;
VVI Adj;
int CN;
vector<set<Link> > s;

bool OK(Link L){
	Link buf(2);
	buf[0] = L.front();
	buf[1] = L.back();
	L.pop_front();
	return (s[2].find(buf)!=s[2].end() && s[CN].find(L)!=s[CN].end());
}

void MaxClique(){
	set<Link>::iterator i;
	int j,k;
	CN = 2;
	while(!s[CN].empty()){
		for(i=s[CN].begin() ; i!=s[CN].end() ; i++){
			Link L = *i;
			k = L.back();
			for(j=0 ; j<Adj[k].size() ; j++){
				L.push_back(Adj[k][j]);
				if(OK(L)){
					s[CN+1].insert(L);
				}
				L.pop_back();
			}
		}

		if(CN !=2 && !s[CN+1].empty()){
			s[CN].clear();
		}
		CN++;
	}
	CN--;
}

bool Can(){
	set<Link>::iterator i;
	int j,k;
	for(i=s[CN].begin() ; i!=s[CN].end() ; i++){
		VB done(H);
		for(j=0 ; j<(*i).size() ; j++)
			done[(*i)[j]]=true;

		bool GD = true;
		for(j=0 ; j<H ; j++){
			if(done[j])
				continue;
			for(k=0 ; k<Adj[j].size() ; k++)
				if(!done[Adj[j][k]])
					GD = false;
		}
		if(GD)
			return true;
	}
	return false;
}

int main(){
	ifstream cin("League.h");
	while(true){
		int i,j,k;
		s.clear();
		cin>>H>>R;
		if(H==0)
			return 0;

		s.clear();
		Adj.clear();

		s.resize(H+5);
		Adj.resize(H);

		for(i=0 ; i<R ; i++){
			cin>>j>>k;
			if(j>k)
				swap(j,k);
			j--;
			k--;
			Adj[j].push_back(k);
			Adj[k].push_back(j);
			Link L(2);
			L[0] = j;
			L[1] = k;
			s[2].insert(L);
		}
		for(i=0 ; i<Adj.size() ; i++)
			sort(All(Adj[i]));

		MaxClique();
		if(Can())
			cout<<"Y"<<endl;
		else
			cout<<"N"<<endl;
	}
}