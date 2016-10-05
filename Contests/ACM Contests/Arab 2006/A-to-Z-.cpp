#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <vector>

using namespace std;

const int MAX=1e6;
vector<pair<int,string> > dic;
vector<bool> used;
vector<int> Start;
vector<int> End;
string str;
int p;

int can(string str1,string str2){
	if(str1.size()<=str2.size()){
		for(int i=0;i<str1.size()-1;i++)
			if(str1.substr(i,str1.size())==str2.substr(0,str1.size()-i))
				return str1.size()-i;
	}
	else{
		for(int j=str1.size()-str2.size();j<str1.size()-1;j++)
			if(str1.substr(j,str1.size())==str2.substr(0,str1.size()-j))
				return str1.size()-j;
	}
	return 0;
}

void rec(int len,string s,string last,int j){
	int buf;
	//try to finish it
	buf=can(last,dic[j].second);
	if(buf!=0){
		len+=dic[j].first-buf;
		if(len>p)
			return;
		p=len;
		str=s+" "+dic[j].second;
		return;
	}

	//check if later by adding the end it will be useless
	if((len+dic[j].first)>p)
		return;

	//check for adding more
	for(int i=0;i<dic.size();i++){
		if(!used[i]){
			buf=can(last,dic[i].second);
			if(buf!=0){
				if(len+dic[i].first-buf>p)
					continue;
				used[i]=true;
				rec(len+dic[i].first-buf,s+" "+dic[i].second,dic[i].second,j);
				used[i]=false;
			}
		}
	}
}

void cal(int i,int j){
	int len=dic[i].first;
	if(len>p)
		return;
	string s=dic[i].second;
	used[i]=true;
	used[j]=true;
	rec(len,s,s,j);
	used[i]=false;
	used[j]=false;
}

bool func(char c1,char c2){
	p=MAX;
	str="";
	Start.clear();
	End.clear();

	for(int i=0;i<dic.size();i++){
		if(dic[i].second[0]==c1)
			Start.push_back(i);
		if(dic[i].second[dic[i].first-1]==c2)
			End.push_back(i);
		if( Start.size()>0 && End.size()>0 && (Start[Start.size()-1]==End[End.size()-1]) && (dic[i].first<p) ){
			p=dic[i].first;
			str=dic[i].second;
		}
	}

	for(int j=0;j<Start.size();j++)
		for(int k=0;k<End.size();k++)
			if(Start[j]!=End[k])
				cal(Start[j],End[k]);

	return p!=MAX;
}

int main(){
	ifstream cin("A-to-Z.h");
	for(int cnt=1;true;cnt++){
		int w;
		cin>>w;
		if(w==0)
			break;
		
		//read te dictionary
		dic.clear();
		used.clear();
		used.resize(w);
		pair<int,string> buf;
		for(int i=0;i<w;i++){
			cin>>buf.second;
			buf.first=buf.second.size();
			if(buf.first>=2)
				dic.push_back(buf);
		}

		sort(dic.begin(),dic.end());

		int q;
		cin>>q;
		for(int j=1;j<=q;j++){
			char c1,c2;
			cin>>c1>>c2;
			if(func(c1,c2))
				cout<<cnt<<"."<<j<<" "<<p<<" "<<str<<endl;
			else
				cout<<cnt<<"."<<j<<" 0"<<endl;
		}
	}
	return 0;
}