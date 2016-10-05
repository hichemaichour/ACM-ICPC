#include <iostream>
#include <fstream>

using namespace std;

struct PAIR{
    int m;
    int s;
    bool operator<(PAIR p){
        if(m != p.m)
            return m<p.m;
        return s<=p.s;
    }
};

int main(){
    ifstream cin ("input.txt");
    int N;
    cin >> N;
    for(int cnt=1 ; cnt<=N ; cnt++){
        PAIR w1,w2;
        PAIR m1,m2;
        char c;
        cin >> w1.m >>c>> w1.s >> w2.m >>c>> w2.s;
        cin >> m1.m >>c>> m1.s >> m2.m >>c>> m2.s;

        cout <<"Case "<<cnt<<": ";
        if(m1<w2 && w1<m2)
            cout << "Mrs Meeting" << endl;
        else
            cout << "Hits Meeting" << endl;
        cout << endl;
    }
    return 0;
}