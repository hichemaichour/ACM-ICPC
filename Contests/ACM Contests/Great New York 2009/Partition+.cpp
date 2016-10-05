#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

int main(){
	//ifstream cin("Partition.h");
	int N;
	cin>>N;
	for(int cnt=1;cnt<=N;cnt++){
		int n,buf,i;
		vector<int> v;
		cin>>buf>>n;
		v.resize(n);
		for(i=0;i<n;i++)
			cin>>v[i];

		int ret=0;
		bool flag=true;
		for(i=0;i<n && flag;i++){
			ret+=v[i];
			int pos=i+1;

			int sum=0;
			while(true){
				if(pos==n)
					break;

				sum+=v[pos++];
				if(sum>ret)
					break;

				if(sum==ret && pos==n)
					flag=false;

				if(sum==ret)
					sum=0;
			}
		}

		cout<<buf<<" "<<ret<<endl;
	}
}