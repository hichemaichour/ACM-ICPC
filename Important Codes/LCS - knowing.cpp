#include <iostream>
#include <fstream>
#include <string>
#include <set>
#include <vector>

using namespace std;

#define T char

vector<T> a;
vector<T> b;
vector<vector<int> > m;
vector<pair<int,int> > trace;
vector<T>ret;

int LCS(){
	int i,j;
	int N,M;
	m.clear();
	trace.clear();
	ret.clear();

	M=a.size();
	N=b.size();
	m.resize(M+1,vector<int>(N+1));
	trace.resize(M+1);
	trace[M]=pair<int,int>(M,M);

	for(i=M;i>=0;i--){
		for(j=N;j>=0;j--){
			if(i==M || j==N){
				m[i][j]=0;
				continue;
			}
			if(a[i]==b[j]){
				m[i][j]=1+m[i+1][j+1];
				trace[i]=pair<int,int>(i,trace[i+1].first);
			}
			else{
				if(m[i][j+1]>m[i+1][j])
					m[i][j]=m[i][j+1];
				else{
					m[i][j]=m[i+1][j];
					trace[i]=trace[i+1];
				}
			}
		}
	}

	for(i=trace[0].first;i<M;i=trace[i].second)
		ret.push_back(a[i]);

	return m[0][0];
}

int main(){
	ifstream cin("input.h");
	while(getline(cin,a) && getline(cin,b)){
		cout<<LCS()<<endl;
		for(int i=0;i<ret.size();i++)
			cout<<ret[i];
		cout<<endl;
	}
}