#include <iostream>
#include <vector>

#define FOR(i,n) for(i=0 ; i<(int)n ; i++)

using namespace std;

vector<int> v(1001);

void init(){
	int i,j;
	v[0] = 1;
	FOR(i,v.size()){
		j = 0;
		while(true){
			if(i - 2*j < 0 || i==0)
				break;
			v[i] += v[j];
			j++;
		}
	}
}

int main(){
	init();
	int T,cnt;
	cin >> T;
	FOR(cnt,T){
		int N;
		cin >> N;
		cout << cnt+1 <<" "<< v[N] <<endl;
	}
	return 0;
}