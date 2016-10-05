// ==================================
// Headers
// ==================================

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
#include <valarray>

#include <cmath>

using namespace std;

#define REP(i, a, b) 		for (i=(int)a ; i<=(int)b ; i++)
#define REPD(i, a, b)		for (i=(int)a ; i>=(int)b ; i--)
#define REPI(i, v)			for (i=v.begin() ; i!=v.end() ; i++)
#define FOR(i, n)			REP (i, 0, n-1)
#define FORD(i, n)			REPD(i, n-1, 0)

#define All(v)				v.begin(),v.end()

#define PB					push_back
#define MP					make_pair

#define PQ					priority_queue

#define IsIn(v,e)			(find(All(v),e) != v.end())
#define Remove(v,e)			v.resize( remove(ALL(v),e) - v.begin() )


typedef long long			LL;
typedef long double			LD;
typedef pair<int, int>		II;
typedef vector<int>			VI;
typedef vector<VI>			VVI;
typedef vector<bool>		VB;
typedef vector<VB>			VVB;
typedef vector<double>		VD;
typedef vector<VD>			VVD;
typedef vector<LL>			VLL;
typedef vector<VLL>			VVLL;
typedef vector<LD>			VLD;
typedef vector<VLD>			VVLD;
typedef vector<II>			VII;
typedef vector<VII>			VVII;
typedef vector<string>		VS;
typedef vector<VS>			VVS;

// ==================================
// 2D Library
// ==================================

const double EPS = 1e-9;
const double PI = acos(-1.0);

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

bool OnLine(Point a,Point b,Point r){ return fabs((a-b).Cross(a-r)) < EPS;}
bool OnSeg(Point a,Point b,Point r){ return (a==r || b==r) || (OnLine(a,b,r) && (b-r).Unit()==(r-a).Unit());}
bool OnHalfLine(Point a,Vector v,Point r){ return (a==r) || (OnLine(a,a+v,r) && (r-a).Unit()==v.Unit());}

bool LineIntLine(Point a,Point b,Point A,Point B,Point& r){
	if( fabs((a-b).Cross(A-B)) < EPS )
		return false;

	double buf = (B-A).Cross(a-A) / (b-a).Cross(B-A) ;
	r = a + (b-a)*buf;
	return true;
}

bool SegIntHalfLine(Point a,Point b,Point A,Vector V,Point& r){
	if (LineIntLine(a,b,A,A+V,r) == false)
		return false;
	return OnSeg(a,b,r) && OnHalfLine(A,V,r);
}

// ==================================
// Code
// ==================================

#define x first
#define y second
#define UP first
#define DOWN second

Point NIL = Point(-1,-1);
int N;
VVII Po;
VVI Adj;
VI H;
II ret;
int Start;
int End;

bool Connect(int j,int k,Point p){
	int i;
	if(p == NIL)
		p = Point( Po[j].front().x , Po[j].front().y );
	Vector v = Point(1,0.000243213);
	int sum = 0;
	FOR(i,Po[k].size()-1){
		Point a = Point( Po[k][i].x , Po[k][i].y );
		Point b = Point( Po[k][i+1].x , Po[k][i+1].y );
		Point r;
		if(SegIntHalfLine(a,b,p,v,r))
			sum++;
	}
	return sum == 1;
}

int Get(Point p){
	int i,j,k;
	VI Gd;
	FOR(i,N){
		if(Connect(0,i,p))
			Gd.push_back(i);
	}

	VB done(Gd.size());
	k = -1;
	int buf;
	FOR(buf,Gd.size()-1){
		FOR(i,Gd.size()){
			j = Gd[i];
			if(Adj[j].empty() && !done[j]){
				done[j] = true;
				k = j;
				break;
			}
			else if(IsIn(Adj[j],k)){
				done[j] = true;
				k = j;
				break;
			}
		}
	}
	FOR(i,Gd.size())
		if(!done[i])
			return Gd[i];
	return N;
}

void Build_Graph(){
	int i,j,k;
	FOR(i,N){
		FOR(j,N){
			if(i==j)
				continue;
			if(Connect(i,j,NIL))
				Adj[i].push_back(j);
		}
	}

	Start = Get(Point(0,0));
	End = Get(Point(100000,0));

	VB Out(N);
	FOR(i,N)
		Out[i] = Adj[i].empty();
	FOR(i,N){
		FOR(j,Adj[i].size()){
			k = Adj[i][j];
			Adj[k].push_back(i);
		}
		REP(j,i+1,N-1){
			if(Out[i] && Out[j]){
				Adj[i].push_back(j);
				Adj[j].push_back(i);
			}
		}
		if(Out[i]){
			Adj[N].push_back(i);
			Adj[i].push_back(N);
		}
	}
}

void BFS(){
	ret = II(0,0);
	if(Start == End)
		return;

	int i;
	int u,v;
	queue<int> q;
	queue<II> d;
	VB done(N);

	q.push(Start);
	d.push(II(0,0));
	done[Start] = true;
	while(!q.empty()){
		u=q.front(); q.pop();
		ret=d.front(); d.pop();
		FOR(i,Adj[u].size()){
			v = Adj[u][i];

			if(u==N) // Taking care of the case when the start is outside
				H[u] = H[v];
			if(v==N && End == N) // Taking care of the case when the end is outside
				return;

			if(done[v] || v==N)
				continue;
			done[v] = true;

			if(v == End){
				if(H[u] > H[v]) // down
					ret.DOWN += H[u]-H[v];
				else // up
					ret.UP += H[v]-H[u];
				return;
			}

			q.push(v);
			II buf = ret;
			if(H[u] > H[v])
				buf.DOWN += H[u]-H[v];
			else
				buf.UP += H[v]-H[u];
			d.push(buf);
		}
	}
}

int main(){
	ifstream cin("Walk.h");
	int T;
	cin >> T;
	while(T--){
		int i,j;
		Po.clear();
		Adj.clear();
		H.clear();

		cin >> N;
		Po.resize(N);
		Adj.resize(N+1);
		H.resize(N);
		FOR(i,N){
			int M;
			cin >> H[i] >> M;
			Po[i].resize(M);
			FOR(j,M)
				cin >> Po[i][j].x >> Po[i][j].y;
			Po[i].push_back(Po[i].front());
		}

		Build_Graph();
		BFS();
		cout << ret.UP <<" "<< ret.DOWN <<endl;
	}
}