#include <iostream>
#include <fstream>
#include <cmath>
#include <algorithm>
#include <vector>

using namespace std;

vector<pair<int,int> > points;

bool Sort(pair<int,int> p1,pair<int,int> p2){
	if(p1.second>p2.second)
		return true;
	if(p1.second<p2.second)
		return false;
	return p1.first<p2.first;
}

double dist(pair<int,int> p1,pair<int,int> p2){
	double dx=p1.first-p2.first;
	double dy=p1.second-p2.second;
	return sqrt( dx*dx + dy*dy );
}

int cross(pair<int,int> p1,pair<int,int> p2){
	return p1.first*p2.second - p1.second*p2.first;
}

pair<int,int> operator-(pair<int,int> p1,pair<int,int> p2){
	p1.first-=p2.first;
	p1.second-=p2.second;
	return p1;
}

bool Line(int Min,int Max){
	for(int i=Min+1;i<Max;i++)
		if(cross(points[i]-points[Min],points[i+1]-points[Min])!=0)
			return false;
	return true;
}

void makeConvex(){
	int i,j;
	for(i=0;i<points.size()-1;i++){
		for(j=i+2;j<points.size();j++){
			if(cross(points[i+1]-points[i],points[j]-points[i]) > 0)
				swap(points[i+1],points[j]);
		}
		if(points[i+1]==points[0])
			points.resize(i+2);
	}

	for(i=0;i<points.size()-2;i++){
		if(Line(i,i+2)){
			remove(points.begin(),points.end(),points[i+1]);
			points.pop_back();
			i--;
		}
	}

	points.pop_back();
}

int main(){
	//ifstream cin("ConvexHall.h");
	int P;
	cin>>P;
	for(int cnt=1;cnt<=P;cnt++){
		points.clear();

		int n,N;
		int i,j,k;
		cin>>n>>N;

		points.resize(N);

		for(i=0;i<N;i++)
			cin>>points[i].first>>points[i].second;

		sort(points.begin(),points.end(),Sort);
		points.push_back(points[0]);

		if(Line(0,points.size()-1)){
			points[1]=points[points.size()-2];
			points.resize(2);
		}
		else
			makeConvex();

		cout<<n<<" "<<points.size()<<endl;
		for(i=0;i<points.size();i++)
			cout<<points[i].first<<" "<<points[i].second<<endl;
	}
}