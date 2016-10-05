#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <algorithm>
#include <queue>

using namespace std;

vector<int> nodes;
map<int,vector<int> > Link;
map<int,bool> done;
map<int,int> ret;

void rec(int n){
	for(int i=0;i<Link[n].size();i++){
		if(!done[Link[n][i]]){
			done[Link[n][i]]=true;
			rec(Link[n][i]);
		}
	}
}

void func(){
	for(int i=0;i<nodes.size();i++){
		done.clear();
		done[nodes[i]]=true;
		for(int j=0;j<nodes.size();j++){
			if(done[nodes[j]])
				continue;
			ret[nodes[i]]++;
			done[nodes[j]]=true;
			rec(nodes[j]);
		}
	}
}

int main(){
	//ifstream cin("SPF.h");
        ifstream cin("input.txt");
	for(int cnt=1;true;cnt++){
		nodes.clear();
		Link.clear();
		done.clear();
		ret.clear();
		int n,m;
		cin>>n;
		if(n==0)
			return 0;
		if(cnt!=1)
			cout<<endl;
		cin>>m;
		nodes.push_back(n);
		nodes.push_back(m);
		Link[n].push_back(m);
		Link[m].push_back(n);
		while(true){
			cin>>n;
			if(n==0)
				break;
			cin>>m;
			if(find(nodes.begin(),nodes.end(),n)==nodes.end())
				nodes.push_back(n);
			if(find(nodes.begin(),nodes.end(),m)==nodes.end())
				nodes.push_back(m);
			if(find(Link[n].begin(),Link[n].end(),m)==Link[n].end())
				Link[n].push_back(m);
			if(find(Link[m].begin(),Link[m].end(),n)==Link[m].end())
				Link[m].push_back(n);
		}

		sort(nodes.begin(),nodes.end());

		func();

		cout<<"Network #"<<cnt<<endl;
		bool flag=true;
		map<int,int>::iterator iter;
		for(iter=ret.begin();iter!=ret.end();iter++){
			if(iter->second>1){
				cout<<"  SPF node "<<iter->first<<" leaves "<<iter->second<<" subnets"<<endl;
				flag=false;
			}
		}
		if(flag)
			cout<<"  No SPF nodes"<<endl;
	}
}