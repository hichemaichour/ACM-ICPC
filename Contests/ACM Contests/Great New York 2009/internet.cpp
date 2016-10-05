#include <iostream>
#include <set>
#include <fstream>
using namespace std;

int main()
{
	//ifstream cin("in.txt");
	int n;
	while(cin >> n)
	{
		multiset<long long> st;
		multiset<long long>::iterator it;

		for(int i = 0; i < n; i++)
		{
			long long x;
			cin >> x;
			st.insert(x);
			it = st.find(x);
			it++;
			if (it != st.end())
				st.erase(it);
		}
		cout << st.size() << endl;
	}
	return 0;
}