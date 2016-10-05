#include <iostream>
#include <algorithm>
#include <string>
#include <vector>

using namespace std;

vector<vector<int> > v0(101,vector<int>(100));
vector<vector<int> > v1(101,vector<int>(100));

void init(){
	v0[1][0]=1;
	v1[1][0]=1;
	for(int i=2;i<=100;i++){
		for(int j=0;j<i;j++){
			v0[i][j]=v0[i-1][j]+v1[i-1][j];
			if(j!=0)
				v1[i][j]=v0[i-1][j]+v1[i-1][j-1];
			else
				v1[i][j]=v0[i-1][j];
		}
	}
}

int main(){
	init();
	int N;
	cin>>N;
	for(int cnt=1;cnt<=N;cnt++){
		int buf;
		int n;
		int k;
		cin>>buf>>n>>k;
		if(k<n && k>=0)
			cout<<buf<<" "<<v0[n][k]+v1[n][k]<<endl;
		else
			cout<<buf<<" 0"<<endl;
	}
}