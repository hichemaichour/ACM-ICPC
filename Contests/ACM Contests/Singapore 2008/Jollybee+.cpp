#include <iostream>
#include <vector>
#include <cmath>
#include <fstream>

using namespace std;

int main() {
    ifstream cin("input.txt");
    int T;
    cin >> T;
    while(T--){
        int i,j,k;
        int N,M;
        cin >> N >> M;
        N = pow(2.0,(double)N);
        vector<int> v(N,1);
        for(i=0 ; i<M ; i++){
            cin >> k;
            v[k-1] = 0;
        }
        int cnt = 0;
        while(N!=1){
            for(i=0 ; i<N ; i+=2){
                if(v[i] ^ v[i+1]){
                    cnt++;
                    v[i/2] = 1;
                }
                else
                    v[i/2] = v[i] || v[i+1];
            }
            N /= 2;
        }

        cout << cnt << endl;
    }
    return 0;
}

