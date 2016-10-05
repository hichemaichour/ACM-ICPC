#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <deque>

using namespace std;

vector<pair<vector<int>,int> > a;
vector<pair<int,int> > m;

bool Sort(pair<vector<int>,int> p1,pair<vector<int>,int> p2){
	return lexicographical_compare(p1.first.begin(),p1.first.end(),p2.first.begin(),p2.first.end());
}

bool Greater(int j,int i){
	for(int k=0;k<a[i].first.size();k++)
		if(a[i].first[k]>=a[j].first[k])
			return false;
	return true;
}

int LIS(){
	int i,j;
	int n=a.size();

	for(i=n-1; i>=0; i--)
	{
		m[i]=pair<int,int>(1,n);
		for(j=i+1; j<n; j++)
			if(Greater(j,i))
				if(m[j].first+1>m[i].first)
					m[i]=pair<int,int>(m[j].first+1,j);
	}

	pair<int,int> ans = pair<int,int>(0,-1);
	for(i=0; i<n; i++) 
		if(ans.first<m[i].first)
			ans=pair<int,int>(m[i].first,i);

	return ans.second;
}

int main(){
	//ifstream cin("StackingBoxes.h");
	int N,n;
	while(cin>>N>>n){
		int i,j,k;
		a.clear();
		m.clear();
		a.resize(N);
		m.resize(N);

		for(i=0;i<N;i++){
			a[i].first.resize(n);
			for(j=0;j<n;j++)
				cin>>a[i].first[j];
			a[i].second=i+1;
			sort(a[i].first.begin(),a[i].first.end());
		}

		sort(a.begin(),a.end(),Sort);

		vector<int> ret;
		for(i=LIS();i<N;i=m[i].second)
			ret.push_back(a[i].second);

		cout<<ret.size()<<endl;
		for(i=0;i<ret.size()-1;i++)
			cout<<ret[i]<<" ";
		cout<<ret[i]<<endl;
	}
}