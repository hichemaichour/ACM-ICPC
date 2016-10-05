#include <iostream>
#include <algorithm>
#include <vector>
#include <fstream>
#include <cmath>

using namespace std;

#define All(v) v.begin(),v.end()
#define VI vector<int>
#define VVI vector<VI>

int N,K;			// Cities and # of Children
double Avg;			// Average
const int H = 0;	// Horizantal
const int V = 1;	// Vertical
VVI D(2);			// Cities vertically or horizantally
int A,B;			// Fraction
VI L;				// Lands

long gcd(long a,long b) {
	if (a%b==0) 
		return b; 
	else 
		return gcd(b,a%b);
}

void Cal(){
	int a = 0;
	for(int i=0 ; i<L.size() ; i++)
		a += abs(N - L[i]*K);
	int b = K*K;

	a /= gcd(a,b);
	b /= gcd(a,b);

	if(A==-1 || ((double)a/b < (double)A/B)){
		A = a;
		B = b;
	}
}

VI Rec(int dir , int pos=0 , int sum=0 , int child=0){
	int i,j,k;
	VI ret;
	if(child == K)
		Cal();

	else if(pos == D[dir].size()){
		L[child] = sum;
		Rec(dir,pos,0,child+1);
	}

	else if(sum + D[dir][pos] < Avg){
		Rec(dir , pos+1 , sum+D[dir][pos] , child);
		return;
	}

	else if(sum + D[dir][pos] == Avg){
		L[child] = sum + D[dir][pos];
		if(child+1 == K){
			while(pos+1 != D[dir].size()){
				L[child] += D[dir][pos+1];
				pos++;
			}
		}
		Rec(dir , pos+1 , 0 , child+1);
	}

	else if(sum + D[dir][pos] > Avg){
		L[child] = sum;
		if(child+1 == K){
			while(pos+1 != D[dir].size()){
				L[child] += D[dir][pos+1];
				pos++;
			}
		}
		Rec(dir , pos+1 , D[dir][pos] , child+1);

		L[child] = sum + D[dir][pos];
		if(child+1 == K){
			while(pos+1 != D[dir].size()){
				L[child] += D[dir][pos+1];
				pos++;
			}
		}
		Rec(dir , pos+1 , 0 , child+1);
	}
}

int main(){
	ifstream cin("I.h");
	for(int cnt=1 ; true ; cnt++){
		A = -1;
		B = -1;
		int i,j,k;
		cin >> N >> K;
		if(N==0)
			return 0;
		Avg = (double)N / K;

		VI X(N);
		VI Y(N);
		for(i=0 ; i<N ; i++)
			cin >> X[i] >> Y[i];

		sort(All(X));
		sort(All(Y));

		D[H].clear();
		j = X[0];
		k = 1;
		for(i=1 ; i<N ; i++){
			if(X[i] == j)
				k++;
			else{
				D[H].push_back(k);
				j = X[i];
				k = 1;
			}
		}
		D[H].push_back(k);

		D[V].clear();
		j = Y[0];
		k = 1;
		for(i=1 ; i<N ; i++){
			if(Y[i] == j)
				k++;
			else{
				D[V].push_back(k);
				j = Y[i];
				k = 1;
			}
		}
		D[V].push_back(k);

		L.clear();
		L.resize(K);
		if(D[H].size() > K)
			Rec(H);
		else{
			for(i=0 ; i<D[H].size() ; i++)
				L[i] = D[H][i];
			Cal();
		}

		L.clear();
		L.resize(K);
		if(D[V].size() > K)
			Rec(V);
		else{
			for(i=0 ; i<D[V].size() ; i++)
				L[i] = D[V][i];
			Cal();
		}

		cout << cnt <<". "<< A <<"/"<< B << endl;
	}
}