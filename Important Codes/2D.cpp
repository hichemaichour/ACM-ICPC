#include <iostream>
#include <fstream>
#include <sstream>

#include <iomanip>

#include <algorithm>

#include <vector>
#include <deque>
#include <list>
#include <stack>
#include <queue>
#include <set>
#include <map>
#include <bitset>
#include <string>

#include <iterator>
#include <functional>
#include <complex>
#include <numeric>
#include <valarray>

#include <cmath>

using namespace std;

#define REP(i, a, b) 		for (i=(int)a ; i<=(int)b ; i++)
#define REPD(i, a, b)		for (i=(int)a ; i>=(int)b ; i--)
#define REPI(i, v)			for (i=v.begin() ; i!=v.end() ; i++)
#define FOR(i, n)			REP (i, 0, n-1)
#define FORD(i, n)			REPD(i, n-1, 0)

#define All(v)				v.begin(),v.end()
#define Resize(v,N)			v.clear(); v.resize(N);

#define IsIn(v,e)			(find(All(v),e) != v.end())
#define Remove(v,e)			v.resize( remove(All(v),e) - v.begin() )

#define VI					vector<int>
#define VVI					vector<VI>

#define x					first
#define y					second
#define II					pair<int,int>
#define VII					vector<II>
#define VVII				vector<VII>


#define MP make_pair
#define Inf 1e20

using namespace std;

const double EPS = 1e-9;
const double PI = acos(-1.0);

// ==================================
// Point and Vector
// ==================================

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
//	bool operator < (Point s)const{ // const so that STL accept it as a defualt <
//		if(fabs(x-s.x) > EPS)
//			return x < s.x;
//		return y < s.y;
//	}
	bool operator < (Point s)const{ // const so that STL accept it as a defualt <
		if(fabs(y-s.y) > EPS)
			return y > s.y;
		return x < s.x;
	}
	bool operator <= (Point s){return (*this<s) || (*this==s);}
	bool operator > (Point s){return !(*this<s) && !(*this==s);}
	bool operator >= (Point s){return !(*this<s);}


	double Dot(Point s){ return( x*s.x + y*s.y );}
	double Cross(Point s){ return( (x*s.y)-(y*s.x) );}

	double Abs(){ return sqrt( x*x + y*y );}

	Point Unit(){ return (Point( x/Abs() , y/Abs() ));}
};

// ==================================
// General
// ==================================

double AreaUnderLine(Point a,Point b){ return 0.5*(b.x-a.x)*(b.y+a.y);} // negative if the vector to the left ... positive if the vector to the right

int SideSign(Point a,Point b,Point r){ // -1 Left - 0 On - 1 right
	if( (b-a).Cross(r-a) > EPS ) return -1;
	else if( (b-a).Cross(r-a) < -EPS ) return 1;
	else return 0;
}

void ClosestPoint(Point a,Point b,Point p,Point& r){ r = a + (b-a).Unit() * ((b-a).Unit().Dot(p-a));}

bool OnLine(Point a,Point b,Point r){ return fabs((a-b).Cross(a-r)) < EPS;}
bool OnSeg(Point a,Point b,Point r){ return (a==r || b==r) || (OnLine(a,b,r) && (b-r).Unit()==(r-a).Unit());}
bool OnHalfLine(Point a,Vector v,Point r){ return (a==r) || (OnLine(a,a+v,r) && (r-a).Unit()==v.Unit());}
bool OnCir(Point o,double rad,Point r){ return fabs( (r-o).Abs() - rad ) < EPS;}
bool InCir(Point o,double rad,Point r){ return ( (r-o).Abs() < rad+EPS );}

// ==================================
// Angles
// ==================================

double AngleUsingSides(double a,double b,double c){ return acos( (b*b + c*c - a*a) / (2*b*c) );}

double AngleBetweenSeg(Point p,Point a,Point b){ // angle p->a to p->b (-PI .. PI)
	if(a==b)
		return 0;
	Vector v,v1,v2;
	v1 = (a-p).Unit();
	v2 = Point( -v1.y , v1.x );
	v = b-p;
	double theta = atan2( v.Dot(v2) , v.Dot(v1) );
	if( theta < -EPS ) theta += 2*PI;
	return theta;
}

