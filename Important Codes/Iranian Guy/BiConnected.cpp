struct Graph{
	vector<int> e[MAX_N];
	int dep[MAX_N];
	vector<vector<Pair> > ans;
	vector<Pair> Glo;
	int n;
	Graph(int s){
		for (int i=0;i<MAX_N;i++){
			e[i].clear();
			dep[i]=0;
		}
		n=s;
		ans.clear();
	}
	int dfs(int s,int t){
		dep[s]=t;
		int Ans=t;
		for (int i=0;i<e[s].size();i++){
			if (dep[e[s][i]]){
				Ans=min(Ans,dep[e[s][i]]);
				if (dep[e[s][i]] < t) Glo.push_back(Pair(s,e[s][i]));
			}else{
				int temp=Glo.size(),a=dfs(e[s][i],t+1);
				if (a >= t){
					ans.push_back(vector<Pair>());
					while (Glo.size() > temp){
						ans.back().push_back(Glo.back());
						Glo.pop_back();
					}
				}
				Ans=min(Ans,a);
			}
		}
		return(Ans);
	}
	vector<vector<Pair> > components(){
		ans.clear();
		Glo.clear();
		for (int i=1;i<=n;i++) if (!dep[i]) dfs(i,1);
		return(ans);
	}
};
