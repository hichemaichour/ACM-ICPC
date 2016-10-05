#include <iostream>
#include <fstream>
#include <cmath>
#include <iomanip>

// h H g -

using namespace std;

const double PI=2*asin(1.0);

int main(){
	//ifstream cin("Clock.h");
	int M;
	cin>>M;
	for(int cnt=1;cnt<=M;cnt++){
		double area;
		double R;
		int H,M,S,U;
		cin>>H>>M>>S>>U;
		area=H+(M/60.0)+((S+(U/100.0))/3600);
		cin>>H>>M>>S>>U;
		area=(H+(M/60.0)+((S+(U/100.0))/3600))-area;
		area*=PI/6.0;
		cin>>R;
		area=(area/2.0)*(R*R);
		cout<<cnt<<". "<<setiosflags(ios::fixed)<<setprecision(3)<<area<<setprecision(0)<<endl;
	}
}