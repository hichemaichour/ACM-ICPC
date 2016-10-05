#include <iostream>
#include <string>

using namespace std;

int main(){
	int T;
	cin>>T;
	cin.ignore(100,'\n');
	for(int cnt=1 ; cnt<=T ; cnt++){
		string str,s;
		getline(cin,str);
		getline(cin,s);
		for(int i=0 ; i<str.size() ; i++)
			if(isalpha(str[i]))
				str[i] = s[ str[i]-'A' ];
		cout<<cnt<<" "<<str<<endl;
	}
}