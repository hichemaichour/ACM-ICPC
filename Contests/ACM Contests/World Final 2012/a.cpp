#include <iostream>
#include <fstream>

#include <vector>
#include <queue>
#include <map>
#include <set>

#include <algorithm>
#include <functional>
#include <cmath>

#define All(v)			v.begin(),v.end()

#define REP(i,a,b)		for(i=(int)a ; i<=(int)b ; i++)
#define FOR(i,N)		REP(i,0,N-1)

#define VI				vector<int>
#define VVI				vector<VI>
#define VVVI			vector<VVI>

#define VD				vector<double>
#define VVD				vector<VD>
#define VVVD			vector<VVD>

#define x				first
#define y				second
#define II				pair<int,int>
#define VII				vector<II>
#define VVII			vector<VII>

using namespace std;

int N;
VVI A,B,C;
VI x,y,z,vx,vy,vz;

int main(){
	ifstream cin("input.txt");
	for(int cnt=1 ; cin >> N ; cnt++){
		int i,j,ii,jj;
		A.clear(); B.clear(); C.clear();
		x.clear(); y.clear(); z.clear();
		vx.clear();vy.clear();vz.clear();

		A.resize(N,VI(N)); B.resize(N,VI(N)); C.resize(N,VI(N));
		x.resize(N); y.resize(N); z.resize(N);
		vx.resize(N); vy.resize(N); vz.resize(N);

		FOR(i,N)
			cin >> x[i] >> y[i] >> z[i] >> vx[i] >> vy[i] >> vz[i];

		FOR(i,N) FOR(j,N){
			int dx = x[i]-x[j]; int dy = y[i]-y[j]; int dz = z[i]-z[j];
			int dvx = vx[i]-vx[j]; int dvy = vy[i]-vy[j]; int dvz = vz[i]-vz[j];

			A[i][j] = dvx*dvx + dvy*dvy + dvz*dvz;
			B[i][j] = 2*(dx*dvx + dy*dvy + dz*dvz);
			C[i][j] = dx*dx + dy*dy + dz*dz;
		}

		VVVD T(N,VVD(N));
		double EPS = 0.000001;
		FOR(i,N) FOR(j,N) REP(ii,i,N-1) REP(jj,j,N-1){
			if(i==ii && j==jj)
				continue;

			int a = A[i][j] - A[ii][jj];
			int b = B[i][j] - B[ii][jj];
			int c = C[i][j] - C[ii][jj];

			double delta = b*b - 2*a*c;
			double t1,t2;

			if(a==0 && b==0)
				continue;
			if(a==0){
				t1 = -c/b;
				if(t1 > EPS){
					T[i][j].push_back(t1);
					T[ii][jj].push_back(t1);
				}
				continue;
			}

			if(fabs(delta) < EPS){
				t1 = -b/(2*a);
				t2 = -1;
			}
			else if(delta > EPS){
				t1 = (-b + sqrt(delta))/(2*a);
				t2 = (-b - sqrt(delta))/(2*a);
			}
			else{
				t1 = -1;
				t2 = -1;
			}

			if(t1 > EPS){
				T[i][j].push_back(t1);
				T[ii][jj].push_back(t1);
			}
			if(t2 > EPS){
				T[i][j].push_back(t2);
				T[ii][jj].push_back(t2);
			}
		}

		cout <<"Case "<<cnt<<": "<<endl;
	}
}