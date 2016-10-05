#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>

using namespace std;

const double EPS=1e-9;

int main(){
	int N,n;
	ifstream cin("Game.h");
	while(cin>>N>>n){
		vector<double> P(N,0);
		vector<double> p(N+1,0.25);
		p[0]=1;
		p[N]=1;
		for(int j=1;j<N;j++)
			cin>>P[j];
		double diff=1;
		double buf;

		while(diff>EPS){
			for(int i=1;i<N;i++){
				buf=p[i];
				p[i]=((1-P[i])*p[i-1])+(P[i]*p[i+1]);
				diff=fabs(buf-p[i]);
			}
		}
		cout<<p[n-1]<<endl;
	}
}
