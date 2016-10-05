#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

vector<int> p(1000010,1);
vector<int> f(1000010);

void generate(){
	p[0]=0;
	p[1]=0;
	for(int i=2;i<p.size();i++){
		if(p[i]==1)
			for(int j=i+i;j<p.size();j+=i)
				p[j]=0;
	}

	f[0]=0;
	f[1]=0;
	f[2]=1;
	for(int k=3;k<p.size();k++){
		p[k]+=p[k-1];
		if(p[k]-p[k-1] && ((k-1)%4==0))
			f[k]=1+f[k-1];
		else
			f[k]=f[k-1];
	}
}

int main(){
	//ifstream cin("Fermat.h");

	generate();

	while(true){
		int L,U;
		cin>>L>>U;
		int l,u;
		l=L;
		u=U;
		if(L==-1 && U==-1)
			break;
		if(L<=0)
			L=1;
		if(U<=0)
			U=1;
		cout<<l<<" "<<u<<" "<<p[U]-p[L-1]<<" "<<f[U]-f[L-1]<<endl;
	}
	return 0;
}