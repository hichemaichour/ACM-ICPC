#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <deque>

using namespace std;

int main(){
    int T;
    cin>>T;
    while(T--){
        int n,k;
        cin>>n>>k;
        deque<int> d;
        
        bool flg=true;
        int buf=-1;
        int rem=0;
        d.push_back(k);
        for(int i=0;i<1000;i++){
            buf=d[0]*n + rem;
            rem=0;
            while(buf>9){
                rem++;
                buf-=10;
            }

            if(buf==k && rem==0){
                flg=false;
                break;
            }
            d.push_front(buf);
        }

        if(flg || d[0]==0)
            cout<<"0"<<endl;
        else{
            while(!d.empty()){
                cout<<d[0];
                d.pop_front();
            }
            cout<<endl;
        }
    }
}