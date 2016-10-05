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

#define REP(i, a, b)                    for (i=(int)a ; i<=(int)b ; i++)
#define REPD(i, a, b)                   for (i=(int)a ; i>=(int)b ; i--)
#define REPI(i, v)			for (i=v.begin() ; i!=v.end() ; i++)
#define FOR(i, n)			REP (i, 0, n-1)
#define FORD(i, n)			REPD(i, n-1, 0)

#define All(v)				v.begin(),v.end()
#define Resize(v,N)			v.clear(); v.resize(N);

#define IsIn(v,e)			(find(All(v),e) != v.end())
#define Remove(v,e)			v.resize( remove(All(v),e) - v.begin() )

#define VI				vector<int>
#define VVI				vector<VI>

#define x				first
#define y				second
#define II				pair<int,int>
#define VII				vector<II>
#define VVII                            vector<VII>

#define VS				vector<string>

int S, F; // Price of Single Ticket & Price of Family Ticket
int N; // Number of People
int NP; // Number of Parents
VS people; // Name of People -- N
VI p; // Who is the parent (index in vector P) -- N
VI P; // Parents -- NP
VI NC; // Number of Children -- NP
VI NCP; // Number of Children who are parents -- NP
VI IsP; // Is parents ?? -- N
VVI C; // Children of Each parents -- NP

int NS, NF, T; // Output

struct St{
    int p;
    int nf;
    int ns;
    St(){}
    St(int i,int j,int k){p=i; nf=j; ns=k;}
};

void modify(string& str){
	while(str[str.size()-1] == ' ')
		str.resize(str.size()-1);
}

void DP_T(){
    int i,j,k;
    queue<int> Q;
    vector<pair<St,St> > V(N);
    FOR(i,N){
        if(IsP[i])
            continue;
        V[i].x = St(F,1,0);
        V[i].y = St(S,0,1);
    }
    FOR(i,NP)
        if(!NCP[i])
            Q.push(i);
    while(!Q.empty()){
        int up = Q.front(); Q.pop();
        int u = P[up];
		if(p[u] != -1)
			NCP[p[u]]--;

        V[u].x = St(F,1,0);
        V[u].y = St(S,0,1);
        FOR(i,C[up].size()){
            int v = C[up][i];
            if(V[v].x.p < V[v].y.p - S){
                V[u].x.p += V[v].x.p;
                V[u].x.nf += V[v].x.nf;
                V[u].x.ns += V[v].x.ns;
            }
            else if(V[v].x.p > V[v].y.p - S){
                V[u].x.p += V[v].y.p - S;
                V[u].x.nf += V[v].y.nf;
                V[u].x.ns += V[v].y.ns - 1;
            }
            else if(V[v].x.nf+V[v].x.ns <= V[v].y.nf+V[v].y.ns){
                V[u].x.p += V[v].x.p;
                V[u].x.nf += V[v].x.nf;
                V[u].x.ns += V[v].x.ns;
            }
            else{
                V[u].x.p += V[v].y.p - S;
                V[u].x.nf += V[v].y.nf;
                V[u].x.ns += V[v].y.ns - 1;
            }

            if(V[v].x.p < V[v].y.p){
                V[u].y.p += V[v].x.p;
                V[u].y.nf += V[v].x.nf;
                V[u].y.ns += V[v].x.ns;
            }
            else if(V[v].x.p > V[v].y.p){
                V[u].y.p += V[v].y.p;
                V[u].y.nf += V[v].y.nf;
                V[u].y.ns += V[v].y.ns;
            }
            else if(V[v].x.nf+V[v].x.ns <= V[v].y.nf+V[v].y.ns){
                V[u].y.p += V[v].x.p;
                V[u].y.nf += V[v].x.nf;
                V[u].y.ns += V[v].x.ns;
            }
            else{
                V[u].y.p += V[v].y.p;
                V[u].y.nf += V[v].y.nf;
                V[u].y.ns += V[v].y.ns;
            }
        }

        if(p[u] != -1 && NCP[p[u]] == 0)
            Q.push(p[u]);
    }

    St ret = St(0,0,0);
    FOR(i,N){
        if (p[i] != -1)
            continue;
        if (V[i].x.p < V[i].y.p) {
            ret.p += V[i].x.p;
            ret.nf += V[i].x.nf;
            ret.ns += V[i].x.ns;
        } else if (V[i].x.p > V[i].y.p) {
            ret.p += V[i].y.p;
            ret.nf += V[i].y.nf;
            ret.ns += V[i].y.ns;
        } else if (V[i].x.nf + V[i].x.ns <= V[i].y.nf + V[i].y.ns) {
            ret.p += V[i].x.p;
            ret.nf += V[i].x.nf;
            ret.ns += V[i].x.ns;
        } else {
            ret.p += V[i].y.p;
            ret.nf += V[i].y.nf;
            ret.ns += V[i].y.ns;
        }
    }
    T = ret.p;
    NS = ret.ns;
    NF = ret.nf;
}

int main() {
    ifstream cin("input.txt");
    for (int cnt = 1; true; cnt++) {
        int i, j, k;
        NS = 0;
        NF = 0;
        people.clear();

        cin >> S >> F;
        if (S == 0)
            return 0;

        map<string, string> c2p;
        map<string, int> str2int;
        VS StrP;

        cin.ignore(100, '\n');
        while (!isdigit(cin.peek())) {
            string str;
            getline(cin, str);
            modify(str);

            VS v;
            str.push_back(' ');
            while (str != "") {
                v.push_back(str.substr(0, str.find(' ')));
                str = str.substr(str.find(' ') + 1);
            }

            people.push_back(v.front());
            StrP.push_back(v.front());

            REP(i, 1, v.size() - 1) {
                c2p[v[i]] = v[0];
                people.push_back(v[i]);
            }
        }

        // Get all the people
        sort(All(people));
        people.resize(unique(All(people)) - people.begin());
        N = people.size();
        NP = StrP.size();

        // Change from string to int
        FOR(i, N)
        str2int[people[i]] = i;

        // Get Ready to build the graph
        p.clear();
        p.resize(N, -1);
        IsP.clear();
        IsP.resize(N);
        P.clear();
        P.resize(NP);
        C.clear();
        C.resize(NP);
        NC.clear();
        NC.resize(NP);
        NCP.clear();
        NCP.resize(NP);

        // Change Parents from string to int
        FOR(i, NP)
        P[i] = str2int[StrP[i]];
        sort(All(P));

        // Get the index of each Parents in P
        map<int, int> m;

        FOR(i, NP) {
            IsP[P[i]] = 1;
            m[P[i]] = i;
        }

        map<string, string>::iterator it;

        REPI(it, c2p) {
            p[str2int[it->x]] = m[str2int[it->y]];
            NC[m[str2int[it->y]]]++;
            if (IsP[str2int[it->x]])
                NCP[m[str2int[it->y]]]++;
            C[m[str2int[it->y]]].push_back(str2int[it->x]);
        }

        DP_T(); // Find the solution

        cout << cnt << ". " << NS << " " << NF << " " << T << endl;
    }
}
