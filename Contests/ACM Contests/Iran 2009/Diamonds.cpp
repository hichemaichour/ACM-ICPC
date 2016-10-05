#include <iostream>
#include <fstream>
#include <map>
#include <vector>
#include <algorithm>
#include <set>

using namespace std;

vector<int> D;
vector<int> M;
map<int,bool> eM;
map<int,bool> used;

int main(){
	ifstream cin("Diamonds.h");
	while(true){
		int i,j,k;
		D.clear();
		M.clear();
		eM.clear();
		used.clear();

		int n,d,m;
		cin>>n>>m>>d;
		if(n==0)
			return 0;
		M.resize(m);
		D.resize(d);

		for(i=0;i<m;i++){
			cin>>M[i];
			eM[M[i]]=true;
		}
		for(i=0;i<d;i++)
			cin>>D[i];
		sort(M.begin(),M.end());
		sort(D.begin(),D.end());

		i=0;
		int ret=0;
		while(!D.empty()){
			if(i==d)
				i=0;

			int left=-1;
			int right=-1;

			for(j=0;j<m;j++)
				if(M[j]>D[i])
					break;
			if(j!=0 && (i==0 || D[i-1]<=M[j-1]) )
				left=D[i]-M[j-1];
			if(j!=m && (i+1!=d || D[i+1]>=M[j]) )
				right=M[j]-D[i];

			if(right==left && right!=-1){
				if(used[M[j-1]]){
					m+=2;
					M.push_back(M[j-1]-1);
					M.push_back(D[i]+1);
					sort(M.begin(),M.end());
					d--;
					remove(D.begin(),D.end(),D[i]);
					D.pop_back();
					ret+=left+1;
				}
				else if(used[M[j]]){
					m+=2;
					M.push_back(M[j]+1);
					M.push_back(D[i]-1);
					sort(M.begin(),M.end());
					d--;
					remove(D.begin(),D.end(),D[i]);
					D.pop_back();
					ret+=right+1;
				}
				else{
					used[M[j]]=true;
					used[M[j-1]]=true;
					i++;
				}
			}
			else if(right>left){
				m+=2;
				M.push_back(M[j-1]-1);
				M.push_back(D[i]+1);
				sort(M.begin(),M.end());
				d--;
				remove(D.begin(),D.end(),D[i]);
				D.pop_back();
				ret+=left+1;
			}
			else if(left!=-1){
				m+=2;
				M.push_back(M[j-1]-1);
				M.push_back(D[i]+1);
				sort(M.begin(),M.end());
				d--;
				remove(D.begin(),D.end(),D[i]);
				D.pop_back();
				ret+=left+1;
			}
		}
		cout<<ret<<endl;
	}
}