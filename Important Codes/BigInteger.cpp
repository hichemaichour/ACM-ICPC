#include <iostream>
#include <fstream>
#include <sstream>

#include <iomanip>

#include <algorithm>

#include <vector>
#include <deque>
#include <list>
#include <stack>
#include <queue>
#include <set>
#include <map>
#include <bitset>
#include <string>

#include <iterator>
#include <functional>
#include <complex>
#include <numeric>
#include <valarray>

#include <cmath>

using namespace std;

#define REP(i, a, b) 		for (i=(int)a ; i<=(int)b ; i++)
#define REPD(i, a, b)		for (i=(int)a ; i>=(int)b ; i--)
#define REPI(i, v)		for (i=v.begin() ; i!=v.end() ; i++)
#define FOR(i, n)		REP (i, 0, n-1)
#define FORD(i, n)		REPD(i, n-1, 0)

#define All(v)			v.begin(),v.end()
#define Resize(v,N)		v.clear(); v.resize(N);

#define IsIn(v,e)		(find(All(v),e) != v.end())
#define Remove(v,e)		v.resize( remove(All(v),e) - v.begin() )

#define VI			vector<int>
#define VVI			vector<VI>

#define x			first
#define y			second
#define II			pair<int,int>
#define VII			vector<II>
#define VVII			vector<VII>

#define BI			VI // -1234 => {4 , 3 , 2 , 1 , -1}

// ********************************
// Declerations
// ********************************

BI Equal(BI& b,int v);
int Equal(int& v,BI& b);
BI Add(BI& b1,BI& b2);
BI Sub(BI& b1,BI& b2);

bool operator<(BI b1,BI b2);
bool operator==(BI& b1,BI& b2);
bool operator>(BI& b1,BI& b2);
bool operator!=(BI& b1,BI& b2);
bool operator<=(BI& b1,BI& b2);
bool operator>=(BI& b1,BI& b2);

BI operator+(BI b1,BI b2);
BI operator-(BI b1,BI b2);
BI operator*(BI b1,BI b2);

void operator+=(BI& b1,BI b2);
void operator-=(BI& b1,BI b2);
void operator*=(BI& b1,BI b2);

// ********************************
// Functions
// ********************************

BI Equal(int v){
	BI b;
	int buf = abs(v);
	while(buf){
		b.push_back(buf%10);
		buf /= 10;
	}
	if(v<0)
		b.push_back(-1);
	if(v == 0)
		b.push_back(0);
	return b;
}
int Equal(BI& b){
	int v = 0;
	int i;
	FORD(i,b.size()){
		v = v*10 + b[i];
	}
	return v;
}
BI Add(BI& b1,BI& b2){
	int i,j,k;
	int n = max(b1.size(),b2.size());
	int rem = 0;
	BI ret(n);
	FOR(i,n){
		j=0; k=0;
		if(i<b1.size()) j=b1[i];
		if(i<b2.size()) k=b2[i];
		ret[i] = (j+k+rem)%10;
		rem = (j+k+rem)/10;
	}
	while(rem){
		ret.push_back(rem%10);
		rem /= 10;
	}
	return ret;
}
BI Sub(BI& b1,BI& b2){
	int i,j,k;
	int n = b1.size();
	BI ret(n);
	FOR(i,n){
		j=0; k=0;
		if(i<b1.size()) j=b1[i];
		if(i<b2.size()) k=b2[i];
		if(j<k){
			j += 10;
			b1[i+1]--;
		}
		ret[i] = j-k;
	}
	while(ret.back()==0 && ret.size()>1)
		ret.pop_back();
	return ret;
}

// ********************************
// Logic Operators
// ********************************

bool operator<(BI b1,BI b2){
	int i;
	bool neg = false;
	if(b1.back()==-1 ^ b2.back()==-1)
		return b1.back()==-1;
	if(b1.back()==-1 && b2.back()==-1){
		b1.pop_back(); b2.pop_back();
		neg = true;
	}
	if(b1.size()!=b2.size())
		return (b1.size()<b2.size()) ^ neg;
	FORD(i,b1.size())
		if(b1[i]!=b2[i])
			return (b1[i]<b2[i]) ^ neg;
	return false;
}
bool operator==(BI& b1,BI& b2){
	int i;
	if(b1.size() != b2.size())
		return false;
	FOR(i,b1.size())
		if(b1[i] != b2[i])
			return false;
	return true;
}
bool operator>(BI& b1,BI& b2){
	return !(b1<b2) && !(b1==b2);
}
bool operator!=(BI& b1,BI& b2){
	return !(b1==b2);
}
bool operator<=(BI& b1,BI& b2){
	return (b1<b2) || (b1==b2);
}
bool operator>=(BI& b1,BI& b2){
	return !(b1<b2);
}

// ********************************
// Arithmatic Operations
// ********************************

BI operator+(BI b1,BI b2){
	BI ret;
	if(b1.back()!=-1 && b2.back()!=-1)
		ret = Add(b1,b2);
	else if(b1.back()==-1 && b2.back()==-1){
		b1.pop_back(); b2.pop_back();
		ret = Add(b1,b2);
		ret.push_back(-1);
	}
	else if(b1.back()!=-1 && b2.back()==-1){
		b2.pop_back();
		if(b1<b2){
			ret = Sub(b2,b1);
			ret.push_back(-1);
		}
		else
			ret = Sub(b1,b2);
	}
	else{
		b1.pop_back();
		if(b2<b1){
			ret = Sub(b1,b2);
			ret.push_back(-1);
		}
		else
			ret = Sub(b2,b1);
	}
	return ret;
}
BI operator-(BI b1,BI b2){
	if(b2.back()==-1)
		b2.pop_back();
	else
		b2.push_back(-1);
	return b1+b2;
}
BI operator*(BI b1,BI b2){
	bool neg = b1.back()==-1 ^ b2.back()==-1;
	if(b1.back()==-1) b1.pop_back();
	if(b2.back()==-1) b2.pop_back();
	BI ret(b1.size()+b2.size());
	int pos,i,j;
	int rem = 0;
	FOR(pos,ret.size()){
		int sum = rem;
		for(i=0,j=pos ; i<=pos ; i++,j--){
			if(i>=b1.size() || j>= b2.size())
				continue;
			sum += b1[i]*b2[j];
		}
		ret[pos] = sum%10;
		rem = sum/10;
	}

	while(ret.back()==0 && ret.size()!=1)
		ret.pop_back();

	if(neg && !(ret.size()==1 && ret[0]==0))
		ret.push_back(-1);
	return ret;
}

// ********************************
// Arithmatic Assignment
// ********************************

void operator+=(BI& b1,BI b2){
	b1 = b1+b2;
}
void operator-=(BI& b1,BI b2){
	b1 = b1-b2;
}
void operator*=(BI& b1,BI b2){
	b1 = b1*b2;
}

// ********************************
// iostream
// ********************************

istream& operator>>(istream& in,BI& b){
	int i;
	in >> i;
	b = Equal(i);
	return in;
}

ostream& operator<<(ostream& out,BI b){
	if(b.back()==-1){
		out <<"-";
		b.pop_back();
	}
	int i;
	FORD(i,b.size())
		out << b[i];
	return out;
}

int main(){
	BI i,j;
	while(cin >> i >> j){
		cout << i*j << endl;
	}
}