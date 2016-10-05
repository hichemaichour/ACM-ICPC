#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <vector>
#include <map>

using namespace std;

#define FOR(i,n) for(i = 0; i < (int)n; i++)
#define REP(i, a, b) for (i = (int)a; i <= (int)b; i++)
#define MS map<string, int>
#define VI vector<int>
#define VVI vector<VI>
#define II pair<int, int>
#define VII vector<II>
#define All(v) v.begin(),v.end()
#define St pair<int,II>
#define x second.first
#define y second.second

using namespace std;

int N;
vector<string> V;
VVI G;
VVI Adj;
VVI T_Adj;
VI t;

int Dist(int u,int v){
    int sum = 0;
    int i,j;
    FOR(i,V[u].size()){
        int n = min(V[u][i],V[v][i]);
        int m = max(V[u][i],V[v][i]);
        sum += min( m-n , n+10-m);
    }
    return sum;
}

int Find(int u){
	int i;
	VI V;
	while(t[u] != u){ // t -> VI
		V.push_back(u);
		u = t[u];
	}
	FOR(i,V.size())
		t[V[i]] = u;
	return u;
}

int MST(){
	int i,j,k;
	int u,v;

	t.resize(N);
	FOR(i,N)
		t[i] = i;

	vector<St> V; // St -> pair<weight , pair<u,v>>
	FOR(i,N){
		FOR(j,Adj[i].size()){
			k = Adj[i][j];
			if(k>i)
				V.push_back(St(G[i][k] , II(i,k)));
		}
	}
	sort(All(V));

	int ret = 0;
	int cnt = 1;
        T_Adj.clear(); T_Adj.resize(N);
	FOR(i,V.size()){
		if(cnt == N)
			break;
		u = V[i].x; v = V[i].y;
		j = Find(u); k = Find(v);
		if(j != k){
			t[k] = j;
			cnt++;
			ret += G[u][v];
			T_Adj[u].push_back(v);
			T_Adj[v].push_back(u);
		}
	}
	return ret;
}

int main() {
    ifstream cin("input.txt");
    int T;
    cin >> T;
    while(T--){
        int i,j,k;
        cin >> N;
        V.clear(); V.resize(N);
        VI Self(N);
        FOR(i,N)
            cin >> V[i];
        G.clear(); G.resize(N,VI(N));
        Adj.clear(); Adj.resize(N);
        FOR(i,N)
            FOR(j,N)
                if(j!=i)
                    Adj[i].push_back(j);
        FOR(i,N){
            REP(j,i+1,N-1){
                G[i][j] = Dist(i,j);
                G[j][i] = G[i][j];
            }
        }
        FOR(i,N){
            k = 0;
            FOR(j,V[i].size()){
                k += min(V[i][j]-'0','0'-V[i][j]+10);
            }
            Self[i] = k;
        }

        int out = MST() + *min_element(All(Self));
        cout << out << endl;
    }
    return 0;
}

