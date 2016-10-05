/*
ID: b0002141
PROG: namenum
LANG: C++
*/
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

char change(char c){
	switch (c){
		case 'A':
		case 'B':
		case 'C':
			return '2';
		case 'D':
		case 'E':
		case 'F':
			return '3';
		case 'G':
		case 'H':
		case 'I':
			return '4';
		case 'J':
		case 'K':
		case 'L':
			return '5';
		case 'M':
		case 'N':
		case 'O':
			return '6';
		case 'P':
		case 'R':
		case 'S':
			return '7';
		case 'T':
		case 'U':
		case 'V':
			return '8';
		case 'W':
		case 'X':
		case 'Y':
			return '9';
	}
}

bool cmp(string buf,string N){
	for(int i=0;i<(int)buf.size();i++)
		buf[i]=change(buf[i]);
	if (buf==N)
		return true;
	return false;
}

int main() {
	string N;
	string buf;
	int count=0;
	string ret[5000];

    ofstream fout ("namenum.out");
    ifstream fin ("namenum.in");

	fin>>N;

	ifstream in("dict.txt");
	while(!in.eof()){
		in>>buf;
		if(buf.size() == N.size())
			if (cmp(buf,N))
				ret[count++]=buf;
	}

	for(int i=0;i<count;i++){
		fout<<ret[i]<<endl;
	}
	if(count==0)
		fout<<"NONE"<<endl;
    return 0;
}