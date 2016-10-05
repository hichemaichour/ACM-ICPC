#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

const double EPS=1e-9;

int main(){
	while(true){
		int N,n;
		cin>>N;
		if(N==0)
			return 0; 
		cin>>n;
		vector<double> E(N,0.25);
		vector<double> p(N,0.25);
		E[0]=0;
		E[N-1]=0;
		p[0]=0;
		p[N-1]=1;
		double diff=1;
		double buf;

		while(diff>EPS){
			for(int i=1;i<N-1;i++){
				buf=E[i];
				E[i]=1+(0.5*(E[i-1]+E[i+1]));
				diff=fabs(E[i]-buf);

				buf=p[i];
				p[i]=0.5*(p[i-1]+p[i+1]);
				diff=max(diff,fabs(buf-p[i]));
			}
		}
		cout<<"It takes "<<E[n-1]<<" steps to stop with a probablity of "<<p[n-1]<<" to stop at jail"<<endl;
	}
}
