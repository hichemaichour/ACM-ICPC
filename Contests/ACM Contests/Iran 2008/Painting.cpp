#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <map>
#include <list>
#include <cmath>

using namespace std;

const double EPS=1e-9;
const int R=0;
const int C=1;
vector<vector<vector<int> > >paint;
vector<vector<vector<int> > >r_c;
list<int> ret;
map<int,bool> done;
map<int,double> m;
int nR;
int nC;

void init(){
	int i,j,k;
	ret.clear();
	done.clear();
	r_c.clear();
	m.clear();

	r_c.resize(2);
	r_c[R].resize(paint[R].size());
	r_c[C].resize(paint[C].size());

	for(i=0;i<2;i++){
		for(j=0;j<paint[i].size();j++){
			for(k=0;k<paint[i][j].size();k++){
				if(count(paint[i][j].begin(),paint[i][j].end(),paint[i][j][k]) > 1){
					r_c[i][j].clear();
					r_c[i][j].push_back(paint[i][j][k]);
					m[paint[i][j][k]]=j + (i+1)/10.0;
					break;
				}
				else
					r_c[i][j].push_back(paint[i][j][k]);
			}
		}
	}

	bool flag=true;
	while(flag){
		flag=false;
		for(i=0;i<2;i++){
			for(j=0;j<r_c[i].size();j++){
				for(k=0;k<r_c[i][j].size();k++){
					if(m[r_c[i][j][k]]>EPS && fabs( m[r_c[i][j][k]] - (j+(i+1)/10.0) )>EPS){
						flag=true;
						int last=r_c[i][j].size()-1;
						swap(r_c[i][j][k],r_c[i][j][last]);
						r_c[i][j].pop_back();
						k--;
					}
					if(r_c[i][j].size()==1 && paint[i][j].size()!=1 && k!=-1)
						m[r_c[i][j][k]]=j + (i+1)/10.0;
				}
			}
		}
	}

	map<int,double>::iterator iter;
	for(iter=m.begin();iter!=m.end();iter++){
		i=iter->second*10 + EPS;
		i%=10;
		j=iter->second+EPS;
		for(k=0;k<paint[i][j].size();k++){

		}
	}
}

int main(){
	ifstream cin("Painting.h");
	while(true){
		int i,j,k;
		paint.clear();
		cin>>nR>>nC;
		if(nR==0)
			return 0;

		paint.resize(2);
		paint[R].resize(nR);
		paint[C].resize(nC);

		int buf;
		for(i=0;i<nR;i++){
			for(j=0;j<nC;j++){
				cin>>buf;
				paint[R][i].push_back(buf);
				paint[C][j].push_back(buf);
			}
		}

		init();

		cout<<endl;
	}
}