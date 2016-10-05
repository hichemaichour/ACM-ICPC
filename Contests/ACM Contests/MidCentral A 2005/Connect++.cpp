#include <iostream>
#include <deque>
#include <cmath>
#include <vector>
#include <list>
#include <algorithm>

#define Pair pair<int,int>
#define X first
#define Y second

using namespace std;

const double EPS = 1e-9;
const double PI = acos(-1.0);

// ************************
// Point
// ************************

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

// ************************
// Seg
// ************************

bool OnLine(Point a,Point b,Point r){ return fabs((a-b).Cross(a-r)) < EPS;}
bool OnSeg(Point a,Point b,Point r){ return (a!=r && b!=r) && (OnLine(a,b,r) && (b-r).Unit()==(r-a).Unit());}

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

// ************************
// Code
// ************************

vector<pair<Pair,Pair> > Seg;
vector<vector<Pair> > B;
vector<bool> b;
vector<vector<Pair> > W;
vector<bool> w;
int N,M;

bool Check(Pair p1, Pair p2){
	Point p;
	Point a = Point(p1.X,p1.Y);
	Point b = Point(p2.X,p2.Y);
	for(int i=0 ; i<Seg.size() ; i++){
		Point A = Point(Seg[i].first.X,Seg[i].first.Y);
		Point B = Point(Seg[i].second.X,Seg[i].second.Y);
		if(SegIntSeg(a,b,A,B,p))
			return false;
	}
	Seg.push_back(pair<Pair,Pair>(p1,p2));
	return true;
}

bool Connect(Pair p1, Pair p2){
	if( (abs(p1.X-p2.X)==2 && abs(p1.Y-p2.Y)==1) || (abs(p1.X-p2.X)==1 && abs(p1.Y-p2.Y)==2) )
		return Check(p1,p2);
	return false;
}

void Insert_B(Pair p){
	bool flg=false;
	bool c;
	int i,j,k;
	for(i=0 ; i<B.size() ; i++){
		if(b[i] == false)
			continue;
		
		c=false;
		for(j=0 ; j<B[i].size() ; j++)
			if(Connect(p,B[i][j]))
				c=true;

		if(c){
			if(flg){
				for(j=0 ; j<B[i].size() ; j++)
					B[k].push_back(B[i][j]);
				b[i]=false;
			}
			else{
				B[i].push_back(p);
				k=i;
				flg=true;
			}
		}
	}

	if(flg==false){
		B.push_back(vector<Pair>(1,p));
		b.push_back(true);
	}
}

void Insert_W(Pair p){
	bool flg=false;
	bool c;
	int i,j,k;
	for(i=0 ; i<W.size() ; i++){
		if(w[i] == false)
			continue;
		
		c=false;
		for(j=0 ; j<W[i].size() ; j++)
			if(Connect(p,W[i][j]))
				c=true;

		if(c){
			if(flg){
				for(j=0 ; j<W[i].size() ; j++)
					W[k].push_back(W[i][j]);
				w[i]=false;
			}
			else{
				W[i].push_back(p);
				k=i;
				flg=true;
			}
		}
	}

	if(flg==false){
		W.push_back(vector<Pair>(1,p));
		w.push_back(true);
	}
}

int main(){
	while(true){
		Seg.clear();
		B.clear();
		b.clear();
		W.clear();
		w.clear();
		int i,j,k;
		cin>>N>>M;
		if(N==0)
			return 0;

		for(i=0 ; i<M/2 ; i++){
			cin>>j>>k;
			Insert_B(Pair(j,k));
			cin>>j>>k;
			Insert_W(Pair(j,k));
		}
		
		cin>>j>>k;
		Insert_B(Pair(j,k));
		bool flg=false;
		for(i=0 ; i<B.size() ; i++){
			sort(B[i].begin(),B[i].end());
			if(B[i].front().first==0 && B[i].back().first==N)
				flg=true;
		}
		if(flg)
			cout<<"yes"<<endl;
		else
			cout<<"no"<<endl;
	}
}