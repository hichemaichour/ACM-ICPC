#include <iostream>
#include <fstream>
#include <vector>

// h H g -

using namespace std;

vector<int> v1;
vector<int> v2;

void func(){
	int sum1=0,sum2=0;
	int sum=0;
	int i=0,j=0;
	bool fst=true;
	while(i<v1.size() || j<v2.size()){
		if(i<v1.size() && j<v2.size() && v1[i]==v2[j]){
			sum+=max(sum1,sum2)+v1[i];
			sum1=0;
			sum2=0;
			i++;
			j++;
		}
		else{
			if(i==v1.size() || (j<v2.size() && v1[i]>v2[j])){
				fst=false;
			}
			if(j==v2.size() || (i<v1.size() && v2[j]>v1[i])){
				fst=true;
			}

			if(fst){
				sum1+=v1[i];
				i++;
			}
			else{
				sum2+=v2[j];
				j++;
			}
		}
	}
	cout<<sum+max(sum1,sum2)<<endl;
}

int main(){
	//ifstream cin("HeliX.h");
	while(true){
		int n,m;
		v1.clear();
		v2.clear();
		cin>>n;
		if(n==0)
			return 0;

		v1.resize(n);
		for(int i=0;i<n;i++)
			cin>>v1[i];
		cin>>m;
		v2.resize(m);
		for(int j=0;j<m;j++)
			cin>>v2[j];
		func();
	}
}