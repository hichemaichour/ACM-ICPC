#include <iostream>
#include <fstream>
#include <string>
#include <queue>
#include <map>

// h H g G -

using namespace std;

const long long END = 123456789;
int N;

struct mystruct{
	long long A;
	long long B;
	long long Q;
	bool operator<(const mystruct my)const{
		if(A<my.A)
			return true;
		if(my.A<A)
			return false;
		if(B<my.B)
			return true;
		if(my.B<B)
			return false;
		if(Q<my.Q)
			return true;
		if(my.Q<Q)
			return false;
	}
};

mystruct QA(mystruct my,int n){
	for(int i=0;i<n;i++){
		my.A=my.Q[0]+my.A;
		my.Q=my.Q.substr(1,my.Q.size());
	}
	return my;
}

mystruct QB(mystruct my,int n){
	for(int i=0;i<n;i++){
		my.B=my.Q[0]+my.B;
		my.Q=my.Q.substr(1,my.Q.size());
	}
	return my;
}

mystruct QQ(mystruct my,int n){
	for(int i=0;i<n;i++){
		my.Q.push_back(my.Q[0]);
		my.Q=my.Q.substr(1,my.Q.size());
	}
	return my;
}

mystruct AQ(mystruct my,int n){
	for(int i=0;i<n;i++){
		my.Q.push_back(my.A[0]);
		my.A=my.A.substr(1,my.A.size());
	}
	return my;
}

mystruct BQ(mystruct my,int n){
	for(int i=0;i<n;i++){
		my.Q.push_back(my.B[0]);
		my.B=my.B.substr(1,my.B.size());
	}
	return my;
}

mystruct AB(mystruct my,int n){
	for(int i=0;i<n;i++){
		my.B=my.A[0]+my.B;
		my.A=my.A.substr(1,my.A.size());
	}
	return my;
}

mystruct BA(mystruct my,int n){
	for(int i=0;i<n;i++){
		my.A=my.B[0]+my.A;
		my.B=my.B.substr(1,my.B.size());
	}
	return my;
}

int bfs(string str){
	if(str==END.substr(0,N))
		return 0;
	mystruct my,buf;
	int ret;
	my.Q=str;
	queue<int> n;
	queue<mystruct> q;
	map<mystruct,bool> exist;
	n.push(0);
	q.push(my);
	exist[my]=true;
	while(!q.empty()){
		ret=n.front();
		n.pop();
		my=q.front();
		q.pop();
		for(int i=1;i<=my.A.size();i++){
			buf=AQ(my,i);
			if(buf.Q == END/(N*10) )
				return ret+1;
			if(!exist[buf]){
				q.push(buf);
				n.push(ret+1);
				exist[buf]=true;
			}
			buf=AB(my,i);
			if(buf.Q==END.substr(0,N))
				return ret+1;
			if(!exist[buf]){
				q.push(buf);
				n.push(ret+1);
				exist[buf]=true;
			}
		}
		for(int j=1;j<=my.B.size();j++){
			buf=BQ(my,j);
			if(buf.Q==END.substr(0,N))
				return ret+1;
			if(!exist[buf]){
				q.push(buf);
				n.push(ret+1);
				exist[buf]=true;
			}
			buf=BA(my,j);
			if(buf.Q==END.substr(0,N))
				return ret+1;
			if(!exist[buf]){
				q.push(buf);
				n.push(ret+1);
				exist[buf]=true;
			}
		}
		for(int k=1;k<=my.Q.size();k++){
			buf=QA(my,k);
			if(buf.Q==END.substr(0,N))
				return ret+1;
			if(!exist[buf]){
				q.push(buf);
				n.push(ret+1);
				exist[buf]=true;
			}
			buf=QB(my,k);
			if(buf.Q==END.substr(0,N))
				return ret+1;
			if(!exist[buf]){
				q.push(buf);
				n.push(ret+1);
				exist[buf]=true;
			}
			buf=QQ(my,k);
			if(buf.Q==END.substr(0,N))
				return ret+1;
			if(!exist[buf]){
				q.push(buf);
				n.push(ret+1);
				exist[buf]=true;
			}
		}
	}
	return -1;
}

int main(){
	ifstream cin("Sort.h");
	while(true){
		int buf;
		cin>>N;
		if(N==0)
			return 0;

		string str;
		for(int i=0;i<N;i++){
			cin>>buf;
			str.push_back('0'+buf);
		}
		cout<<bfs(str)<<endl;
	}
}