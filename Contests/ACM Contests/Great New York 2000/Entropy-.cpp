#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include <queue>
#include <iomanip>

using namespace std;

map<char,int> m;
vector<int> v;
vector<string> next;
vector<string> s;
int MAX;
int MIN;
int Size;

bool funcS(string str1,string str2){
	if(str1.size() < str2.size())
		return true;
	if(str1.size() > str2.size())
		return false;
	return str1<str2;
}

int funcT(pair<char,int> p){
	return p.second;
}

void init(){
	queue<string> q;
	q.push("");
	int i=0;
	for(int j=0;j<8;j++){
		while(q.front().size()==j){
			q.push("0"+q.front());
			q.push("1"+q.front());
			next.push_back("0"+q.front());
			next.push_back("1"+q.front());
			q.pop();
		}
	}

	sort(next.begin(),next.end(),funcS);
}

bool cal(){
	int buf=0;
	for(int i=0;i<s.size();i++)
		buf+=s[i].size()*v[i];
	if(buf<MIN && s.size()==v.size())
		MIN=buf;
	return buf>MIN;
}

bool legal(string str){
	for(int i=1;i<str.size();i++)
		if(find(s.begin(),s.end(),str.substr(0,i))!=s.end())
			return false;
	return true;
}

void rec(int n){
	if(s.size()==v.size()){
		cal();
		return;
	}

	if(s.size()==0 && next[n].size()==8)
		return;

	if(cal())
		return;

	for(int i=n;i<next.size();i++){
		if (legal(next[i])){
			s.push_back(next[i]);
			rec(i+1);
			if(s.size()==v.size() || cal())
				break;

			/*if(s.size()<Size){
				s.resize(v.size());
				return;
			}
			else
				Size=s.size();*/

			s.pop_back();
		}
	}
}

int main(){
	ifstream cin("Entropy.h");
	init();
	while(true){
		string str;
		m.clear();
		v.clear();
		getline(cin,str);
		if(str=="END")
			return 0;

		for(int i=0;i<str.size();i++)
			m[str[i]]++;

		v.resize(m.size());
		transform(m.begin(),m.end(),v.begin(),funcT);
		sort(v.begin(),v.end());
		reverse(v.begin(),v.end());

		MAX=8*str.size();
		MIN=MAX;

		for(int i=0;i<next.size();i++){
			s.clear();
			Size=0;
			rec(i);
		}

		cout<<MAX<<" "<<MIN<<" ";
		cout<<setiosflags(ios::fixed)<<setprecision(1)<<((double)MAX)/MIN<<endl;
		cout<<setprecision(0);
	}
}