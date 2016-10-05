#include <iostream>
#include <fstream>
#include <vector>

// h H g G -

using namespace std;

vector<vector<int> > v;

bool check(){
	for(int i=0;i<v.size()-1;i++)
		for(int j=0;j<v.size()-1;j++)
			if(v[i][j+1]+v[i+1][j]-v[i][j]!=v[i+1][j+1])
				return false;
	return true;
}

int main(){
	//ifstream cin("Johnny.h");
	int M;
	cin>>M;
	for(int cnt=1;cnt<=M;cnt++){
		int N;
		cin>>N;
		v.clear();
		v.resize(N,vector<int>(N));
		for(int i=0;i<N;i++)
			for(int j=0;j<N;j++)
				cin>>v[i][j];
		if(check())
			cout<<cnt<<". YES"<<endl;
		else
			cout<<cnt<<". NO"<<endl;
	}
	return 0;
}