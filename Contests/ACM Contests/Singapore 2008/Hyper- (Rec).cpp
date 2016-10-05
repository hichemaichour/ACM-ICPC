#include <iostream>
#include <map>
#include <fstream>
#include <vector>

#define VI map<int,long long>
#define VVI map<int,VI>

using namespace std;

int n,m,a,b;
int N,B;
VVI V;

long long Rec(int nn, int bb){
    if(V[nn].find(bb) != V[nn].end())
        return V[nn][bb];
    if(nn==0)
        return bb+1;
    if(bb==0){
        if(nn==1)
            return a;
        if(nn==2)
            return 0;
        return 1;
    }
    long long i = Rec(nn-1 , Rec(nn,bb-1)%m);
    V[nn][bb] = i%m;
    return V[nn][bb];
}

int main() {
    ifstream cin("input.txt");
    int T;
    cin >> T;
    for(int cnt=1 ; cnt<=T ; cnt++){
        V.clear();
        int i,j,k;
        cin >> m >> n >> a >> b;

        int out = Rec(n,b);

        cout <<"Case #"<< cnt <<": "<< out << endl;
    }
    return 0;
}


