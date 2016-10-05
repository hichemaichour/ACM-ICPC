#include <iostream>
#include <string>

using namespace std;

int main(){
	while (true){
		int n=1;
		int N;
		string str;
		cin>>str;
		if(str=="0")
			return 0;
		N=0;
		while(str!=""){
			N+=str[str.size()-1]-'0';
			str.resize(str.size()-1);
		}
		while(N>=10){
			n=0;
			while(N){
				n+=N%10;
				N/=10;
			}
			N=n;
		}
		cout<<N<<endl;
	}
}