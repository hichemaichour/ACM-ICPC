#include <iostream>
#include <string>
#include <cctype>
#include <algorithm>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <set>
#include <bitset>
#include <cmath>
#include <deque>
#include <cstring>
#include <list>
#include <functional>
#include <queue>
#include <climits>

#define FOR(i,N)		for(i=0 ; i<(long long)N ; i++)
#define REP(i,a,b)		for(i=(long long)a ; i<=(long long)b ; i++)
#define REPD(i,a,b)		for(i=(long long)a ; i>=(long long)b ; i--)
#define FORD(i,N)		REPD(i,N-1,0)

#define II				pair<long long,long long>

#define VI				deque<long long>
#define VVI				vector<VI>

#define VII				vector<II>
#define VVII			vector<VII>

#define VS				deque<string>
#define VVS				vector<VS>

#define VD				deque<double>
#define VVD				deque<VD>

#define All(v)			v.begin(),v.end()

#define DD				pair<double,double>
#define VDD				vector<DD>

#define VC				deque<char>
#define VVC				deque<VC>

using namespace std;

bool check(string s1, string s2, string s3){
	string s1n = s1.substr(0,s1.size()-1); string s2n = s2.substr(0,s2.size()-1); string s3n = s3.substr(0,s3.size()-1);
	string s1t = s1.substr(s1.size()-1); string s2t = s2.substr(s2.size()-1); string s3t = s3.substr(s3.size()-1);

	if(s3t=="+" && s1t=="-" && s2t=="-") return false;

	if(s3n == "O") return (s1n!="AB" && s2n!="AB");
	if(s3n == "A") return ((s1n=="A") || (s1n=="AB") || (s2n=="A") || (s2n=="AB"));
	if(s3n == "B") return ((s1n=="B") || (s1n=="AB") || (s2n=="B") || (s2n=="AB"));
	if(s3n == "AB") return (s1n!="O" && s2n!="O" && ((s1n=="A" && s2n!="A") || (s1n=="B" && s2n!="B") || (s1n=="AB")));
}

string pos[] = {"A+","A-" , "B+","B-" , "AB+","AB-", "O+","O-"};

int main(){
	ifstream cin("input.txt");
	string s1,s2,s3;
	int cnt = 1;
	while(cin >> s1 >> s2 >> s3){
		if(s1=="E") break;
		VS ans;
		int i;
		if(s1 == "?") FOR(i,8) if(check(pos[i],s2,s3)) ans.push_back(pos[i]);
		if(s2 == "?") FOR(i,8) if(check(s1,pos[i],s3)) ans.push_back(pos[i]);
		if(s3 == "?") FOR(i,8) if(check(s1,s2,pos[i])) ans.push_back(pos[i]);

		cout <<"Case "<<cnt++<<":";
		if(s1=="?"){
			if(ans.empty()) cout <<" IMPOSSIBLE";
			else if(ans.size()==1) cout <<" "<<ans[0];
			else {
				cout <<" {";
				FOR(i,ans.size()){
					if(i) cout <<", ";
					cout << ans[i];
				}
				cout <<"}";
			}
		}
		else cout <<" "<<s1;

		if(s2=="?"){
			if(ans.empty()) cout <<" IMPOSSIBLE";
			else if(ans.size()==1) cout <<" "<<ans[0];
			else {
				cout <<" {";
				FOR(i,ans.size()){
					if(i) cout <<", ";
					cout << ans[i];
				}
				cout <<"}";
			}
		}
		else cout <<" "<<s2;

		if(s3=="?"){
			if(ans.empty()) cout <<" IMPOSSIBLE";
			else if(ans.size()==1) cout <<" "<<ans[0];
			else {
				cout <<" {";
				FOR(i,ans.size()){
					if(i) cout <<", ";
					cout << ans[i];
				}
				cout <<"}";
			}
		}
		else cout <<" "<<s3;
		cout << endl;
	}
	return 0;
}
