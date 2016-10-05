#include <iostream>
#include <string>
#include <fstream>
#include <regex>
using namespace std;

string str;

void simplify()
{
	int i;
	for(i=0 ; i<str.size()-1 ; i++)
	{
		if(str[i]=='*' && str[i+1]=='*')
			str.replace(i--,2,"*");
		else if(str[i]=='#' && str[i+1]=='#')
			str.replace(i--,2,"*");
		else if(str[i]=='*' && str[i+1]=='#')
			str.replace(i--,2,"#");
		else if(str[i]=='#' && str[i+1]=='*')
			str.replace(i--,2,"#");
	}
	
	for(i=0 ; i<str.size() ; i++){
		if(str[i]=='#')
			str.replace(i,1,"[0-9]([0-9][0-9])$");
		if(str[i]=='*')
			str.replace(i,1,"([0-9][0-9])$");
	}

	for(i=0 ; i<str.size() ; i++)
		if(str[i]=='$')
			str.replace(i,1,"*");
}

bool match(string& s){
	const std::tr1::regex pattern(str.c_str());
	return std::tr1::regex_match(s, pattern);
}

int main() {
	ifstream cin("match.h");
	int cnt1 = 0;
	
	while (true)
	{
		cin >> str;
		if (str[0] == 'Q')
			return 0;
		if (str[0] == 'E')
			continue;
		int cnt2 = 0;

		simplify();

		cnt1++;
		while (true)
		{
			string s;
			cin >> s;
			if (s[0] == 'E')
				break;
			if (s[0] == 'Q')
				return 0;

			cout << cnt1 << "." << ++cnt2 << ". ";
			if(match(s))
				cout<<"match"<<endl;
			else
				cout<<"not"<<endl;
		}
	}
	return 0;
}