/*
ID: your_id_here
PROG: crypt1
LANG: C++
*/
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

vector<int> a(10);

bool check(int fst,int scd,vector<bool> b, int count){
	int buf;

	//lenth of fst partial mul
	if( (fst*(scd%10))/1000 )
		return false;

	//length of scd partial mul
	if ( (fst*(scd/10))/1000 )
		return false;

	//lenth of total mul
	if ( (fst*scd)/10000 )
		return false;

	buf=fst*(scd%10);
	for(int i=0;i<3;i++){
		if(!b[buf%10])
			return false;
		buf/=10;
	}

	buf=fst*(scd/10);
	for(int i=0;i<3;i++){
		if(!b[buf%10])
			return false;
		buf/=10;
	}

	buf=fst*scd;
	for(int i=0;i<4;i++){
		if(!b[buf%10])
			return false;
		buf/=10;
	}
	return true;
}

int main() {
	int N;
	int buf;
	vector<bool> b(10);
	int fst[1000];
	int scd[100];
	int c1=0,c2=0;
	static int count=0;

	ofstream fout ("crypt1.out");
	ifstream fin ("crypt1.in");

	fin>>N;

	for(int i=0;i<N;i++){
		fin>>a[i];
		b[a[i]]=true;
	}

	sort(a.begin(),a.begin()+N);

	for(int i=0;i<N;i++){
		for(int j=0;j<N;j++){
			scd[c2]=(a[i]*10)+a[j];
			for(int k=0;k<N;k++){
				fst[c1]=scd[c2]*10+a[k];
				c1++;
			}
			c2++;
				
		}
	}

	for(int i=0;i<c1;i++)
		for(int j=0;j<c2;j++)
			if(check(fst[i],scd[j],b,count))
				count++;

	fout<<count<<endl;	

	return 0;
}