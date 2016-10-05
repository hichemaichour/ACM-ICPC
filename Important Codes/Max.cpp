#include <iostream>
#include <fstream>
#include <cmath>
#include <vector>

using namespace std;

vector<int> r;
vector<vector<int> > mm;

void init(){
	int i,j,b;
	int n=r.size();
	mm.resize(r.size()+1,vector<int>(18));
	
	for(i=0;i<n;i++)
		mm[i][0]=r[i];

	for(i=1;i<18;i++)
		for(j=0;j+(1<<i)-1<n;j+=1<<i)
			mm[j][i]=max(mm[j][i-1],mm[j+(1<<i)][i-1]);
}

int GetMax(int a,int b){
	if(a>b)
		return -1;
	
	for(int i=17;i>=0;i--)
		if( a%(1<<i)==0 && a+(1<<i)-1<=b)
			return max(mm[a][i],GetMax(a+(1<<i),b));
}

int main(){
	ifstream cin("input.h");
	int N;
	cin>>N;
	r.resize(N);
	for(int i=0;i<N;i++)
		cin>>r[i];

	init();
	
	int A,B;
	cin>>A>>B;
	cout<<GetMax(A,B)<<endl;
}