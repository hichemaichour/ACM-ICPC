#include <iostream>
#include <vector>
#include <fstream>
#include <string>

using namespace std;

int main(){
    int T;
    cin>>T;
    while(T--){
        int R,C;
        cin>>R>>C;
        vector<vector<int> > v(R+1,vector<int>(C+1));
        int X,Y;
        cin>>X>>Y;
        string dir;
        cin>>dir;
        pair<int,int> d;
        if(dir[0]=='U')
            d.first=-1;
        else
            d.first=1;
        if(dir[1]=='L')
            d.second=-1;
        else
            d.second=1;

        v[X][Y]++;
        int cnt=0;
        while(true){
            X+=d.first;
            Y+=d.second;
            v[X][Y]++;
            if(v[X][Y]==2)
                cnt++;
            if((X==1 || X==R) && (Y==1 || Y==C))
                break;
            if( (X==1 || X==R || Y==1 || Y==C) && (v[X][Y]==2) )
                break;
            if(X==1)
                d.first=1;
            if(X==R)
                d.first=-1;
            if(Y==1)
                d.second=1;
            if(Y==C)
                d.second=-1;
        }

        cout<<cnt<<endl;
    }
}
