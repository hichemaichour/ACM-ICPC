#include <iostream>
#include <fstream>
#include <vector>
#include <numeric>

using namespace std;

vector<int> p(1e6+1,1);

void init_p(){
	p[0]=0;
	p[1]=0;
	for(int i=2;i<p.size();i++){
		if(p[i]!=1)
			continue;
		for(int j=2;i*j<p.size();j++){
			if(p[j]!=1 || j<=i)
				p[i*j]=p[j]+1;
		}
	}
	for(int k=2;k<p.size();k++){
		if(p[k]==1){
			p[k]=-1;
		}
	}

	partial_sum(p.begin(),p.end(),p.begin());
}

int cal(int i,int j){
	return ((p[j]-p[i-1]) - (j-i+1));
}

int func(int L,int U){
	int ret=-1*1e6;
	int buf;
	int I,J;
	for(int i=L;i<=U;i++){
		for(int j=i;j<=U;j++){
			buf=cal(i,j);
			if(buf>ret){
				ret=buf;
				I=i;
				J=j;
			}
		}
	}
	return ret;
}

int myfunc(int L,int U){
	int ret=-1*1e6;
	int buf;
	int I,J;
	for(int i=L;i<=L+10;i++){
		for(int j=U-10;j<=U;j++){
			buf=cal(i,j);
			if(buf>ret){
				ret=buf;
				I=i;
				J=j;
			}
		}
	}
	return ret;
}

int main(){
	//ifstream cin("Number.h");
	init_p();
	for(int cnt=1;true;cnt++){
		int L,U;
		cin>>L>>U;
		if(L==-1)
			break;
		if(U-L <=20)
			cout<<cnt<<". "<<func(L,U)<<endl;
		else
			cout<<cnt<<". "<<myfunc(L,U)<<endl;
	}
	return 0;
}