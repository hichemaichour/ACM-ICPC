#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <sstream>
#include <fstream>

using namespace std;

int main() {
    ifstream cin("input.h");
    int N;
    for(int cnt=1 ; cin >> N && N ; cnt++){
        int i,j,k;
        vector<string> V(N);
        vector<int> v(N);
        for(i=0 ; i<N ; i++){
            cin >> V[i];
            stringstream ss;
            ss << V[i];
            ss >> v[i];
        }

        vector<int> n(N);

        for(i=0 ; i<N ; i++){
            k = 0;
            for(j=i ; j<N ; j++,k++){
                if(v[j] - v[i] != k)
                    break;
            }
            n[i] = k-1;
            i = j-1;
        }

        cout <<"Case "<< cnt <<":"<<endl;
        for(i=0 ; i<N ; i++){
            cout << V[i];
            if(n[i]==0)
                cout << endl;
            else{
                string str = V[i + n[i]];
                cout <<"-";
                for(j=0 ; j<str.size() ; j++)
                    if(str[j] != V[i][j])
                        break;
                cout << str.substr(j,str.size()) << endl;
                i += n[i];
            }
        }
        cout << endl;
    }
    return 0;
}

