#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <cmath>
#include <algorithm>

using namespace std;

vector<int> v1(6);
vector<int> v2(6);
map<int,vector<int> > m;
vector<vector<int> > v;
vector<int> all;

void init(){
	v.resize(6);
	int cnt=1;
	int buf=2;
	int lim=7;
	for(int i=0;i<v.size();i++){
		for(int j=0;j<lim;j++)
			v[i].push_back(cnt++);
		lim+=buf;
		if(i==1)
			buf=0;
		if(i==2)
			buf=-2;
	}

	for(int I=0;I<v.size();I++){
		for(int J=0;J<v[I].size();J++){
			//left
			if(J!=0)
				m[v[I][J]].push_back(v[I][J-1]);
			//rigt
			if(J!=v[I].size()-1)
				m[v[I][J]].push_back(v[I][J+1]);
			//down & up
			if( (I<=2 && J%2==0) || (I!=5 && I>=3 && J%2) ){
				m[v[I][J]].push_back(v[I][J]+((v[I].size()+v[I+1].size())/2));
				m[v[I][J]+((v[I].size()+v[I+1].size())/2)].push_back(v[I][J]);
			}
		}
	}
}

bool func(int num){
	vector<int> buf=m[num];
	int cnt=0;
	int n;
	for(int i=0;i<buf.size();i++){
		if(find(all.begin(),all.end(),buf[i])==all.end()){
			cnt++;
			n=buf[i];
		}
	}
	if(cnt>1)
		return false;
	for(int I=0;I<v1.size();I++){
		buf=m[v1[I]];
		for(int J=0;J<buf.size();J++){
			if(buf[J]==n)
				return true;
		}
	}
	return false;
}

int main(){
	//ifstream cin("Sahara.h");
	init();
	for(int cnt=1;true;cnt++){
		all.clear();
		cin>>v1[0];
		if(v1[0]==0)
			break;
		all.push_back(v1[0]);
		for(int i=1;i<6;i++){
			cin>>v1[i];
			all.push_back(v1[i]);
		}
		for(int j=0;j<6;j++){
			cin>>v2[j];
			all.push_back(v2[j]);
		}
		
		bool flag=false;
		for(int k=0;k<6;k++)
			if(func(v2[k]))
				flag=true;

		if(flag)
			cout<<cnt<<". TRAPPED"<<endl;
		else
			cout<<cnt<<". FREE"<<endl;
	}
	return 0;
}