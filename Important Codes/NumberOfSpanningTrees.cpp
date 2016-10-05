#include "h++.cpp"

#define Mat vector<vector<double> >
#define VD vector<double>

const double EPS = 1e-9;

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

int N;
VVI Adj;

NumOfST(){
	int i,j,k;
	Mat M(N,VD(N));
	FOR(i,N)
		M[i][i] = Adj[i].size();
	FOR(i,N){
		FOR(j,Adj[i].size()){
			int u = i;
			int v = Adj[i][j];
			M[u][v]--;
		}
	}
	return Det(M);
}

int main(){

}