#include <iostream>
#include <queue>
#include <map>
#include <vector>
#include <string>
#include <fstream>

using namespace std;

string ret,str;
const string GOAL="ABCDEF_";
vector<int> v(7);

void init(){
	for(int i=0;i<7;i++){
		if(i==1 || i==4)
			v[i]=3;
		else
			v[i]=2;
	}
}

string trans(string s,int n,int i){
	switch(n){
		case 0:
			if(i==0)
				swap(s[0],s[5]);
			else
				swap(s[0],s[1]);
			break;

		case 1:
			if(i==0)
				swap(s[1],s[2]);
			else if(i==1)
				swap(s[1],s[0]);
			else
				swap(s[1],s[6]);
			break;

		case 2:
			if(i==0)
				swap(s[2],s[1]);
			else
				swap(s[2],s[3]);
			break;

		case 3:
			if(i==0)
				swap(s[3],s[2]);
			else
				swap(s[3],s[4]);
			break;

		case 4:
			if(i==0)
				swap(s[4],s[3]);
			else if(i==1)
				swap(s[4],s[5]);
			else
				swap(s[4],s[6]);
			break;

		case 5:
			if(i==0)
				swap(s[5],s[0]);
			else
				swap(s[5],s[4]);
			break;

		case 6:
			if(i==0)
				swap(s[6],s[1]);
			else
				swap(s[6],s[4]);
			break;
	}
	return s;
}

bool BFS(){
	map<string,bool> done;
	queue<pair<string,string> > q;
	if(str==GOAL)
		return true;

	pair<string,string> p;
	string buf;
	int pos;
	q.push(pair<string,string>(str,""));
	done[str]=true;
	while(!q.empty()){
		p=q.front();
		q.pop();
		pos=p.first.find('_');
		for(int i=0;i<v[pos];i++){
			buf=trans(p.first,pos,i);
			if(buf==GOAL){
				ret=p.second+buf[pos];
				return true;
			}
			if(!done[buf]){
				q.push(pair<string,string>(buf,p.second+buf[pos]));
				done[buf]=true;
			}
		}
	}
	return false;
}

int main(){
	//ifstream cin("Theta.h");
	int N;
	cin>>N;
	init();
	for(int cnt=1;cnt<=N;cnt++){
		int buf;
		ret="";
		cin>>buf>>str;
		str.push_back('_');
		if(BFS()){
			if(ret!="")
				cout<<buf<<" "<<ret.size()<<" "<<ret<<endl;
			else
				cout<<buf<<" 0"<<endl;
		}
		else
			cout<<buf<<" NO SOLUTION"<<endl;
	}
}