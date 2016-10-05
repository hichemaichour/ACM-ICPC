#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <map>
#include <fstream>
using namespace std;

// * means even
// # means odd
#define Pair pair<int, int>
vector<int> sign;
vector<string> num;
vector<vector<int> > pos;
vector<int> SZ;
map<pair<int, int>, bool> visited;
map<string,int> m;
int Size;


void kmpsetup(string pat,vector<int>& f){
	int i,k,len = pat.size();
	f[0] = -1;
	for(i = 1; i < len; i++){
		k = f[i-1];
		while (k>=0)
		{
			if(pat[k]==pat[i-1])
				break;
			else k=f[k];
		}
		f[i] = k + 1;
	}
}

int kmpscan(string pat,string text, vector<int> f, int st){
	int i=st,k,ret=-1,len=pat.size();
	for(k=0; text[i];)
	{
		if(k==-1)
		{
			i++;
			k = 0;
		}
		else if(text[i]==pat[k]){
			i++;
			k++;
			if(k>=len)
			{
				ret = i-len;
				break;
			}
		}
		else 
			k=f[k];
	}
	return ret;
}

void simplify(string& str)
{
	for(int i=0;i<str.size()-1;i++)
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
}

void extractSign(const string& s)
{
	int i;
	string str = "";
	sign.push_back(-1);
	for (i = 0; i < s.size(); i++)
	{
		if (!isdigit(s[i]))
		{
			if (!str.empty())
			{
				num.push_back(str);
				SZ.push_back(str.size());
			}
			if (i == 0)
				sign.pop_back();
			if (s[i] == '#')
				sign.push_back(1);
			else
				sign.push_back(0);
			str = "";
		}
		else
			str.push_back(s[i]);
	}

	if (!str.empty())
	{
		num.push_back(str);
		SZ.push_back(str.size());
		sign.push_back(-1);
	}
}


int preprocess(const string& s)
{
	if (num.empty())
	{
		if (s.size()%2 == sign[0])
			return -1;
		else
			return 0;
	}

	pos.clear();
	pos.resize(num.size());

	int i;
	//string::size_type Pos = 0;
	int Pos = 0;
	for (i = 0; i < num.size(); i++)
	{
		if (i == 0)
			Pos = 0;
		else
			Pos = pos[i-1][0]+SZ[i-1];

		if(m.find(num[i]) == m.end()){
			vector<int> f(num[i].size());
			kmpsetup(num[i] ,f);
			while (true)
			{
				Pos = kmpscan(num[i], s, f, Pos);
				if (Pos == -1)
					break;
				pos[i].push_back(Pos);
				Pos++;
			}
		}

		else{
			int pre = m[num[i]];
			m[num[i]] = i;
			int j = lower_bound(pos[pre].begin(),pos[pre].end(),Pos) - pos[pre].begin();
			for( ; j<pos[pre].size() ; j++)
				pos[i].push_back(pos[pre][j]);
		}

		if (pos[i].empty())
			return 0;
	}

	return 1;
}

bool rec(int x, int Pos)
{
	if (x == num.size())
	{
		// match
		if (sign[x] == -1)
		{
			if (Size == Pos)
				return true;
		}
		else if ((Size-Pos)%2 == sign[x])
			return true;

		return false;
	}
	if (visited[Pair(x, Pos)])
		return false;

	int y = lower_bound(pos[x].begin(), pos[x].end(), Pos)-pos[x].begin();
	int i;
	for (i = y; i < pos[x].size(); i++)
	{
		int diff = pos[x][i] - Pos;
		if (sign[x] == -1)
		{
			if (diff == 0)
			{
				if (rec(x+1, pos[x][i]+SZ[x]))
					return true;
				else
					visited[Pair(x+1,pos[x][i]+SZ[x])] = true;
			}

		}
		else if (diff%2 == sign[x])
		{
			if (rec(x+1, pos[x][i]+SZ[x]))
				return true;
			else
				visited[Pair(x+1,pos[x][i]+SZ[x])] = true;
		}
	}
	visited[Pair(x,Pos)] = true;
	return false;
}

int main()
{
	ifstream cin("match.h");
	int cnt1 = 0;
	while (true)
	{
		string s;
		cin >> s;
		if (s[0] == 'Q')
			break;
		int cnt2 = 0;

		simplify(s);
		num.clear();
		sign.clear();
		SZ.clear();
		extractSign(s);
		cnt1++;
		while (true)
		{
			cin >> s;
			if (s[0] == 'E')
				break;
			if (s[0] == 'Q')
				return 0;

			bool ans;
			int hi = preprocess(s);
			if (hi == 0)
				ans = false;// print not match
			else if (hi == -1)
				ans = true;
			else
			{

				visited.clear();
				Size = s.size();
				ans = rec(0, 0);
			}


			cout << cnt1 << "." << ++cnt2 << ". ";

			if (ans)
				cout << "match" << endl;
			else
				cout << "not" << endl;
		}
	}
	return 0;
}
