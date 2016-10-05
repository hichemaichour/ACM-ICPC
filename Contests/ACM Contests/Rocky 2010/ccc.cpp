#include <iostream>
#include <queue>
#include <deque>
#include <string>
#include <map>
#include <vector>
#include <algorithm>
#include <set>
#include <fstream>

#define FOR(i,N)		for(i=0 ; i<(int)N ; i++)

#define II				pair<int,int>
#define VII				deque<II>

#define VI				vector<int>
#define MVI				map<int,VI>

using namespace std;

int dx[8] = {1,1,0,-1,-1,-1, 0, 1};
int dy[8] = {0,1,1, 1, 0,-1,-1,-1};



int main() {
	ifstream cin("input2.txt");
	string str;
	VII v;
	
	while(cin >> str){
		int i,j,k;
		
		int x = 0;
		int y = 0;
		int pos = 0;
		
		v.push_back(II(x,y));
		FOR(i,str.size()){
			k = str[i] - '0';
			
		}
		
		
	}
	return 0;
}