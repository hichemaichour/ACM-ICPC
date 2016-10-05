#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include <queue>
#include <iomanip>
#include <functional>
#include <deque>

using namespace std;

map<char,int> m;
deque<int> v;
vector<string> s;
int MAX;
int MIN;

int funcT(pair<char,int> p){
	return p.second;
}

int rec(int pos,int pre,int depth){
	if(depth==9) // nothing should be encoded with more than 8 bits :)
		return -1;

	int Max=2*pre;
	if(v.size()-pos <= Max){
		return ((v[v.size()-1]-v[pos-1])*depth);
	}

	int ret=-1;
	int buf;
	for(int i=0;i<Max;i++){
		buf=rec(pos+i,Max-i,depth+1);
		if(buf==-1)
			continue;
		buf+=(v[pos-1+i]-v[pos-1])*depth;
		if(ret==-1)
			ret=buf;
		if(buf<=ret)
			ret=buf;
		else
			break;
	}
	return ret;
}

int main(){
	while(true){
		string str;
		m.clear();
		v.clear();
		getline(cin,str);
		if(str=="END")
			return 0;

		for(int i=0;i<str.size();i++)
			m[str[i]]++;

		v.resize(m.size());
		transform(m.begin(),m.end(),v.begin(),funcT);
		sort(v.begin(),v.end(),greater<int>());
		
		// Partial Sum Trick
		for(int i=1;i<v.size();i++)
			v[i]+=v[i-1];
		v.push_front(0);

		MAX=8*str.size();
		MIN=rec(1,1,1);

		cout<<MAX<<" "<<MIN<<" ";
		cout<<setiosflags(ios::fixed)<<setprecision(1)<<((double)MAX)/MIN<<endl;
		cout<<setprecision(0);
	}
}