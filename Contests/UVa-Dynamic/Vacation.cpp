#include <vector>
#include <iostream>
#include <string>
#include <fstream>

using namespace std;

string a;
string b;
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
	//ifstream cin("Vacation.h");
	for(int cnt=1;true;cnt++){
		getline(cin,a);
		if(a=="#")
			return 0;
		getline(cin,b);

		cout<<"Case #"<<cnt<<": you can visit at most "<<LCS()<<" cities."<<endl;
	}
}