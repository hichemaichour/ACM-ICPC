#include <iostream>
#include <string>
#include <fstream>

#define FOR(i,N)		for(i=0 ; i<N ; i++)

using namespace std;

string str;

string Num2Str(int n,bool flg=false){
	string str = "";
	int m;
	if(n >= 1000){
		m = n/1000;
		n %= 1000;
		str = str + Num2Str(m) + "thousand";
		if(n==0 && flg)
			str += "th";
	}
	if(n >= 100){
		m = n/100;
		n %= 100;
		str = str + Num2Str(m) + "hundred";
		if(n==0 && flg)
			str += "th";
	}
	if(n >= 20){
		m = n/10;
		n %= 10;
		if(m == 2)
			str += "twenty";
		if(m == 3)
			str += "thirty";
		if(m == 4)
			str += "forty";
		if(m == 5)
			str += "fifty";
		if(m == 6)
			str += "sixty";
		if(m == 7)
			str += "seventy";
		if(m == 8)
			str += "eighty";
		if(m == 9)
			str += "ninety";
		if(n == 0 && flg)
			str += "eth";
	}
	if(n && flg){
		if(n==1)
			str += "first";
		if(n==2)
			str += "second";
		if(n==3)
			str += "third";
		if(n==4)
			str += "fourth";
		if(n==5)
			str += "fifth";
		if(n==6)
			str += "sixth";
		if(n==7)
			str += "seventh";
		if(n==8)
			str += "eighth";
		if(n==9)
			str += "ninth";
		if(n==10)
			str += "tenth";
		if(n==11)
			str += "eleventh";
		if(n==12)
			str += "twelfth";
		if(n==13)
			str += "thirteenth";
		if(n==14)
			str += "fourteenth";
		if(n==15)
			str += "fifteenth";
		if(n==16)
			str += "sixteenth";
		if(n==17)
			str += "seventeenth";
		if(n==18)
			str += "eighteenth";
		if(n==19)
			str += "nineteenth";
	}
	else if(n){
		if(n==1)
			str += "one";
		if(n==2)
			str += "two";
		if(n==3)
			str += "three";
		if(n==4)
			str += "four";
		if(n==5)
			str += "five";
		if(n==6)
			str += "six";
		if(n==7)
			str += "seven";
		if(n==8)
			str += "eight";
		if(n==9)
			str += "nine";
		if(n==10)
			str += "ten";
		if(n==11)
			str += "eleven";
		if(n==12)
			str += "twelve";
		if(n==13)
			str += "thirteen";
		if(n==14)
			str += "fourteen";
		if(n==15)
			str += "fifteen";
		if(n==16)
			str += "sixteen";
		if(n==17)
			str += "seventeen";
		if(n==18)
			str += "eighteen";
		if(n==19)
			str += "nineteen";
	}
	return str;
}


int v[1000000];

void init(){
	int i,j,k;
	int offset = 6;
	v[1] = 1;
	v[2] = 4;
	int cnt = 3;
	for(int pos=1 ; cnt <= 100010 ; pos++){
		string str = Num2Str(v[pos],true);
		FOR(i,str.size()){
			if(str[i] == 't'){
				v[cnt++] = offset + i + 1;
			}
			if(cnt > 100000)
				break;
		}
		offset += str.size();
	}
}

int main() {
	ifstream cin("input.txt");
	init();
	int N;
	while(cin >> N && N){
		cout << v[N] << endl;
	}
	return 0;
}

//int main(){
//	ifstream cin("input.txt");
//	int N;
//	while(cin >> N && N){
//		cout << Num2Str(N) << endl;
//	}
//	return 0;
//}

