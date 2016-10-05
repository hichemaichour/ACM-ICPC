#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include <iomanip>

using namespace std;

int score(int i){
	switch(i){
		case 0:
			return 10;
		case 1:
			return 8;
		default:
			return 8-i;
	}
}

string re(string str){
	while(str[0]==' ')
		str=str.substr(1,str.size());
	while(str[str.size()-1]==' ')
		str.resize(str.size()-1);
	return str;
}

bool sort_players(pair<pair<int,vector<int> >,string> p1, pair<pair<int,vector<int> >,string> p2){
	if(p1.first.first > p2.first.first)
		return true;
	if(p1.first.first < p2.first.first)
		return false;

	if(p1.first.second > p2.first.second)
		return true;
	if(p1.first.second < p2.first.second)
		return false;

	string f1,f2,l1,l2;
	f1=p1.second.substr(0,p1.second.find(" "));
	f2=p2.second.substr(0,p2.second.find(" "));
	l1=p1.second.substr(p1.second.find(" "),p1.second.size());
	l2=p2.second.substr(p2.second.find(" "),p2.second.size());
	
	if(l1<l2)
		return true;
	if(l1>l2)
		return false;
	return f1<f2;
}

bool sort_teams(pair<int,string> t1, pair<int,string> t2){
	if(t1.first>t2.first)
		return true;
	if(t1.first<t2.first)
		return false;

	return (t1.second<t2.second);
}

int main(){
	//ifstream cin("races.h");
	for(int cnt=1;true;cnt++){
		int N;
		cin>>N;
		if(N==0)
			break;

		vector< pair<pair<int,vector<int> >,string> > players;
		vector< pair<int,string> > teams;

		map<string,vector<int> > P;
		map<string,int> T;

		for(int i=0;i<N;i++){
			string buf;
			getline(cin,buf);//remove the blank line
			getline(cin,buf);//remove the name of the contest
			getline(cin,buf);//remove the heading

			string player,team;
			for(int j=0;j<8;j++){
				cin>>buf;//remove the ranking
				cin>>player>>buf;//get the player name
				player+=" "+buf;

				getline(cin,team);
				team=re(team);
				team.resize(team.size()-1);

				if(P[player].size()==0)
					P[player].resize(8);
				P[player][j]++;
				T[team]+=score(j);
			}

			cin>>buf;//remove "---"
		}

		map<string,vector<int> >::iterator iterP;
		for(iterP=P.begin();iterP!=P.end();iterP++){
			pair<pair<int,vector<int> >,string> p;
			p.second=iterP->first;
			p.first.second=iterP->second;
			for(int j=0;j<8;j++){
				p.first.first+=p.first.second[j]*score(j);
			}
			players.push_back(p);
		}

		map<string,int>::iterator iterT;
		for(iterT=T.begin();iterT!=T.end();iterT++){
			pair<int,string> t;
			t.second=iterT->first;
			t.first=iterT->second;
			teams.push_back(t);
		}

		sort(players.begin(),players.end(),sort_players);
		sort(teams.begin(),teams.end(),sort_teams);

		cout<<"Season "<<cnt<<":"<<endl;
		cout<<"Drivers Standing:"<<endl;
		for(int I=0;I<players.size();I++){
			cout<<setiosflags(ios::left)<<setw(25)<<players[I].second;
			cout<<" "<<players[I].first.first<<endl;
		}
		cout<<endl;
		cout<<"Teams Standing:"<<endl;
		for(int J=0;J<teams.size();J++){
			cout<<setiosflags(ios::left)<<setw(25)<<teams[J].second;
			cout<<" "<<teams[J].first<<endl;
		}
		cout<<endl;
	}
	return 0;
}