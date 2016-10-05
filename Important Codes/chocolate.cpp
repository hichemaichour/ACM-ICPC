#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <algorithm>

#define Pair pair<int,int>

using namespace std;

int Q;
int d;
int N;
vector<int> w;
map<int, int> m;
vector<vector<map<int, int> > > v;
vector<vector<int> > e;
vector<vector<int> > eff;
vector<int> c;
vector<int> sum;
vector<int> done;
int sum_c;
int ret;

void DP() {
    int i, j, k;

    v.clear();
    v.resize(Q + d + 1);
    v[0].resize(1);
    for (i = 0; i < N; i++)
        v[0][0][w[i]] = 0;

    for (i = 0; i < N; i++) {
        for (j = w[i]; j <= Q + d; j++) {
            for (k = 0; k < v[j - w[i]].size(); k++) {
                if (v[j - w[i]][k][w[i]] < m[w[i]] && j - w[i] < Q - d) {
                    v[j].push_back(v[j - w[i]][k]);
                    v[j][v[j].size() - 1][w[i]]++;
                }
            }
        }
    }

    e.clear();
    vector<int> buf;
    map<int, int>::iterator it;
    for (i = Q - d; i <= Q + d; i++) {
        for (j = 0; j < v[i].size(); j++) {
            buf.clear();
            for (it = v[i][j].begin(); it != v[i][j].end(); it++)
                buf.push_back(it->second);
            e.push_back(buf);
        }
    }

}

void rec(int i) {
    if (i == e.size())
        return;

    bool flag = true;
    int j;
    while (flag) {
        if (done[i] >= 0) {
            sum_c += c[i];
            ret = max(ret, sum_c);
            rec(i + 1);
            break;
        } else {
            ret = max(ret, sum_c);
            rec(i + 1);
            sum_c++;
            c[i]++;
            for (j = 0; j < eff[i].size(); j++) {
                sum[eff[i][j]] += e[i][eff[i][j]];
                if (sum[eff[i][j]] > m[w[eff[i][j]]])
                    flag = false;
            }
        }
    }

    if (done[i] >= 0) {
        sum_c -= c[i];
    } else {
        for (j = 0; j < eff[i].size(); j++)
            sum[eff[i][j]] -= e[i][eff[i][j]] * c[i];
        sum_c -= c[i];
        c[i] = 0;
    }
}

void LP() {
    int i, j;
    ret = 0;
    sum_c = 0;
    c.clear();
    c.resize(e.size());
    sum.clear();
    sum.resize(w.size());
    eff.clear();
    done.clear();
    eff.resize(e.size());
    done.resize(c.size(), -1);
    for (i = 0; i < e.size(); i++) {
        for (j = 0; j < w.size(); j++) {
            if (e[i][j] != 0) {
                eff[i].push_back(j);

                if (done[i] == -1)
                    done[i] = j;
                else
                    done[i] = -2;
            }
        }
    }

    for (i = 0; i < done.size(); i++) {
        for (j = 0; j < c.size() && done[i] >= 0; j++)
            if (j != i && e[j][done[i]] != 0)
                done[i] = -2;

        if (done[i] >= 0)
            c[i] = m[w[done[i]]] / e[i][done[i]];
    }

    rec(0);
}

int main() {
    ifstream cin("chocolate.in");
    int T;
    cin >> T;
    while (T--) {
        int i, j, k;
        w.clear();
        cin >> Q >> d >> N;
        w.resize(N);
        for (i = 0; i < N; i++) {
            cin >> j >> w[i];
            m[w[i]] = j;
        }
        sort(w.begin(), w.end());

        DP();
        LP();
        cout << ret << endl;
    }
    return 0;
}
