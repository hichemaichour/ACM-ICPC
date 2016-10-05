#include "2D.cpp"

// ==================================
// World Final :)
// ==================================

struct Circle{
	Point c;
	double r;
	bool dir;
};

struct Seg{
	Point a;
	Point b;
	Seg(pair<Point,Point>& p){
		a=p.first;
		b=p.second;
	}
};

vector<Circle> v;
map<int,vector<pair<int,pair<Point,Point> > > > m;
int Start,End;
double d;

bool IsNext(int i,int j,Point& p1,Point& p2){
	vector<Point> t1;
	vector<Point> t2;
	CirTanCir( v[i].c,v[i].r , v[j].c,v[j].r , t1,t2 );

	int k;
	if( v[i].dir==false && v[j].dir==false )
		k=0;
	if( v[i].dir==true && v[j].dir==true )
		k=1;
	if( v[i].dir==false && v[j].dir==true )
		k=2;
	if( v[i].dir==true && v[j].dir==false )
		k=3;

	p1 = t1[k];
	p2 = t2[k];

	if((p1-p2).Abs() > d+EPS)
		return false;

	Point p;
	for(k=0 ; k<v.size() ; k++)
		if( k!= i && k!=j && CirIntSeg(v[k].c,v[k].r , p1,p2 , p,p)!=2 )
			return false;
	return true;
}

void init(){
	Point p1,p2;
	for(int i=0;i<v.size();i++)
		for(int j=0;j<v.size();j++)
			if( i!=j && IsNext(i,j,p1,p2) )
				m[i].push_back(MP( j , MP(p1,p2) ));
}

bool Int(Seg s, vector<Seg>& S){
	Point p;
	for(int i=0;i<S.size();i++)
		if(SegIntSeg(s.a,s.b , S[i].a,S[i].b , p))
			return true;
	return false;
}

double BFS(){
	if(Start == End)
		return 0;

	queue<int> I;
	queue<vector<Seg> > J;
	queue<double> K;
	queue<Point> P;
	int i=Start;
	vector<Seg> j;
	double k=0;
	Point p;
	I.push(i); J.push(j); K.push(k); P.push(p);
	double D = Inf;
	while(!I.empty()){
		i=I.front(); j=J.front(); k=K.front(); p=P.front();
		I.pop(); J.pop(); K.pop(); P.pop();

		double buf;
		for(int n=0; n<m[i].size() ; n++){
			if( m[i][n].first==Start || Int(Seg(m[i][n].second),j) )
				continue;
			if( i==Start )
				p=m[i][n].second.first;

			buf = k;
			if (v[i].dir)
				buf += Arc( v[i].r , AngleBetweenSeg(v[i].c , p , m[i][n].second.first) );
			else
				buf += Arc( v[i].r , AngleBetweenSeg(v[i].c , m[i][n].second.first , p) );
			buf += (m[i][n].second.first-m[i][n].second.second).Abs();
			
			if(m[i][n].first == End){
				D = min(D,buf);
				continue;
			}

			if(buf > D+EPS)
				continue;

			I.push(m[i][n].first);
			j.push_back(Seg(m[i][n].second));
			J.push(j);
			j.pop_back();
			K.push(buf);
			P.push(m[i][n].second.second);
		}
	}
	return D;
}

int main(){
	ifstream cin("input.h");
	for(int cnt=1;true;cnt++){
		int i,j,k;
		int N;
		cin>>N;
		if(N==0) 
			return 0;

		v.clear();
		v.resize(N);
		string str;
		for(i=0 ; i<N ; i++){
			cin>>v[i].c.x>>v[i].c.y>>v[i].r>>str;
			v[i].dir = (str == "cc");
		}
		
		cin>>Start>>End>>d;

		m.clear();
		init();

		double dist = BFS();
		dist = (int)((dist+EPS+0.005)*100)/100.0;
		if(dist < 0)
			cout<<"Case "<<cnt<<": Cannot reach destination shaft"<<endl;
		else
			cout<<"Case "<<cnt<<": "<<dist<<endl;
	}
	return 0;
}