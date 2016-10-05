#include <iostream>
#include <fstream>
#include <map>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

vector<int> v;
map<char,string> m;
map<string,char> M;
string str;

void init(){
	m['A']=".-";
	m['B']="-...";
	m['C']="-.-.";
	m['D']="-..";
	m['E']=".";
	m['F']="..-.";
	m['G']="--.";
	m['H']="....";
	m['I']="..";
	m['J']=".---";
	m['K']="-.-";
	m['L']=".-..";
	m['M']="--";
	m['N']="-.";
	m['O']="---";
	m['P']=".--.";
	m['Q']="--.-";
	m['R']=".-.";
	m['S']="...";
	m['T']="-";
	m['U']="..-";
	m['V']="...-";
	m['W']=".--";
	m['X']="-..-";
	m['Y']="-.--";
	m['Z']="--..";
	m['_']="..--";
	m[',']=".-.-";
	m['.']="---.";
	m['?']="----";

	map<char,string>::iterator iter;
	for(iter=m.begin();iter!=m.end();iter++)
		M[iter->second]=iter->first;
}

void func(){
	string buf="";
	for(int i=0;i<str.size();i++){
		buf+=m[str[i]];
		v.push_back(m[str[i]].size());
	}

	reverse(v.begin(),v.end());

	int pos=0;
	for(int j=0;j<str.size();j++){
		str[j]=M[buf.substr(pos,v[j])];
		pos+=v[j];
	}
}

int main(){
	//ifstream cin("P,MTHBGWB.h");
	init();
	int N;
	cin>>N;
	for(int cnt=1;cnt<=N;cnt++){
		v.clear();
		cin>>str;
		func();
		cout<<cnt<<": "<<str<<endl;
	}
}