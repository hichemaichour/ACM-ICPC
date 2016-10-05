#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

int main(){
	ifstream cin("football.h");
	for(int i=1;true;i++){
		int N;
		cin>>N;
		if(N==0)break;

		vector<vector<int> > banks(N);
		vector<int> my(N);
		int B=0;
		for(int j=0;j<N;j++){
			banks[j].resize(N);
			for(int k=0;k<N;k++){
				cin>>banks[j][k];
				B+=banks[j][k];
				my[j]+=banks[j][k];
				my[k]-=banks[j][k];
				
			}
		}

		int A=0;
		for(int I=0;I<N;I++)
			if(my[I]>0)
				A+=my[I];
			

		cout<<i<<". "<<B<<" "<<A<<endl;
	}
	return 0;
}