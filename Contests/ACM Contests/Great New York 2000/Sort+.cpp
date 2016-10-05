#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
#include <string>
#include <sstream>

using namespace std;

vector<string> n;
vector<string> w;
vector<bool> word;

bool funcN(string str1,string str2){
	stringstream s1,s2;
	int n1,n2;
	s1<<str1;
	s1>>n1;
	s2<<str2;
	s2>>n2;
	return n1<n2;
}

bool funcW(string str1,string str2){
	for(int i=0;i<str1.size();i++)
		str1[i]=tolower(str1[i]);
	for(int j=0;j<str2.size();j++)
		str2[j]=tolower(str2[j]);
	return str1<str2;
}

int main(){
	//ifstream cin("Sort.h");
	while(true){
		string str=",";
		n.clear();
		w.clear();
		word.clear();
		while(str[str.size()-1]!='.'){
			cin>>str;
			if(str==".")
				return 0;
			if(isdigit(str[0]) || str[0]=='-'){
				word.push_back(false);
				n.push_back(str.substr(0,str.size()-1));
			}
			else{
				word.push_back(true);
				w.push_back(str.substr(0,str.size()-1));
			}
		}

		sort(w.begin(),w.end(),funcW);
		sort(n.begin(),n.end(),funcN);

		int i=0;
		int j=0;
		for(int k=0;k<word.size();k++){
			if(k!=0)
				cout<<" ";
			
			if(word[k]){
				cout<<w[i];
				i++;
			}
			else{
				cout<<n[j];
				j++;
			}

			if(k==word.size()-1)
				cout<<"."<<endl;
			else
				cout<<",";
		}
	}
}