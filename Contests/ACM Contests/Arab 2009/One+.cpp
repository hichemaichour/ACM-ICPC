#include <iostream>

using namespace std;

int main(){
	for(int cnt = 1 ; true ; cnt++){
		long long n,n1,n2,n3,n4;
		cin >> n;
		if(n==0)
			return 0;

		n1 = 3*n;
		if(n1%2)
			n2 = (n1+1)/2;
		else
			n2 = n1/2;
		n3 = 3*n2;
		n4 = n3/9;
		if(n1%2)
			cout << cnt <<". odd "<<n4<<endl;
		else
			cout << cnt <<". even "<<n4<<endl;
	}
}
