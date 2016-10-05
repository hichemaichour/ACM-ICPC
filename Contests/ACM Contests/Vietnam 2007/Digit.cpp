#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

#define MAX 10010

vector<vector<int> > V(MAX);

void init(){
    V[0] = vector<int>(10);
    for(int i=1 ; i<MAX ; i++){
        V[i] = V[i-1];
        for(int n=i ; n ; n /= 10)
            V[i][n%10]++;
    }
}

int main() {
    init();
    int N;
    cin >> N;
    while(N--){
        int n;
        cin >> n;
        for(int i=0 ; i<9 ; i++)
            cout << V[n][i] <<" ";
        cout << V[n][9] << endl;
    }
    return 0;
}

