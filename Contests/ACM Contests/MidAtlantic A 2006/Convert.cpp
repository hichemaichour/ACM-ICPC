#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <vector>
#include <cmath>
#include <map>

using namespace std;

vector<string> units1;
vector<string> units2;
map<string,double> order;
map<pair<string,string>,double> conv1;
map<pair<string,string>,double> conv2;
map<pair<string,string>,double> conv;
const double EPS=1e-9;

void fill_units1(string str){
	string::iterator iter;
	pair<string,string> p;
	int o=1;
	while(str!=""){
		iter=find(str.begin(),str.end(),' ');
		units1.push_back(str.substr(0,iter-str.begin()));
		order[units1[units1.size()-1]]=o++;
		p.first=units1[units1.size()-1];
		p.second=p.first;
		conv1[p]=1;
		if(iter!=str.end()){
			str=str.substr(iter-str.begin()+1,str.end()-iter-1);
		}
		else
			str="";
	}
}

void fill_units2(string str){
	pair<string,string> p;
	string::iterator iter;
	int o=1;
	while(str!=""){
		iter=find(str.begin(),str.end(),' ');
		units2.push_back(str.substr(0,iter-str.begin()));
		order[units2[units2.size()-1]]=o++;
		p.first=units2[units2.size()-1];
		p.second=p.first;
		conv2[p]=1;
		if(iter!=str.end()){
			str=str.substr(iter-str.begin()+1,str.end()-iter-1);
		}
		else
			str="";
	}
}

void floyed(){
	vector<pair<string,string> > v(3);
	for(int k=0;k<units1.size();k++){
		for(int i=0;i<units1.size();i++){
			for(int j=0;j<units1.size();j++){
				v[0].first=units1[i];
				v[0].second=units1[k];
				v[1].first=units1[k];
				v[1].second=units1[j];
				v[2].first=units1[i];
				v[2].second=units1[j];
				if((conv1[v[0]]*conv1[v[1]])>conv1[v[2]])
					conv1[v[2]]=conv1[v[0]]*conv1[v[1]];
			}
		}
	}

	for(int K=0;K<units2.size();K++){
		for(int I=0;I<units2.size();I++){
			for(int J=0;J<units2.size();J++){
				v[0].first=units2[I];
				v[0].second=units2[K];
				v[1].first=units2[K];
				v[1].second=units2[J];
				v[2].first=units2[I];
				v[2].second=units2[J];
				if((conv2[v[0]]*conv2[v[1]])>conv2[v[2]] )
					conv2[v[2]]=conv2[v[0]]*conv2[v[1]];
			}
		}
	}

}

double pow(int i,int j){
	if(j==0)
		return 1;
	return i*pow(i,j-1);
}

int str2i(string str){
	int ret=0;
	for(int i=0;i<str.size();i++){
		ret*=10;
		ret+=str[i]-'0';
	}
	return ret;
}

double str2d(string str){
	string i;
	string d;
	string::iterator iter=find(str.begin(),str.end(),'.');
	if(iter==str.end()){
		return str2i(str)*1.0;
	}
	else{
		i=str.substr(0,iter-str.begin());
		d=str.substr(iter-str.begin()+1,str.size());
	}
	double integer=(str2i(i)*1.0);
	double decimal=(str2i(d)/pow(10,d.size()));
	return integer+decimal+EPS;
}

void output(double number){
	static ofstream cout("myout.txt");
	pair<string,string> u;
	u.second=units2[units2.size()-1];
	int n;
	for(int i=0;i<units2.size();i++){
		u.first=units2[i];
		if(i!=units2.size()-1){
			n=number/conv2[u];
			number-=n*conv2[u];
		}
		else
			n=number+0.5;

		if(i!=0)
			cout<<" ";
		cout<<n<<" "<<u.first;
	}
	cout<<endl;
}

void convert(string str,pair<string,string> u){
	string::iterator iter;
	string base1=u.first;
	string base2=u.second;
	string num;
	string unit;
	double number=0;
	while(str!=""){
		iter=find(str.begin(),str.end(),' ');
		num=str.substr(0,iter-str.begin());
		if(iter!=str.end()){
			str=str.substr(iter-str.begin()+1,str.end()-iter-1);
		}
		else
			str="";

		iter=find(str.begin(),str.end(),' ');
		unit=str.substr(0,iter-str.begin());
		if(iter!=str.end()){
			str=str.substr(iter-str.begin()+1,str.end()-iter-1);
		}
		else
			str="";

		u.first=unit;
		u.second=base1;
		number+=conv1[u]*str2d(num);
	}
	
	//convert to the other base
	u.first=base1;
	u.second=base2;
	number=conv[u]*number;
	
	//convert to the smallest in the other base
	u.first=base2;
	u.second=units2[units2.size()-1];
	number=conv2[u]*number;

	output(number);
}

int main(){
	ifstream cin("Convert.h");
	string str;
	while(getline(cin,str) && str!=""){
		pair<double,double> num;
		pair<string,string> u;

		order.clear();
		units1.clear();
		fill_units1(str);
		
		for(int i=0;i<units1.size()-1;i++){
			cin>>num.first>>u.first>>str>>num.second>>u.second;
			getline(cin,str);//remove the endl

			conv1[u]=num.second/num.first;
			swap(u.first,u.second);
			conv1[u]=num.first/num.second;
		}

		getline(cin,str);
		units2.clear();
		fill_units2(str);

		for(int i=0;i<units2.size()-1;i++){
			cin>>num.first>>u.first>>str>>num.second>>u.second;
			getline(cin,str);//remove the endl

			conv2[u]=num.second/num.first;
			swap(u.first,u.second);
			conv2[u]=num.first/num.second;
		}

		floyed();

		//converassion from one to another
		cin>>num.first>>u.first>>str>>num.second>>u.second;
		conv[u]=num.second/num.first;
		getline(cin,str);

		while(getline(cin,str) && str!="")
			convert(str,u);
	}
}