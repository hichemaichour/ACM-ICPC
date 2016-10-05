//#include <iostream>
//#include <fstream>
//#include <vector>
//#include <map>
//#include <algorithm>
//#include <set>
//
//using namespace std;
//
//map<int,int> m;
//vector<int> v;
//
//int main(){
//	ifstream cin("History.h");
//	int i,j,k,buf;
//	int N;
//	cin>>N;
//
//	for(i=1;i<=N;i++){
//		cin>>buf;
//		m[buf]=i;
//	}
//
//	v.resize(N);
//
//	while(cin>>buf){
//		v[0]=m[buf];
//		for(i=1;i<N;i++){
//			cin>>buf;
//			v[i]=m[buf];
//		}
//
//		cout<<endl;
//	}
//}

#include <iostream>
#include <vector>
#include <fstream>
using namespace std;

int n;
vector<vector<int> > s;
vector<int> num;
vector<int> temp;

int main()
{
	ifstream cin("History.h");
	int t;
	cin>>n;
	num.resize(n+1);
	temp.resize(n+1);
	s.resize(n+1,vector<int>(n+1));

	for(int i=1;i<=n;++i){
		cin>>t;
		num[t]=i;
	}

	while(cin>>t){
		temp[t]=1;
		for(int i=2;i<=n;++i){
			cin>>t;
			temp[t]=i;
		}

		for(int i=1;i<=n;++i){
			for(int j=1;j<=n;++j){
				if(num[i]==temp[j]) 
					s[i][j]=s[i-1][j-1]+1;
				else 
					s[i][j]=max(s[i-1][j],s[i][j-1]);
			}
		}

		cout<<s[n][n]<<endl;
	}
	return 0;
}