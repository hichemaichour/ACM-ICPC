#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int main(){
	//ifstream cin("Smarty.h");
	for(int cnt=1;true;cnt++){
		int R,N;
		string p1,p2;
		char c=' ';
		cin>>R;
		if(R==0)
			break;
		cin>>N;

		//reading p1
		while(c == ' ')
			cin.get(c);

		if(c=='\"'){
			p1.push_back(c);
			cin.get(c);
			while(c!='\"'){
				p1.push_back(c);
				cin.get(c);
			}
			p1=p1.substr(1,p1.size());
			c=' ';
		}
		else{
			p1.push_back(c);
			cin.get(c);
			while(c != ' '){
				p1.push_back(c);
				cin.get(c);
			}
		}


		//reading p2
		while(c == ' ')
			cin.get(c);

		if(c=='\"'){
			p2.push_back(c);
			cin.get(c);
			while(c!='\"'){
				p2.push_back(c);
				cin.get(c);
			}
			p2=p2.substr(1,p2.size());
			c=' ';
		}
		else{
			p2.push_back(c);
			cin.get(c);
			while(c != ' ' && c != '\n'){
				p2.push_back(c);
				cin.get(c);
			}
		}

		for(int i=0;i<p1.size();i++)
			if(isupper(p1[i]))
				p1[i]=tolower(p1[i]);
		for(int j=0;j<p2.size();j++)
			if(isupper(p2[j]))
				p2[j]=tolower(p2[j]);

		int buf=R%(2*N);
		if(buf==0)
			buf+=2*N;
		if( buf<=N )
			cout<<cnt<<". "<<p1<<endl;
		else
			cout<<cnt<<". "<<p2<<endl;
	}
	return 0;
}