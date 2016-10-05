#include <iostream>
#include <cmath>

using namespace std;

long GCD(long a,long b) {
	if (a%b==0) 
		return b; 
	else 
		return GCD(b,a%b);
}


int main(){
	while(true){
		long long N,M;
		cin >> N >> M;
		if(N==0)
			return 0;
		cout << (N/GCD(N,M))*(M/GCD(N,M)) << endl;
	}
}