Vector Rotate(Vector v,double theta){
	if(v.Abs()<EPS)
		return v;
	theta += atan2( v.Unit().y , v.Unit().x );
	return Point( cos(theta) , sin(theta) )*v.Abs();
}
Point Rotate(Point o,Point p,double theta){ return Rotate(p-o,theta) + o;}

Point Reflect(Point o,Point p){ return o - (p-o);}
Point Reflect(Point a,Point b,Point p){
	Point r;
	ClosestPoint(a,b,p,r);
	return (r-p)*2 + p;
}

// ==================================
// Lines - Segments - Half Lines
// ==================================

bool LineIntLine(Point a,Point b,Point A,Point B,Point& r){
	if( fabs((a-b).Cross(A-B)) < EPS )
		return false;

	double buf = (B-A).Cross(a-A) / (b-a).Cross(B-A) ;
	r = a + (b-a)*buf;
	return true;
}

bool SegIntSeg(Point a,Point b,Point A,Point B,Point& r){
	if (LineIntLine(a,b,A,B,r) == false)
		return false;
	return OnSeg(a,b,r) && OnSeg(A,B,r);
}

bool HalfLineIntHalfLine(Point a,Vector v,Point A,Vector V,Point& r){
	if (LineIntLine(a,a+v,A,A+V,r) == false)
		return false;
	return OnHalfLine(a,v,r) && OnHalfLine(A,V,r);
}

bool LineIntSeg(Point a,Point b,Point A,Point B,Point& r){
	if (LineIntLine(a,b,A,B,r) == false)
		return false;
	return OnSeg(A,B,r);
}

bool LineIntHalfLine(Point a,Point b,Point A,Vector V,Point& r){
	if (LineIntLine(a,b,A,A+V,r) == false)
		return false;
	return OnHalfLine(A,V,r);
}

bool SegIntHalfLine(Point a,Point b,Point A,Vector V,Point& r){
	if (LineIntLine(a,b,A,A+V,r) == false)
		return false;
	return OnSeg(a,b,r) && OnHalfLine(A,V,r);
}

// ==================================
// Circle
// ==================================

double CirArea(double rad){ return PI*rad*rad;}
double CirPerimeter(double rad){ return 2*PI*rad;}

double Arc(double rad,double theta){ return fabs(theta*rad);}
double Sector(double rad,double theta){ return fabs(theta*rad*rad/2);}


int CirIntCir(Point o,double rad,Point O,double Rad,Point& r1,Point& r2){ // 0 two - 1 one - 2 same - 3 none
	if( (o-O).Abs()<EPS ){
		if( fabs(rad-Rad) < EPS )
			return 2;
		return 3;
	}

	if(rad<Rad){ swap(o,O);	swap(rad,Rad); }

	if( (o-O).Abs()>rad+Rad+EPS || (o-O).Abs()<rad-Rad-EPS ) return 3;

	r1 = o + (O-o).Unit()*rad;
	r2 = r1;
	if( fabs( (o-O).Abs()-rad-Rad ) < EPS ) return 1;

	double theta=AngleUsingSides(Rad,(O-o).Abs(),rad);
	r1=Rotate(o,r1,theta);
	r2=Rotate(o,r2,-theta);
	return 0;
}

int CirIntLine(Point o,double rad,Point a,Point b,Point& r1,Point& r2){ // 0 two - 1 one - 2 none
	ClosestPoint(a,b,o,r1);
	r2=r1;

	if( (r1-o).Abs() > rad+EPS ) return 2;
	if( fabs( (r1-o).Abs()-rad ) < EPS ) return 1;

	double buf = sqrt( rad*rad - (r1-o).Abs()*(r1-o).Abs() );
	r1 += (b-a).Unit()*buf;
	r2 += (a-b).Unit()*buf;
	return 0;
}

int CirIntSeg(Point o,double rad,Point a,Point b,Point& r1,Point& r2){ // 0 two - 1 one - 2 none
	switch (CirIntLine(o,rad,a,b,r1,r2)){
		case 2:
			return 2;
		case 1:
			if (OnSeg(a,b,r1))
				return 1;
			return 2;
		case 0:
			if (OnSeg(a,b,r1) && OnSeg(a,b,r2))
				return 0;
			else if (OnSeg(a,b,r1))
				return 1;
			else if (OnSeg(a,b,r2)){
				r1=r2;
				return 1;
			}
			return 2;
	}
	return 2;
}

