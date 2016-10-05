template<typename x,typename y,typename z>
struct tripple{
  x first;
  y second;
  z third;
  tripple(x a,y b,z c){ 
    first=a;
    second=b;
    third=c;
  }
  
  inline bool operator < (const tripple<x,y,z> &s)const{
    if (first != s.first) return(first < s.first);
    if (second != s.second) return(second < s.second);
    return(third < s.third);
  }
};

template<typename type>
vector<pair<type,int> > dijkstra(vector<tripple<type,type,int> > yal,type s){
  map<type,vector<type> > e;
  map<type,vector<int> >dist;
  for (int i=0;i<yal.size();i++){
    e[yal[i].first].push_back(yal[i].second);
    dist[yal[i].first].push_back(yal[i].third);
  }
  map<type,int> fas;
  fas[s]=0;
  set<pair<int,type> > Set;
  vector<pair<type,int> > ans;
  Set.insert(pair<int,type>(0,s));
  while (Set.size()){
    pair<int,type> x=*Set.begin();;
    Set.erase(Set.begin());
    type who=x.second;
    ans.push_back(pair<type,int>(x.second,x.first));
    for (int i=0;i<e[who].size();i++){
      if (fas.find(e[who][i]) == fas.end()) fas[e[who][i]]=x.first+dist[who][i]+1;
      if (fas[e[who][i]] > x.first+dist[who][i]){
	Set.erase(pair<int,type>(fas[e[who][i]],e[who][i]));
	fas[e[who][i]]=x.first+dist[who][i];
	Set.insert(pair<int,type>(fas[e[who][i]],e[who][i]));
      }
    }
  }
  return(ans);
}
