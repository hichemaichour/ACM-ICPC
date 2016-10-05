#include <iostream>
#include <string>
#include <algorithm>
#include <map>
#include <vector>
#include <functional>
#include <fstream>

#define FOR(i,N)		for(i=0 ; i<N ; i++)

#define All(v)			v.begin(),v.end()

#define VI				vector<int>

using namespace std;

int N,M;
vector<string> Teams;
vector<int> Pts;
vector<pair<int,int> > DK;
vector<int> MaxPos;
vector<int> MinPos;

void Rec(int k){
	int i;
	if(k == DK.size()){
		VI V = Pts;

		sort(All(V),greater<int>());

		FOR(i,N){
			int pos = lower_bound(All(V),Pts[i]) - V.begin();
			pos++;
			MaxPos[i] = min(MaxPos[i] , pos);
			MinPos[i] = max(MinPos[i] , pos);
		}
		return;
	}
	// first win
	Pts[DK[k].first] += 3;
	Rec(k+1);
	Pts[DK[k].first] -= 3;
	
	// second win
	Pts[DK[k].second] += 3;
	Rec(k+1);
	Pts[DK[k].second] -= 3;
	
	// draw
	Pts[DK[k].first] += 1;
	Pts[DK[k].second] += 1;
	Rec(k+1);
	Pts[DK[k].first] -= 1;
	Pts[DK[k].second] -= 1;
}

int main() {
	ifstream cin("soccer.in");
	int flg = false;
	while(cin >> N >> M && N){
		if(flg)
			cout << endl;
		flg = true;
		
		int i,j,k;
		Teams.resize(N);
		FOR(i,N) cin >> Teams[i];
		
		map<string,int> ID;
		FOR(i,N) ID[Teams[i]] = i;
		
		Pts.clear(); Pts.resize(N,0);
		DK.clear();
		
		FOR(i,M){
			string T1,buf,T2;
			int n1,n2;
			cin >> T1 >> buf >> T2 >> n1 >> n2;
			T2.resize(T2.size()-1);
			if(n1 == -1){
				DK.push_back(pair<int,int>(ID[T1],ID[T2]));
			}
			else if(n1 > n2){
				Pts[ID[T1]] += 3;
			}
			else if(n2 > n1){
				Pts[ID[T2]] += 3;
			}
			else{
				Pts[ID[T1]] += 1;
				Pts[ID[T2]] += 1;
			}
		}
		
		MaxPos.clear(); MaxPos.resize(N,N);
		MinPos.clear(); MinPos.resize(N,1);
		
		Rec(0);
		
		FOR(i,N) {
			cout <<"Team "<< Teams[i] <<" can finish as high as "<<MaxPos[i];
			if(MaxPos[i] == 1)
				cout <<"st";
			else if (MaxPos[i] == 2)
				cout <<"nd";
			else if (MaxPos[i] == 3)
				cout <<"rd";
			else
				cout <<"th";
			
			cout <<" place and as low as "<<MinPos[i];
			if(MinPos[i] == 1)
				cout <<"st";
			else if (MinPos[i] == 2)
				cout <<"nd";
			else if (MinPos[i] == 3)
				cout <<"rd";
			else
				cout <<"th";
			
			cout <<" place."<<endl;
		}
	}
	return 0;
}

