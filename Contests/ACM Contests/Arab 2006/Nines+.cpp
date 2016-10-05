#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

using namespace std;

int cal(string n){
	int ret=0;
	while (n!=""){
		ret+=n[n.size()-1]-'0';
		n.resize(n.size()-1);
	}
	return ret;
}

int main(){
	//ifstream cin("Nines.h");
	for(int cnt=1;true;cnt++){
		string str;
		getline(cin,str);
		if(str==".")
			break;

		stringstream ss;
		char op;
		if( str.find('*')!=string::npos )
			op='*';
		else
			op='+';
		
		string a,b,c;

		ss<<str.substr(0,str.find(op));
		ss>>a;
		str=str.substr(str.find(op)+1,str.size());
		ss.str("");
		ss.clear();

		ss<<str.substr(0,str.find('='));
		ss>>b;
		str=str.substr(str.find('=')+1,str.size());
		ss.str("");
		ss.clear();

		ss<<str.substr(0,str.find('.'));
		ss>>c;
		str=str.substr(str.find('.')+1,str.size());
		ss.str("");
		ss.clear();

		int A,B,C;
		A=cal(a);
		B=cal(b);
		C=cal(c);

		int ri,le;
		if(op=='*')
			ri=A*B;
		else
			ri=A+B;
		le=C;

		if(ri%9 == le%9)
			cout<<cnt<<". PASS"<<endl;
		else
			cout<<cnt<<". NOT!"<<endl;
	}
}