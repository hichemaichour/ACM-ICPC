#include <iostream>
#include <fstream>
#include <cmath>
#include <vector>

using namespace std;

const double EPS = 1e-5;
const double PI = acos(-1.0);

// *****************************
// Point
// *****************************

struct Point{
	double x,y,z;
	Point (double a=0,double b=0,double c=0){ x=a; y=b; z=c;}

	Point operator + (Point s){ return(Point( x+s.x , y+s.y , z+s.z));}
	Point operator - (Point s){ return(Point( x-s.x , y-s.y , z-s.z));}

	Point operator * (double s){ return(Point(x*s,y*s,z*s));}
	Point operator / (double s){ return(Point(x/s,y/s,z*s));}

	void operator += (Point s){*this=*this+s;}
	void operator -= (Point s){*this=*this-s;}
	void operator *= (double s){*this=*this*s;}
	void operator /= (double s){*this=*this/s;}

	bool operator == (Point s)
{ return fabs(x-s.x)<EPS && fabs(y-s.y)<EPS && fabs(z-s.z)<EPS;}
	bool operator != (Point s){return !(*this==s);}

	double Dot(Point s){ return( x*s.x + y*s.y + z*s.z);}
	Point Cross(Point s)
{ return Point( (y*s.z)-(z*s.y) , (z*s.x)-(x*s.z) , (x*s.y)-(y*s.x) );}

	double Abs(){ return sqrt( x*x + y*y + z*z);}

	Point Unit(){ return (Point( x/Abs() , y/Abs() , z/Abs() ));}
};

// *****************************
// Angle
// *****************************

double AngleUsingSides(double a,double b,double c)
{ return acos( (b*b + c*c - a*a) / (2*b*c) );}

// *****************************
// Code
// *****************************

vector<Point> v;

int main(){
	//ifstream cin("Lost.h");
	int T;
	cin>>T;
	while(T--){
		v.clear();
		int i,j,k;

		double p,q,r;
		double sp,sq,sr;
		cin>>sp>>sq>>sr;
		p = AngleUsingSides(sp,sq,sr);
		q = AngleUsingSides(sq,sp,sr);
		r = AngleUsingSides(sr,sp,sq);

		int N;
		cin>>N;
		v.resize(N);
		for(i=0 ; i<N ; i++)
			cin>>v[i].x>>v[i].y>>v[i].z;

		bool flag=true;
		for(i=0 ; i<N ; i++){
			for(j=0 ; j<N ; j++){
				for(k=0 ; k<N ; k++){
					if(i!=j && i!=k && j!=k){
						sp = AngleUsingSides( (v[j]-v[k]).Abs() , (v[i]-v[k]).Abs() , (v[j]-v[i]).Abs());
						sq = AngleUsingSides( (v[i]-v[k]).Abs() , (v[j]-v[i]).Abs() , (v[j]-v[k]).Abs());
						sr = AngleUsingSides( (v[j]-v[i]).Abs() , (v[j]-v[k]).Abs() , (v[i]-v[k]).Abs());
						if(fabs(sp-p)<EPS && fabs(sq-q)<EPS && fabs(sr-r)<EPS && flag){
							cout<<i+1<<" "<<j+1<<" "<<k+1<<endl;
							flag=false;
						}
					}
				}
			}
		}
	}
	return 0;
}