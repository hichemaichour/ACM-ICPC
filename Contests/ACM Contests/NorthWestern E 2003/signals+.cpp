#include <iostream>
#include <algorithm>
#include <fstream>
#include <set>

#define REP(i,a,b)		for(i=(int)a ; i<=(int)b ; i++)
#define FOR(i,N)		REP(i,0,N-1)

using namespace std;

int main(){
	ifstream cin("input.txt");
	int T;
	cin >> T;
	int V[40010];
	while(T--){
		int i,j;
		int N;
		set<int> st;
		set<int>::iterator it;
		cin >> N;

		FOR(i,N) {
			cin >> j;
			st.insert(j); it=st.find(j); it++;
			if(it!=st.end()) st.erase(it);
		}

		cout << st.size() << endl;
	}
}