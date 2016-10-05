#include <iostream>
#include <fstream>
#include <cmath>

#define REP(i,a,b)	for(i=(int)a ; i<=(int)b ; i++)
#define FOR(i,N)	for(i=0 ; i<(int)N ; i++)

#define EPS			1e-9

using namespace std;

long gcd(long a,long b) {
	if (a%b==0) 
		return b; 
	else 
		return gcd(b,a%b);
}


int main(){
	ifstream cin("e.txt");
	int T;
	cin >> T;
	while(T--){
		int i,j,k;
		int X,Y;
		cin >> X >> Y;

		int ans = 0;
		REP(i,1,X) REP(j,1,Y){
			int val = gcd(i,j);
			int buf = sqrt((double)val) + EPS;
			if(buf*buf == val && val!=1)
				continue;

			ans += i*j/val/val;
		}
		cout << ans << endl;
	}
}