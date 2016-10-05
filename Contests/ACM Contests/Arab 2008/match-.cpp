#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

string func(string str){
	for(int i=0;i<str.size()-1;i++){
		if(str[i]=='*' && str[i+1]=='*')
			str.replace(i--,2,"*");
		else if(str[i]=='#' && str[i+1]=='#')
			str.replace(i--,2,"*");
		else if(str[i]=='*' && str[i+1]=='#')
			str.replace(i--,2,"#");
		else if(str[i]=='#' && str[i+1]=='*')
			str.replace(i--,2,"#");
	}
	return str;
}

bool cmp(string single,string seq){
	int j=0;
	int i=0;
	//check until before reaching the last element
	for(;i<single.size()-1;(i++)+(j++)){
		if(single[i]==seq[j])
			continue;

		if(isdigit(single[i]))
			return false;

		//for odd u need to at least jump one
		if(single[i]=='#')
			j++;
		//for even u might have no jump
		else;

		//check with the next number
		i++;
		//check
		while(true){
			if(j>=seq.size())
				return false;
			if(single[i]==seq[j])
				break;
			j+=2;
		}
	}
	//check if the digit before the last was not a digit which means that u already checked the last element
	if(i==single.size()){
		if(j==seq.size())
			return true;
		return false;
	}

	//check the last element if it is digit
	if(isdigit(single[i])){
		if(single[i]==seq[j] && j==seq.size()-1)
			return true;
		return false;
	}

	//check the last if it is sign
	if(single[i]=='*'){
		if((seq.size()-j)%2==0)
			return true;
		return false;
	}
	else{
		if((seq.size()-j)%2==1)
			return true;
		return false;
	}	
	return true;
}


int main(){
	ifstream cin("match.h");
	for(int cnt=1;true;cnt++){
		string single,buf;
		vector<string> seq;
		cin>>single;
		while(true){
			cin>>buf;
			if(buf=="END" || buf=="QUIT")
				break;
			seq.push_back(buf);
		}

		//remove any duplication of stars or hashs
		single=func(single);

		for(int i=0;i<seq.size();i++){
			if(cmp(single,seq[i]))
				cout<<cnt<<"."<<i+1<<". match\n";
			else
				cout<<cnt<<"."<<i+1<<". not\n";
		}

		if(buf=="QUIT")
			break;
	}
	return 0;
}