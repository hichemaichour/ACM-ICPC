/*
ID: b0002141
PROG: friday
LANG: C++
*/

#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int main() {
	int N;
	int d=2;
	int leap;
	int week[7]={0};
	int add[12];
	add[0]=5;
	add[1]=1;
	add[2]=1;
	add[3]=4;
	add[4]=6;
	add[5]=2;
	add[6]=4;
	add[7]=0;
	add[8]=3;
	add[9]=5;
	add[10]=1;
	add[11]=3;
	
	ofstream fout ("friday.out");
	ifstream fin ("friday.in");

	fin>>N;

	for(int j=0;j<N;j++){
		if(j==100)
			leap=1;
		else if (j%100 == 0)
			leap=0;
		else if ((1900+j)%4 == 0)
			leap=1;
		else 
			leap=0;

		for(int i=0;i<12;i++){
			if(i<2)
				week[(d+add[i])%7]++;
			else
				week[(d+add[i]+leap)%7]++;
		}

		d+=1+leap;
	}

	//outputing
	for(int i=0;i<7;i++){
		fout<<week[i];
		if(i!=6)
			fout<<" ";
	}
	fout<<endl;

    return 0;
}