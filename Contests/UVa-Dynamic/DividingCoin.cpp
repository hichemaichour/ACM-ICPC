#include <iostream>
#include <vector>

using namespace std;

int sum;
vector<int> v;
vector<int> re;

int init(){
	re.clear();
	re.resize(sum+1);
	re[0] = 1;
	for(int i=0;i<v.size();i++)
		for(int j=sum; j>=v[i] ; j--)
			re[j] += re[j-v[i]];

	for(int k=sum/2 ; k>=0 ; k--)
		if(re[k] != 0)
			return k;
}

int main(){
	int N;
	cin>>N;
	while(N--){
		int M;
		cin>>M;
		v.clear();
		v.resize(M);
		sum=0;
		for(int i=0;i<M;i++){
			cin>>v[i];
			sum+=v[i];
		}
		int j=init();
		cout<<(sum-j)-j<<endl;
	}
}