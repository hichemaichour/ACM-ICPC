#include <iostream>
#include <fstream>
#include <cmath>
#include <vector>

const double EPS = 1e-9;
const double PI = acos(-1.0);

using namespace std;

#define Vector Point

struct Point{
	double x,y;
	Point (double a=0,double b=0){ x=a; y=b; }

	Point operator + (Point s){ return(Point( x+s.x , y+s.y ));}
	Point operator - (Point s){ return(Point( x-s.x , y-s.y ));}

	Point operator * (double s){ return(Point(x*s,y*s));}
	Point operator / (double s){ return(Point(x/s,y/s));}

	void operator += (Point s){*this=*this+s;}
	void operator -= (Point s){*this=*this-s;}
	void operator *= (double s){*this=*this*s;}
	void operator /= (double s){*this=*this/s;}

	bool operator == (Point s){return fabs(x-s.x)<EPS && fabs(y-s.y)<EPS;}
	bool operator != (Point s){return !(*this==s);}

	double Dot(Point s){ return( x*s.x + y*s.y );}
	double Cross(Point s){ return( (x*s.y)-(y*s.x) );}

	double Abs(){ return sqrt( x*x + y*y );}

	Point Unit(){ return (Point( x/Abs() , y/Abs() ));}
};

Vector Rotate(Vector v,double theta){
	if(v.Abs()<EPS)
		return v;
	theta += atan2( v.Unit().y , v.Unit().x );
	return Point( cos(theta) , sin(theta) )*v.Abs();
}

double TriArea(Point a,Point b,Point c){ return fabs( (a-b).Cross(a-c) )/2; }

int main(){

}