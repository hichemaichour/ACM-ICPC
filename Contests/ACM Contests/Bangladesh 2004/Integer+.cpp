#include <iostream>
#include <vector>
#include <iomanip>
#include <fstream>

using namespace std;

bool neg;
int a,b,c;

long long gcd(long long a, long long b){
    if (a%b==0)
        return b;
    else
        return gcd(b,a%b);
}

int main() {
    ifstream cin("input.h");
    int N;
    for(int cnt=1 ; cin >> N && N ; cnt++){
        long long i,j,k;
        long long sum = 0;
        for(i=0 ; i<N ; i++){
            cin >> k;
            sum += k;
        }

        neg = sum<0;
        if(neg)
            sum *= -1;

        a = sum/N;
        sum = sum%N;
        if(sum == 0){
            b = 0;
            c = 1;
        }
        else{
            b = sum/gcd(sum,N);
            c = N/gcd(sum,N);
        }

        int n;
        int mul = 1;
        for(n=0 ; c/mul ; n++)
            mul *= 10;
        int m;
        mul = 1;
        for(m=0 ; a/mul ; m++)
            mul *= 10;

        cout <<"Case "<< cnt <<":"<<endl;
        string str = "";
        // only an integer
        if(b == 0){
            if(neg)
                cout <<"- ";
            cout << a << endl;
        }
        else{
            if(neg)
                str = "  ";
            if(a != 0){
                for(i=0 ; i<m ; i++)
                    str += " ";
            }
            cout << str;
            cout << setiosflags(ios::right) << setw(n) << b << endl;
            if(neg)
                cout <<"- ";
            if(a != 0)
                cout << a;
            for(i=0 ; i<n ; i++)
                cout <<"-";
            cout << endl;
            cout << str << c << endl;
        }
    }
    return 0;
}

