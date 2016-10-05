#include <iostream>
#include <fstream>
#include <queue>
#include <vector>

using namespace std;

int N,D;

vector<vector<int> > pat;

int simulate(){
	int i,j,k;

	vector<int> cnt;
	vector<int> run;
	queue<int> wait;
	int fill=0;
	int front;

	cnt.resize(N);

	for(i=0 ; i<N ; i++)
		run.push_back(pat[i][cnt[i]++]);

	int ret=0;
	for(i=1 ; i<=D ; i++){
		if(!wait.empty())
			ret+=wait.size();

		for(j=0 ; j<N ; j++){
			if(run[j]==0)
				continue;
			run[j]--;
			if(run[j]==0)
				wait.push(j);
		}

		if(fill>0){
			fill--;
			if(fill==0)
				run[front] = pat[front][cnt[front]++];
		}

		if(fill==0 && !wait.empty()){
			front = wait.front();
			wait.pop();
			fill = pat[front][cnt[front]];
			cnt[front] = (cnt[front]+1)%pat[front].size();
		}
	}
	return ret;
}

int main(){
	//ifstream cin("Batteries.h");
	while(true){
		pat.clear();
		cin>>N>>D;
		if(N==0) return 0;

		int buf;
		pat.resize(N);
		for(int i=0 ; i<N ; i++){
			cin>>buf;
			while(buf!=0){
				pat[i].push_back(buf);
				cin>>buf;
			}
		}

		cout<<simulate()<<endl;
	}
}