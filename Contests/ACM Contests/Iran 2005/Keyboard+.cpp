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

#define x			first
#define y			second
#define II			pair<int,int>
#define VII			vector<II>
#define VVII			vector<VII>

VI St;
VI En;

int main(){
    ifstream cin("input.txt");
    int cnt;
    int T;
    cin >> T;
    FOR(cnt,T){
        int i,j,k;
        char c;
        int N;
        cin >> N;
        VVI V(26);
        int Min = 1001;
        int Max = -1;
        FOR(i,N){
            cin >> c >> j >> k;
            V[c-'A'].push_back(j);
            V[c-'A'].push_back(k);
            Min = min(Min,j);
            Max = max(Max,k);
        }

        int t = Min-1;
        VI v(26);
        bitset<26> keys;
        keys.reset();
        while(t<=Max){
            FOR(i,26)
                if(v[i] < V[i].size() && V[i][v[i]] == t){
                    keys.flip(i);
                    v[i]++;
                }
            int n = keys.count() - 1;
            if(n >= 0)
                cout << (char)('A'+n);
            t++;
        }
        cout << endl;
    }
}