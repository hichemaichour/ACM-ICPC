#include <iostream>
#include <deque>
#include <map>
#include <algorithm>

using namespace std;

deque<int> v;
map<int,int> m;
map<int,bool> IN;

int main(){
    for(int cnt=1 ; true ; cnt++){
        v.clear();
        m.clear();
        IN.clear();
        int W;
        int i,j,k;

        cin>>W;
        if(W==-1)
            return 0;
        int sum = 0;
        while(true){
            char c;
            cin>>c;
            if(c=='E')
                break;
            if(c=='A'){
                cin>>i>>j;
                m[i] = j;
                if(IN[i])
                    continue;
                v.push_front(i);
                IN[i] = true;
                sum += j;
                while(sum > W){
                    sum -= m[v.back()];
                    IN[v.back()] = false;
                    v.pop_back();
                }
            }
            if(c=='R'){
                cin>>i;
                if(!IN[i])
                    continue;
                IN[i] = false;
                sum -= m[i];
                remove(v.begin(),v.end(),i);
                v.resize(v.size()-1);
            }
        }

        cout<<"PROBLEM "<<cnt<<":";
        for(i=0 ; i<v.size() ; i++)
            cout<<" "<<v[i];
        cout<<endl;
    }
}