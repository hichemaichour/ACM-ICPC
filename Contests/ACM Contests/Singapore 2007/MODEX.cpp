#include <iostream>
#include <fstream>
#include <map>

using namespace std;

int x,y,n;

map<int,int> m;

int rec(int i){
	if(i==1)
		return x%n;
	if(m.find(i)==m.end())
		m[i]=( ((rec(i/2)%n)*(rec(i-(i/2))%n))%n );
	return m[i];
}

int main(){
	//ifstream cin("MODEX.h");
	int N;
	cin>>N;
	for(int cnt=1;cnt<=N;cnt++){
		cin>>x>>y>>n;
		m.clear();
		cout<<rec(y)<<endl;
	}
}