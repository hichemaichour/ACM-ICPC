#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>

using namespace std;

vector<vector<int> > v;
const int MAX=-4000020;

int st(){
	int ret=MAX;
	int sum_h;
	int sum_v;
	for(int i=0;i<v.size();i++){
		for(int j=0;j<v.size()-3;j++){
			sum_h=v[i][j]+v[i][j+1]+v[i][j+2]+v[i][j+3];
			sum_v=v[j][i]+v[j+1][i]+v[j+2][i]+v[j+3][i];
			ret=max(ret,sum_h);
			ret=max(ret,sum_v);
		}
		
	}
	return ret;
}

int zig(){
	int ret=MAX;
	int sum_h;
	int sum_v;
	for(int i=0;i<v.size()-1;i++){
		for(int j=0;j<v.size()-2;j++){
			sum_h=v[i][j]+v[i][j+1]+v[i+1][j+1]+v[i+1][j+2];
			sum_v=v[j+1][i]+v[j+2][i]+v[j+1][i+1]+v[j][i+1];
			ret=max(ret,sum_h);
			ret=max(ret,sum_v);
		}
	}
	return ret;
}

int l(){
	int ret=MAX;
	int h1,h2,v1,v2;
	for(int i=0;i<v.size()-1;i++){
		for(int j=0;j<v.size()-2;j++){
			h1=v[i][j]+v[i+1][j]+v[i+1][j+1]+v[i+1][j+2];
			h2=v[i][j]+v[i][j+1]+v[i][j+2]+v[i+1][j+2];
			v1=v[j][i]+v[j+1][i]+v[j+2][i]+v[j][i+1];
			v2=v[j+2][i]+v[j][i+1]+v[j+1][i+1]+v[j+2][i+1];
			ret=max(ret,max(h1,h2));
			ret=max(ret,max(v1,v2));
		}
	}
	return ret;
}

int t(){
	int ret=MAX;
	int h1,h2,v1,v2;
	for(int i=0;i<v.size()-1;i++){
		for(int j=0;j<v.size()-2;j++){
			h1=v[i][j]+v[i][j+1]+v[i][j+2]+v[i+1][j+1];
			h2=v[i][j+1]+v[i+1][j]+v[i+1][j+1]+v[i+1][j+2];
			v1=v[j][i]+v[j+1][i]+v[j+2][i]+v[j+1][i+1];
			v2=v[j+1][i]+v[j][i+1]+v[j+1][i+1]+v[j+2][i+1];
			if(i==0 && j==0)
				ret=v1;
			ret=max(ret,max(h1,h2));
			ret=max(ret,max(v1,v2));
		}
	}
	return ret;
}

int sq(){
	int ret=MAX;
	int sum;
	for(int i=0;i<v.size()-1;i++){
		for(int j=0;j<v.size()-1;j++){
			sum=v[i][j]+v[i][j+1]+v[i+1][j]+v[i+1][j+1];
			if(i==0 && j==0)
				ret=sum;
			ret=max(ret,sum);
		}
	}
	return ret;
}

int main(){
	//ifstream cin("Tetris.h");
	for(int cnt=1;true;cnt++){
		int N;
		cin>>N;
		if(N==0)
			break;
		v.clear();
		v.resize(N,vector<int>(N));
		for(int i=0;i<N;i++)
			for(int j=0;j<N;j++)
				cin>>v[i][j];

		int m=MAX;
		m=max(m,st());
		m=max(m,zig());
		m=max(m,l());
		m=max(m,t());
		m=max(m,sq());

		cout<<cnt<<". "<<m<<endl;
	}
	return 0;
}