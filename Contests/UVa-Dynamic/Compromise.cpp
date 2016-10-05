#include <iostream>
#include <vector>
#include <string>
#include <deque>

using namespace std;

vector<string> a;
vector<string> b;
vector<vector<int> > m;
vector<pair<int,int> > trace;
deque<string>ret;

//int LCS(){
//	int i,j;
//	int N,M;
//	m.clear();
//	trace.clear();
//	ret.clear();
//
//	M=a.size();
//	N=b.size();
//	m.resize(M+1,vector<int>(N+1));
//	trace.resize(M+1);
//	trace[0]=pair<int,int>(0,0);
//
//	for(i=0;i<=M;i++){
//		for(j=0;j<=N;j++){
//			if(i==0 || j==0){
//				m[i][j]=0;
//				continue;
//			}
//			if(a[i-1]==b[j-1]){
//				m[i][j]=1+m[i-1][j-1];
//				trace[i]=pair<int,int>(i,trace[i-1].first);
//			}
//			else{
//				if(m[i][j-1]>m[i-1][j])
//					m[i][j]=m[i][j-1];
//				else{
//					m[i][j]=m[i-1][j];
//					trace[i]=trace[i-1];
//				}
//			}
//		}
//	}
//
//	for(i=trace[M].first ; i>0 ; i=trace[i].second)
//		ret.push_front(a[i-1]);
//
//	return m[0][0];
//}

int LCS(){
	int i,j;
	int N,M;
	m.clear();
	trace.clear();
	ret.clear();

	M=a.size();
	N=b.size();
	m.resize(M+1,vector<int>(N+1));
	trace.resize(M+1);
	trace[M]=pair<int,int>(M,M);

	for(i=M;i>=0;i--){
		for(j=N;j>=0;j--){
			if(i==M || j==N){
				m[i][j]=0;
				continue;
			}
			if(a[i]==b[j]){
				m[i][j]=1+m[i+1][j+1];
				trace[i]=pair<int,int>(i,trace[i+1].first);
			}
			else{
				if(m[i][j+1]>m[i+1][j])
					m[i][j]=m[i][j+1];
				else{
					m[i][j]=m[i+1][j];
					trace[i]=trace[i+1];
				}
			}
		}
	}

	for(i=trace[0].first;i<M;i=trace[i].second)
		ret.push_back(a[i]);

	return m[0][0];
}


int main(){
	string str;
	while(cin>>str){
		a.clear();
		b.clear();
		while(str!="#"){
			a.push_back(str);
			cin>>str;
		}

		cin>>str;
		while(str!="#"){
			b.push_back(str);
			cin>>str;
		}

		LCS();

		int i;
		for(i=0 ; i<ret.size()-1 ; i++)
			cout<<ret[i]<<" ";
		cout<<ret[i]<<endl;
	}
}