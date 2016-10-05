#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <cmath>
#include <map>

using namespace std;

struct a{
	double x;
	double y;
	double h;
};

int R,C;
int N;
vector<vector<double> > H;
vector<vector<int> > P;
vector<a> A;
pair<int,int> Start;
pair<int,int> End;
const double EPS=1e-9;

void intersection(int i,int j,int k){
	double x,y,h;
	if (P[j][k]!=-1)
		return;
	if(j==A[i].x || k==A[i].y){
		P[j][k]=0;
		return;
	}

	int dx,dy;
	if(j>A[i].x)
		dx=1;
	else
		dx=-1;
	if(k>A[i].y)
		dy=1;
	else
		dy=-1;

	double a,b,c;
	a=(0-A[i].h)/(j-A[i].x);
	b=(0-A[i].h)/(k-A[i].y);
	c=(k-A[i].y)/(j-A[i].x);

	for(x=A[i].x+dx;x!=j;x+=dx){
		y=c*x - c*A[i].x + A[i].y;
		h=a*x - a*A[i].x + A[i].h;

		if(fabs(y-floor(y+EPS))<EPS){
			if(H[int(x+EPS)][int(y+EPS-1)]-h>EPS || H[int(x+EPS-1)][int(y+EPS)]-h>EPS)
				return;
		}
		else{
			if(H[int(x+EPS-1)][int(y)]-h>EPS || H[int(x+EPS)][int(y)]-h>EPS)
				return;
		}
	}

	for(y=A[i].y+dy;y!=k;y+=dy){
		x=y/c - A[i].y/c + A[i].x;
		h=a*x - a*A[i].x + A[i].h;

		if(fabs(x-floor(x+EPS))<EPS){
			if(H[int(x+EPS)][int(y+EPS-1)]-h>EPS || H[int(x+EPS-1)][int(y+EPS)]-h>EPS)
				return;
		}
		else{
			if(H[int(x)][int(y+EPS-1)]-h>EPS || H[int(x)][int(y+EPS)]-h>EPS)
				return;
		}
	}

	dx=(dx+1)/2;
	dy=(dy+1)/2;
	
	if(H[j-dx][k-dy]>EPS)
		return;

	P[j][k]=0;
}

void init(){
	int i,j,k;
	for(i=0;i<N;i++)
		for(j=0;j<=R;j++)
			for(k=0;k<=C;k++)
				intersection(i,j,k);
}

pair<int,int> trans(pair<int,int> p,int i){
	switch(i){
		case 0:
			if(p.second+1 <= C)
				p.second++;
			break;
		case 1:
			if(p.first-1 >= 0)
				p.first--;
			break;
		case 2:
			if(p.second-1 >= 0)
				p.second--;
			break;
		case 3:
			if(p.first+1 <= R)
				p.first++;
			break;
	}
	return p;
}

int BFS(){
	if(Start==End)
		return 0;

	map<pair<int,int>,bool> done;
	queue<pair<int,int> > q;
	queue<int> ret;
	q.push(Start);
	ret.push(0);
	int cnt;
	done[Start]=true;

	while(!q.empty()){
		Start=q.front();
		cnt=ret.front();
		q.pop();
		ret.pop();

		for(int i=0;i<4;i++){
			pair<int,int> buf=trans(Start,i);
			if(buf==End)
				return (cnt+1)*10;
			if(done[buf] || P[buf.first][buf.second]==-1)
				continue;
			q.push(buf);
			ret.push(cnt+1);
			done[buf]=true;
		}
	}
	return -1;
}

int main(){
	//ifstream cin("Mobile.h");
	int T;
	cin>>T;
	while(T--){
		int i,j,k;
		H.clear();
		P.clear();
		A.clear();

		cin>>R>>C;
		H.resize(R,vector<double>(C));
		P.resize(R+1,vector<int>(C+1,-1));

		for(i=0;i<R;i++)
			for(j=0;j<C;j++)
				cin>>H[i][j];

		cin>>Start.first>>Start.second>>End.first>>End.second;

		cin>>N;
		A.resize(N);
		for(i=0;i<N;i++)
			cin>>A[i].x>>A[i].y>>A[i].h;

		init();

		cout<<BFS()<<endl;
	}
}