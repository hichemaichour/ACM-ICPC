#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <map>

#define Pair pair<POS,POS>
#define POS pair<int,int>
#define B first
#define M second
#define x first
#define y second

using namespace std;

int w,h;
int dx[]={1,-1,0,0};
int dy[]={0,0,1,-1};
int ret;
vector<vector<int> > Next;
vector<vector<int> > Place;
map<Pair,bool> done;
POS man;
POS box;
POS goal;

void Next_Pos(vector<Pair>& v){
	int i,j,k;
	POS buf;
	Next=Place;
	Next[man.x][man.y]=2;
	Next[box.x][box.y]=1;
	queue<POS> q;
	q.push(man);
	while(!q.empty()){
		buf=q.front(); q.pop();
		for(k=0 ; k<4 ; k++){
			i=buf.x+dx[k];
			j=buf.y+dy[k];
			if(i<h && i>=0 && j<w && j>=0 && Next[i][j]==0){
				Next[i][j]=2;
				q.push(POS(i,j));
			}
		}
	}
	
	for(k=0 ; k<4 ; k++){
		man.x=box.x+dx[k];
		man.y=box.y+dy[k];
		i=box.x-dx[k];
		j=box.y-dy[k];
		if(i<h && i>=0 && j<w && j>=0 && man.x<h && man.x>=0 && man.y<w && man.y>=0 && Next[i][j]!=1 && Next[man.x][man.y]==2 && !done[Pair(box,man)] && !done[Pair(POS(i,j),box)]){
			v.push_back(Pair(POS(i,j),box));
			done[Pair(box,man)]=true;
		}
	}
}

//bool hichem(){
//	int x,y;
//	if(man.x==box.x && man.x==goal.x && (man.y-box.y)*(box.y-goal.y)>0){
//		x=man.x;
//		for(y=min(box.y,goal.y) ; y<max(box.y,goal.y) ; y++)
//			if(Place[x][y]!=0)
//				break;
//		if(y==max(box.y,goal.y)){
//			ret = min(len+abs(box.y-goal.y) , ret);
//			return true;
//		}
//	}
//	if(man.y==box.y && man.y==goal.y && (man.x-box.x)*(box.x-goal.x)>0){
//		y=man.y;
//		for(x=min(box.x,goal.x) ; x<max(box.x,goal.x) ; x++)
//			if(Place[x][y]!=0)
//				break;
//		if(x==max(box.x,goal.x)){
//			ret = min(len+abs(box.x-goal.x) , ret);
//			return true;
//		}
//	}
//	return false;
//}

int BFS(){
	done.clear();
	queue<POS> BOX;
	queue<POS> MAN;
	queue<int> LEN;
	BOX.push(box);
	MAN.push(man);
	LEN.push(0);
	int len;
	ret=INT_MAX;
	while(!LEN.empty()){
		man=MAN.front(); box=BOX.front(); len=LEN.front();
		MAN.pop(); BOX.pop(); LEN.pop();

		//if(len!=0 && hichem())
		//	continue;

		if(len > ret)
			continue;

		vector<Pair> v;
		Next_Pos(v);
		for(int i=0 ; i<v.size() ; i++){
			if(v[i].B == goal)
				ret = min(len+1 , ret);
			else{
				MAN.push(v[i].M);
				BOX.push(v[i].B);
				LEN.push(len+1);
			}
		}
	}
	if(ret==INT_MAX)
		return -1;
	return ret;
}

int main(){
	//ifstream cin("Push.h");
	while(true){
		int i,j,k;
		Next.clear();
		Place.clear();
		cin>>w>>h;
		if(w==0)
			return 0;
		Place.resize(h,vector<int>(w));
		Next.resize(h,vector<int>(w));
		for(i=0 ; i<h ; i++){
			for(j=0 ; j<w ; j++){
				cin>>k;
				if(k==1)
					Place[i][j]=1;
				else
					Place[i][j]=0;
				if(k==2)
					box = POS(i,j);
				if(k==3)
					goal = POS(i,j);
				if(k==4)
					man = POS(i,j);
			}
		}

		cout<<BFS()<<endl;
	}
}