#include <cmath>
#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#include <set>

#define DD pair<double,double>
#define x first
#define y second
#define VDD vector<DD>
#define VD vector<double>
#define St pair<DD,int>
#define VSt vector<St>
#define ID second
#define Pos first

using namespace std;

const double EPS = 1e-6;
const double PI = 3.141;

int N;
double D;
DD fst,scd;

double Dist(DD p1,DD p2){
	double dx = p1.x - p2.x;
	double dy = p1.y - p2.y;
	return sqrt(dx*dx + dy*dy);
}

bool func1(St p1, St p2){
	return Dist(p1.first,fst) < Dist(p2.first,fst);
}

bool func2(St p1, St p2){
	return Dist(p1.first,scd) < Dist(p2.first,scd);
}

int main(){
	//ifstream cin("I.h");
	for(int cnt=1 ; true ; cnt++){
		int ret = INT_MAX;
		int i,j,k;

		cin >> N;
		if(N==0)
			return 0;

		VSt P1,P2;
		P1.resize(N);
		cin >> fst.x >> fst.y >> scd.x >> scd.y >> D;
		for(i=0 ; i<N ; i++){
			cin >> P1[i].Pos.x >> P1[i].Pos.y;
			P1[i].ID = i;
		}
		P2 = P1;

		sort(P1.begin(),P1.end(),func1);
		sort(P2.begin(),P2.end(),func2);

		VD D1,D2;
		for(i=0 ; i<N ; i++){
			D1.push_back(Dist(P1[i].Pos,fst));
			D2.push_back(Dist(P2[i].Pos,scd));
		}

		double d1,d2;
		double MaxD = sqrt(D/PI);
		set<int> s1,s;
		for(i=-1 ; i<N ; i++){
			if(i == -1)
				d1 = 0;
			else{
				d1 = D1[i];
				s1.insert(P1[i].ID);
			}
			if(d1 > MaxD+EPS)
				break;
			s = s1;

			d2 = sqrt((D - PI*d1*d1)/PI);
			d2 += EPS;
			k = lower_bound(D2.begin(),D2.end(),d2) - D2.begin();
			for(j=0 ; j<k ; j++)
				s.insert(P2[j].ID);

			if(N-s.size() < ret)
				ret = N-s.size();
		}

		s1.clear();
		for(i=-1 ; i<N ; i++){
			if(i == -1)
				d2 = 0;
			else{
				d2 = D2[i];
				s1.insert(P2[i].ID);
			}
			if(d2 > MaxD+EPS)
				break;
			s = s1;

			d1 = sqrt((D - PI*d2*d2)/PI);
			d1 += EPS;
			k = lower_bound(D1.begin(),D1.end(),d1) - D1.begin();
			for(j=0 ; j<k ; j++)
				s.insert(P1[j].ID);

			if(N-s.size() < ret)
				ret = N-s.size();
		}

		cout << cnt <<". "<<ret<<endl;
	}
}