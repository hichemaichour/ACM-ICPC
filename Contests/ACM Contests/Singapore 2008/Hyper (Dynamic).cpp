#include <iostream>
#include <fstream>
#include <vector>

#define VI vector<int>
#define VVI vector<VI>

using namespace std;

int n,m,a,b;
int N,B;

int main() {
    ifstream cin("input.txt");
    int T;
    cin >> T;
    for(int cnt=1 ; cnt<=T ; cnt++){
        int i,j,k;
        cin >> m >> n >> a >> b;
        N = n+1;
        B = b+1;
        if(m > B)
            B = m;
        VVI V(n+1,b+1);
        for(i=0 ; i<B ; i++){
            V[0][i] = i+1;
        }

        for(i=1 ; i<N ; i++){
            V[i][0] = 1;
            if(i==1)
                V[i][0] = a;
            if(i==2)
                V[i][0] = 0;
        }

        for(i=1 ; i<N ; i++)
            for(j=1 ; j<B ; j++)
                V[i][j] = V[ i-1 ][ V[i][j-1]%m ];


        cout <<"Case #"<< cnt <<": "<< V[n][b] << endl;
    }
    return 0;
}

