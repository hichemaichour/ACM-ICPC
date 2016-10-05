#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <map>

using namespace std;

bool re(char c){
	if(islower(c) || c==' ' || c=='\n')
		return false;
	return true;
}

map<int,bool> m;

int main(){
	//ifstream cin("Moon.h");
	string str,buf;
	str="";
	while(true){
		getline(cin,buf);
		if(str!="")
			str+="\n"+buf;
		else
			str+=buf;
		if(str.find("EOF")!=string::npos){
			str=str.substr(0,str.find("EOF"));
			break;
		}
	}
	int pos;
	int temp;

	//replace "pink" with "floyd"
	pos=0;
	while(str.find("pink",pos)!=string::npos){
		temp=str.find("pink",pos);
		str.replace(str.find("pink",temp),4,"floyd");
		m[temp+4]=true;
		pos=temp+1;
	}

	//replace "dd" with "p"
	pos=0;
	int dec=0;
	while(str.find("dd",pos)!=string::npos){
		temp=str.find("dd",pos);
		if(!m[temp+dec]){
			str.replace(str.find("dd",temp),2,"p");
			dec++;
		}
		pos=temp+1;
	}

	//replace "ei" with "ie"
	pos=0;
	while(str.find("ei",pos)!=string::npos){
		if(str.find("ei",pos)-1>=0 && str[str.find("ei",pos)-1]=='c')
			pos=str.find("ei",pos)+2;
		else{
			temp=str.find("ei",pos);
			str.replace(str.find("ei",temp),2,"ie");
			pos=temp+2;
		}
	}

	//remove any character that is not ' ' or '\n' or small letter
	string::iterator iter;
	iter=remove_if(str.begin(),str.end(),re);
	str.resize(iter-str.begin());

	cout<<str;
}