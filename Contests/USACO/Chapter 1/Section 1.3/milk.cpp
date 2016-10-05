/*
ID: b0002141
PROG: milk
LANG: C++
*/
#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <vector>

using namespace std;

int main() {
	int N,M;
	vector< pair<int,int> > farmer(5000);
	int price=0;


    ofstream fout ("milk.out");
    ifstream fin ("milk.in");

	fin>>N>>M;

	for(int i=0;i<M;i++){
		fin>>farmer[i].first>>farmer[i].second;
	}

	sort(farmer.begin(),farmer.begin()+M);

	for(int i=0;i<M;i++){
		if(farmer[i].second<=N){
			price+=farmer[i].first*farmer[i].second;
			N-=farmer[i].second;
		}
		else{
			price+=farmer[i].first*N;
			break;
		}
	}

	fout<<price<<endl;

    return 0;
}