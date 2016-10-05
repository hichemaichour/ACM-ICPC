#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <vector>
#include <algorithm>

using namespace std;

string Start,End;
map<string,vector<string> > m;
map<string,bool> done;

bool func(string str){
	if(find(m[str].begin(),m[str].end(),End) != m[str].end())
		return true;
	for(int i=0;i<m[str].size();i++){
		if(!done[m[str][i]]){
			done[m[str][i]]=true;
			if(func(m[str][i]))
				return true;
			done[m[str][i]]=false;
		}
	}
	return false;
}

int main(){
	//ifstream cin("Mazes.h");
	for(int cnt=1;true;cnt++){
		int N;
		cin>>N;
		if(N==0)
			return 0;

		Start="";
		End="";
		m.clear();
		done.clear();
		int buf;
		int i;
		for(i=0;i<N;i++){
			cin>>buf;
			Start.push_back(buf+'0');
		}
		for(i=0;i<N;i++){
			cin>>buf;
			End.push_back(buf+'0');
		}

		while(true){
			string str1,str2;
			str1="";
			str2="";
			cin>>buf;
			if(buf==-1)
				break;
			str1.push_back(buf+'0');
			for(i=1;i<N;i++){
				cin>>buf;
				str1.push_back(buf+'0');
			}
			for(i=0;i<N;i++){
				cin>>buf;
				str2.push_back(buf+'0');
			}
			m[str1].push_back(str2);
			m[str2].push_back(str1);
			m[str1].resize(unique(m[str1].begin(),m[str1].end())-m[str1].begin());
			m[str2].resize(unique(m[str2].begin(),m[str2].end())-m[str2].begin());
		}

		done[Start]=true;
		if(func(Start))
			cout<<"Maze #"<<cnt<<" can be travelled"<<endl;
		else
			cout<<"Maze #"<<cnt<<" cannot be travelled"<<endl;
	}
}