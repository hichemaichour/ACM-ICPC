#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <algorithm>
#include <fstream>

#define FOR(i,N)		for(i=0 ; i<(int)N ; i++)

#define VI				vector<int>
#define MVI				map<int,VI>

using namespace std;

int dx[8] = {1,1,0,-1,-1,-1, 0, 1};
int dy[8] = {0,1,1, 1, 0,-1,-1,-1};

int main() {
	ifstream cin("chaincode.in");
	string str;
	while(cin >> str){
		int i,j,k;
		int x = 0;
		int y = 0;
		map<int,int> MAX;
		map<int,int> MIN;
		MAX[x] = y;
		MIN[x] = y;
		FOR(i,str.size()){
			k = str[i]-'0';
			x += dx[k];
			y += dy[k];
			if(MAX.find(x)==MAX.end()){
				MAX[x] = y;
				MIN[x] = y;
			}
			else{
				MAX[x] = max(MAX[x],y);
				MIN[x] = min(MIN[x],y);
			}
		}
		
		long long sum = 0;
		map<int,int>::iterator it;
		
		for(it=MAX.begin() ; it!=MAX.end() ; it++){
			k = it->first;
			sum += MAX[k] - MIN[k] + 1;
		}
			
		cout << sum << endl;
		
	}
	return 0;
}

