#include <iostream>
#include <vector>
#include <cmath>
#include <fstream>

using namespace std;

#define VI				vector<int>
#define VVI				vector<VI>

#define II				pair<int,int>
#define VII				vector<II>
#define VVII			vector<VII>

#define REP(i,a,b)		for(i=(int)a ; i<=(int)b ; i++)
#define FOR(i,N)		REP(i,0,N-1)

int main(){
	ifstream cin("input.txt");
	int T,cnt;
	cin >> T;
	REP(cnt,1,T){
		int N;
		cin >> N;
		VI A;
		VI B;

		int a = 0;
		int b;
		int mul;
		while(N>0){
			for(; (N&1)==0 ; N>>=1 , a++);
			for(b=0,mul=1 ; mul*3 <= N ; b++,mul*=3);

			A.push_back(a);
			B.push_back(b);
			N -= mul;
		}

		cout << cnt <<" "<< A.size();
		FOR(mul,A.size()) cout <<" ["<< A[mul] <<","<< B[mul]<<"]";
		cout << endl;
	}
}