int CirIntHalfLine(Point o,double rad,Point a,Vector v,Point& r1,Point& r2){ // 0 two - 1 one - 2 none
	switch (CirIntLine(o,rad,a,a+v,r1,r2)){
		case 2:
			return 2;
		case 1:
			if (OnHalfLine(a,v,r1))
				return 1;
			return 2;
		case 0:
			if (OnHalfLine(a,v,r1) && OnHalfLine(a,v,r2))
				return 0;
			else if (OnHalfLine(a,v,r1))
				return 1;
			else if (OnHalfLine(a,v,r2)){
				r1=r2;
				return 1;
			}
			return 2;
	}
	return 2;
}

void Tangent(Point o,double rad,Point p,Vector& v){ v = Rotate((p-o).Unit(),PI/2);}

bool TangentFromPoint(Point o,double rad,Point p,Point& r1,Point& r2){
	if (InCir(o,rad,p))
		return false;

	double a,b,c;
	b = rad;
	c = (p-o).Abs();
	a = sqrt( c*c - b*b );
	double theta=AngleUsingSides(a,b,c);

	r1 = o + (p-o).Unit()*rad;
	r2 = r1;

	r1=Rotate(o,r1,theta);
	r2=Rotate(o,r2,-theta);
	return true;
}

bool CirTanCir(Point o,double rad,Point O,double Rad,vector<Point>& t1,vector<Point>& t2){
	Point p;
	if (CirIntCir(o,rad,O,Rad,p,p) != 3 || InCir(o,rad,O))
		return false;

	t1.resize(4);
	t2.resize(4);

	t1[0] = o + (O-o).Unit()*rad;
	t2[0] = O + (o-O).Unit()*Rad;
	t1[1] = t1[0];
	t2[1] = t2[0];

	Rotate(o,t1[0], PI/2); Rotate(O,t2[0],-PI/2);
	Rotate(o,t1[1],-PI/2); Rotate(O,t2[1], PI/2);

	p = (O-o)*(rad/Rad);
	TangentFromPoint(o,rad,p,t1[2],t1[3]);
	TangentFromPoint(O,Rad,p,t2[2],t2[3]);
	return true;
}

// ==================================
// Triangle
// ==================================

bool OnTri(Point a,Point b,Point c,Point r){ return (OnSeg(a,b,r) || OnSeg(b,c,r) || OnSeg(c,a,r));}
bool IsTri(Point a,Point b,Point c){ return fabs((a-b).Cross(a-c)) > EPS;}
bool IsTri(double a,double b,double c){ 
	double s = (a+b+c)/2;
	return s*(s-a)*(s-b)*(s-c) > EPS;
}

double TriArea(Point a,Point b,Point c){ return fabs( (a-b).Cross(a-c) )/2; }
double TriHeight(Point a,Point b,Point c){ return TriArea(a,b,c) * 2 / (b-c).Abs(); }

bool HeightCenter(Point a,Point b,Point c,Point& r){ // OrthoCenter
	if( TriArea(a,b,c) < EPS ) return false;
	Point r1,r2;
	ClosestPoint(b,c,a,r1); ClosestPoint(a,c,b,r2);
	return LineIntLine( a,r1 , b,r2 , r );
}

bool AngleCenter(Point a,Point b,Point c,Point& r){ // InCircle
	if( TriArea(a,b,c) < EPS ) return false;
	Point r1,r2;
	double d1,d2;
	d1 = (a-b).Abs() / ((a-b).Abs()+(a-c).Abs());
	d2 = (b-a).Abs() / ((b-a).Abs()+(b-c).Abs());
	r1 = b*d1 + c*(1-d1);
	r2 = a*d2 + c*(1-d2);
	return LineIntLine( a,r1 , b,r2 , r );
}

