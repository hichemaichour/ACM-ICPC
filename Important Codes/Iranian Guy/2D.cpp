namespace std{
	inline bool operator < (const Point &s,const Point &t){
		if (abs(s.real()-t.real()) > EPS) return(s.real() < t.real());
		if (abs(s.imag()-t.imag()) > EPS) return(s.imag() < t.imag());
		return(false);
	}
}

struct circle{
	Point cen;
	double r;
	circle(Point x,double y){ cen=x; r=y;
	}
	bool is_in(const Point &s)const{ return(abs(cen-s) <= r+EPS);
	}
	bool is_on(const Point &s)const{ return(abs(abs(cen-s)-r) < EPS);
	}
};

struct line{
	Point a,b;
	line(Point x,Point y){ a=x; b=y;
	}
	bool is_on(const Point &s)const{
		return(abs(((s-a)/(b-a)).imag()) < EPS);
	}
};

struct segment{
	Point a,b;
	segment(Point x,Point y):a(x),b(y){
	}
	bool is_on(const Point &s)const{
		if (abs(s-a) < EPS || abs(s-b) < EPS) return(true);
		if (abs(((s-a)/(b-a)).imag()) > EPS) return(false);
		return((a < s) == (s < b));
	}
};

struct half_line{
	Point a,b;
	half_line(Point x,Point y):a(x),b(y){
	}
	bool is_on(const Point &s)const{
		if (abs(s-a) < EPS) return(true);
		if (abs(((s-a)/(b-a)).imag()) > EPS) return(false);
		return((a < s) == (a < b));

	}
};

template<typename first,typename second> // first and second should be line or segment or half_line
vector<Point> intersection(first a,second b){
	Point x=(b.a-a.a)/(a.b-a.a),y=(b.b-a.a)/(a.b-a.a);

	if (abs(x.imag()-y.imag()) < EPS) return(vector<Point>());

	Point res=x+(y-x)*(x.imag()/(x-y).imag());
	res=res*(a.b-a.a)+a.a;
	vector<Point> ans;
	if (a.is_on(res) && b.is_on(res))
		ans.push_back(res);
	return(ans);
}

template<typename first>
vector<Point> intersection(first a,circle b){
	Point x=(b.cen-a.a)/(a.b-a.a);
	double r=b.r/abs(a.b-a.a);
	if (r < abs(x.imag())+EPS) return(vector<Point>());
	Point temp;

	vector<Point> ans;
	temp=Point(x.real()-sqrt(r*r-x.imag()*x.imag()),0)*(a.b-a.a)+a.a;
	if (a.is_on(temp)) ans.push_back(temp);

	temp=Point(x.real()+sqrt(r*r-x.imag()*x.imag()),0)*(a.b-a.a)+a.a;
	if (a.is_on(temp)) ans.push_back(temp);

	if (ans.size() == 2 && abs(ans[0] - ans[1])) ans.pop_back();
	return(ans);
}

template<typename first>
vector<Point> intersection(circle a,first b){
	return(intersection(b,a));

}

vector<Point> intersection(circle a,circle b){
	double r1=a.r/abs(a.cen-b.cen),r2=b.r/abs(a.cen-b.cen);
	if (abs(r1-r2)-EPS > 1 || r1+r2 < 1-EPS)
		return(vector<Point>());
	double mid=0.5+(pow(r1,2)-pow(r2,2))/2;
	vector<Point> ans;
	ans.push_back(Point(mid,sqrt(pow(r1,2)-pow(mid,2)))*(b.cen-a.cen)+a.cen);
	ans.push_back(Point(mid,-sqrt(pow(r1,2)-pow(mid,2)))*(b.cen-a.cen)+a.cen);
	if (abs(ans[0] - ans[1]) < EPS)
		ans.pop_back();
	return(ans);
}

Point outer_circle(Point a,Point b,Point c){
	vector<Point> res=intersection(line((a+b)/2.0,(b-a)*Point(0,1)+(a+b)/2.0),line((b+c)/2.0,(b-c)*Point(0,1)+(b+c)/2.0));
	return(res[0]);
}

Point inner_circle(Point a,Point b,Point c){
	vector<Point> res=intersection(line(a,a+sqrt((c-a)/(b-a))*(b-a)),
		line(b,b+sqrt((a-b)/(c-b))*(c-b)));
	return(res[0]);
}

vector<Point> tangent(circle a,Point b){
	return(intersection(a,circle(b,sqrt(pow(abs(a.cen-b),2)-pow(a.r,2)))));
}
