#include <iostream>
#include <fstream>
#include <string>
#include <map>

using namespace std;

map<char,string> m;

void init(){
	m['1']="45";
	m['2']="";
	m['3']="45";
	m['4']="23";
	m['5']="8";
	m['6']="23";
	m['7']="8";
	m['8']="67";
}

bool is(string str){
	if(str[0]!='1' || str[str.size()-1]!='2')
		return false;
	for(int i=0;i<str.size()-1;i++)
		if(m[str[i]].find(str[i+1])==string::npos)
			return false;
	return true;
}

int main(){
	//ifstream cin("Blocks.h");
	init();
	for(int cnt=1;true;cnt++){
		string str;
		cin>>str;
		if(str=="0")
			break;
		cout<<cnt<<". ";
		if(is(str))
			cout<<"VALID"<<endl;
		else
			cout<<"NOT"<<endl;
	}
	return 0;
}