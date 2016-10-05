#include <iostream>
#include <fstream>
#include <set>
#include <vector>

using namespace std;

int main(){
	ifstream  cin("LIS.h");
	vector<int> v(10);
	for(int i=0;i<v.size();i++)
		cin>>v[i];

	set<int> st;
	set<int>::iterator it;
	for(int i=0;i<v.size();i++){
		st.insert(v[i]);
		it=st.find(v[i]);
		it++;
		if(it!=st.end())
			st.erase(it);
	}
	cout<<st.size()<<endl;
}