struct TwoSat{
	int n;
	vector<Pair> e[MAX_N][2];
	vector<int> Glo;
	bool mark[MAX_N],ans[MAX_N];
	TwoSat(int s){ 
		n=s; 
		for (int i=0;i<MAX_N;i++){
			e[i][0].clear(); e[i][1].clear();
			mark[i]=ans[i]=false;
		}
	}
	inline bool dfs(int s,bool t){
		if (mark[s]) return(ans[s] == t);
		mark[s]=true; ans[s]=t; Glo.push_back(s);
		for (int i=0;i<e[s][t].size();i++)
			if (!dfs(e[s][t][i].first,e[s][t][i].second))
				return(false);
		return(true);
	}
	inline bool fix(Pair s){
		Glo.clear();
		if (dfs(s.first,s.second)) return(true);
		for (int i=0;i<Glo.size();i++) mark[Glo[i]]=ans[Glo[i]]=false;
		return(false);
	}
	inline void push_back(int A,bool a,int B,bool b){  
		e[A][!a].push_back(Pair(B,b));
		e[B][!b].push_back(Pair(A,a));
	}
	inline bool relax(){
		for (int i=1;i<=n;i++) 
			if (!fix(Pair(i,0)) && !fix(Pair(i,1))) 
				return(false);
		return(true);
	}
};
