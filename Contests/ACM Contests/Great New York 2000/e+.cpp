#include <iostream>
#include <iomanip>
#include <fstream>

using namespace std;

double fact(double n){
	if(n==0 || n==1)
		return 1;
	return (fact(n-1)*n);
}

int main(){
	double ret=0;
	long long l;
	cout<<"n e"<<endl;
	cout<<"- -----------"<<endl;
	for(double i=0;i<10;i++){
		if(i<3){
			ret+=1.0/fact(i);
			cout<<i<<" "<<ret<<endl;
		}
		else{
			ret+=1.0/fact(i);
			cout<<i<<" ";
			cout<<setiosflags(ios::fixed)<<setprecision(9)<<ret<<endl;
			cout<<setprecision(0);
		}
	}
}