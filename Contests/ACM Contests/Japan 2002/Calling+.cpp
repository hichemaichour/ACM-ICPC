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

#define x			first
#define y			second
#define II			pair<long long,long long>
#define VII			vector<II>
#define VVII			vector<VII>

#define St pair<long long,II>
#define Size 100010

vector<St> V;
VI P;
bitset<Size+10> IsP;

void Sieve(){
    long long i,j;
    P.clear();
    IsP.set(); // everything 1
    IsP.set(0,false); IsP.set(1,false);
    REP(i,2,Size-1){
        if(!IsP.test(i))
            continue;
        for(j=i*i ; j<Size ; j+=i)
            IsP.set(j,false);
        P.push_back(i); // P -> VI (all primes)
    }
}

void init(){
    int i,j,k;
    Sieve();

    V.clear();
    FOR(i,P.size()){
        REP(j,i,P.size()-1){
            if(P[i]*P[j] > Size)
                break;
            V.push_back(St(P[i]*P[j] , II(P[i],P[j])));
        }
    }

    sort(All(V));
}

#define EPS 1e-9

int main(){
    ifstream cin("input.txt");
    init();
    while(true){
        int i,j,k;
        int m;
        double a,b;
        cin >> m >> a >> b;
        if(m==0)
            return 0;
        k = lower_bound(All(V),St(m,II(Size,Size))) - V.begin();
        k--;
        REPD(i,k,0){
            double p = V[i].second.first;
            double q = V[i].second.second;
            if((a/b) < (p/q + EPS))
                break;
        }
        if(i!=-1){
            cout << V[i].second.first <<" "<< V[i].second.second << endl;
        }
    }
}