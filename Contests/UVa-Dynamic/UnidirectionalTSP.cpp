#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

vector<vector<int> > v;
vector<vector<pair<int,pair<int,int> > > > m;
vector<int> ret;

int TSP(){
	int i,j,k;
	int N,M;
	ret.clear();

	N=v.size();
	M=v[0].size();

	for(j=M-2;j>=0;j--){
		for(i=0;i<N;i++){
			m[i][j]=min(m[(i+N-1)%N][j+1],m[(i+1)%N][j+1]);
			m[i][j]=min(m[i][j],m[i][j+1]);
			swap(m[i][j].second.first,m[i][j].second.second);
			m[i][j].second.first=i;
			m[i][j].first+=v[i][j];
		}
	}

	int pos;
	int sum=INT_MAX;
	for(i=0;i<N;i++){
		if(m[i][0].first<sum){
			sum=m[i][0].first;
			pos=i;
		}
	}

	j=0;
	for(i=pos;i<N;i=m[i][j++].second.second)
		ret.push_back(i+1);

	return m[pos][0].first;
}

int main(){
	//ifstream cin("UnidirectionalTSP.h");
	int N,M;
	while(cin>>N>>M){
		int i,j,k;

		v.clear();
		m.clear();
		v.resize(N,vector<int>(M));
		m.resize(N,vector<pair<int,pair<int,int> > >(M));
		for(i=0;i<N;i++){
			for(j=0;j<M;j++){
				cin>>v[i][j];
				if(j==M-1)
					m[i][j]=pair<int,pair<int,int> >(v[i][j],pair<int,int>(i,N));
			}
		}

		int sum=TSP();

		cout<<ret[0];
		for(int i=1;i<ret.size();i++)
			cout<<" "<<ret[i];
		cout<<endl;
		cout<<sum<<endl;
	}
}