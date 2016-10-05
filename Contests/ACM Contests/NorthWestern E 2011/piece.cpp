#include<iostream>
#include<fstream>

#include<vector>
#include<set>

#define FOR(i,N)	for(i=0 ; i<(int)N ; i++)
#define REP(i,a,b)	for(i=(int)a ; i<=(int)b ; i++)

#define VI			vector<int>
#define VVI			vector<VI>

#define VC			vector<char>
#define VVC			vector<VC>

#define II			pair<int,int>
#define VII			vector<II>

using namespace std;

int L,W;
VVC B;
int dx[] = {-1, 0,1,0,-1};
int dy[] = { 0,-1,0,1, 0};
VII BLK;

int Cal(int pos){
	int i;
	int ux,uy;
	int vx1,vx2,vy1,vy2;
	int ans = 0;
	ux=BLK[pos].first; uy=BLK[pos].second;
	FOR(i,4){
		vx1=ux+dx[i]; vx2=ux+dx[i+1];
		vy1=uy+dy[i]; vy2=uy+dy[i+1];
		if(vx1<0 || vx1>=L || vx2<0 || vx2>=L) continue;
		if(vy1<0 || vy1>=W || vy2<0 || vy2>=W) continue;
		if(B[vx1][vy1]!='W' || B[vx2][vy2]!='W') continue;
		ans++;
	}
	return ans;
}

void Assign(int pos,VI& gd){
	int i,j;
	int ux,uy;
	int vx1,vx2,vy1,vy2;
	ux=BLK[pos].first; uy=BLK[pos].second;
	FOR(i,4){
		vx1=ux+dx[i]; vx2=ux+dx[i+1];
		vy1=uy+dy[i]; vy2=uy+dy[i+1];
		if(vx1<0 || vx1>=L || vx2<0 || vx2>=L) continue;
		if(vy1<0 || vy1>=W || vy2<0 || vy2>=W) continue;
		if(B[vx1][vy1]!='W' || B[vx2][vy2]!='W') continue;
		B[ux][uy]='.'; B[vx1][vy1]='.'; B[vx2][vy2]='.';
		FOR(j,4){
			ux=vx1+dx[i]; uy=vx1+dy[i];

			ux=vx2+dx[i]; uy=vy1+dy[i];
		}
	}
}

bool Solve(int NB){
	int i,j,k;
	VI V(BLK.size());
	VI gd;
	FOR(i,BLK.size()){
		if(Cal(i)==0)
			return false;
		if(Cal(i)==1)
			gd.push_back(i);
	}
	while(!gd.empty()){
		k = gd.back(); gd.pop_back();
		Assign(k,gd);
	}
	return NB==0;
}

int main(){
	ifstream cin("input.txt");
	int T;
	cin >> T;
	while(T--){
		int i,j,k1,k2;
		cin >> L >> W;
		B.clear(); B.resize(L,VC(W));
		FOR(i,L) FOR(j,W) cin >> B[i][j];

		k1=0; k2=0;
		BLK.clear();
		FOR(i,L) FOR(j,W){
			if(B[i][j] == 'B'){
				k1++;
				BLK.push_back(II(i,j));
			}
			if(B[i][j] == 'W')
				k2++;
		}
		if(k2 != k1*2){
			cout <<"NO"<< endl;
			continue;
		}

		if(Solve(k1))
			cout <<"YES"<<endl;
		else
			cout <<"NO"<<endl;
	}
	return 0;
}