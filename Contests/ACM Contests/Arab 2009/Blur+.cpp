#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include <iomanip>

using namespace std;

#define II pair<int,int>
#define VI vector<int>
#define VD vector<double>
#define Mat vector<vector<double> >
#define VVI vector<VI>
#define x first
#define y second

const double EPS = 1e-9;

// ==================================
// Solve
// ==================================

bool LUP_De(Mat& LU, VI& P){
	int i,j,k,kk;
	P.clear();

	int N = LU.size();

	P.resize(N);
	for(i=0 ; i<N ; i++)
		P[i] = i;

	for(k=0 ; k<N ; k++){
		double p = 0;
		for(i=k ; i<N ; i++){
			if(fabs(LU[i][k]) > p){
				p = fabs(LU[i][k]);
				kk = i;
			}
		}

		if(fabs(p) < EPS)
			return false; // singular

		swap(P[k],P[kk]);
		for(i=0 ; i<N ; i++)
			swap(LU[k][i],LU[kk][i]);

		for(i=k+1 ; i<N ; i++){
			LU[i][k] /= LU[k][k];
			for(j=k+1 ; j<N ; j++)
				LU[i][j] -= LU[i][k]*LU[k][j];
		}
	}
	return true;
}

void LUP_Sol(Mat& LU , VI& P , VD& b , VD& x){
	int i,j;
	int N = LU.size();

	VD y(N);
	for(i=0 ; i<N ; i++){
		y[i] = b[P[i]];
		for(j=0 ; j<i ; j++)
			y[i] -= LU[i][j]*y[j];
	}

	x.resize(N);
	for(i=N-1 ; i>=0 ; i--){
		x[i] = y[i];
		for(j=i+1 ; j<N ; j++)
			x[i] -= LU[i][j]*x[j];
		x[i] /= LU[i][i];
	}
}

bool Solve(Mat& A, VD b, VD& x){
	VI P;
	Mat LU = A;
	if(LUP_De(LU,P)==false)
		return false;
	LUP_Sol(LU,P,b,x);
	return true;
}

VVI dx;
VVI dy;
int W,H,D;

void init(){
	dx.clear();
	dx.resize(21);
	dy.clear();
	dy.resize(21);

	int i,j,k;
	for(i=-10 ; i<=10 ; i++){
		for(j=-10 ; j<=10 ; j++){
			k = abs(i)+abs(j);
			dx[k].push_back(i);
			dy[k].push_back(j);
		}
	}
}

II trans(II p,int j,int k){
	p.x += dx[j][k];
	p.y += dy[j][k];
	return p;
}

void Build_Mat(Mat& A){
	A.clear();
	A.resize(W*H,VD(W*H));
	int i,j,k;
	for(i=0 ; i<W*H ; i++){
		II p = II(i%W , i/W);
		int cnt = 0;
		for(j=0 ; j<=D ; j++){
			for(k=0 ; k<dx[j].size() ; k++){
				II nxt = trans(p,j,k);
				if(nxt.x<0 || nxt.x>=W || nxt.y<0 || nxt.y>=H)
					continue;
				int buf = nxt.y*W + nxt.x;
				A[i][buf] = 1;
				cnt++;
			}
		}

		for(j=0 ; j<W*H ; j++)
			if(A[i][j] > 0.5)
				A[i][j] /= cnt;
	}
}

int main(){
	ifstream cin("I.h");
	init();
	bool flg = false;
	while(true){
		int i,j,k;
		cin >> W >> H >> D;
		if(W == 0)
			return 0;
		if(flg)
			cout<<endl;
		flg = true;

		VD b;
		Mat In(H,VD(W));
		for(i=0 ; i<H ; i++){
			for(j=0 ; j<W ; j++){
				cin >> In[i][j];
				b.push_back(In[i][j]);
			}
		}

		Mat A;
		Build_Mat(A);

		VD x;
		Solve(A,b,x);
		for(i=0 ; i<H ; i++){
			for(j=0 ; j<W ; j++){
				k = i*W + j;
				if(fabs(x[k])<EPS)
					x[k] = 0;
				cout << setiosflags(ios::fixed) << setprecision(2) << setw(8) << x[k];
			}
			cout << endl;
		}
	}
}