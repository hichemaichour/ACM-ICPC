#include <vector>
#include <fstream>
#include <iostream>
#include <string>
#include <sstream>

using namespace std;

int main(){
	//ifstream cin("Clock.h");
	int T;
	cin>>T;
	for(int cnt=1 ; cnt<=T ; cnt++){
		int i;
		vector<int> time(3);
		char c1,c2;
		for(i=0 ; i<3 ; i++){
			cin >> c1 >> c2;
			time[i] = ((int)(c1-'0'))*10 + (c2-'0');
			if(i!=2)
				cin >> c1;
		}

		vector<string> v(3,string("      "));
		int j;
		for(i=0 ; i<3 ; i++){
			for(j=5 ; j>=0 ; j--){
				int k = 1<<j;
				v[i][5-j] = '0' + time[i]/k;
				time[i] %= k;
			}
		}

		cout<<cnt<<" ";
		for(i=0 ; i<6 ; i++)
			for(j=0 ; j<3 ; j++)
				cout<<v[j][i];
		cout<<" ";
		for(i=0 ; i<3 ; i++)
			for(j=0 ; j<6 ; j++)
				cout<<v[i][j];
		cout<<endl;
	}
}