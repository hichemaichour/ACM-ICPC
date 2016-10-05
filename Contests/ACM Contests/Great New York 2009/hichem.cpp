//#include <iostream>
//#include <vector>
//#include <algorithm>
//
//#define All(V) V.begin(),V.end()
//
//using namespace std;
//
//const long long M = 1e12 + 10;
//vector<long long> V;
//vector<long long> v4;
//vector<long long> v7;
//
//void init(){
//    V.clear();
//    long long mul = 1;
//    int i;
//    for(i=0 ; true ; i++){
//        mul *= 4;
//        if(mul>M)
//            break;
//        v4.push_back(mul);
//        V.push_back(mul);
//    }
//    mul = 1;
//    for(i=0 ; true ; i++){
//        mul *= 7;
//        if(mul>M)
//            break;
//        v7.push_back(mul);
//        V.push_back(mul);
//    }
//
//    int j;
//    j = 3;
//    for(i=0 ; i<v4.size() ; i++){
//        for(j=0 ; j<v7.size() ; j++){
//            mul = v4[i]*v7[j];
//            if(mul>M)
//                break;
//            V.push_back(mul);
//        }
//    }
//
//    sort(V.begin(),V.end());
//}
//
//int main(){
//    init();
//    int N;
//    cin >> N;
//    for(int cnt=0 ; cnt<N ; cnt++){
//        int A,B;
//        cin >> A >> B;
//        cout << upper_bound(All(V),B) - lower_bound(All(V),A) << endl;
//    }
//    return 0;
//}
