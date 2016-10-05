#include <iostream>
#include <vector>
#include <set>
#include <map>
#include <algorithm>

#define Pair pair<int,int>
#define st pair<int,Pair>
#define LTH first
#define LNK second
#define x first
#define y second

using namespace std;

bool Sort(st s1,st s2){
	if(s1.LTH != s2.LTH)
		return s1.LTH < s2.LTH;
	if(s1.LNK.x != s2.LNK.x)
		return s1.LNK.x < s2.LNK.x;
	return s1.LNK.y > s2.LNK.y;
}

int main(){
	int T;
	cin>>T;
	bool flg=false;
	while(T--){
		int i,j,k;
		if(flg)
			cout<<endl;
		flg = true;

		int N;
		cin>>N;
		char c = ' ';
		char buf;
		Pair p = Pair(0,0);

		map<int,vector<int> > mX;
		map<int,vector<int> > mY;
		map<int,int> m;
		set<int> X;
		set<int> Y;
		vector<Pair> v;

		cin.ignore(100,'\n');
		for(i=0 ; i<N ; i++){
			cin>>buf;
			if(buf != c){
				X.insert(p.x);
				Y.insert(p.y);
				mX[p.x].push_back(v.size());
				mY[p.y].push_back(v.size());
				m[v.size()] = i;
				v.push_back(p);
				c = buf;
			}
			if(buf == 'N')
				p.y++;
			else if(buf == 'S')
				p.y--;
			else if(buf == 'E')
				p.x++;
			else
				p.x--;
		}

		vector<st> Pos;
		set<int>::iterator it;
		for(it=X.begin() ; it!=X.end() ; it++){
			for(i=0 ; i<mX[*it].size() ; i++){
				for(j=i+1 ; j<mX[*it].size() ; j++){
					if( mX[*it][j] - mX[*it][i] != 1 ){
						p = Pair( mX[*it][i] , mX[*it][j] );
						Pos.push_back( st( abs(v[p.x].y-v[p.y].y) , p ));
					}
				}
			}
		}
		for(it=Y.begin() ; it!=Y.end() ; it++){
			for(i=0 ; i<mY[*it].size() ; i++){
				for(j=i+1 ; j<mY[*it].size() ; j++){
					if( mY[*it][j] - mY[*it][i] != 1 ){
						p = Pair( mY[*it][i] , mY[*it][j] );
						Pos.push_back( st( abs(v[p.x].x-v[p.y].x) , p ));
					}
				}
			}
		}

		if(Pos.size() == 0)
			continue;

		sort(Pos.begin(),Pos.end(),Sort);
		int l = Pos[0].LTH;
		int b = Pos[0].LNK.x;
		int e = Pos[0].LNK.y;
		char d;
		if(v[b].x == v[e].x){
			if(v[e].y - v[b].y > 0)
				d = 'N';
			else
				d = 'S';
		}
		else{
			if(v[e].x - v[b].x > 0)
				d = 'E';
			else
				d = 'W';
		}
		b = m[b];
		e = m[e];
		cout << l <<" "<< b <<" "<< e <<" "<< d <<endl;
	}
}