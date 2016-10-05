/*
ID: b0002141
PROG: beads
LANG: C++
*/
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int main() {
    int N;
	string str;
	int count;
	int ret=0;
	bool change=false;
	
	ofstream fout ("beads.out");
    ifstream fin ("beads.in");

	fin>>N>>str;

	str+=str;

	for(int i=0;i<N;i++){
		count=0;
		//to the right
		if(str[i]=='w'){
			for(int l=1;l<N;l++)
				if(str[i+l]!='w'){
					str[i]=str[i+l];
					change=true;
				}
		}
		for(int j=0;j<N;j++){
			if(j==N-1){
				fout<<N<<endl;
				return 0;
			}
			if(str[i]==str[i+j] || str[i+j]=='w')
				count++;
			else{
				if(change){
					str[i]='w';
					change=false;
				}
				break;
			}
		}

		//to the left
		if(str[N+i-1]=='w'){
			for(int l=2;l<N;l++)
				if(str[N+i-l]!='w'){
					str[N+i-1]=str[N+i-l];
					change=true;
				}
		}
		for(int k=1;k<N;k++){
			if(str[N+i-1]==str[N+i-k] || str[N+i-k]=='w')
				count++;
			else{
				if(change){
					str[N+i-1]='w';
					change=false;
				}
				break;
			}
		}
		if(ret<count)
			ret=count;
	}
	if(ret>N)
		ret=N;
	fout<<ret<<endl;

    return 0;
}