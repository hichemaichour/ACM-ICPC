#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

int main(){
	//ifstream cin("Judging.h");
	while(true){
		vector<int>grades(6);
		double sum=0;
		int Max,Min;
		cin>>grades[0];
		Min=grades[0];
		Max=grades[0];
		sum+=grades[0];
		for(int i=1;i<6;i++){
			cin>>grades[i];
			if(grades[i]<Min)
				Min=grades[i];
			if(grades[i]>Max)
				Max=grades[i];
			sum+=grades[i];
		}
		if(sum==0)
			break;
		cout<<(sum-Min-Max)/4<<endl;
	}
}