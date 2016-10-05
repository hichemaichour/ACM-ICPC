#include <iostream>
#include <algorithm>
#include <string>
#include <vector>

using namespace std;

int main(){
	int N;
	cin>>N;
	for(int cnt=1;cnt<=N;cnt++){
		vector<int> v;
		vector<int> ret;
		int buf;
		int me;
		int n;
		cin>>buf>>n;
		for(int i=0;i<n;i++){
			cin>>me;
			v.push_back(me);
			if(i%2 == 0){
				sort(v.begin(),v.end());
				ret.push_back(v[v.size()/2]);
			}
		}

		cout<<buf<<" "<<ret.size()<<endl;
		int j;
		for( j=0;j<ret.size()-1;j++){
			if(j%10==9)
				cout<<ret[j]<<endl;
			else
				cout<<ret[j]<<" ";
		}
		cout<<ret[j]<<endl;		
	}
}