template <typename type>
vector<pair<type,int> > bfs(vector<pair<type,type> > yal,type s){
	map<type,vector<type> > e;
	for (int i=0;i<yal.size();i++) e[yal[i].first].push_back(yal[i].second);

	vector<type> qu;
	map<type,int> dist;
	qu.push_back(s);
	dist[s]=0;
	vector<pair<type,int> > ans;
	for (int first=0;first < qu.size();first++){
		ans.push_back(pair<type,int>(qu[first],dist[qu[first]]));
		type x=qu[first];
		for (int i=0;i<e[x].size();i++) if (dist.find(e[x][i]) == dist.end()){
			dist[e[x][i]]=dist[x]+1;
			qu.push_back(e[x][i]);
		}
	}
	return(ans);
}
