#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <map>
#include <cmath>

using namespace std;

#define FOR(i,n) for(i = 0; i < (int)n; i++)
#define REP(i, a, b) for (i = (int)a; i <= (int)b; i++)
#define MS map<string, int>
#define VI vector<int>
#define II pair<int, int>
#define VII vector<II>
#define All(v) v.begin(),v.end()

int N;
vector<string> Name;
VII V;

int main() {
    int T;
    cin >> T;
    while(T--){
        int i,j,k;
        cin >> N;
        Name.clear(); Name.resize(N);
        V.clear(); V.resize(N);
        FOR(i,N)
            cin >> Name[i] >> V[i].first >> V[i].second;
        int Q,n;
        cin >> Q;
        FOR(k,Q){
            cin >> n;
            j = -1;
            FOR(i,N){
                if(n<V[i].first || n>V[i].second)
                    continue;
                if(j != -1){
                    j=-1;
                    break;
                }
                j = i;
            }
            if(j==-1)
                cout <<"UNDETERMINED"<<endl;
            else
                cout << Name[j] << endl;
        }
        if(T)
            cout << endl;
    }
    return 0;
}

