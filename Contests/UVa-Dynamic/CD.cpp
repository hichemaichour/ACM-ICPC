#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>

using namespace std;

int T;
int ret;
vector<int> a;
vector<vector<string > > v;

string func(){
	int Max=0;
	int ind;
	for(int i=0 ; i<v[ret].size() ; i++){
		int buf = count(v[ret][i].begin(),v[ret][i].end(),' ');
		if( buf > Max ){
			Max = buf;
			ind = i;
		}
	}
	return v[ret][ind];
}

string init(){
	v[0].push_back("");
	for(int i=0;i<a.size();i++){
		for(int j=T ; j>=a[i] ; j--){
			if(!v[j-a[i]].empty()){
				for(int k=0 ; k<v[j-a[i]].size() ; k++){
					stringstream ss;
					ss<<v[j-a[i]][k]<<a[i]<<" ";
					v[j].push_back(ss.str());
				}
			}
		}
	}

	for(ret=T ; ret>=0 ; ret--)
		if(!v[ret].empty())
			return func();
}

int main(){
	while(cin>>T){
		int N;
		cin>>N;
		a.clear();
		a.resize(N);
		v.clear();
		v.resize(T+10);
		for(int i=0;i<N;i++)
			cin>>a[i];
		string str=init();
		cout<<str<<"sum:"<<ret<<endl;
	}
}