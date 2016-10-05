#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>

using namespace std;

int main(){
	int N;
	cin>>N;
	for(int cnt=1;cnt<=N;cnt++){
		vector<int> v(10);
		int buf;
		cin>>buf;
		for(int i=0;i<10;i++)
			cin>>v[i];
		sort(v.begin(),v.end(),greater<int>());
		cout<<buf<<" "<<v[2]<<endl;
	}
}