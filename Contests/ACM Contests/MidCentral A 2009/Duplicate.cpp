#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main(){
	while(true){
		int N;
		vector<int> v;
		
		cin >> N;
		if(N==0)
			return 0;
		v.resize(N);

		for(int i=0 ; i<N ; i++)
			cin >> v[i];
		v.resize( unique(v.begin(),v.end()) - v.begin() );
		for(int j=0 ; j<v.size() ; j++)
			cout << v[j] <<" ";
		cout<<"$"<<endl;
	}
}