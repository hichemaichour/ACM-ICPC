#include <iostream>
#include <fstream>
#include <vector>

// h H g -

using namespace std;

vector<int> p(1e6+10,1);

void init(){
	p[0]=0;
	p[1]=0;
	for(int i=2;i<p.size();i++){
		if(p[i]==0)
			continue;
		for(int j=2;i*j<p.size();j++){
			if(p[j]!=1 || j<=i)
				p[i*j]=0;
		}
	}

	for(int k=2;k<p.size();k++){
		if(p[k] && k%10!=3)
			p[k]=0;
	}

	for(int I=2;I<p.size();I++){
		if(p[I]==0)
			continue;
		for(int J=2;I*J<p.size();J++){
			if(p[J]==1)
				p[I*J]=1;
		}
	}
}

int main(){
	//ifstream cin("Three.h");
	init();
	while(true){
		int n;
		cin>>n;
		if(n<0)
			return 0;
		if(p[n])
			cout<<n<<" YES"<<endl;
		else
			cout<<n<<" NO"<<endl;
	}
}