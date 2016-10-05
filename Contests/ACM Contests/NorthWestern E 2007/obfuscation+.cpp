#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <fstream>

#define VS			vector<string>
#define VVS			vector<VS>

#define VI			vector<long long>
#define VVI			vector<VI>

#define REP(i,a,b)	for(i=(int)a ; i<=(int)b ; i++)
#define FOR(i,N)	REP(i,0,N-1)

#define All(v)		v.begin(),v.end()

using namespace std;

string STR;
int N;
VS V;
VS v;
VI dp;
VVI Adj;
VVI ADJ;

bool Valid(int i,int pos){
	if(v[i].size() < 3) return true;
	if(v[i].size() == 3) return v[i][1] == STR[pos+1];
	string str1 = v[i].substr(1,v[i].size()-2);
	string str2 = STR.substr(pos+1,v[i].size()-2);
	sort(All(str2));
	return str1 == str2;
}

void pre(){
	int i,j,k;
	int pos;
	VI GD(STR.size());
	Adj.clear(); Adj.resize(STR.size());
	ADJ.clear(); ADJ.resize(STR.size());
	GD[0] = 1;
	FOR(pos,GD.size()){
		if(!GD[pos]) continue;

		FOR(i,v.size()){
			if(STR.size()-pos < v[i].size()) continue;
			if(v[i][0]!=STR[pos] || v[i][v[i].size()-1]!=STR[pos+v[i].size()-1] || !Valid(i,pos)) continue;

			Adj[pos].push_back(pos+v[i].size());
			ADJ[pos].push_back(i);
			if(pos+v[i].size() < GD.size()) GD[pos+v[i].size()] = 1;
		}
	}
}

VI st;
string sol;

long long Rec(int pos=0){
	int i,j,k;
	long long ret=0;
	long long buf;

	if(pos == STR.size()){
		sol = "";
		FOR(i, st.size()-1)
			sol += V[st[i]] + " ";
		sol += V[st[i]];
		return 1;
	}
	if(dp[pos] != -1) return dp[pos];		// dynamic

	FOR(i,Adj[pos].size()){
		st.push_back(ADJ[pos][i]);
		ret += Rec(Adj[pos][i]);
		st.pop_back();
	}

	dp[pos]=ret;
	return ret;
}

int main(){
	ifstream cin("input.txt");
	int T;
	cin >> T;
	while(T--){
		int i,j,k;
		cin >> STR >> N;
		V.clear(); V.resize(N);
		FOR(i,N) cin >> V[i];
		v = V;
		FOR(i,N) if(v[i].length()>3) sort(v[i].begin()+1 , v[i].end()-1);

		pre();

		dp.clear(); dp.resize(STR.size(),-1);

		long long ans = Rec();
		if(ans == 0)
			cout << "impossible" << endl;
		else if(ans > 1)
			cout << "ambiguous" << endl;
		else
			cout << sol << endl;
	}
}