#include <iostream>
#include <string>
#include <queue>
#include <map>

using namespace std;

string state;

bool good(string s)
{
	int f = s.find("B");
	int l = s.rfind("B");
	for(int i = f; i <= l; i++)
	{
		if(s[i] == 'W')
		{
			return false;
		}
	}
	return true;
}

string trans(string s, int i)
{
	if(i == 1) //move forward
	{
		if(s[s.size()-1] != 'F')
		{
			swap(s[s.find("F")],s[s.find("F")+1]);
		}
	}
	else if(i == 2) //move backward
	{
		if(s[0] != 'F')
		{
			swap(s[s.find("F")],s[s.find("F")-1]);
		}
	}
	else if(i == 3) //hop forward
	{
		int k = s.find("F");
		if(s[s.size()-2] != 'F' && s[s.size()-1] != 'F')
		{
			swap(s[k],s[k+2]);
			//swap(s[k],s[k+1]);
			if(s[k] == 'B'){s[k] = 'W';}
			else if(s[k] == 'W'){s[k] = 'B';}
		}
	}
	else if(i == 4) //hop backward
	{
		int k = s.find("F");
		if(s[1] != 'F' && s[0] != 'F')
		{
			swap(s[k],s[k-2]);
			//swap(s[k],s[k-1]);
			if(s[k] == 'B'){s[k] = 'W';}
			else if(s[k] == 'W'){s[k] = 'B';}
		}
	}
	return s;
}

int BFS()
{
	if(good(state))
	{
		return 0;
	}
	queue<string> Q;
	queue<int> D;
	int d;
	string buf;

	map<string,bool> m;
	m[state] = true;
	Q.push(state);
	D.push(0);
	while(!Q.empty())
	{
		state = Q.front(); Q.pop();
		d = D.front(); D.pop();

		for(int i = 1; i <= 4; i++)
		{
			buf = trans(state,i);
			if(good(buf))
			{
				return d + 1;
			}
			if(m[buf])
			{
				continue;
			}
			m[buf] = true;
			Q.push(buf);
			D.push(d+1);
			if (d+1 >= 10)
			{
				return -1;
			}
		}
	}
	return -1;
}

int main()
{
	string input;
	int cnt = 1;
	while(true)
	{
		cin >> input;
		if(input[0] == '-')
		{
			break;
		}
		state = input;
		cout << cnt++ << ". " << BFS() << endl;
	}
	return 0;
}