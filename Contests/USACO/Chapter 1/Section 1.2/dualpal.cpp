/*
ID: b0002141
PROG: dualpal
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

	int N,S;
	int base;
	int check;
	string buf;

    ofstream fout ("dualpal.out");
    ifstream fin ("dualpal.in");
		
	fin>>N>>S;
	S++;

	for(int i=0;i<N;S++){
		check=0;
		for(base=2;base<11;base++)
			if(isPal(change(S,base))){
				check++;
				if(check==2){
					fout<<S<<endl;
					i++;
					break;
				}
			}
	}

    return 0;
}