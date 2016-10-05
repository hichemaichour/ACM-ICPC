/*
ID: b0002141
PROG: milk2
LANG: C++
*/
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

void sort(int x[],int y[],int N){
	int a,b;

	//sort
	for(int i=0;i<N;i++){
		for(int j=i;j<N;j++){
			if (x[j]<x[i]){
				a=x[i];
				b=y[i];
				x[i]=x[j];
				y[i]=y[j];
				x[j]=a;
				y[j]=b;
			}
		}
	}
}

void march(int x[],int y[],int N,int n){
	for(int i=n;i<N-1;i++){
		x[i]=x[i+1];
		y[i]=y[i+1];
	}
}

int main() {
	int N;
	int x[5000],y[5000];
	
    ofstream fout ("milk2.out");
    ifstream fin ("milk2.in");
	
	fin>>N;

	//get the values
	for(int i=0;i<N;i++)
		fin>>x[i]>>y[i];
		
	sort(x,y,N);

	for(int i=0;i<N-1;i++){
		if(y[i]>=x[i+1]){
			if(y[i]<y[i+1])
				y[i]=y[i+1];
			march(x,y,N,i+1);
			N--;
			i--;
		}
	}

	int maxIn=0;
	int maxOut=0;
	int buf;

	for(int i=0;i<N;i++){
		buf=y[i]-x[i];
		if(buf>maxIn)
			maxIn=buf;
		if(i != N-1){
			buf=x[i+1]-y[i];
			if(buf>maxOut)
				maxOut=buf;
		}
	}

	fout<<maxIn<<" "<<maxOut<<endl;
}