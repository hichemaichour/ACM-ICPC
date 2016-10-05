/*
ID: b0002141
PROG: calfflac
LANG: C++
*/
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

void remove(string file,string& find,int a[]){
	char buf[]=" ";
	for(int i=0;i<file.size();i++){
		if(file[i] >= 'A' && file[i]<='Z'){
			buf[0]=file[i];
			find+=buf;
			a[find.size()-1]=i;
		}
		else if(file[i] >= 'a' && file[i]<='z'){
			buf[0]=file[i]-'a'+'A';
			find+=buf;
			a[find.size()-1]=i;
		}
	}
}

bool isPal(string str){
	for(int i=0;i<str.size()/2;i++)
		if(str[i]!=str[str.size()-1-i])
			return false;
	return true;
}

int lenPal(string find,double i){
	int ret=0;
	if(i-(int)i== 0)
		ret++;
	for(int j=0;i-j-0.5>=0 && i+j+1<find.size();j++){
		if(find[(int)(i-j-0.5)]!=find[(int)(i+j+1)])
			break;
		ret+=2;
	}
	return ret;
}

void PAL(int& start,int& end,string find){
	int max=0;
	double center;
	int n;
	for(double i=0.5;i<find.size();i+=0.5){
		n=lenPal(find,i);
		if(max<n){
			max=n;
			center=i;
		}
	}
	start=((int)(center+0.5)-(max/2));
	end=start+max;
}

int main() {
	string file="";
	char buf[81];
	string find="\n";
	int a[20000];
	int start=0;
	int end=0;
	int length;

    ofstream fout ("calfflac.out");
    ifstream fin ("calfflac.in");
	//ifstream fin ("File.txt");

	while(!fin.eof()){
		fin.getline(buf,81);
		file+=buf;
		file+=find;
	}

	find="";
	remove(file,find,a);

	PAL(start,end,find);

	length=end-start;
	start=a[start];
	end=a[end-1];

	fout<<length<<endl<<file.substr(start,end-start+1)<<endl;

    return 0;
}