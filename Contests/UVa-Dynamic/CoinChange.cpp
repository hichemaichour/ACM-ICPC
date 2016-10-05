#include <iostream>
#include <vector>
#include <fstream>

using namespace std;

vector<int> ret;

void init(){
	int i,j,k;
	int c[]={1,5,10,25,50};

	ret.resize(7500);
	ret[0]=1;
	for(i=0;i<5;i++)
		for(j=c[i];j<ret.size();j++)
			ret[j]+=ret[j-c[i]];
}

int main(){
	//ifstream cin("CoinChange.h");
	init();
	int N;
	while(cin>>N)
		cout<<ret[N]<<endl;
}