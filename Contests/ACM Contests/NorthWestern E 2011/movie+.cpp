#include<iostream>
#include<fstream>

#include<vector>

#define FOR(i,N)	for(i=0 ; i<(int)N ; i++)
#define REP(i,a,b)	for(i=(int)a ; i<=(int)b ; i++)

#define VI			vector<int>
#define VVI			vector<VI>

using namespace std;

VVI BT;
VI V;
int N,M;

int cal(int pos){
	int d=BT.size()-1;
	int ans = 0;
	while(d){
		if(pos%2)
			ans+=BT[d-1][pos/2];
		pos/=2;
		d--;
	}
	return ans;
}

void change(int pos,int val){
	int d=BT.size()-1;
	while(d){
		if(pos%2==0)
			BT[d-1][pos/2] += val;
		pos /=2;
		d--;
	}
}

void Build_BT(){
	int i,j,k;
	BT.clear();
	V.clear();
	for(int i=0 ; (1<<i)/2 < N+M ; i++)
		BT.push_back(VI(1<<i));
	V.resize(N);
	FOR(i,N){
		change(M+i,1);
		V[i] = M+i;
	}
}

int main(){
	ifstream cin("input.txt");
	int T;
	cin >> T;
	while(T--){
		int i,j,k;
		cin >> N >> M;
		Build_BT();
		while(M--){
			cin >> k; k--;
			cout << cal(V[k]);
			if(M) cout <<" ";
			change(V[k],-1);
			V[k] = M;
			change(V[k],1);
		}
		cout << endl;
	}
}