#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

int N;
vector<string> s1(4);
vector<string> s2(4);
vector<string> s3(4);
vector<string> data;

void init(){
	for(int i=0;i<4;i++){
		s1[i].resize(N);
		s2[i].resize(N);
		s3[i].resize(N);
		s4[i].resize(N);
	}

	for(int j=0;j<N;j++){
		s1[0][j]=data[j][N-1];
		s1[1][j]=data[0][j];
		s1[2][j]=data[N-1-j][0];
		s1[3][j]=data[N-1][N-1-j];

		s2[0][j]=data[N+j][N-1];
		s2[1][j]=data[N+0][j];
		s2[2][j]=data[N+N-1-j][0];
		s2[3][j]=data[N+N-1][N-1-j];
		
		s3[0][j]=data[N+N+j][N-1];
		s3[1][j]=data[N+N+0][j];
		s3[2][j]=data[N+N+N-1-j][0];
		s3[3][j]=data[N+N+N-1][N-1-j];
	}
}

bool eq_n(string str1,string str2){
	return str1==str2;
}

bool eq_r(string str1,string str2){
	reverse(str2.begin(),str2.end());
	return str1==str2;
}

bool func1(){
	for(int i=0;i<s1.size();i++){
		for(int j=0;j<s2.size();j++){
			if( eq_r(s1[i],s2[j]) ){
				for(int k=0;k<s3.size();k++){
					if( eq_r(s1[(i+1)%4],s3[k]) && eq_r(s2[(j+3)%4],s3[(k+1)%4]) )
						return true;
				}
			}
		}
	}
	return false;
}

bool func(){
	//s1 s2 s3
	if(func1())
		return true;

	//s1 s3 s2
	swap(s2,s3);
	if(func1())
		return true;

	//s3 s1 s2
	swap(s1,s3);
	if(func1())
		return true;

	//s2 s1 s3
	swap(s2,s3);
	if(func1())
		return true;

	//s2 s3 s1
	swap(s1,s3);
	if(func1())
		return true;

	//s3 s2 s1
	swap(s2,s3);
	if(func1())
		return true;

	return false;
}

int main(){
	//ifstream cin("Plato.h");
	for(int cnt=1;true;cnt++){
		cin>>N;
		if(N==0)
			return 0;

		data.resize(3*N);
		for(int i=0;i<3*N;i++)
			cin>>data[i];

		init();

		if(func())
			cout<<"Data set "<<cnt<<": Valid set of patterns"<<endl;
		else
			cout<<"Data set "<<cnt<<": Impossible combination"<<endl;
	}
}