#include <iostream>
#include <fstream>

using namespace std;

int main(){
	while(true){
		int n,m;
		cin>>n>>m;
		if(n==-1)
			break;
		if(n==1 || m==1)
			cout<<n<<"+"<<m<<"="<<n+m<<endl;
		else
			cout<<n<<"+"<<m<<"!="<<n+m<<endl;
	}
	return 0;
}