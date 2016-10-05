#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

char a[] = {' ','!','$','(',')','*'};
string b[] = {"%20","%21","%24","%28","%29","%2a"};

void Modify(string& str){
	int pos = 0;
	while(str.find('%',pos) != string::npos){
		pos = str.find('%',pos);
		str.replace(pos,1,"%25");
		pos++;
	}

	for(int i=0 ; i<6 ; i++){
		pos = 0;
		while(str.find(a[i],pos) != string::npos){
			pos = str.find(a[i],pos);
			str.replace(pos,1,b[i]);
			pos++;
		}
	}
}

int main(){
	while(true){
		string str;
		getline(cin,str);
		if(str == "#")
			return 0;
		Modify(str);
		cout << str << endl;
	}
}