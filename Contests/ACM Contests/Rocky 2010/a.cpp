#include <iostream>
#include <string>
#include <vector>

#define VS				vector<string>

#define FOR(i,N)		for(i=0 ; i<(int)N ; i++)

using namespace std;

bool match(char c1,char c2){
	return (islower(c1) || c1==')') && (islower(c2) || c2=='(');
}

string rec(string str,int Mul=0){
	int i,j,k;
	VS v;
	str = str.substr(1,str.size()-2);
	
	FOR(i,str.size()){
		string buf = "x";
		if(str[i] == '('){
			int sum=1;
			j = i;
			while(sum){
				j++;
				if(str[j] == '(')
					sum++;
				if(str[j] == ')')
					sum--;
			}
			v.push_back(str.substr(i,j-i+1));
			i = j;
		}
		else{
			buf[0] = str[i];
			v.push_back(buf);
		}
	}
	
	FOR(i,v.size()){
		if(v[i]=="+" || v[i]=="*") continue;
		
		if(v[i].size() != 1){
			if(i!=0 && v[i-1]=="*")
				v[i] = rec(v[i],1);
			else if(i!=v.size()-1 && v[i+1]=="*")
				v[i] = rec(v[i],1);
			else
				v[i] = rec(v[i],0);
		}
	}
	
	str = "";
	FOR(i,v.size()){
		if(v[i] != "*")
			str += v[i];
	}
	
	v.clear();
	FOR(i,str.size()){
		string buf = "x";
		if(str[i] == '('){
			int sum=1;
			j = i;
			while(sum){
				j++;
				if(str[j] == '(')
					sum++;
				if(str[j] == ')')
					sum--;
			}
			v.push_back(str.substr(i,j-i+1));
			i = j;
		}
		else{
			buf[0] = str[i];
			v.push_back(buf);
		}
	}
	if(Mul){
		Mul = 0;
		FOR(i,v.size())
			if(v[i] == "+")
				Mul = 1;
	}
	
	if(Mul)
		str = '(' + str + ')';
	return str;
}

int main(){
	string str;
	while(cin >> str){
		int i;
		str = '(' + str + ')';
		FOR(i,str.size()-1){
			if(match(str[i],str[i+1])){
				str = str.substr(0,i+1) + '*' + str.substr(i+1,str.size());
				i++;
			}
		}
		cout << rec(str) << endl;
	}
}
