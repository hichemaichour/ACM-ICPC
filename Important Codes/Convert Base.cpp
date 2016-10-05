#include <iostream>
#include <cmath>
#include <string>

using namespace std;

const string digit="0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";

string Dec2Base(double N,double B){
	string ret;
	int n=floor(log(N)/log(B));
	ret.resize(n+1);

	int r=N;
	int d;
	for(int i=0;i<ret.size();i++){
		d=floor(r/pow(B,n-i));
		r-=d*pow(B,n-i);
		ret[i]=digit[d];
	}

	return ret;
}

int main(){
	while(true){
		int N,B;
		cin>>N>>B;
		cout<<Dec2Base(N,B)<<endl;
	}
}