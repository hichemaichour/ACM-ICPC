#include <iostream>
#include <algorithm>

#define FOR(i,N)		for(i=0 ; i<(int)N ; i++)

using namespace std;

int main() {
	int N;
	while(cin >> N && N){
		int i,j,k;
		int v[100];
		for(i=0 ; i<N ; i++) cin >> v[i];
		
		int sum = 0;
		FOR(i,N) sum += v[i];
		
		int ans5=0,ans6=0,ans7=0;
		int buf;
		buf = *(max_element(v,v+N));
		if(sum <= 25){
			ans5 = 50/buf + 1;
		}
		if(sum <= 30){
			ans6 = 60/buf + 1;
		}
		if(sum <= 35){
			ans7 = 70/buf + 1;
		}
		
		cout << ans5 <<" "<< ans6 <<" "<< ans7 << endl;
	}
	return 0;
}

