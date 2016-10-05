#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>

using namespace std;

vector<char> v1;
vector<char> v2;
map<char,pair<char,char> > fst;
map<char,pair<char,char> > scd;
char f;
char s;

void init1(char t){
	if(t!='#'){
		fst[t].first=v1[v1.size()-1];
		v1.pop_back();
		init1(fst[t].first);
		fst[t].second=v1[v1.size()-1];
		v1.pop_back();
		init1(fst[t].second);
	}
}

void init2(char t){
	if(t!='#'){
		scd[t].first=v2[v2.size()-1];
		v2.pop_back();
		init2(scd[t].first);
		scd[t].second=v2[v2.size()-1];
		v2.pop_back();
		init2(scd[t].second);
	}
}

bool check(char t1,char t2){
	if(t1!=t2)
		return false;
	if(t1=='#')
		return true;
	return ( (check(fst[t1].first,scd[t2].first) && check(fst[t1].second,scd[t2].second)) || (check(fst[t1].first,scd[t2].second) && check(fst[t1].second,scd[t2].first)) );
}

int main(){
	//ifstream cin("Apple.h");
	int M;
	cin>>M;	
	for(int cnt=1;cnt<=M;cnt++){
		fst.clear();
		scd.clear();
		v1.clear();
		v2.clear();

		string str="";
		char c;
		cin>>str;
		while(str!="end"){
			if(str=="nil")
				c='#';
			else
				c=str[0];
			v1.push_back(c);
			cin>>str;
		}
		cin>>str;
		while(str!="end"){
			if(str=="nil")
				c='#';
			else
				c=str[0];
			v2.push_back(c);
			cin>>str;
		}

		if(v1.size()!=v2.size()){
			cout<<"false"<<endl;
			continue;
		}

		f=v1[v1.size()-1];
		v1.pop_back();
		init1(f);
		s=v2[v2.size()-1];
		v2.pop_back();
		init2(s);

		if(check(f,s))
			cout<<"true"<<endl;
		else
			cout<<"false"<<endl;
	}
	return 0;
}