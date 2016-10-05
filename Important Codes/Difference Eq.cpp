#include <iostream>
#include <fstream>
#include <cmath>

using namespace std;

// Y(n) = aY(n-1) + bY(n-2) : Y(0) = y0 ... Y(1) = y1

double Y0=1;
double Y1=1;
double A=1;
double B=1;

double C1;
double C2;
double R1;
double R2;
double R;
double Theta;
int Flag;

void init(){ // Set Global Variables
	A/=2;
	B*=-1;

	if(B == A*A){
		Flag=0;

		R=A;

		C1 = Y0;
		C2 = (Y1 - C1*R)/R;
	}

	else if(B < A*A){
		Flag=1;

		R1=A-sqrt(A*A - B);
		R2=A+sqrt(A*A - B);

		C1= (Y1 - Y0*R2) / (R1 - R2);
		C2= Y0 - C1;
	}

	else{
		Flag=-1;

		R=sqrt(B);
		Theta=atan(sqrt(B-A*A) / A);

		C1=Y0;
		C2= (Y1 - C1*R*cos(Theta)) / (R*sin(Theta));
	}
}

double Y(double n){
	switch(Flag){
		case 0:
			return C1*pow(R,n) + C2*n*pow(R,n);
		case 1:
			return C1*pow(R1,n) + C2*pow(R2,n);
		case -1:
			return C1*pow(R,n)*cos(Theta*n) + C2*pow(R,n)*sin(Theta*n);
	}
}

int main(){
	init();
	for(int i=0;i<20;i++)
		cout<<i<<" "<<Y(i)<<endl;
}
