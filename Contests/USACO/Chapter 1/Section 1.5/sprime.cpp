/*
ID: b0002141
PROG: sprime
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
    if(n==0 || n==1)
        return false;
    if(n==2)
        return true;
    if(n%2 == 0)
        return false;
    for(int i=2 ; i<=sqrt((double)n) ; i++)
        if(n%i == 0)
            return false;
    return true;
}

void Rec(int dp,int n=0){
    if(dp==0){
        P.push_back(n);
        return;
    }
    for(int i=1 ; i<10 ; i++)
        if(IsP(n*10 + i))
            Rec(dp-1 , n*10 + i);
}

int main(){
    ifstream cin("sprime.in");
    ofstream cout("sprime.out");
    int N;
    cin >> N;
    P.clear();
    Rec(N);
    int i;
    FOR(i,P.size())
        cout << P[i] << endl;
}