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
#define REPI(i, v)			for (i=v.begin() ; i!=v.end() ; i++)
#define FOR(i, n)			REP (i, 0, n-1)
#define FORD(i, n)			REPD(i, n-1, 0)

#define All(v)				v.begin(),v.end()
#define Resize(v,N)			v.clear(); v.resize(N);

#define IsIn(v,e)			(find(All(v),e) != v.end())
#define Remove(v,e)			v.resize( remove(All(v),e) - v.begin() )

#define VI					vector<int>
#define VVI					vector<VI>

#define x					first
#define y					second
#define II					pair<int,int>
#define VII					vector<II>
#define VVII				vector<VII>

char OP[] = {'&','^','|'};
vector<char> v;
map<char,bool> m;
string Exp1,Exp2;

void Modify(string& str){
	int i;
	string ret="";
	FOR(i,str.size()){
		char c = str[i];

		if(c=='~' && ret!="" && ret[ret.size()-1]=='~')
			ret.resize(ret.size()-1);
		else if((isalpha(c) && islower(c)) || c=='~' || c=='&' || c=='|' || c=='^' || c=='(' || c==')')
			ret.push_back(c);

		if(isalpha(c) && islower(c))
			v.push_back(c);
	}
	str = ret;
	sort(All(v));
	v.resize(unique(All(v)) - v.begin());
}

void Modify_Exp(string& str,bool b=true){
	vector<string> v_exp;
	deque<char> op;

	int i,j,k;

	string buf = "";
	FOR(i,str.size()){
		if(isalpha(str[i])){
			buf.push_back(str[i]);
			v_exp.push_back(buf);
			buf = "";
			continue;
		}

		if(str[i]=='~'){
			buf.push_back(str[i]);
			continue;
		}

		if(str[i] != '('){
			op.push_back(str[i]);
			continue;
		}

		k = 0;
		string mod;
		REP(j,i,str.size()-1){
			if(str[j] == '(')
				k++;
			else if(str[j] == ')')
				k--;
			mod.push_back(str[j]);
			if(!k)
				break;
		}
		mod = mod.substr(1,mod.size()-2);
		if(b)
			Modify_Exp(mod);
		buf += "(" + mod + ")";
		i = j;
		v_exp.push_back(buf);
		buf = "";
	}

	
	FOR(k,3){
		FOR(i,v_exp.size()-1){
			if(OP[k] == op.front()){
				v_exp[i+1] = "(" + v_exp[i] + OP[k] + v_exp[i+1] + ")";
				v_exp[i] = "";
				op.pop_front();
			}
			else{
				op.push_back(op.front());
				op.pop_front();
			}
		}
		v_exp.resize(remove(All(v_exp),"") - v_exp.begin());
	}
	str = v_exp.front();
}

void Find_Exp(string str){
	int pos;
	FOR(pos,str.size()-1)
		if((isalpha(str[pos]) || str[pos]==')') && (isalpha(str[pos+1]) || str[pos+1]=='~' || str[pos+1]=='('))
			break;
	pos++;
	Exp1 = str.substr(0,pos);
	Exp2 = str.substr(pos);

	Modify_Exp(Exp1);
	Modify_Exp(Exp2);
}

bool func(bool b1,char op, bool b2){
	if(op == '|')
		return b1 || b2;
	else if(op == '&')
		return b1 && b2;
	else
		return b1 ^ b2;
}

bool Exp(string str){
	int i;
	bool b,b1,b2;
	str = "(" + str + ")";
	stack<bool> s;
	stack<char> op;
	FOR(i,str.size()){
		if(isalpha(str[i]) || str[i]==')'){
			if(str[i] == ')'){
				op.pop();
				b2 = s.top(); s.pop();
			}
			else
				b2 = m[str[i]];

			if(!op.empty() && op.top()=='~'){
				b2 = !b2;
				op.pop();
			}
			if(s.empty() || op.top()=='(')
				s.push(b2);
			else{
				b1 = s.top(); s.pop();
				b = func(b1,op.top(),b2); op.pop();
				s.push(b);
			}
		}
		else
			op.push(str[i]);
	}
	return s.top();
}

bool check(){
	bool b1 = Exp(Exp1);
	bool b2 = Exp(Exp2);
	if(b1 != b2)
		b1 = b1;
	return b1 == b2;
}

bool Rec(int pos=0){
	if(pos == v.size())
		return check();

	bool ret;
	m[v[pos]] = true;
	ret = Rec(pos+1);
	if(ret == false)
		return false;

	m[v[pos]] = false;
	return Rec(pos+1);
}

int main(){
	ifstream cin("Logical.txt");
	int T;
	cin >> T;
	cin.ignore(100,'\n');
	for(int cnt=1 ; cnt<=T ; cnt++){
		m.clear();
		v.clear();

		string str;
		getline(cin,str);
		Modify(str);
		Find_Exp(str);

		if(cnt == 8)
			cnt=8;

		bool out;
		out = Rec();
		cout <<"Data set "<<cnt<<": ";
		if(out)
			cout <<"Equivalent"<<endl;
		else
			cout <<"Different"<<endl;
	}
}