/*
ID: b0002141
PROG: transform
LANG: C++
*/
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int check_1(string O[],string I[],int N){
	for(int i=0;i<N;i++)
		for(int j=0;j<N;j++)
			if(O[i][j] != I[j][N-1-i])
				return 7;
	return 1;
}

int check_2(string O[],string I[],int N){
	for(int i=0;i<N;i++)
		for(int j=0;j<N;j++)
			if(O[i][j] != I[N-1-i][N-1-j])
				return 7;
	return 2;
}

int check_3(string O[],string I[],int N){
	for(int i=0;i<N;i++)
		for(int j=0;j<N;j++)
			if(O[i][j] != I[N-1-j][i])
				return 7;
	return 3;
}

int check_4(string O[],string I[],int N){
	for(int i=0;i<N;i++)
		for(int j=0;j<N;j++)
			if(O[i][j] != I[i][N-1-j])
				return 7;
	return 4;
}

int check_5(string O[],string I[],int N){
	string buf[10];
	string b;
	for(int i=0;i<N;i++)
		buf[i]="0000000000";
	for(int i=0;i<N;i++)
		for(int j=0;j<N;j++)
			buf[i][j]=O[i][N-1-j];
	if( check_1(buf,I,N)==7 && check_2(buf,I,N)==7 && check_3(buf,I,N)==7)
		return 7;
	return 5;
}

int check_6(string O[],string I[],int N){
	for(int i=0;i<N;i++)
		if(O[i]!=I[i])
			return 7;
	return 6;
}

int main() {
	int N;
	string O[10];
	string I[10];
	int t=7;

    ofstream fout ("transform.out");
    ifstream fin ("transform.in");

	fin>>N;

	for(int i=0;i<N;i++)
		fin>>O[i];

	for(int i=0;i<N;i++){
		fin>>I[i];
	}

	t=check_6(O,I,N);
	if(check_5(O,I,N)!=7)
		t=5;
	if(check_4(O,I,N)!=7)
		t=4;
	if(check_3(O,I,N)!=7)
		t=3;
	if(check_2(O,I,N)!=7)
		t=2;
	if(check_1(O,I,N)!=7)
		t=1;

	fout<<t<<endl;

    return 0;
}