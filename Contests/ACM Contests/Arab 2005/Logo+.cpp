#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>

// h H g G -

using namespace std;

map<pair<int,int>,int> m;
pair<int,int> p;
int N;

void func(char c){
	switch(c){
		case 'U':
			p.second++;
			break;
		case 'D':
			p.second--;
			break;
		case 'L':
			p.first--;
			break;
		case 'R':
			p.first++;
			break;
	}
	m[p]++;
	if(m[p]==2)
		N++;
}

int main(){
	//ifstream cin("Logo.h");
	while(true){
		string str;
		cin>>str;
		if(str=="Q")
			return 0;
		str.resize(str.size()-1);

		m.clear();
		p.first=0;
		p.second=0;
		N=0;

		m[p]=1;
		for(int i=0;i<str.size();i++)
			func(str[i]);

		cout<<N<<endl;
	}
}