/*
ID: b0002141
PROG: barn1
LANG: C++
*/
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <set>

using namespace std;

int main() {
	int M,S,C;
	int plates;
	int stalls;
	vector <int> min(200);
	vector <int> caw(200);
	vector < pair<int,int> > con(200);

    ofstream fout ("barn1.out");
    ifstream fin ("barn1.in");

	fin>>M>>S>>C;

	for(int i=0;i<C;i++){
		fin>>caw[i];
	}

	sort(caw.begin(),caw.begin()+C);

	plates=0;
	stalls=0;
	for(int i=0;i<C;i++){
		con[plates].first=caw[i];
		while(i!=C-1 && caw[i]+1 == caw[i+1])i++;
		con[plates].second=caw[i];
		stalls+=con[plates].second-con[plates].first+1;
		if(plates>0)
			min[plates-1]=con[plates].first-con[plates-1].second-1;
		plates++;
	}

	sort(min.begin(),min.begin()+plates-1);

	for(int i=0;plates-M>0;i++){
		if(i>0 && min[i]==min[i-1])
			continue;
		for(int j=0;j<plates-1;j++){
			if(con[j+1].first-con[j].second-1 == min[i]){
				stalls+=min[i];
				M++;
			}
			if(plates==M)
				break;
		}
	}

	fout<<stalls<<endl;

    return 0;
}