#include <iostream>
#include <cmath>

using namespace std;

#define Vector Point
const double EPS = 1e-9;

struct Point{
	double x,y,z;
	Point (double a=0,double b=0,double c=0){ x=a; y=b; z=c;}

	Point operator+ (Point s){ return(Point( x+s.x , y+s.y , z+s.z ));}
	Point operator- (Point s){ return(Point( x-s.x , y-s.y , z-s.z ));}

	Point operator * (double s){ return(Point(x*s,y*s,z*s));}
	Point operator / (double s){ return(Point(x/s,y/s,z/s));}

	void operator += (Point s){*this=*this+s;}
	void operator -= (Point s){*this=*this-s;}
	void operator *= (double s){*this=*this*s;}
	void operator /= (double s){*this=*this/s;}

	bool operator == (Point s){return (x==s.x && y==s.y && z==s.z);}
	bool operator != (Point s){return !(*this==s);}

	double Dot(Point s){ return( x*s.x + y*s.y + z*s.z );}
	Point Cross(Point s){ return(Point( (y*s.z)-(z*s.y) , (z*s.x)-(x*s.z) , (x*s.y)-(y*s.x) ));}

	double Abs(){ return sqrt( x*x + y*y + z*z );}

	Point Unit(){ return (Point( x/Abs() , y/Abs() , z/Abs() ));}
};

struct Line{
	Vector v;
	Point p;

	Line(Vector V,Point P){v=V; p=P;}

	bool operator ==(Line L){return (v==L.v && p==L.p);}
	bool operator !=(Line L){return !(*this==L);}

	bool IsOn(Point P){return fabs(v.Cross(P-p).Abs())<EPS;}

	int Intersect(Line L,Point& P){// 0 one point - 1 same line - 2 Parallel - 3 No Intersection
		if( fabs(v.Dot(L.v)) <EPS){ // Parallel
			if(IsOn(L.p))
				return 1;
			return 2;
		}
		/*
		To Do: Find the Point of intersection if exsit
		*/
		return 0;
	}

	double dist(Point P){return v.Cross(P-p).Abs()/v.Abs();}
};

struct Plane{
	Vector n;
	Point p;

	Plane(Vector N,Point P){n=N; p=P;}

	bool IsOn(Point P){return fabs( n.Dot(p-P) )<EPS;}
	bool IsOn(Line L){return (fabs( n.Dot(L.v) )<EPS) && IsOn(L.p);}

	int Intersect(Plane PL,Line& L){ // 0 One Line - 1 same plane - 2 Parallel
		if(n.Cross(PL.n).Abs()<EPS){
			if(IsOn(PL.p))
				return 1;
			return 2;
		}

		L.v=n.Cross(PL.n).Unit();
		/*
		To Do: find the line of intersection
		*/
		return 0;
	}

	int Intersect(Line L,Point& P){ // 0 One Point - 1 same line - 2 Parallel
		if(IsOn(L))
			return 1;
		if( fabs(n.Dot(L.v)) < EPS )
			return 2;

		double Lmda=(n.Dot(p) - n.Dot(L.p)) / n.Dot(L.v);
		P=L.p + L.v*Lmda;
		return 0;
	}
};

int main(){
	return 0;
}
