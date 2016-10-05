namespace std{
	inline bool operator < (const Point &s,const Point &t){
		if (abs(s.real()-t.real()) > EPS) return(s.real() < t.real());
		if (abs(s.imag()-t.imag()) > EPS) return(s.imag() < t.imag());
		return(false);
	}
}

struct line{
	Point a,b;
	line(Point x,Point y){
		a=x;
		b=y;
	}
	inline bool is_on(const Point &s)const{
		Point A=a,B=b,C=s;
		if (B < A) swap(A,B);
		if (C < A) swap(A,C);
		if (C < B) swap(B,C);
		return(abs(abs(A-C)-abs(A-B)-abs(B-C)) < EPS);
	}
	vector<Point> intersection(const line &s)const;
};

vector<Point> line::intersection(const line &s)const{
	Point A=(s.a-a)/(b-a),B=(s.b-a)/(b-a);
	if (abs(A.imag()-B.imag()) < EPS) return(vector<Point>());
	vector<Point> ans;
	ans.push_back(A+(B-A)*(A.imag()/(A-B).imag()));

	for (int i=0;i<ans.size();i++) ans[i]=ans[i]*(b-a)+a;
	for (int i=0;i<ans.size();i++) if (!is_on(ans[i])){
		swap(ans[i],ans.back());
		ans.pop_back();
	}
	return(ans);
}

inline bool canSee(line a,Point x){
	return((x-a.a).real()*(a.b-a.a).imag()+EPS > (a.b-a.a).real()*(x-a.a).imag());
}

const double INF=1e10;

struct HalfLines{
	vector<line> lines;
	void push_back(line s){
		lines.push_back(s);
	}
	bool haveIntersection(){
		if (lines.size() == 0) return(false);
		if (lines.size() == 1) return(true);

		Point x=lines[0].a;
		for (int i=1;i<lines.size();i++){
			if (canSee(lines[i],x)) continue;
			double left=-INF,right=INF;
			for (int j=0;j<i;j++){
				line temp((lines[j].a-lines[i].a)/(lines[i].b-lines[i].a),
					(lines[j].b-lines[i].a)/(lines[i].b-lines[i].a));
				if (!canSee(temp,Point(left,0))){
					vector<Point> a=temp.intersection(line(Point(0,0),Point(1,0)));
					if (a.size() == 0) return(false);
					else left=max(left,a[0].real());
				}
				if (!canSee(temp,Point(right,0))){
					vector<Point> a=temp.intersection(line(Point(0,0),Point(1,0)));
					if (a.size() == 0) return(false);
					else
						right=min(right,a[0].real());
				}

			}
			if (left < right+EPS)
				x=Point(left,0)*(lines[i].b-lines[i].a)+lines[i].a;
			else
				return(false);
		}
		return(true);
	}
	inline void print(){
		for (int i=0;i<lines.size();i++)
			cout<<lines[i].a<<' '<<lines[i].b<<endl;
		cout<<endl;
	}
};
