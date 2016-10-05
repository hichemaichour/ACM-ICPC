#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

vector<vector<int> > tri;

int MAX(int n,int m){
	if (n<m)
		return m;
	return n;
		
}

int m_down(int R,int C){
	int N=tri.size();
	int m=-1001;
	int n=0;
	for(int i=R;i<N;i++){
		n+=tri[i][C+((i-R)*2)]-tri[i][C-1];
		m=MAX(n,m);
	}
	return m;
}

int m_up(int R,int C){
	int N=tri.size();
	int m=-1001;
	int n=0;
	for(int i=R;C<tri[i].size() && (C-((R-i)*2)-1)>0;i--){
		n+=tri[i][C]-tri[i][C-((R-i)*2)-1];
		m=MAX(n,m);
	}
	return m;
}

int normal(){
	int N=tri.size();
	int m=-1001;
	for(int i=0;i<N;i++){
		for(int j=1;j<tri[i].size();j+=2){
			m=max(m,m_down(i,j));
		}
	}
	return m;
}

int abnormal(){
	int N=tri.size();
	int m=-1001;
	for(int i=0;i<N;i++){
		for(int j=2;j<tri[i].size();j+=2){
			m=max(m,m_up(i,j));
		}
	}
	return m;
}

int main(){
	//ifstream cin("triangles.h");
	for(int cnt=1;true;cnt++){
		int N;
		cin>>N;
		if(N==0)
			return false;
		tri.clear();
		tri.resize(N);
		for(int i=0;i<N;i++){
			tri[i].resize(2*(i+1));
			tri[i][0]=0;
			int buf;
			for(int j=1;j<tri[i].size();j++){
				cin>>buf;
				tri[i][j]=buf+tri[i][j-1];
			}
		}
		
		//finding the max
		int m=MAX(normal(),abnormal());
		
		cout<<cnt<<". "<<m<<endl;
	}
	return 0;
}