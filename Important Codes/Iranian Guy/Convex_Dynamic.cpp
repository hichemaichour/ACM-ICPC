typedef pair<int,int> Pair;
typedef complex<double> Point;

const double EPS=1e-6;

vector<Point> points;
Point middle;
struct Convex{
	vector<int> next,prev;
	struct Comp{
		bool operator () (int s,int t)const{
			Point a=points[s],b=points[t];
			a-=middle; b-=middle;
			double x=arg(a),y=arg(b);
			if (abs(x-y) < EPS) return(false);
			return( x > y);
		}
	};
	set<int,Comp> Set;
	long long area;
	long long getArea(){ return(area);
	}
	long long tri(const Point &x,const Point &y,const Point &z){
		long long ans=(long long)x.real()*(long long)y.imag()-(long long)y.real()*(long long)x.imag();
		ans+=(long long)y.real()*(long long)z.imag()-(long long)z.real()*(long long)y.imag();
		ans+=(long long)z.real()*(long long)x.imag()-(long long)x.real()*(long long)z.imag();
		return(abs(ans));
	}
	inline bool is_left(const Point &a,Point b,Point c){
		b-=a; c-=a;
		return(b.real()*c.imag() > c.real()*b.imag());
	}
	Convex(Point x,Point y,Point z){
		if (is_left(x,y,z)) swap(x,z);
		points.push_back(x); points.push_back(y); points.push_back(z);
		next.push_back(1); next.push_back(2); next.push_back(0);
		prev.push_back(2); prev.push_back(0); prev.push_back(1);

		middle=((double)2.0*x+(double)2.0*y+(double)5.0*z)/(double)9.0;
		Set.insert(0);
		Set.insert(1);
		Set.insert(2);
		area=tri(x,y,z);
	}
	void push_back(Point s){
		points.push_back(s);
		int after,before;
		if (Set.upper_bound(points.size()-1) == Set.end()) after=*Set.begin();
		else after=*Set.upper_bound(points.size()-1);
		before=prev[after];

		if (is_left(points[before],points[points.size()-1],points[after])) return;

		next[before]=points.size()-1;
		prev[after]=points.size()-1;
		next.push_back(after);
		prev.push_back(before);
		Set.insert(points.size()-1);

		int who=points.size()-1;
		area+=tri(points[who],points[prev[who]],points[next[who]]);
		while (is_left(points[prev[prev[who]]],points[prev[who]],points[who])){
			int temp=prev[who];
			prev[who]=prev[prev[who]];
			next[prev[who]]=who;
			Set.erase(temp);
			area+=tri(points[who],points[temp],points[prev[who]]);
		}
		while (is_left(points[who],points[next[who]],points[next[next[who]]])){
			int temp=next[who];
			next[who]=next[next[who]];
			prev[next[who]]=who;
			Set.erase(temp);
			area+=tri(points[who],points[temp],points[next[who]]);
		}
	}
};
