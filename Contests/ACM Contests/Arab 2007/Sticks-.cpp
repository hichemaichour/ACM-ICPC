#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <sstream>
#include <map>
#include <vector>

using namespace std;

char op;
string str;
string ret;
map<char,string> m1;
map<string,char> m2;
vector<string> v;
vector<map<int,bool> > done;
bool finish;

void init(){
	m1['0']="0111111";
	m1['1']="0000110";
	m1['2']="1011011";
	m1['3']="1001111";
	m1['4']="1100110";
	m1['5']="1101101";
	m1['6']="1111101";
	m1['7']="0000111";
	m1['8']="1111111";
	m1['9']="1100111";
	m1['+']="+";
	m1['-']="-";
	m1['*']="*";
	m1['/']="/";
	m1['=']="=";
	map<char,string>::iterator iter;
	for(iter=m1.begin();iter!=m1.end();iter++)
		m2[iter->second]=iter->first;
}

bool func(char c){
	if(c>='0' && c<='9')
		return false;
	return true;
}

string trans1(char c){
	return m1[c];
}

char trans2(string STR){
	return m2[STR];
}

int str2int(string STR){
	stringstream ss;
	ss<<STR;
	int n;
	ss>>n;
	return n;
}

bool check(){
	int n1=str2int(ret.substr(0,ret.find(op)));
	int n2=str2int(ret.substr(ret.find(op)+1,ret.find('=')-ret.find(op)-1));
	int n3=str2int(ret.substr(ret.find('=')+1,ret.size()-ret.find('=')-1));
	switch(op){
		case '+':
			return (n1+n2==n3);
		case '-':
			return (n1-n2==n3);
		case '*':
			return (n1*n2==n3);
		case '/':
			return (n2!=0 && n1/n2==n3 && n1%n2==0);
	}
}

void rec(int n,bool Get=true){
	//check if the answer is correct
	if(n==0){
		ret.resize(v.size());
		transform(v.begin(),v.end(),ret.begin(),trans2);
		if(count(ret.begin(),ret.end(),'\0')!=0)
			return;
		finish=check();
		return;
	}


	for(int i=0;i<v.size();i++){
		if(v[i].size()<7)
			continue;
		if(Get){
			for(int j=0;j<v[i].size();j++){
				if(v[i][j] == '1' && !done[i][j]){
					done[i][j]=true;
					v[i][j]='0';
					rec(n,false);
					if(finish)
						return;
					v[i][j]='1';
					done[i][j]=false;
				}
			}
		}
		else{
			for(int j=0;j<v[i].size();j++){
				if(v[i][j] == '0' && !done[i][j]){
					done[i][j]=true;
					v[i][j]='1';
					rec(n-1,true);
					if(finish)
						return;
					v[i][j]='0';
					done[i][j]=false;
				}
			}
		}
	}
}

int main(){
	//ifstream cin("Sticks.h");
	init();
	for(int cnt=1;true;cnt++){
		v.clear();
		done.clear();
		getline(cin,str);
		str.resize(remove(str.begin(),str.end(),' ')-str.begin());
		if(str=="EOF")
			return 0;
		int n;
		stringstream ss;

		ss<<str.substr(str.find('(')+1,str.find(')')-str.find('(')-1);

		str=str.substr(0,str.find('('));
		ss>>n;

		op=*find_if(str.begin(),str.end(),func);

		v.resize(str.size());
		done.resize(str.size());
		transform(str.begin(),str.end(),v.begin(),trans1);

		finish=false;
		ret="";
		rec(n);

		if(finish)
			cout<<cnt<<". "<<ret<<endl;
		else
			cout<<cnt<<". "<<"UNSOLVABLE"<<endl;
	}
}