#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <set>
#include <map>

using namespace std;

#define VI vector<int>
#define II pair<int,int>
#define VII vector<II>

VI p;

void PF(int N){
	if (N==1 || N==0 || N==-1)
		return;
	if(N<-1){
		PF(N*-1);
		return;
	}

	for(int i=2;i<=sqrt((double)N);i++){
		if(N%i==0){
			PF(N/i);
			PF(i);
			return;
		}
	}

	p.push_back(N);
}

VI func(int N){
	p.clear();
	PF(N);
	return p;
}

int main(){
	for(int cnt=1 ; true ; cnt++){
		int N,M;
		cin >> N >> M;
		if(N==0)
			return 0;
		VI PN = func(N);
		VI PM = func(M);
		
		sort(PN.begin(),PN.end());
		sort(PM.begin(),PM.end());

		int i,j;
		II k(-1,-1);
		VII NN;
		for(i=0 ; i<PN.size() ; i++){
			if(k.first != PN[i]){
				if(k.first != -1)
					NN.push_back(k);
				k.first = PN[i];
				k.second = 1;
			}
			else
				k.second++;
		}
		if(k.first != -1)
			NN.push_back(k);

		k = II(-1,-1);
		VII MM;
		for(i=0 ; i<PM.size() ; i++){
			if(k.first != PM[i]){
				if(k.first != -1)
					MM.push_back(k);
				k.first = PM[i];
				k.second = 1;
			}
			else
				k.second++;
		}
		if(k.first != -1)
			MM.push_back(k);

		map<int,int> mm;
		set<int> s;
		for(i=0 ; i<NN.size() ; i++){
			s.insert(NN[i].first);
			mm[NN[i].first] -= NN[i].second;
		}
		for(i=0 ; i<MM.size() ; i++){
			s.insert(MM[i].first);
			mm[MM[i].first] += MM[i].second;
		}

		int n,m;
		n = s.size();
		m = 0;
		map<int,int>::iterator it;
		for(it=mm.begin() ; it!=mm.end() ; it++)
			m += abs(it->second);

		cout << cnt <<". " << n <<":"<< m << endl;
	}
}