#include <iostream>
#include <fstream>

using namespace std;

int main(){
	while(true){
		int N;
		cin>>N;
		if(N==0)
			break;
		cout<<N<<" => "<<(N*N)-N+1<<endl;
	}
}