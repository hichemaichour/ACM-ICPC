#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

#define FOR(i,N) for(i=0 ; i<(int)N ; i++)
#define All(v) v.begin(),v.end()

#define T int

int N;
vector<T> V;
vector<T> Seq;

int LIS(){
	int i,j,k; // V -> VI
	VI lis(N,1);
	VI prev(N);
	FOR(i,N)
		prev[i] = i;
	FOR(i,N){ // getting the LIS till i
		FOR(j,i){ // checking the previous states
			if(V[j] < V[i] && lis[j]+1>lis[i]){ // change operator to get different versions
				prev[i] = j;
				lis[i] = lis[j]+1;
			}
		}
	}

	// get the LIS value
	int ret = 0;
	int index = -1;
	FOR(i,N){
		if(ret < lis[i]){
			ret = lis[i];
			index = i;
		}
	}

	// get the numbers in the LIS
	Seq.clear(); // Seq -> VI
	Seq.push_back(index);
	while(prev[index] != index){
		Seq.push_back(prev[index]);
		index = prev[index];
	}
	reverse(All(Seq));

	return ret;
}
