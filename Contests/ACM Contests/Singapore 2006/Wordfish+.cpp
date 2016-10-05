#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <fstream>

using namespace std;

int main() {
    ifstream cin("input.txt");
    string str;
    while(cin >> str){
        int i,j,k;      
        vector<string> V(21);
        V[10] = str;
        for(i=11 ; i<21 ; i++){
            if(next_permutation(str.begin(),str.end()))
                V[i] = str;
//            else{
//                reverse(str.begin(),str.end());
//                V[i] = str;
//            }
        }

        str = V[10];
        for(i=9 ; i>=0 ; i--){
            if(prev_permutation(str.begin(),str.end()))
                V[i] = str;
//            else{
//                reverse(str.begin(),str.end());
//                V[i] = str;
//            }
        }


        int n=0;
        for(i=0 ; i<21 ; i++){
            if(V[i] == "")
                continue;
            int m = 30;
            for(j=0 ; j<V[i].size()-1 ; j++)
                if(abs(V[i][j+1]-V[i][j]) < m)
                    m = abs(V[i][j+1]-V[i][j]);
            if(m>n){
                str = V[i];
                n = m;
            }
        }
        cout <<str<<n <<endl;
    }
    return 0;
}

