/*
ID: b0002141
PROG: pprime
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

VI P;

bool IsP(int n){
    int i;
    if(n==0 || n==1 || n%2)
        return false;
    if(n==2)
        return true;
    for(int i=3 ; i*i<=n ; i+=2)
        if(n%i == 0)
            return false;
    return true;
}

void Rec(int mul1 , int mul2 , int n=0){
    if(mul1>mul2){
        if(IsP(n))
            P.push_back(n);
        return;
    }
    for(int i=0 ; i<=9 ; i++){
        if(mul1 == mul2)
            Rec(mul1*10 , mul2/10 , n + mul1*i);
        else if(n==0 && i==0)
            continue;
        else
            Rec(mul1*10 , mul2/10 , n + mul1*i + mul2*i);
    }
}

void init(){
    int i,j,k;
    P.clear();

    int buf = 1;
    REP(i,1,8){
        int mul1 = 1;
        int mul2 = buf;
        buf *= 10;
        Rec(mul1,mul2);
    }
    sort(All(P));
}

int main(){
    ifstream cin("pprime.in");
    ofstream cout("pprime.out");
    init();
    int i,j;
    cin >> i >> j;
    int pos = lower_bound(All(P) , i) - P.begin();
    VI Pal;
    for(; pos<P.size() && P[pos]<=j ; pos++)
        cout << P[pos] << endl;
}