#include <iostream>
#include <algorithm>
#include <string>

using namespace std;

int main(){
	int N;
	cin>>N;
	for(int cnt=1;cnt<=N;cnt++){
		string str;
		bool ret;
		int buf;
		cin>>buf>>str;
		ret=next_permutation(str.begin(),str.end());
		if(ret)
			cout<<buf<<" "<<str<<endl;
		else
			cout<<buf<<" BIGGEST"<<endl;
	}
}