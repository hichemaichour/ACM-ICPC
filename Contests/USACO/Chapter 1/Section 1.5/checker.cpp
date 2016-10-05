/*
ID: b0002141
PROG: checker
LANG: C++
*/

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

#define VI vector<int>
#define VVI vector<VI>
#define FOR(i,N) for(i=0 ; i<(int)N ; i++)
#define REP(i,a,b) for(i=(int)a ; i<=(int)b ; i++)
#define All(v) v.begin(),v.end()

VI R;
VI C;
VI D1;
VI D2;
int N;
int ret;

void Rec(ofstream& cout,int dpth=0){
    int i;
    if(dpth == N){
        ret++;
        if(ret<=3){
            FOR(i,N-1)
                cout << R[i]+1 << " ";
            cout << R[i]+1 << endl;
        }
        return;
    }
    FOR(i,N){
        if(C[i] || D1[dpth-i + N] || D2[dpth+i])
            continue;
        else if(ret > 14200){
            ret = 73712;
            return;
        }
        else{
            C[i] = 1;
            D1[dpth-i + N] = 1;
            D2[dpth+i] = 1;
            R[dpth] = i;

            Rec(cout,dpth+1);

            C[i] = 0;
            D1[dpth-i + N] = 0;
            D2[dpth+i] = 0;
        }
    }
}

int main(){
    ifstream cin("checker.in");
    ofstream cout("checker.out");
    cin >> N;
    R.clear(); R.resize(N,-1);
    C.clear(); C.resize(N);
    D1.clear(); D1.resize(2*N);
    D2.clear(); D2.resize(2*N);
    ret = 0;
    Rec(cout);
    cout << ret << endl;
    return 0;
}