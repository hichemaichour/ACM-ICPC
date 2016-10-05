#include <iostream>
#include <vector>

using namespace std;

vector<int> MW;
vector<int> W;
vector<pair<int,int> > O;

int DP(){
	W.clear();
	W.resize(35,-1);
	W[0]=0;
	for(int i=0 ; i<O.size() ; i++)
		for(int j=30 ; j>=O[i].second ; j--)
			if( W[j-O[i].second] != -1 )
				W[j] = max(W[j],W[j-O[i].second]+O[i].first);

	for(int k=1;k<W.size();k++)
		W[k] = max(W[k-1],W[k]);

	int sum=0;
	for(int I=0 ; I<MW.size() ; I++)
		sum += W[MW[I]];

	return sum;
}

int main(){
	int T;
	cin>>T;
	while(T--){
		MW.clear();
		W.clear();
		O.clear();

		int N;
		cin>>N;
		O.resize(N);
		for(int i=0 ; i<N ; i++)
			cin>>O[i].first>>O[i].second;

		int G;
		cin>>G;
		MW.resize(G);
		for(int j=0 ; j<G ; j++)
			cin>>MW[j];

		cout<<DP()<<endl;
	}
}