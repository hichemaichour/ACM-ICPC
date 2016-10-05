#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <algorithm>

using namespace std;

vector<pair<pair<int,int>,int> > a;
vector<pair<int,int> > m;
vector<int> ret;

int LIS(){
	m.clear();
	ret.clear();
	int i,j;
	int N;

	N=a.size();
	m.resize(N);

	for(i=N-1; i>=0; i--)
	{
		m[i]=pair<int,int>(1,N);
		for(j=i+1; j<N; j++)
			if(a[j].first.second<a[i].first.second && a[j].first.first>a[i].first.first)
				if(m[j].first+1>m[i].first)
					m[i]=pair<int,int>(m[j].first+1,j);
	}

	pair<int,int> ans = pair<int,int>(0,-1);
	for(i=0; i<N; i++) 
		if(ans.first<m[i].first)
			ans=pair<int,int>(m[i].first,i);

	for(i=ans.second;i<N;i=m[i].second)
		ret.push_back(a[i].second);

	return ret.size();
}

int main(){
	//ifstream cin("BiggerSmarter.h");
	int X,Y;
	int i=1;
	a.clear();
	while(cin>>X>>Y)
		a.push_back(pair<pair<int,int>,int>(pair<int,int>(X,Y),i++));

	sort(a.begin(),a.end());

	cout<<LIS()<<endl;
	for(i=0;i<ret.size();i++)
		cout<<ret[i]<<endl;
}