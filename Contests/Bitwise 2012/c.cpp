#include <iostream>
#include <fstream>
#include <vector>
#include <map>

#define REP(i,a,b)		for(i=(int)a ; i<=(int)b ; i++)
#define FOR(i,N)		REP(i,0,N-1)

#define VI				vector<int>
#define VVI				vector<VI>

using namespace std;

int N,M;
VI V;
VVI P;

VI p;
void PF(int N){
	if (N==1 || N==0 || N==-1)
		return;
	if(N<-1){
		PF(N*-1);
		return;
	}

	for(int i=2;i<=sqrt((double)N);i++){
		if(N%i==0){
			p.push_back(i);
			PF(N/i);
			return;
		}
	}

	p.push_back(N);
}

int main(){
	ifstream cin("c.txt");
	while(cin >> N >> M){
		int i,j,k;
		V.resize(N);
		FOR(i,N)
			cin >> V[i];

		P.clear();
		FOR(i,N){
			p.clear();
			PF(V[i]);
			P.push_back(p);
		}

		FOR(i,M){

		}
	}
	return 0;
}