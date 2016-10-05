/*
ID: b0002141
PROG: clocks
LANG: C++
*/
#include <fstream>

using namespace std;

const int with [10] [5 ]={{},{ 1,2,4,5}, {1,2,3}, {2,3,5,6}, {1,4,7}, {2,4,5,6,8}, {3,6,9}, {4,5,7,8}, {7,8,9}, {5,6,8,9}};
int t [10], ans_min = 30, ans [30], way [30] = {1}, use [10];

void dfs (int);
bool check ();
void work (int);

int main () {
    ifstream fin ("clocks.in");
    ofstream fout ("clocks.out");
    for (int i = 1; i <= 9; i++) {
        fin>> t [i];
        t[i] %= 12;
    }
    dfs (1);
    for (int i = 1; i <ans_min; i++) fout <<ans[i] <<' ';
    fout <<ans [ans_min] <<endl;
    fin.close ();
    fout.close ();
    return 0;
}

void dfs (int cur) {
    if (cur-1 >= ans_min) return;
    if (check ()) {
        ans_min = cur-1;
        for (int i = 1; i <cur; i++) ans [i] = way [i];
        return;
    }
    for (int i = way[cur-1]; i <= 9; i++) {
        if (use [i]>= 3) continue;
        work(i);
        use[i]++;
        way[cur] = i;
        dfs(cur+1);
        for (int j = 1; j <= 3; j++) work(i);
        use[i]--;
    }
}

bool check () {
    for (int i = 1; i <= 9; i++) if (t[i]!= 0) return false;
    return true;
}

void work (int k) {
    for (int i = 0; i <= 4 & & with[k][i]!= 0; i++) t [with[k][i]] = (t [with[k][i]] +3) % 12;
}

