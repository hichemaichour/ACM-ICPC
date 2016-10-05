#include <iostream>
#include <fstream>
#include <set>
#include <deque>
#include <vector>
#include <algorithm>

using namespace std;

int main(){
	//ifstream cin("Rings.h");
	for(int cnt=1;true;cnt++){
		int N;
		cin>>N;
		if(N==0)
			break;

		set<int> s;
		vector< vector<int> > v(N,vector<int>(N));
		for(int i=0;i<N;i++){
			for(int j=0;j<N;j++){
				cin>>v[i][j];
				s.insert(v[i][j]);
			}
		}

		set<int>::iterator iterS = s.end();
		iterS--;
		if(s.size()!=N*N || *iterS != N*N){
			cout<<cnt<<". NO"<<endl;
			continue;
		}

		int half=(N+1)/2;
		bool flag=true;
		vector< deque<int> > d(half);
		for(int I=0;I<half;I++){
			//get the rings
			for(int R=I;R<N-I;R++)
				d[I].push_back(v[I][R]);
			for(int D=I+1;D<N-I;D++)
				d[I].push_back(v[D][N-I-1]);
			for(int L=N-I-2;L>=I;L--)
				d[I].push_back(v[N-I-1][L]);
			for(int U=N-I-2;U>I;U--)
				d[I].push_back(v[U][I]);

			//get the initial of each ring
			int index=find(d[I].begin(),d[I].end(),(I*N)+I+1)-d[I].begin();
			if(index==d[I].size()){
				flag=false;
				break;
			}

			//sort each ring
			for(int J=0;J<index;J++){
				d[I].push_back(d[I][0]);
				d[I].pop_front();
			}

			//find if it is correct or not
			int num;
			int start=0;
			int end=N-(2*I);
			for(num=0;num<end;num++)
				if(d[I][num]!=(N*I)+I+1+(num-start))
					flag=false;
			start=end;
			end+=N-(2*I)-1;
			for(;num<end;num++)
				if(d[I][num]!=(N*(I+2))-I+((num-start)*N))
					flag=false;
			start=end;
			end+=N-(2*I)-1;
			for(;num<end;num++)
				if(d[I][num]!=(N*N)-(N*I)-I-1-(num-start))
					flag=false;
			start=end;
			end+=N-(2*I)-2;
			for(;num<end;num++)
				if(d[I][num]!=(N*(N-2))-(N*I)+1+I-((num-start)*N))
					flag=false;

			if(flag==false)
				break;
		}

		if(flag==false){
			cout<<cnt<<". NO"<<endl;
			continue;
		}

		cout<<cnt<<". YES"<<endl;
	}
}