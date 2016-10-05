#include <iostream>
#include <fstream>
#include <sstream>

#include <iomanip>

#include <algorithm>

#include <vector>
#include <deque>
#include <list>
#include <stack>
#include <queue>
#include <set>
#include <map>
#include <bitset>
#include <string>

#include <iterator>
#include <functional>
#include <complex>
#include <numeric>
#include <valarray>

#include <cmath>

using namespace std;

#define REP(i, a, b) 		for (i=(int)a ; i<=(int)b ; i++)
#define REPD(i, a, b)		for (i=(int)a ; i>=(int)b ; i--)
#define REPI(i, v)		for (i=v.begin() ; i!=v.end() ; i++)
#define FOR(i, n)		REP (i, 0, n-1)
#define FORD(i, n)		REPD(i, n-1, 0)

#define All(v)			v.begin(),v.end()
#define Resize(v,N)		v.clear(); v.resize(N);

#define IsIn(v,e)		(find(All(v),e) != v.end())
#define Remove(v,e)		v.resize( remove(All(v),e) - v.begin() )

#define VI			vector<int>
#define VVI			vector<VI>

#define x			first
#define y			second
#define II			pair<int,int>
#define VII			vector<II>
#define VVII			vector<VII>

#define NIL -1

struct Node{
    int c1;
    int c2;
    int lo;
    int hi;
    int val;
    Node(){
        c1 = NIL;
        c2 = NIL;
    }
};

VI V;
vector<Node> ST;
const int root = 0;

void Build(int node , int lo , int hi){
    ST[node].lo = lo;
    ST[node].hi = hi;
    if(lo == hi){ // Base Case
        ST[node].val = V[lo]; // Modify this part
        return;
    }

    // Create Children
    ST[node].c1 = ST.size(); ST.push_back(Node());
    ST[node].c2 = ST.size(); ST.push_back(Node());

    // Build Children
    int mid = (hi+lo)/2;
    Build(ST[node].c1 , lo , mid);
    Build(ST[node].c2 , mid+1 , hi);

    // modify the value based on children
    int u = ST[ST[node].c1].val;
    int v = ST[ST[node].c2].val;
    ST[node].val = u+v;
}

void Build_Segment_Tree(){ // Assuming Minimum Range Queary of vector V
    ST.clear();
    ST.push_back(Node());
    Build(root,0,V.size()-1);
}

int Query_Sum(int node , int i , int j){ // From i to j in the range lo to hi
    if(i==ST[node].lo && ST[node].hi==j)
        return ST[node].val;

    int mid = (ST[node].lo + ST[node].hi)/2;
    if(i>mid)
        return Query_Sum(ST[node].c2 , i , j);
    else if (j<=mid)
        return Query_Sum(ST[node].c1 , i , j);
    else{
        int u = Query_Sum(ST[node].c1 , i , mid);
        int v = Query_Sum(ST[node].c2 , mid+1 , j);
        return u+v;
    }
}

void Query_Val(int node , int u , int val){
    if(ST[node].lo == ST[node].hi){
        ST[node].val = val;
        return;
    }
    int mid = (ST[node].lo + ST[node].hi)/2;
    if(u<=mid)
        Query_Val(ST[node].c1 , u , val);
    else
        Query_Val(ST[node].c2 , u , val);
    ST[node].val = ST[ST[node].c1].val + ST[ST[node].c2].val;
}

int main(){
    ifstream cin("input.txt");
    bool b = false;
    for(int cnt = 1 ; true ; cnt++){
        int N;
        cin >> N;
        if(N==0)
            return 0;

        if(b)
            cout <<endl;
        b = true;

        V.clear(); V.resize(N);
        int i;
        FOR(i,N)
            cin >> V[i];
        Build_Segment_Tree();
        cout <<"Case "<< cnt <<":"<<endl;
        while(true){
            string str;
            int x,y;
            cin >> str;
            if(str == "END")
                break;
            cin >> x >> y;
            if(str == "S")
                Query_Val(root,x-1,y);
            else
                cout << Query_Sum(root,x-1,y-1) << endl;
        }
    }
}