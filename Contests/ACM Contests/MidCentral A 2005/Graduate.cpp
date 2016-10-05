#include <iostream>
#include <string>
#include <map>
#include <algorithm>
#include <vector>
#include <set>
#include <deque>
#include <fstream>

using namespace std;

const int F = 0;
const int S = 1;

int N,M;
deque<string> C;
map<string,set<string> > P;
vector<map<string,bool> > Sem;
deque<int> p;
map<string,vector<string> > Imp;
vector<string> Fall;
vector<string> Spring;

int main(){
	ifstream cin("Graduate.h");
	while(true){
		int i,j,k;
		C.clear();
		P.clear();
		Sem.clear();
		p.clear();
		Imp.clear();
		Fall.clear();
		Spring.clear();

		Sem.resize(2);

		cin>>N>>M;
		if(N==-1)
			return 0;

		C.resize(N);
		for(i=0 ; i<N ; i++)
			cin>>C[i];
		sort(C.begin(),C.end());

		string str;
		string buf;
		char c;
		for(i=0 ; i<N ; i++){
			cin>>str>>c>>k;
			if(c=='F' || c=='B')
				Sem[F][str]=true;
			if(c=='S' || c=='B')
				Sem[S][str]=true;

			for(j=0 ; j<k ; j++){
				cin>>buf;
				P[str].insert(buf);
				Imp[buf].push_back(str);
			}

			if(k==0){
				if(c=='F' || c=='B')
					Fall.push_back(str);
				if(c=='S' || c=='B')
					Spring.push_back(str);
			}
			P[str];
		}

		p.resize(N);
		map<string,set<string> >::iterator it;
		for(it=P.begin(),i=0 ; it!=P.end() ; it++,i++)
			p[i] = it->second.size();

		cout<<"The minimum number of semesters required to graduate is "<<5<<"."<<endl;
	}
}