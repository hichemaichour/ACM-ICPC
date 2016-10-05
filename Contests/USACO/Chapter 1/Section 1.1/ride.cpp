/*
ID: b0002141
PROG: ride
LANG: C++
*/

#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int main() {
	char comet[7];
	char group[7];
	int c1=1,c2=1;
	int buf;

    ofstream fout ("ride.out");
    ifstream fin ("ride.in");
    
	fin.getline(comet,7);
	fin.getline(group,7);

	for(int i=0;comet[i]!='\0';i++){
		buf=comet[i]-'A'+1;
		c1*=buf;
	}

	for(int j=0;group[j]!='\0';j++){
		buf=group[j]-'A'+1;
		c2*=buf;
	}

	if((c1%47)==(c2%47))
		fout<<"GO"<<endl;
	else
		fout<<"STAY"<<endl;

    return 0;
}