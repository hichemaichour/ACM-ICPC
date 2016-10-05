#include <iostream>
#include <fstream>
#include <string>
#include <queue>
#include <map>

using namespace std;

const string goal="123456789";

struct mystruct{
	string str;
	int n;
};

mystruct ar(mystruct my){
	char buf=my.str[0];
	my.str[0]=my.str[3];
	my.str[3]=my.str[4];
	my.str[4]=my.str[1];
	my.str[1]=buf;
	my.n++;
	return my;
}

mystruct al(mystruct my){
	char buf=my.str[0];
	my.str[0]=my.str[1];
	my.str[1]=my.str[4];
	my.str[4]=my.str[3];
	my.str[3]=buf;
	my.n++;
	return my;
}

mystruct br(mystruct my){
	char buf=my.str[1];
	my.str[1]=my.str[4];
	my.str[4]=my.str[5];
	my.str[5]=my.str[2];
	my.str[2]=buf;
	my.n++;
	return my;
}

mystruct bl(mystruct my){
	char buf=my.str[1];
	my.str[1]=my.str[2];
	my.str[2]=my.str[5];
	my.str[5]=my.str[4];
	my.str[4]=buf;
	my.n++;
	return my;
}

mystruct cr(mystruct my){
	char buf=my.str[3];
	my.str[3]=my.str[6];
	my.str[6]=my.str[7];
	my.str[7]=my.str[4];
	my.str[4]=buf;
	my.n++;
	return my;
}

mystruct cl(mystruct my){
	char buf=my.str[3];
	my.str[3]=my.str[4];
	my.str[4]=my.str[7];
	my.str[7]=my.str[6];
	my.str[6]=buf;
	my.n++;
	return my;
}

mystruct dr(mystruct my){
	char buf=my.str[4];
	my.str[4]=my.str[7];
	my.str[7]=my.str[8];
	my.str[8]=my.str[5];
	my.str[5]=buf;
	my.n++;
	return my;
}

mystruct dl(mystruct my){
	char buf=my.str[4];
	my.str[4]=my.str[5];
	my.str[5]=my.str[8];
	my.str[8]=my.str[7];
	my.str[7]=buf;
	my.n++;
	return my;
}

mystruct trans(mystruct my,int x){
	switch(x){
		case 0:
			return ar(my);
		case 1:
			return al(my);
		case 2:
			return br(my);
		case 3:
			return bl(my);
		case 4:
			return cr(my);
		case 5:
			return cl(my);
		case 6:
			return dr(my);
		case 7:
			return dl(my);
	}
}

int bfs(mystruct my,int n){
	queue<mystruct> q;
	map<string,bool> m;
	q.push(my);
	while(!q.empty()){
		my=q.front();
		q.pop();
		for(int i=0;i<8;i++){
			mystruct x=trans(my,i);
			if(x.n>n)
				return -1;
			if (m[x.str])
				continue;
			if (x.str==goal)
				return x.n;
			m[x.str]=true;
			q.push(x);
		}
	}
	return -1;
}

int main(){
	//ifstream cin("tobo.h");
	for(int i=1;true;i++){
		string str;
		cin>>str;
		if(str=="0000000000")
			break;
		int n=str[0]-'0';
		str=str.substr(1,str.length());
		if(str=="123456789"){
			cout<<i<<". 0"<<endl;
			continue;
		}
		mystruct my;
		my.str=str;
		my.n=0;
		int ans=bfs(my,n);
		cout<<i<<". "<<ans<<endl;
	}
	return 0;
}