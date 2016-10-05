#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>

using namespace std;

const int inf=999999;
vector<vector<int> > city;

void floyd(int N){
	for(int k=0;k<N;k++)
		for(int i=0;i<N;i++)
			for(int j=0;j<N;j++)
				if(city[i][k]+city[k][j]<city[i][j])
					city[i][j]=city[i][k]+city[k][j];
}

int main(){
	//ifstream cin("ein.h");
	for(int cnt=1;true;cnt++){
		int N,C,R;
		cin>>N>>C>>R;
		if(N==0)
			break;
		city.clear();
		city.resize(N, vector<int>(N,inf));
		for(int k=0;k<N;k++)
			city[k][k]=0;
		vector<string> cars(C+1);
		
		for(int i=0;i<C+1;i++){
			cin>>cars[i];
		}
		cars.push_back(cars[0]);

		map<string,int> m;
		string fst,scd;
		char c1,buf,c2;
		int dist, count = 0;
		for(int j=0;j<R;j++){
			cin>>fst>>c1>>buf>>dist>>buf>>c2>>scd;
			if(m.count(fst)==0)
				m[fst]=count++;
			if(m.count(scd)==0)
				m[scd]=count++;
			
			if(c2=='>' && city[m[fst]][m[scd]]>dist)
				city[m[fst]][m[scd]]=dist;
			if(c1=='<' && city[m[scd]][m[fst]]>dist)
				city[m[scd]][m[fst]]=dist;
		}

		floyd(N);

		int sum=0;
		for(int p=1;p<cars.size()-1;p++)
			sum+=city[m[cars[p]]][m[cars[0]]]+city[m[cars[0]]][m[cars[p]]];
		cout<<cnt<<". "<<sum<<endl;
	}
	return 0;
}