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

#define PB					push_back
#define MP					make_pair

#define PQ					priority_queue

#define IsIn(v,e)			(find(All(v),e) != v.end())
#define Remove(v,e)			v.resize( remove(ALL(v),e) - v.begin() )


typedef long long LL;
typedef long double LD;
typedef vector<int> VI;
typedef vector<VI> VVI;
typedef vector<bool> VB;
typedef vector<VB> VVB;
typedef vector<double> VD;
typedef vector<VD> VVD;
typedef pair<int, int> II;
typedef vector<II> VII;
typedef vector<VII> VVII;
typedef vector<string> VS;
typedef vector<VS> VVS;

int N;
double best;
VD P(26);
VI POS;
VI ret;
VI V;

void Rec(int pos=0 , int n=1 , int k=0 , double sum=0) {
    if(sum > best)
        return;
    if(pos == 26 && k == N-1){
       ret = POS;
       best = sum;
    }
    if(pos == 26 || k==N)
        return;

    if(n <= 8){
        POS[pos] = k;
        Rec(pos+1 , n+1 , k , sum + n*P[pos]);
    }
    POS[pos] = k+1;
    Rec(pos+1 , 2 , k+1 , sum + P[pos]);
}

int main() {
    ifstream cin("input.txt");
    int T;
    cin >> T;
    for (int cnt = 1; cnt <= T; cnt++) {
        int i, j, k;
        POS.clear();
        POS.resize(26,-1);
        cin >> N;
        FOR(i, 26)
        cin >> P[i];

        best = 1e11;
        Rec();
        cout << cnt <<" "<< setiosflags(ios::fixed) << setprecision(3) << best/100 <<" ";
        
        j = 0;
        FOR(i,ret.size()){
            if(ret[i] == j)
                cout << (char)('A' + i);
            else{
                j++;
                cout << ' ' << (char)('A' + i);
            }
        }
        cout << endl;
    }
}