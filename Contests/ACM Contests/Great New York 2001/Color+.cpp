#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>

using namespace std;

vector<pair<pair<int,int>,int> > v;
pair<pair<int,int>,int> p;

double dist(int i){
	double dx=v[i].first.first-p.first.first;
	double dy=v[i].first.second-p.first.second;
	double dz=v[i].second-p.second;

	return sqrt( (dx*dx) + (dy*dy) + (dz*dz) );
}

int func(){
	int ret;
	double d=1e12;
	
	for(int i=0;i<v.size();i++){
		if(dist(i)<d){
			d=dist(i);
			ret=i;
		}
	}
	return ret;
}

int main(){
	//ifstream cin("Color.h");
	v.resize(16);
	for(int i=0;i<v.size();i++)
		cin>>v[i].first.first>>v[i].first.second>>v[i].second;

	while(true){
		cin>>p.first.first>>p.first.second>>p.second;
		if(p.second==-1)
			return 0;
		int n=func();
		
		cout<<"("<<p.first.first<<","<<p.first.second<<","<<p.second<<") maps to ("<<v[n].first.first<<","<<v[n].first.second<<","<<v[n].second<<")"<<endl;
	}
}