const int MAX_N=100+20;
const double EPS=1e-6;

namespace std{
	bool operator < (const Point &s,const Point &t){
		if (abs(s.real()-t.real()) > EPS) return(s.real() < t.real());
		if (abs(s.imag()-t.imag()) > EPS) return(s.imag() < t.imag());
		return(false);
	}
}

Point *Num;
struct Convex{
	int n;
	Point num[MAX_N];
	Convex(int s){
		n=s;
		fill(num,num+MAX_N,Point(0,0));
	}
	inline static bool is_left(Point s,Point t){ return(s.real()*t.imag() > t.real()*s.imag()+EPS);
	}
	inline static bool dif(Point s,Point t){
		s-=Num[1]; t-=Num[1];
		if (is_left(s,t)) return(true);
		if (is_left(t,s)) return(false);
		return(abs(s-Num[1]) < abs(t-Num[1]));
	}
	inline static bool online(Point a,Point b,Point c){
		return(abs(abs(a-c)-abs(a-b)-abs(b-c)) < EPS);
	}
	vector<Point> ConvexHall(){
		for (int i=1;i<=n;i++)
			if (num[i] < num[1])
				swap(num[1],num[i]);
		Num=num;
		sort(num+2,num+n+1,dif);
		int temp=n;
		while (online(num[temp-1],num[temp],num[1])) temp--;
		reverse(num+temp,num+n+1);
		vector<Point> ans;
		ans.push_back(num[1]);
		for (int i=2;i<=n;i++){
			while (ans.size() > 1 && is_left(num[i]-ans.back(),ans[ans.size()-1]-ans[ans.size()-2])) ans.pop_back();
			ans.push_back(num[i]);	     
		} 
		return(ans);
	}
};
