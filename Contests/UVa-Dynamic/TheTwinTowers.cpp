#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

#define T int

vector<T> a;
vector<T> b;
vector<vector<int> > m;

int LCS(){
	int i,j;
	int N,M;
	m.clear();

	M=a.size();
	N=b.size();
	m.resize(M+1,vector<int>(N+1));

	for(i=M;i>=0;i--){
		for(j=N;j>=0;j--){
			if(i==M || j==N){
				m[i][j]=0;
				continue;
			}
			if(a[i]==b[j])
				m[i][j]=1+m[i+1][j+1];
			else
				m[i][j]=max(m[i][j+1],m[i+1][j]);
		}
	}

	return m[0][0];
}

int main(){
	//ifstream cin("TheTwinTowers.h");
	for(int cnt=1;true;cnt++){
		int i,j,k;
		int N,M;
		cin>>N>>M;
		if(N==0)
			return 0;

		a.resize(N);
		b.resize(M);

		for(i=0;i<N;i++)
			cin>>a[i];
		for(i=0;i<M;i++)
			cin>>b[i];

		cout<<"Twin Towers #"<<cnt<<endl;
		cout<<"Number of Tiles : "<<LCS()<<endl<<endl;
	}
}