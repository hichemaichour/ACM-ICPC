#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <sstream>

using namespace std;

const double EPS = 1e-9;

int m[] = {5,10,20,50,100,200,500,1000,2000,5000,10000};

vector<long long> v(50000);

void init(){
	v[0]=1;
	for(int i=0;i<11;i++)
		for(int j=m[i];j<50000;j++)
			v[j] += v[j-m[i]];
}

int main(){
	init();
	while(true){
		double d;
		string str;
		cin>>str;

		stringstream ss;
		ss<<str;
		ss>>d;

		if(d==0)
			return 0;

		int D = d*100 + EPS;

		cout<<setw(6)<<str<<setw(17)<<v[D]<<endl;
	}
	return 0;
}