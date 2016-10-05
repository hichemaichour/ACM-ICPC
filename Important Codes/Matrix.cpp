#include "h++.cpp"

#define Mat vector<vector<double> >
#define VD vector<double>

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

// ==================================
// Matrix
// ==================================

Mat operator+(Mat& M1, Mat& M2){
	int R=M1.size(); int C=M1[0].size();
	if(R != M2.size() || C != M2[0].size())
		return Mat();
	Mat ret = M1;
	for(int i=0 ; i<R ; i++)
		for(int j=0 ; j<C ; j++)
			ret[i][j] += M2[i][j];
	return ret;
}

Mat operator-(Mat& M1, Mat& M2){
	int R=M1.size(); int C=M1[0].size();
	if(R != M2.size() || C != M2[0].size())
		return Mat();
	Mat ret = M1;
	for(int i=0 ; i<R ; i++)
		for(int j=0 ; j<C ; j++)
			ret[i][j] -= M2[i][j];
	return ret;
}

Mat operator*(Mat& M, double d){
	int R=M.size(); int C=M[0].size();
	Mat ret = M;
	for(int i=0 ; i<R ; i++)
		for(int j=0 ; j<C ; j++)
			ret[i][j] *= d;
	return ret;
}
Mat operator*(double d, Mat& M){ return M*d;}

Mat operator/(Mat& M, double d){
	int R=M.size(); int C=M[0].size();
	Mat ret = M;
	for(int i=0 ; i<R ; i++)
		for(int j=0 ; j<C ; j++)
			ret[i][j] /= d;
	return ret;
}

Mat operator*(Mat& M1, Mat& M2){
	int R=M1.size(); int C=M2[0].size();
	int buf=M1[0].size();
	if(buf != M2.size())
		return Mat();
	Mat ret(R,VD(C,0));
	for(int i=0 ; i<R ; i++)
		for(int j=0 ; j<C ; j++)
			for(int k=0 ; k<buf ; k++)
				ret[i][j] += M1[i][k]*M2[k][j];
	return ret;
}

void operator+=(Mat& M1, Mat& M2){ M1 = M1+M2;}
void operator-=(Mat& M1, Mat& M2){ M1 = M1-M2;}
void operator*=(Mat& M, double d){ M = M*d;}
void operator/=(Mat& M, double d){ M = M/d;}
void operator*=(Mat& M1, Mat& M2){ M1 = M1*M2;}

Mat Trans(Mat& M){
	int R=M.size(); int C=M[0].size();
	Mat ret(C,VD(R));
	for(int i=0 ; i<R ; i++)
		for(int j=0 ; j<C ; j++)
			ret[j][i] = M[i][j];
	return ret;
}
Mat Inv(Mat M){ // only for N*N Mat
	int i;
	int N=M.size();
	Mat I = Mat(N,VD(N,0));
	for(i=0 ; i<N ; i++) I[i][i]=1;
	
	Mat ret = Mat(N,VD(N));
	VI P;
	LUP_De(M,P);
	for(i=0 ; i<N ; i++)
		LUP_Sol(M,P,I[i],ret[i]);

	return ret;
}
double Det(Mat& M){
	int i,j,k;
	Mat LU = M;
	VI P;
	if(!LUP_De(LU,P))
		return 0;
	double ret=1;
	FOR(i,LU.size())
		ret *= LU[i][i];
	FOR(i,P.size()){
		while(P[i] != i){
			ret *= -1;
			swap(P[i],P[P[i]]);
		}
	}
	return ret;
}

// ==================================
// Code
// ==================================

int main(){
	ifstream cin("input.txt");
	int cnt = 0;
	while(true){
		int i,j;
		int N;
		cin>>N;
		if(N==0)
			return 0;
		Mat A(N,VD(N));

		for(i=0 ; i<N ; i++)
			for(j=0 ; j<N ; j++)
				cin>>A[i][j];

		cout<<++cnt<<". "<<Det(A)<<endl;
	}
}