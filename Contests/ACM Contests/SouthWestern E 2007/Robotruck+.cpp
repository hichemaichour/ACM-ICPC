#include <iostream>
#include <fstream>
#include <vector>

#define FOR(i,N)    for(i=0 ; i<(int)N ; i++)
#define REP(i,a,b)    for(i=a ; i<=b ; i++)

#define II pair<int,int>
#define VII vector<II>
#define VVII vector<VII>

using namespace std;

int N;
int C;
VVII V;
vector<int> v;

int main() {
    ifstream cin("input.txt");
    int T;
    cin >> T;
    bool b = false;
    while (T--) {
        int i, j, k;
        V.clear();
        v.clear();
        if (b)
            cout << endl;
        b = true;

        cin >> C >> N;
        V.resize(N + 1);
        v.resize(N + 1, 1e6);
        int x0, y0, x1, y1, c;
        x0 = 0;
        y0 = 0;
        V[0].push_back(II(0, 0));

        REP(i, 1, N) {
            cin >> x1 >> y1 >> c;

            FOR(j, V[i - 1].size()) {
                pair<int,int> p;
                if (V[i - 1][j].first == 0) {
                    p = V[i-1][j];
                    V[i].push_back(II(0,p.second + x1+x1 + y1+y1));
                    p.first += c;
                    p.second += abs(x1) + abs(y1);
                    V[i].push_back(p);
                }
                else {
                    p = V[i - 1][j];
                    if(V[i][0].second > p.second + x1+x1 + y1+y1)
                        V[i][0].second = p.second + x1+x1 + y1+y1;
                    p.first += c;
                    int d = abs(x1 - x0) + abs(y1 - y0);
                    p.second += d;
                    if(p.first <= C)
                        V[i].push_back(p);
                }
            }
            x0 = x1;
            y0 = y1;
        }
        cout << V[N][0].second << endl;
    }
}