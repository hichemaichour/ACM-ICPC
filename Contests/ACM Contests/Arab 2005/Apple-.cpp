#include <iostream>
#include <fstream>
#include <string>
#include <vector>

// h H g G -

using namespace std;

struct tree{
	string str;
	tree* r;
	tree* l;
};

vector<string> v1;
vector<string> v2;
string str1,str2;
tree fst,scd;

void v(){
	while(str1!=""){
		v1.push_back(str1.substr(0,str1.find(' ')));
		str1=str1.substr(str1.find(' ')+1,str1.size());
	}
	while(str2!=""){
		v2.push_back(str2.substr(0,str2.find(' ')));
		str2=str2.substr(str2.find(' ')+1,str2.size());
	}
}

void init1(tree* t){
	if(t->str=="nil"){
		t->l=NULL;
		t->r=NULL;
	}
	else{
		t->r=new tree;
		t->r->str=v1[v1.size()-1];
		v1.pop_back();
		init1(t->r);
		t->l=new tree;
		t->l->str=v1[v1.size()-1];
		v1.pop_back();
		init1(t->l);
	}
}

void init2(tree* t){
	if(t->str=="nil"){
		t->l=NULL;
		t->r=NULL;
	}
	else{
		t->r=new tree;
		t->r->str=v2[v2.size()-1];
		v2.pop_back();
		init2(t->r);
		t->l=new tree;
		t->l->str=v2[v2.size()-1];
		v2.pop_back();
		init2(t->l);
	}
}

bool check(tree t1,tree t2){
	if(t1.str!=t2.str)
		return false;
	if(t1.str=="nil")
		return true;
	return ( (check(*t1.l,*t2.l) && check(*t1.r,*t2.r)) || (check(*t1.l,*t2.r) && check(*t1.r,*t2.l)) );
}

void del(tree t){
	if(t.r!=NULL){
		del(*t.r);
		delete t.r;
	}
	if(t.l!=NULL){
		del(*t.l);
		delete t.l;
	}
}

int main(){
	ifstream cin("Apple.h");
	int M;
	string buf;
	cin>>M;
	getline(cin,buf);	
	for(int cnt=1;cnt<=M;cnt++){
		getline(cin,str1);
		getline(cin,str2);

		str1=str1.substr(0,str1.find("end"));
		str2=str2.substr(0,str2.find("end"));

		v();

		fst.str=v1[v1.size()-1];
		fst.l=NULL;
		fst.r=NULL;
		v1.pop_back();
		init1(&fst);
		scd.str=v2[v2.size()-1];
		scd.l=NULL;
		scd.r=NULL;
		v2.pop_back();
		init2(&scd);

		if(check(fst,scd))
			cout<<"true"<<endl;
		else
			cout<<"false"<<endl;

		del(fst);
		del(scd);
	}
	return 0;
}