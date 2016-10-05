#include <iostream>
#include <algorithm>

using namespace std;

int main(){
	while(true){
		int a,b,c,d;
		int ret;
		cin>>c>>d>>a>>b;
		if(a==0)
			return 0;
		a*=100;
		b*=100;
		ret = max( min(a/c,b/d) , min(a/d,b/c) );
		if(ret>100)
			ret = 100;
		cout<<ret<<"%"<<endl;
	}
}