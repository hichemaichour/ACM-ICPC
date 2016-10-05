#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <stack>
#include <deque>
#include <set>
#include <algorithm>

using namespace std;
	
deque<string> v;

string e(string str){
	if(str.find(' ')==string::npos)
		return str;
	return str.substr(0,str.find(' '));
}

bool not_gd(string str){
	if(str.find(' ')==string::npos)
		return false;
	str=str.substr(str.find(' ')+1,str.size());
	str=str+" ";

	set<string> attributes;
	string attribute;
	while(str.find(' ')!=string::npos){
		attribute=str.substr(0,str.find(' '));
		str=str.substr(str.find(' ')+1,str.size());
		if(attribute.find('=')==string::npos)
			return false;
		attribute=attribute.substr(0,attribute.find('='));
		if(attributes.find(attribute)!=attributes.end())
			return false;
		attributes.insert(attribute);
	}

	return true;
}

bool check(){
	deque<string> elements;

	if(v[0][0] == '/' || v[0][v[0].size()-1]== '/')
		return false;
	if(not_gd(v[0]))
		return false;

	elements.push_front(v[0]);
	v.pop_front();
	while(!elements.empty() && v.size()>0){
		string element;
		if(v[0][v[0].size()-1] == '/'){ // empty element
			v[0].resize(v.size()-1);

			if(not_gd(v[0]))
				return false;

			v.pop_front();
		}

		else if(v[0][0] == '/'){ // end-tag element
			v[0]=v[0].substr(1,v[0].size());

			if(not_gd(v[0]))
				return false;

			element=e(v[0]);
			if(element!=elements[0])
				return false;

			v.pop_front();
			elements.pop_front();
		}

		else{ // start-tag element
			if(not_gd(v[0]))
				return false;

			element=e(v[0]);
			if(find(elements.begin(),elements.end(),element) != elements.end())
				return false;
			elements.push_front(element);
			v.pop_front();
		}
	}

	if(v.size()!=0 || !elements.empty())
		return false;

	return true;
}

int main(){
	//ifstream cin("Well-Formed.h");
	bool flag=true;
	string str;
	getline(cin,str,'<');
	getline(cin,str,'>');
	if(str=="?end?")
		return 0;

	while(flag){
		v.clear();
		str="";
		while(str.substr(0,1)!="?"){
			getline(cin,str,'<');
			getline(cin,str,'>');
			v.push_back(str);
		}
		v.pop_back();
		if(str=="?end?")
			flag=false;

		if(check())
			cout<<"well-formed"<<endl;
		else
			cout<<"non well-formed"<<endl;
	}
	return 0;
}