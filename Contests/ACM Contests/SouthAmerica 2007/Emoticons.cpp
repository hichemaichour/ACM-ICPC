#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <vector>

using namespace std;

#define VI vector<int>
#define VVI vector<VI>
#define VS vector<string>

#define All(v) v.begin(),v.end()
#define IsIn(v,e) (find(All(v),e) != v.end())
#define Remove(v,e) v.resize( remove(All(v),e) - v.begin() )

int main(){
	ifstream cin("I.h");
	for(int hi=1 ; true ; hi++){
		int i,j,k;
		int N,M;
		cin >> N >> M;
		if(N==0)
			return 0;
		cin.ignore(100,'\n');

		VS str(N);
		for(i=0 ; i<N ; i++){
			getline(cin,str[i]);
			str[i].resize( remove(All(str[i]),' ') - str[i].begin() );
		}

		VS In(M);
		for(i=0 ; i<M ; i++)
			getline(cin,In[i]);

		int n = 0;
		for(i=0 ; i<M ; i++){
			VVI v(In[i].size());
			
			int cnt = 0;
			for(j=0 ; j<N ; j++){
				int pos = 0;
				while(In[i].find(str[j],pos) != string::npos){
					pos = In[i].find(str[j],pos);
					for(k=0 ; k<str[j].size() ; k++)
						v[pos+k].push_back(cnt);
					pos++;
					cnt++;
				}
			}
			
			while(true){
				int I;
				int Max = -1;
				for(j=0 ; j<v.size() ; j++){
					if((Max==-1 && !v[j].empty()) || (Max!=-1 && v[j].size()>Max)){
						Max = v[j].size();
						I = j;
					}
				}
				if(Max == -1)
					break;
				
				while(!v[I].empty()){
					k = v[I].front();
					int pos = I;
					while(pos < v.size() && IsIn(v[pos],k)){
						Remove(v[pos],k);
						pos++;
					}
					pos = I-1;
					while(pos >= 0 && IsIn(v[pos],k)){
						Remove(v[pos],k);
						pos--;
					}
				}
				n++;
			}
		}

		cout << n << endl;
	}
}