bool MedianCenter(Point a,Point b,Point c,Point& r){ // Centroid - 2:1 Ratio
	if( TriArea(a,b,c) < EPS ) return false;
	return LineIntLine( a,(b+c)/2 , b,(a+c)/2 , r );
}

bool CircleCenter(Point a,Point b,Point c,Point& r){ // CircumCenter
	if( TriArea(a,b,c) < EPS ) return false;
	Point a1,a2,b1,b2;
	a1 = (b+c)/2;
	a2 = (a+c)/2;
	b1 = a1 + Point( b.y-c.y , c.x-b.x );
	b2 = a2 + Point( a.y-c.y , c.x-a.x );
	return LineIntLine( a1,b1 , a2,b2 , r );
}

bool NinePointCenter(Point a,Point b,Point c,Point& r){ 
// 3 midpoints - 3 feet of altitude - 3 midpoints of orthocenter to the vertix 
	Point r1,r2;
	if( HeightCenter(a,b,c,r1) == false || CircleCenter(a,b,c,r2) == false )
		return false;
	r = (r1+r2)/2;
	return true;
}

// ==================================
// Convex
// ==================================

bool IsCon(vector<Point> Po){
	int i,j,k;
	FOR(i,Po.size()-1)
		REP(j,i+2,Po.size()-1)
			if((Po[i+1]-Po[i]).Cross(Po[j]-Po[i]) > EPS)
				return false;
	return true;
}

vector<Point> makeCon(vector<Point> Po) {
	int i,j,k;
	sort(All(Po));
	Po.push_back(Po.front()); // to make it a closed Convex
	FOR(i,Po.size()-1) {
		REP(j,i+2,Po.size()-1) {
			if ((Po[i+1]-Po[i]).Cross(Po[j]-Po[i]) > EPS)
				swap(Po[i+1],Po[j]);
			// remove on the same line || order it if you want
			else if( fabs( (Po[i+1]-Po[i]).Cross(Po[j]-Po[i]) ) < EPS){
// ***** choose one of the if statements based on your application ***** //
				// to order them
//				if((Po[i+1]-Po[i]).Abs() > (Po[j]-Po[i]).Abs()){
//					swap(Po[i+1],Po[j]); // the closer in i+1
//					swap(Po[i+2],Po[j]); // the further in i+2
//				}

				// to remove smallest
				if((Po[i+1]-Po[i]).Abs() < (Po[j]-Po[i]).Abs())
					swap(Po[i+1] , Po[j]); // the further in i+1
			}
		}
		if (Po[i+1] == Po[0])
			Po.resize(i+2);
	}

	Po.pop_back(); // to remove the added point which is equal to the first one
	return Po;
}

// ==================================
// Polygens
// ==================================

bool InPoly(vector<Point>& Po, Point p){
	int n=0;
	Point buf;
	for(int i=0 ; i<Po.size() ; i++)
		if(SegIntHalfLine(Po[i],Po[(i+1)%Po.size()] , p,p+p , buf))
			n++;
	return n==1;
}

bool OnPoly(vector<Point>& Po,Point p){
	for(int i=0 ; i<Po.size() ; i++)
		if(OnSeg( Po[i],Po[(i+1)%Po.size()] , p))
			return true;
	return false;
}

double PolyPerimeter(vector<Point>& Po){
	double buf=0;
	int n=Po.size();
	for(int i=0;i<n;i++) buf+=(Po[(i+1)%n]-Po[i]).Abs();
	return buf;
}

double PolyArea(vector<Point>& Po){
	double buf=0;
	int n=Po.size();
	for(int i=0;i<n;i++) buf+=AreaUnderLine(Po[i],Po[(i+1)%n]);
	return buf;
}

int main(){
	ifstream cin("input.txt");
	ofstream cout("Me.txt");
	int P;
	cin>>P;
	for(int cnt=1;cnt<=P;cnt++){
		vector<Point> points;

		int n,N;
		int i,j,k;
		cin>>n>>N;

		points.resize(N);

		for(i=0;i<N;i++)
			cin>>points[i].first>>points[i].second;

		points = makeCon(points);

		cout<<n<<" "<<points.size()<<endl;
		for(i=0;i<points.size();i++)
			cout<<points[i].first<<" "<<points[i].second<<endl;
	}
	cout.close();
}
