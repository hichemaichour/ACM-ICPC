#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

vector<pair<int,int> > pts;

double slope(int i,int j){
	double x1,x2,y1,y2;
	x1=pts[i].first;
	y1=pts[i].second;
	x2=pts[j].first;
	y2=pts[j].second;
	return ((y2-y1)/(x2-x1));
}

bool between(int i,int j,int k){
	int xMin,yMin,xMax,yMax;
	int x,y;
	xMin=min(pts[i].first,pts[j].first);
	xMax=max(pts[i].first,pts[j].first);
	yMin=min(pts[i].second,pts[j].second);
	yMax=max(pts[i].second,pts[j].second);
	x=pts[k].first;
	y=pts[k].second;
	return ((x>=xMin) && (x<=xMax) && (y>=yMin) && (y<=yMax));
}

int func(int i,int j){
	int ret=2;
	for(int k=j+1;k<pts.size();k++)
		if((slope(i,k)==slope(k,j)) && between(i,j,k))
			ret++;
	return ret;
}

int num(){
	int ret=0;
	for(int i=0;i<pts.size()-1;i++)
		for(int j=i+1;j<pts.size();j++)
			ret=max(ret,func(i,j));
	return ret;
}

int main(){
	//ifstream cin("Points.h");
	for(int cnt=1;true;cnt++){
		pts.clear();
		char c1,c2;
		pair<int,int> xy;
		string str;
		while(true){
			cin.get(c1);
			cin.get(c2);
			if( (c1==c2) && c1=='-'){
				cin.putback(c2);
				getline(cin,str);
				break;
			}
			cin.putback(c2);
			cin.putback(c1);
			cin>>xy.first>>xy.second;
			getline(cin,str);
			pts.push_back(xy);
		}
		if(pts.size()==0)
			break;

		int n;
		n=num();
		cout<<cnt<<". "<<n<<endl;
	}
	return 0;
}