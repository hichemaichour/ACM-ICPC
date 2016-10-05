#include <iostream>
#include <fstream>
#include <string>

using namespace std;

string func(string str){
	int re=0;
	//find the number
	for(int i=str.size()-2;i>=0;i--){
		str[i]=str[i]-str[i+1]+'0'+re;
		re=0;
		if(str[i]<'0'){
			str[i]+=10;
			re=-1;
		}
		if(str[i]>'9'){
			str[i]-=10;
			re=1;
		}
	}
	return str;
}

int main(){
	//ifstream cin("Hide.h");
	for(int cnt=1;true;cnt++){
		string str;
		cin>>str;
		if(str=="0")
			break;
		str=func(str);
		if(str[0]=='0')
			cout<<cnt<<". IMPOSSIBLE"<<endl;
		else
			cout<<cnt<<". "<<str<<endl;
	}
}