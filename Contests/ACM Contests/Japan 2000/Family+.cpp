#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <string>
#include <stack>

#define MP make_pair

using namespace std;

struct Node{
	string p;
	vector<string> c;
	Node(){ p="";}
};

map<string,Node> tree;
vector<pair<int,string> > v;

void init(){
	stack<string> s;
	int k=0;
	string p="";
	for(int i=0 ; i<v.size() ; i++){
		if(k<v[i].first){
			s.push(p);
			p=v[i-1].second;
			k++;
		}
		while(k>v[i].first){
			k--;
			p=s.top();
			s.pop();
		}
		tree[p].c.push_back(v[i].second);
		tree[v[i].second].p=p;
	}
}

int main(){
	//ifstream cin("Family.h");
	while(true){
		v.clear();
		tree.clear();
		int i,j,k;
		int N,M;
		cin>>N>>M;
		if(N==0)
			return 0;
		cin.ignore(1000,'\n');

		v.resize(N);
		for(i=0 ; i<N ; i++){
			k=0;
			while(cin.peek() == ' '){
				cin.get();
				k++;
			}
			v[i].first = k;
			cin>>v[i].second;
			cin.ignore(1000,'\n');
		}

		init();

		string s1,s2,str;
		string buf;
		for(i=0 ; i<M ; i++){
			cin >> s1 >> buf>>buf >> str >> buf >> s2;
			s2.resize(s2.size()-1);

			bool ret=false;

			if(str=="child"){
				ret = tree[s1].p == s2;
			}
			if(str=="parent"){
				ret = tree[s2].p == s1;
			}
			if(str=="sibling"){
				ret = tree[s1].p == tree[s2].p;
			}
			if(str=="descendant"){
				while(s1!=""){
					if(tree[s1].p == s2){
						ret=true;
						break;
					}
					s1 = tree[s1].p;
				}
			}
			if(str=="ancestor"){
				while(s2!=""){
					if(tree[s2].p == s1){
						ret=true;
						break;
					}
					s2 = tree[s2].p;
				}
			}

			if(ret)
				cout<<"True"<<endl;
			else
				cout<<"False"<<endl;
		}

		cout<<endl;
	}
}