#include <iostream>
#include <string>
#include <sstream>
#include <algorithm>

#define All(v)			v.begin(),v.end()

using namespace std;

int N;

int main() {
	while(cin >> N && N){
		int i,j,k;
		int u,v;
		int V[1001];
		for(i=0 ; i<=N ; i++)
			V[i] = 0;
		string str;
		cin >> str;
		str = str + ',';
		while(str != ""){
			string buf = str.substr(0,str.find(','));
			str = str.substr(str.find(',')+1,str.size());
			istringstream STRin;
			STRin.str(buf);
			if(buf.find('-') == string::npos){
				STRin >> u;
				if(u>0 && u<=N)
					V[u] = 1;
			}
			else{
				char c;
				STRin >> u >> c >> v;
				for(i=u ; i<=N && i<=v ; i++)
					V[i] = 1;
			}
		}
		int sum = 0;
		for(i=1 ; i<=N ; i++)
			if(V[i])
				sum++;
		cout << sum << endl;
	}
	return 0;
}

