#include <iostream>
#include <vector>
#include <queue>
#include <string>
#include <sstream>
#include <fstream>

#define Node vector<int>

using namespace std;

struct Info{
	string H;
	string G;
	string M;
	string S;
};

vector<Info> V;
vector<Node> Adj;

bool Diff(string s1 , string s2){
	if(s1.size() > 5 || s2.size() > 5)
		if(s1.size() != s2.size())
			return true;
	if(s1.size() > 5){
		if(s1.substr(0,s1.size()-2) != s2.substr(0,s1.size()-2))
			return true;
		s1 = s1.substr(s1.size()-2,2);
		s2 = s2.substr(s2.size()-2,2);
	}
	stringstream ss1;
	stringstream ss2;
	int i,j;
	ss1 << s1;
	ss2 << s2;
	ss1 >> i;
	ss2 >> j;
	return abs(i-j) > 40;
}

bool Connected(int i,int j){
	if( Diff(V[i].H , V[j].H) )
		return true;
	if(V[i].G == V[j].G)
		return true;
	if(V[i].M != V[j].M)
		return true;
	return V[i].S == V[j].S;
}

void Build_Graph(){
	for(int i=0 ; i<V.size() ; i++){
		for(int j=i+1 ; j<V.size() ; j++){
			if(Connected(i,j)){
				Adj[i].push_back(j);
				Adj[j].push_back(i);
			}
		}
	}
}

int Coloring(){
	int i,j,k;
	int ret = 0;

	int N = Adj.size();
	vector<int> v(N);
	queue<int> q;
	vector<vector<bool> > cnt(N,vector<bool>(N));
	vector<bool> done(N);
	vector<bool> InQ(N);
	
	q.push(0);
	InQ[0] = true;
	while(!q.empty()){
		k = q.front(); q.pop();
		
		for(i=0 ; i<Adj[k].size() ; i++){
			j = Adj[k][i];
			cnt[j][v[k]] = true;
		}

		for(i=0 ; i<Adj[k].size() ; i++){
			j = Adj[k][i];
			if(done[j])
				continue;
			while(cnt[j][v[j]])
				v[j]++;
			if(v[j]>ret)
				ret = v[j];
			if(!InQ[j])
				q.push(j);
			InQ[j] = true;
		}

		done[k] = true;
	}
	return ret+1;
}

int main(){
	ifstream cin("in.h");
	int T;
	cin>>T;
	while(T--){
		int i;

		int N;
		cin>>N;
		Adj.clear();
		V.clear();

		Adj.resize(N);
		V.resize(N);

		for(i=0 ; i<N ; i++)
			cin >> V[i].H >> V[i].G >> V[i].M >> V[i].S;

		Build_Graph();

		cout<<K_Graph()<<endl;
	}
}