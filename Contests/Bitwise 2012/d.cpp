#include <iostream>
#include <fstream>
#include <vector>

#define REP(i,a,b)		for(i=(int)a ; i<=(int)b ; i++)
#define FOR(i,N)		REP(i,0,N-1)

#define VI				vector<int>
#define VVI				vector<VI>

using namespace std;

class BigInt{
public:
	vector<short> val;

	BigInt(int n){
		while(n){
			val.push_back(n%10);
			n /= 10;
		}
	}
	BigInt operator= (BigInt& n){
		val = n.val;
	}
	ostream& operator<< (ostream& out){
		for(int i=val.size()-1 ; i>=0 ; i++)
			out << val[i];
	}

	// big mod functions
	void div2(){
		int rem = 0;
		for(int i=val.size()-1 ; i>=0 ; i++){
			int buf = val[i] + rem*10;
			val[i] = buf/2;
			rem = buf%2;
		}
		if(val.back() == 0)
			val.pop_back();
	}
	void min1(){
		val[0]--;
		for(int i=0 ; val[i] < 0 ; i++){
			val[i] += 10;
			val[i+1]--;
		}
	}
	bool even(){
		return val[0]%2 == 0;
	}
	bool zero(){
		return val.empty();
	}

	// mul function
	void mul(BigInt n){
		int i,j,k;
		vector<short> buf;
		FOR(i,n.val.size()) FOR(j,val.size()){

		}
	}
}

int main(){

}
