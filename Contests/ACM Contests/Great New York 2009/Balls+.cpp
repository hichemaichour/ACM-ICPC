#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

int func(int n){
	int i=0;
	while(i*(i+1)/2 <n)
		i++;

	return i;
}

int func2(int n){
	int i=0;
	while(i*(i+1)/2 < n/3)
		i++;

	return i*(i+1)/2;
}

int main(){
	//ifstream cin("Balls.h");
	int N;
	cin>>N;
	for(int cnt=1;cnt<=N;cnt++){
		int buf,balls,n;
		cin>>buf>>balls>>n;

		if(buf==6)
			buf=6;

		if(balls==1){
			cout<<buf<<" "<<n<<endl;
			continue;
		}

		int ret=0;
		while(n){
			if(balls==2 || balls==3)
				break;
			ret++;
			balls--;
			n/=2;
		}

		if(balls==3 && n/2){
			n=func2(n);
			ret++;
			balls--;
		}

		if(n==1 || n==2)
			ret+=n;

		if(n>2)
			ret+=func(n);

		cout<<buf<<" "<<ret<<endl;
	}
}