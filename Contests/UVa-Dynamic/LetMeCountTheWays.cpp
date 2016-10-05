#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <sstream>

using namespace std;

const double EPS = 1e-9;

int m[] = {1,5,10,25,50};

vector<long long> v(50000);

void init(){
	v[0]=1;
	for(int i=0;i<5;i++)
		for(int j=m[i];j<50000;j++)
			v[j] += v[j-m[i]];
}

int main(){
	init();
	int d;
	while(cin>>d){
		if(v[d]>1)
			cout<<"There are "<<v[d]<<" ways to produce "<<d<<" cents change."<<endl;
		else
			cout<<"There is only "<<v[d]<<" way to produce "<<d<<" cents change."<<endl;
	}
	return 0;
}