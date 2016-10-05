#include <iostream>
#include <algorithm>
using namespace std;

bool isL(double v[]){
	return (v[0]>=0.25 && v[1]>=90 && v[2]>=125) && (v[0]<=7 && v[1]<=155 && v[2]<=290);
}
bool isPc(double v[]){
	return (v[0]>=0.25 && v[1]>=90 && v[2]>=125) && (v[0]<=50 && v[1]<=300 && v[2]<=380);
}
bool isPa(double v[]){
	return (v[0]>=0.25 && v[1]>=90 && v[2]>=125) && (v[2] + 2*(v[0]+v[1]) < 2100);
}

int main() {
	double v[3];
	while(cin >> v[0] >> v[1] >> v[2] && v[0]){
		sort(v,v+3);
		if(isL(v)){
			cout << "letter" << endl;
		}
		else if(isPc(v)){
			cout << "packet"<<endl;
		}
		else if(isPa(v)){
			cout << "parcel"<<endl;
		}
		else{
			cout << "not mailable"<<endl;
		}
	}
	return 0;
}