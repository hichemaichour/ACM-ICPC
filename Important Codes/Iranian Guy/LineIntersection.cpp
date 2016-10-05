typedef complex<double> Point;
typedef pair<int,int>   Pair;

const double EPS=1e-6;
const Point Change(cos(13),sin(13)); // With love

namespace std{
	bool operator < (const Point &a,const Point &b){
		if (abs(a.real()-b.real()) > EPS) return(a.real() < b.real());
		if (abs(a.imag()-b.imag()) > EPS) return(a.imag() < b.imag());
		return(false);
	}
}

vector<Point> __first,__second;
struct Lines{
	struct Cmp{
		inline static bool is_intersection(const Point &a1,const Point &b1,Point a2,Point b2){
			a2=(a2-a1)/(b1-a1); b2=(b2-a1)/(b1-a1);
			if (min(a2.imag(),b2.imag()) > EPS) return(false);
			if (max(a2.imag(),b2.imag()) < -EPS) return(false);
			if (abs(a2.imag()-b2.imag()) < EPS) return(false);
			Point ans=a2+(b2-a2)*(a2.imag()/(a2-b2).imag());
			if (ans.real() < -EPS || ans.real() > 1+EPS) return(false);
			return(true);
		}
		bool operator () (int s,int t)const{
			if (is_intersection(__first[s],__second[s],__first[t],__second[t])) throw("Intersection :D");
			double eq=max(__first[s].real(),__first[t].real());
			double a=__first[s].imag()+((eq-__first[s].real())/
				(__second[s].real()-__first[s].real()))*(__second[s].imag()-__first[s].imag());
			double b=__first[t].imag()+((eq-__first[t].real())/
				(__second[t].real()-__first[t].real()))*(__second[t].imag()-__first[t].imag());
			if (abs(eq) < EPS) throw("Intersection :D");
			return(a < b);
		}
	};
	vector<Point> first,second;
	void push_back(Point a,Point b){
		if (abs(a-b) > EPS){
			a*=Change; b*=Change;
			if (b < a) swap(a,b);
			first.push_back(a);
			second.push_back(b);
		}
	}
	static double get(Pair s){
		if (s.second == 0) return(__first[s.first].real());
		else return(__second[s.first].real());
	}
	static bool dif(Pair s,Pair t){
		double a=get(s),b=get(t);
		if (abs(a-b) > EPS) return(a < b);
		return(s < t);
	}
	inline bool HaveIntersection(){
		set<Point> Set;
		for (int i=0;i<first.size();i++){
			Set.insert(first[i]); Set.insert(second[i]);
		}
		if (Set.size() != 2*first.size()) return(true);
		vector<Pair> all;
		for (int i=0;i<first.size();i++){
			all.push_back(Pair(i,0));
			all.push_back(Pair(i,1));
		}
		__first=first; __second=second;
		sort(all.begin(),all.end(),dif);
		try{
			set<int,Cmp> Set;
			for (int i=0;i<all.size();i++){
				if (all[i].second == 1) Set.erase(all[i].first);
				set<int,Cmp> :: iterator pointer=Set.lower_bound(all[i].first);
				if (pointer != Set.end()) Cmp()(*pointer,all[i].first);
				if (pointer != Set.begin()){
					pointer--;
					Cmp()(*pointer,all[i].first);
				}
				if (all[i].second == 0) Set.insert(all[i].first);
			}
		}catch(...){
			return(true);
		}
		return(false);
	}
};
