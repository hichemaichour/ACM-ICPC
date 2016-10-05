#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

long long pow(long long n,int p){
	if(p==0)
		return 1;
	return n*pow(n,p-1);
}

int w(long long r,long long s,long long e,int N){
	if(N==0)
		return 1;

	long long half=pow(2,N-1);

	if(r<half){ //upper quarters
		if(s<half && e<half)
			return w(r,s,e,N-1);
		if(s>=half && e>=half)
			return w(r,s-half,e-half,N-1);
		return w(r,s,half-1,N-1)+w(r,0,e-half,N-1);
	}
	else{ //lower quarters
		if(s<half && e<half)
			return w(r-half,s,e,N-1);
		if(s>=half && e>=half)
			return (-1*w(r-half,s-half,e-half,N-1));
		return w(r-half,s,half-1,N-1)-w(r-half,0,e-half,N-1);
	}
}

int main(){
	//ifstream cin("whales.h");
	while (true){
		int N;
		long long R,S,E;
		cin>>N>>R>>S>>E;
		if(N==-1)
			break;

		int sum=0;
		sum=w(R,S,E,N);
		cout<<sum<<endl;
	}
	return 0;
}