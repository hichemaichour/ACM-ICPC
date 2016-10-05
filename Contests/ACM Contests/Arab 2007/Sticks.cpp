#include <iostream>
#include <fstream>
#include <map>
#include <vector>
#include <algorithm>
#include <sstream>

using namespace std;

char op;
int n;
int Get;
int Put;
bool finish;
string str;
map<pair<char,char>,pair<int,int> > m;

void init(){
	m[pair<char,char>('0','1')]=pair<int,int>(4,0);
	m[pair<char,char>('0','2')]=pair<int,int>(1,1);
	m[pair<char,char>('0','3')]=pair<int,int>(1,1);
	m[pair<char,char>('0','4')]=pair<int,int>(2,1);
	m[pair<char,char>('0','5')]=pair<int,int>(1,1);
	m[pair<char,char>('0','6')]=pair<int,int>(0,1);
	m[pair<char,char>('0','7')]=pair<int,int>(3,0);
	m[pair<char,char>('0','8')]=pair<int,int>(-1,0);
	m[pair<char,char>('0','9')]=pair<int,int>(1,1);

	m[pair<char,char>('1','2')]=pair<int,int>(-3,1);
	m[pair<char,char>('1','3')]=pair<int,int>(-3,0);
	m[pair<char,char>('1','4')]=pair<int,int>(-2,0);
	m[pair<char,char>('1','5')]=pair<int,int>(-3,1);
	m[pair<char,char>('1','6')]=pair<int,int>(-4,1);
	m[pair<char,char>('1','7')]=pair<int,int>(-1,0);
	m[pair<char,char>('1','8')]=pair<int,int>(-5,0);
	m[pair<char,char>('1','9')]=pair<int,int>(-3,0);

	m[pair<char,char>('2','3')]=pair<int,int>(0,1);
	m[pair<char,char>('2','4')]=pair<int,int>(0,2);
	m[pair<char,char>('2','5')]=pair<int,int>(0,2);
	m[pair<char,char>('2','6')]=pair<int,int>(-1,1);
	m[pair<char,char>('2','7')]=pair<int,int>(2,1);
	m[pair<char,char>('2','8')]=pair<int,int>(-2,0);
	m[pair<char,char>('2','9')]=pair<int,int>(0,2);

	m[pair<char,char>('3','4')]=pair<int,int>(1,1);
	m[pair<char,char>('3','5')]=pair<int,int>(0,1);
	m[pair<char,char>('3','6')]=pair<int,int>(-1,1);
	m[pair<char,char>('3','7')]=pair<int,int>(2,0);
	m[pair<char,char>('3','8')]=pair<int,int>(-2,0);
	m[pair<char,char>('3','9')]=pair<int,int>(0,1);

	m[pair<char,char>('4','5')]=pair<int,int>(-1,1);
	m[pair<char,char>('4','6')]=pair<int,int>(-2,1);
	m[pair<char,char>('4','7')]=pair<int,int>(1,1);
	m[pair<char,char>('4','8')]=pair<int,int>(-3,0);
	m[pair<char,char>('4','9')]=pair<int,int>(-1,0);

	m[pair<char,char>('5','6')]=pair<int,int>(-1,0);
	m[pair<char,char>('5','7')]=pair<int,int>(2,1);
	m[pair<char,char>('5','8')]=pair<int,int>(-2,0);
	m[pair<char,char>('5','9')]=pair<int,int>(0,1);

	m[pair<char,char>('6','7')]=pair<int,int>(3,1);
	m[pair<char,char>('6','8')]=pair<int,int>(-1,0);
	m[pair<char,char>('6','9')]=pair<int,int>(1,1);

	m[pair<char,char>('7','8')]=pair<int,int>(-4,0);
	m[pair<char,char>('7','9')]=pair<int,int>(-2,0);

	m[pair<char,char>('8','9')]=pair<int,int>(2,0);

	for(char c1='9';c1>='0';c1--)
		for(char c2=c1;c2>='0';c2--)
			m[pair<char,char>(c1,c2)]=pair<int,int>(m[pair<char,char>(c2,c1)].first*-1,m[pair<char,char>(c2,c1)].second);
}


int str2int(string STR){
	stringstream ss;
	ss<<STR;
	int n;
	ss>>n;
	return n;
}

bool check(){
	int n1=str2int(str.substr(0,str.find(op)));
	int n2=str2int(str.substr(str.find(op)+1,str.find('=')-str.find(op)-1));
	int n3=str2int(str.substr(str.find('=')+1,str.size()-str.find('=')-1));
	switch(op){
		case '+':
			return (n1+n2==n3);
		case '-':
			return (n1-n2==n3);
		case '*':
			return (n1*n2==n3);
		case '/':
			return (n2!=0 && n1/n2==n3 && n1%n2==0);
	}
}

void rec(int pos,int sum){
	if(pos>=str.size())
		return;
	if(!isdigit(str[pos])){
		rec(pos+1,sum);
		return;
	}

	pair<char,char> p;
	p.first=str[pos];
	for(char c='0';c<='9';c++){
		p.second=c;

		if(m[p].first>0)
			Get+=m[p].first;
		else
			Put+=abs(m[p].first);
		sum+=m[p].second;
		str[pos]=p.second;

		if(Get==Put && Get+sum==n && check()){
			finish=true;
			return;
		}

		if(sum+max(Get,Put)<=n)
			rec(pos+1,sum);

		if(finish)
			return;

		if(m[p].first>0)
			Get-=m[p].first;
		else
			Put-=abs(m[p].first);
		sum-=m[p].second;
		str[pos]=p.first;
	}
}

int main(){
	ifstream cin("Sticks.h");
	init();
	for(int cnt=1;true;cnt++){
		getline(cin,str);
		str.resize(remove(str.begin(),str.end(),' ')-str.begin());
		if(str=="EOF")
			return 0;
		stringstream ss;

		ss<<str.substr(str.find('(')+1,str.find(')')-str.find('(')-1);

		str=str.substr(0,str.find('('));
		ss>>n;

		op=*find_if(str.begin(),str.end(),ispunct);

		Get=0;
		Put=0;
		finish=false;
		if(op=='/')
			rec(0,0);
		else{
			
		}

		if(finish)
			cout<<cnt<<". "<<str<<endl;
		else
			cout<<cnt<<". UNSOLVABLE"<<endl;
	}
}