#include <iostream>
#include <fstream>

#define REP(i, a, b) 		for (i=(int)a ; i<=(int)b ; i++)
#define FOR(i, n)			REP (i, 0, n-1)

#define All(v)				v.begin(),v.end()

#define VI					vector<int>
#define VVI					vector<VI>

using namespace std;

int N;
const long long inf = 1e17;
long long Hx[15],Hy[15],Tx[15],Ty[15];
long long dist[15][15];
long long mc[15];
long long cc[15];
long long cccnt;

long long Dis(long long x,long long y){
	long long ret;

	if(x<0) x *= -1;
	if(y<0) y *= -1;
	if(x>y) swap(x,y);

	if(x==0 && y==0) return 0;
	if(x==0 && y==1) return 3;
	if(x==0 && y==2) return 2;
	if(x==0 && y==3) return 3;
	if(x==1 && y==1) return 2;
	if(x==1 && y==2) return 1;
	if(x==2 && y==2) return 4;
	if(x==2 && y==3) return 3;

	if(x<=y/2){
		y -= 2*x;
		ret = (y/4)*2 + x + y%4;
	}
	else{
		ret = x+y;
		ret = ret/3 + ret%3;
	}
	return ret;
}

int augCycle(){
	int i,j,k;
	long long dt[15][15];
	long long fs[15][15];
	FOR(i,N){
		FOR(j,N){
			dt[i][j] = dist[i][mc[i]]-dist[i][mc[j]];
			fs[i][j] = j;
		}
	}

	FOR(k,N){
		FOR(i,N){
			FOR(j,N){
				if(dt[i][k]+dt[k][j] > dt[i][j]){
					dt[i][j] = dt[i][k]+dt[k][j];
					fs[i][j] = fs[i][k];
					if(i==j){
						cccnt=0;
						do{
							cc[cccnt]=i; cccnt++;
							i=fs[i][j];
						}while(i!=j);
						return 1;
					}
				}
			}
		}
	}
	return 0;
}

long long matching(){
	int i,j,k;
	FOR(i,N) mc[i] = i; // initialy ... every knight is assigned to the same target

	
	while(augCycle()){
		j = mc[cc[0]];
		FOR(i,cccnt-1) mc[cc[i]] = mc[cc[i+1]];
		mc[cc[i]] = j; 
	}
	long long ret=0;
	FOR(i,N) ret += dist[i][mc[i]];
	return ret;
}

int main(){
	ifstream cin("input.txt");
	for(int cnt=1 ; true ; cnt++){
		int i,j,k;
		cin >> N;
		if(!N) break;

		FOR(i,N) cin >> Hx[i] >> Hy[i];
		FOR(i,N) cin >> Tx[i] >> Ty[i];

		FOR(i,N) FOR(j,N) dist[i][j] = Dis(Hx[i]-Tx[j] , Hy[i]-Ty[j]);

		cout << cnt<<". "<<matching()<<endl;
	}
	return 0;
}