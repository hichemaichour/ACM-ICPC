#include <iostream>

using namespace std;

long gcd(long a,long b) {
	if (a%b==0) 
		return b; 
	else return gcd(b,a%b);
}
void Divbygcd(long& a,long& b) {
	long g=gcd(a,b);
	a/=g;
	b/=g;
}

long nCr(int n,int r){
	long numerator=1,denominator=1,toMul,toDiv,i;
	if (r>n/2) r=n-r; /* use smaller k */
	for (i=r;i;i--) {
		toMul=n-r+i;
		toDiv=i;
		Divbygcd(toMul,toDiv); /* always divide before multiply */
		Divbygcd(numerator,toDiv);
		Divbygcd(toMul,denominator);
		numerator*=toMul;
		denominator*=toDiv;
	}
	return numerator/denominator;
}

int main(){
	while(true){
		int n,r;
		cin>>n>>r;
		if(n==0)
			return 0;
		cout<<endl<<nCr(n,r)<<endl<<endl;
	}
}