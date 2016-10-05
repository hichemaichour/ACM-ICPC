#include <iostream>

using namespace std;

long gcd(long a,long b) {
	if (a%b==0) 
		return b; 
	else 
		return gcd(b,a%b);
}

long lcm(long a,long b){
	return (a/gcd(a,b)) * b;
}

int main(){
	int T;
	cin>>T;
	int cnt;
	for(cnt=0 ; cnt<T ; cnt++){
		int a,b;
		cin >> a >> b;
		cout<<cnt+1 <<" "<< lcm(a,b) <<" "<< gcd(a,b) << endl;
	}
}