#include <iostream>
#include <string>
#include <map>

using namespace std;

map<char,int> m;

void init(){
	m['R'] = 0;
	m['S'] = 1;
	m['P'] = 2;
}

int main(){
	init();
	while(true){
		string s1,s2;
		cin >> s1 >> s2;
		if(s1 == "E")
			return 0;

		int n1=0,n2=0;
		for(int i=0 ; i<s1.size() ; i++){
			if(s1[i] == s2[i])
				continue;
			if((m[s1[i]] + 1)%3 == m[s2[i]])
				n1++;
			else
				n2++;
		}
		cout <<"P1: "<< n1 << endl;
		cout <<"P2: "<< n2 << endl;
	}
}