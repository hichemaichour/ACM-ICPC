#include <iostream>
#include <stack>
#include <string>
using namespace std;

int main()
{
	string input;
	int cnt = 1;
	int ans;
	while(true)
	{
		cin >> input;
		if(input[0] == '-')
		{
			break;
		}
		stack<char> s;
		ans = 0;
		for(int i = 0; i < input.size(); i++)
		{
			if(input[i] == '{')
			{
				s.push(input[i]);
			}
			else if (input[i] == '}')
			{
				if(!s.empty())
				{
					if(s.top() == '{')
					{
						s.pop();
					}
					else
					{
						ans++;
					}
				}
				else
				{
					s.push('{');
					ans++;
				}
			}
		}
		
		
		if(s.size()%2 == 0)
		{
			ans += s.size()/2;
		}
		else 
		{
			ans -= (s.size()/2)-1;
		}
		cout << cnt++ << ". " << ans << endl;
	}
	return 0;
}

