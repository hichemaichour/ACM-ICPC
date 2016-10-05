#include <iostream>
#include <string>
#include <map>
#include <vector>

using namespace std;

map<char,int> m;
char M[]={' ','A','D','G','J','M','P','T','W'};
int n,k;

void init(){
	int i=1;
	for(char c='A';c<'Z';c+=3){
		m[c]=i;
		m[c+1]=i;
		m[c+2]=i;
		if(c=='P' || c=='W'){
			m[c+3]=i;
			c++;
		}
		i++;
	}
	m[' ']=0;
}

int func(string str){
	int ret=0;
	for(int i=1;i<str.size();i++){
		if(m[str[i]]==m[str[i-1]] && str[i]!=' ')
			ret+=k;

		ret+=n;
		ret+=n*(str[i]-M[m[str[i]]]);
	}

	return ret;
}

void main(){
	int T;
	init();
	cin>>T;
	while(T--){
		string str;
		cin>>n>>k;

		getline(cin,str);
		getline(cin,str);
		str='a'+str;

		cout<<func(str)<<endl;
	}
}