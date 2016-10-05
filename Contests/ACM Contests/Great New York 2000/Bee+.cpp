#include <iostream>
#include <fstream>
#include <cmath>
#include <vector>
#include <iomanip>

using namespace std;

const double EPS=1e-9;
const double PI=acos(-1.0);
double d;
double X,Y,D;
pair<double,double> A,B;
pair<double,double> CA,CB;

double dist(pair<double,double> p1,pair<double,double> p2){
	return sqrt( ((p2.first-p1.first)*(p2.first-p1.first)) + ((p2.second-p1.second)*(p2.second-p1.second)) );
}

void func(){
	vector<pair<double,double> >v(3);
	double buf;

	v[0].first=((int)floor(A.first/X))*X;
	v[1].first=v[0].first;
	v[2].first=v[0].first+X;
	v[0].second=(abs((int)(v[0].first/X))%2)*Y;
	v[0].second+=((int)floor((A.second-v[0].second)/(2*Y)))*2*Y;
	v[1].second=v[0].second+(2*Y);
	v[2].second=v[0].second+Y;
	
	buf=D*3;
	for(int i=0;i<3;i++){
		if(dist(v[i],A)<buf){
			buf=dist(v[i],A);
			CA=v[i];
		}
	}

	v[0].first=((int)floor(B.first/X))*X;
	v[1].first=v[0].first;
	v[2].first=v[0].first+X;
	v[0].second=(abs((int)(v[0].first/X))%2)*Y;
	v[0].second+=((int)floor((B.second-v[0].second)/(2*Y)))*2*Y;
	v[1].second=v[0].second+(2*Y);
	v[2].second=v[0].second+Y;

	buf=D*3;
	for(int i=0;i<3;i++){
		if(dist(v[i],B)<buf){
			buf=dist(v[i],B);
			CB=v[i];
		}
	}
}

double cal(){
	if(CA==CB)
		return dist(A,B);

	double ret;
	ret=(fabs(CB.first-CA.first)/X)*D;
	ret+=dist(A,CA)+dist(B,CB);
	if(max(CA.second,CB.second)-((fabs(CB.first-CA.first)/X)*Y) > min(CA.second,CB.second))
		ret+=max(CA.second,CB.second)-((fabs(CB.first-CA.first)/X)*Y)-min(CA.second,CB.second);

	return ret;
}

int main(){
	//ifstream cin("Bee.h");
	while(true){
		cin>>d>>A.first>>A.second>>B.first>>B.second;
		if(d==0)
			return 0;

		X=d+(d*cos(PI/3));
		Y=d*sin(PI/3);
		D=sqrt((X*X)+(Y*Y));

		func();
		
		cout<<setiosflags(ios::fixed)<<setprecision(3)<<cal()+EPS<<endl;
	}
}