#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>

// h H g -

using namespace std;

int func(string str){
	int i;
	int cnt=1;
	for(i=0;cnt;i++){
		if(str[i]=='(')
			cnt++;
		if(str[i]==')')
			cnt--;
	}
	return i-1;
}

void rec(string str){
	int n=0;
	int mul=1;
	if(isalpha(str[str.size()-1]))
		n=1;
	while(isdigit(str[str.size()-1])){
		n+=(str[str.size()-1]-'0')*mul;
		mul*=10;
		str.resize(str.size()-1);
	}

	for(int cnt=0;cnt<n;cnt++){
		for(int i=0;i<str.size();i++){
			if(isalpha(str[i])){
				cout<<str[i];
				continue;
			}
			int len=func(str.substr(i+1,str.size()));
			rec( str.substr(i+1,len) );
			i+=1+len;
		}
	}
}

int main(){
	//ifstream cin("Earth.h");
	while (true){
		string str;
		getline(cin,str);
		//remove spaces
		str.resize(remove(str.begin(),str.end(),' ')-str.begin());

		if(str=="$")
			break;

		str.resize(str.size()-1);
		if(str[0]=='(')
			str=str.substr(1,str.size()-2);
		rec(str);
		cout<<endl;
	}
	return 0;
}