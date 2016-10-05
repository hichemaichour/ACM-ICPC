#include <iostream>
#include <set>
using namespace std;

int main()
{
	char c;
	int n,a,b,yes,no;
	set<int> map[10001];
	while(cin>>n)
	{
		yes=no=0;
		for(int i=1;i<=n;i++)
			map[i].clear();
		while(1)
		{
		cin>>c;
		if(c=='c')
		{
			cin>>a>>b;
			map[a].insert(b);
			map[b].insert(a);
			set<int>::iterator i,j;
			for(i=map[a].begin();i!=map[a].end();i++)
			{
				map[b].insert(*i);
				map[*i].insert(b);
				for(j=map[b].begin();j!=map[b].end();j++)
				{
					map[a].insert(*j);
					map[*j].insert(a);
					map[*j].insert(*i);
					map[*i].insert(*j);
				}
			}
		}
		else if(c=='d')
		{
			cin>>a;
			map[a].clear();
		}
		else if(c=='q')
		{
			cin>>a>>b;
			if(map[a].find(b)!=map[a].end())
				yes++;
			else
				no++;
		}
		else if(c=='e')
			break;
		}
		cout<<yes<<" , "<<no<<endl;
	}
	return 0;
}