/*
ID: b0002141
PROG: gift1
LANG: C++
*/
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

struct p{
	int id;
	string name;
	int amount;
	string friends[10];
	int take;
	int give;
};

int main() {
	int N,n;
	p group[10];
	string buf;

    ofstream fout ("gift1.out");
    ifstream fin ("gift1.in");
	//ifstream fin("File.txt");

	//get the names
    fin>>N;
	for(int i=0;i<N;i++){
		group[i].id=i;
		fin>>group[i].name;
		group[i].take=0;
	}

	//get to whom each will give
	for(int i=0;i<N;i++){
		fin>>buf;
		for(int k=0;k<N;k++){

			if (buf==group[k].name){
				fin>>group[k].amount>>n;
				if(n==0)
					break;
				group[k].give=group[k].amount/n;
				group[k].take+=group[k].amount-(group[k].give*n);
				for(int l=0;l<n;l++){
					fin>>buf;
					for(int j=0;j<N;j++){
						if (buf==group[j].name){
							group[j].take+=group[k].give;
							break;
						}
					}
				}
				break;
			}

		}
	}

	for(int i=0;i<N;i++){
		fout<<group[i].name<<" "<<group[i].take-group[i].amount<<endl;
	}

    return 0;
}