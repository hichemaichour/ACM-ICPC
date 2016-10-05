/*
ID: b0002141
PROG: palsquare
LANG: C++
*/
#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <map>

using namespace std;

char c[20];

string change(int n,int base){
	string ret;
	char* buf;
	int mul=1;
	int size;

	//get the size of the 
	for(size=1;n/mul;size++){
		mul*=base;
	}
	buf = new char [size];
	buf[size-1]=0;

	//get the c-string with the number in the corosponding b ase
	size=0;
	for(mul/=base;mul>0;mul/=base){
		buf[size]=c[(n/mul)];
		n%=mul;
		size++;
	}

	ret=buf;
	delete[] buf;
	return ret;
}

bool isPal(string str){
	for(int i=0;i<(int)str.size()/2;i++)
		if(str[i]!=str[str.size()-1-i])
			return false;
	return true;
}

int main() {
	for(int i=0;i<10;i++)
		c[i]='0'+i;
	for(int i=0;i<10;i++)
		c[i+10]='A'+i;

	int N;
	string buf;

    ofstream fout ("palsquare.out");
    ifstream fin ("palsquare.in");
	
	fin>>N;

	for(int i=1;i<=300;i++){
		buf=change(i*i,N);
		if(isPal(buf)){
			fout<<change(i,N)<<" "<<buf<<endl;
		}
	}

    return 0;
}