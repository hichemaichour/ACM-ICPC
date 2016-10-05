#include <iostream>
#include <fstream>
#include <cmath>
#include <string>

using namespace std;

string str;
double slope;

void Get_Slope(){
	double x=0;
	double y=0;
	for(int i=0;i<str.size();i++){
		if(str[i]=='R')
			x++;
		else
			y++;
	}
	slope=y/x;
}

double f(double x,double y){
	return ( (slope*x*x/2) - (y*x) );
}

double cal(){
	double ret=0;

	double x=0;
	double y=0;
	double buf;
	for(int i=0;i<str.size();i++){
		if(str[i]=='U')
			y++;
		else{
			if( (y/slope > x) && (y/slope < x+1) ){
				buf=f(y/slope,y)-f(x,y);
				buf=f(x+1,y)-f(y/slope,y);
				ret+=fabs(f(y/slope,y)-f(x,y));
				ret+=fabs(f(x+1,y)-f(y/slope,y));
				x++;
				continue;
			}
			buf=f(x+1,y)-f(x,y);
			ret+=fabs(f(x+1,y)-f(x,y));
			x++;
		}
	}

	return ret;
}

int main(){
	ifstream cin("Geometry.h");
	for(int cnt=1;true;cnt++){
		cin>>str;
		if(str=="S")
			return 0;
		str.resize(str.size()-1);

		Get_Slope();

		cout<<cnt<<". "<<cal()<<endl;
	}
}