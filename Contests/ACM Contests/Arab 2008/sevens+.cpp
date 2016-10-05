#include <iostream>
#include <fstream>
#include <string>
#include <map>

using namespace std;

map<string,int> m1;
map<int,string> m2;

void init(){
	m1["063"]=0;
	m1["010"]=1;
	m1["093"]=2;
	m1["079"]=3;
	m1["106"]=4;
	m1["103"]=5;
	m1["119"]=6;
	m1["011"]=7;
	m1["127"]=8;
	m1["107"]=9;
	m2[0]="063";
	m2[1]="010";
	m2[2]="093";
	m2[3]="079";
	m2[4]="106";
	m2[5]="103";
	m2[6]="119";
	m2[7]="011";
	m2[8]="127";
	m2[9]="107";

}

int s2i(string str){
	int ret=0;
	while(str.length()){
		ret*=10;
		ret+=m1[str.substr(0,3)];
		int k=str.length();
		if(str.length()>3)
			str=str.substr(3,str.length());
		else
			str="";
	}
	return ret;
}

string i2s(int n){
	string ret="";
	while(n){
		ret=m2[n%10]+ret;
		n/=10;
	}
	return ret;
}

int main(){
	init();
	//ifstream cin("sevens.h");
	while(true){
		string str;
		cin>>str;
		if(str=="BYE")
			break;
		string fst,scd;
		fst=str.substr(0,str.find("+"));
		scd=str.substr(str.find("+")+1,str.length());
		scd.resize(scd.length()-1);
		cout<<str<<i2s(s2i(fst)+s2i(scd))<<endl;
	}
	return 0;
}