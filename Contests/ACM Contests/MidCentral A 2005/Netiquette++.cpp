#include <iostream>
#include <string>
#include <vector>

using namespace std;

bool check(string str){
    int i,j,k;
    if(str.size() == 1 && str[0]!='a' && str[0]!='A' && str[0]!='I')
        return false;

    for(int i=0 ; i<str.size()-1 ; i++){
        if(isupper(str[i]) && isupper(str[i+1]))
            return false;
        if((isdigit(str[i]) && isalpha(str[i+1])) || (isalpha(str[i]) && isdigit(str[i+1])))
            return false;
        if(ispunct(str[i]) && ispunct(str[i+1]) && str[i]!='\"' && str[i+1]!='\"')
            return false;
    }
    return true;
}

int main(){
    while(true){
        string str;
        getline(cin,str);
        if(str=="#")
            return 0;
        str.push_back(' ');

        int i;
        bool flg = true;
        while(str!=""){
            i=str.find(' ');
            flg = check(str.substr(0,i));
            str = str.substr(i+1,str.size());
            if(flg == false)
                break;
        }

        if(flg)
            cout<<"OK"<<endl;
        else
            cout<<"suspicious"<<endl;
    }
}