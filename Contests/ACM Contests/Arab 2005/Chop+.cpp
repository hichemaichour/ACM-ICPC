#include <iostream>
#include <fstream>
#include <string>

// h H g -

using namespace std;

int cal(string str){
	int ret=0;
	for(int i=0;i<str.size();i++){
		ret+=str[i]-'0';
	}
	return ret;
}

int rec(string str,int min){
	int n=0;

	for(int i=1;i<str.size();i++)
		if(cal(str.substr(0,i))>=min)
			n+=rec(str.substr(i,str.size()),cal(str.substr(0,i)));

	if(cal(str)>=min)
		return n+1;
	else
		return 0;
}

int main(){
	//ifstream cin("Chop.h");
	for(int cnt=1;true;cnt++){
		string str;
		cin>>str;
		if(str=="bye")
			return 0;
		cout<<cnt<<". "<<rec(str,0)<<endl;
	}
}