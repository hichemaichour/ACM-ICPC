typedef complex<double> Point;
typedef pair<int,int> Pair;

const int MAX_N=100000+20;
const double EPS=1e-6;
const Point Change(1.434,2.4353);

Point *Coor;
struct DCEL{
	Point coor[MAX_N];
	int n;
	vector<Pair> e;
	vector<int> next,part;
	DCEL(int s){
		n=s; e.clear(); next.clear(); part.clear();
		fill(coor,coor+MAX_N,Point(0,0));
	}
	inline void push_back(int a,int b){
		e.push_back(Pair(a,b)); 
		e.push_back(Pair(b,a));
	}

	inline static bool dif(Pair s,Pair t){
		double a=arg((Coor[s.second]-Coor[s.first])*Change),b=arg((Coor[t.second]-Coor[t.first])*Change);
		if (abs(a-b) > EPS) return(a < b);
		else return(s < t);
	}

	inline void relax(){
		Coor=coor;
		sort(e.begin(),e.end(),dif);
		e.resize(unique(e.begin(),e.end())-e.begin());
		map<Pair,int> where;
		for (int i=0;i<e.size();i++) where[e[i]]=i;
		for (int i=0;i<e.size();i++) part.push_back(where[Pair(e[i].second,e[i].first)]);
		int temp[MAX_N]; fill(temp+1,temp+n+1,-1);

		for (int i=0;i<e.size();i++){ next.push_back(temp[e[i].first]); temp[e[i].first]=i;
		}
		for (int i=0;i<e.size();i++) if (next[i]==-1) next[i]=temp[e[i].first];
	}
	inline vector<vector<int> > Faces(){
		vector<vector<int> > ans;
		vector<bool> mark;
		relax();
		mark.resize(e.size());
		for (int i=0;i<e.size();i++) if (!mark[i]){
			ans.push_back(vector<int>());
			int temp=i;
			while (!mark[temp]){
				mark[temp]=true;
				ans.back().push_back(e[temp].first);
				temp=next[part[temp]];
			}
		}
		return(ans);
	}
};
