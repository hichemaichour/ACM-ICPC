#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

int N;
int n;
vector<int> cuts;
vector<vector<int> > v;

int DP(){
	v.resize(cuts.size(),vector<int>(cuts.size()));
	for(int d=2;d<=n;d++){
		for(int i=0;i<=n-d;i++){
			int buf=INT_MAX;
			for(int k=i+1;k<i+d;k++)
				buf=min(buf,v[i][k]+v[k][i+d]+cuts[i+d]-cuts[i]);
			v[i][i+d]=buf;
		}
	}

	return v[0][n];
}

int main(){
	//ifstream cin("CuttingSticks.h");
	while(true){
		int i,j,k;
		cuts.clear();
		v.clear();

		cin>>N;
		if(N==0)
			return 0;

		cin>>n;
		n++;
		cuts.resize(n+1);
		for(i=1;i<n;i++)
			cin>>cuts[i];
		cuts[i]=N;

		cout<<"The minimum cutting is "<<DP()<<"."<<endl;
	}
}