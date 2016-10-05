#include <iostream>
#include <cmath>
#include <vector>

using namespace std;

vector<int> p;

void PF(int N){
	if (N==1 || N==0 || N==-1)
		return;
	if(N<-1){
		PF(N*-1);
		return;
	}

	for(int i=2;i<=sqrt((double)N);i++){
		if(N%i==0){
			PF(N/i);
			PF(i);
			return;
		}
	}

	p.push_back(N);
}

int main(){
	while(true){
		int N;
		cin>>N;
		if(N==-1)
			return 0;

		p.clear();
		PF(N);

		for(int i=0;i<p.size();i++)
			cout<<p[i]<<" ";
		cout<<endl;
	}
}