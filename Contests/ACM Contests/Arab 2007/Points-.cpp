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

int func(int i){
	int ret=0;
	while(true){
		int m=2;
		for(int k=i+1;k<pts.size();k++){
			if((slope(i,k)==slope(k,j))){
				m++;
			}
		}
	}
	return ret;
}

int num(){
	int ret=0;
	for(int i=0;i<pts.size()-1;i++)
		ret=max(ret,func(i));
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