struct StronglyConnected{
	int n;
	vector<int> e[MAX_N],re[MAX_N],sorted,Glo;
	vector<vector<int> > ans;
	bool mark[MAX_N];
	StronglyConnected(int s){
		n=s;
		for (int i=0;i<MAX_N;i++){e[i].clear(); mark[i]=false; re[i].clear();
		}
		sorted.clear();  ans.clear();
	}
	inline void dfs(int s){
		if (mark[s]) return;
		mark[s]=true;
		Glo.push_back(s);
		for (int i=0;i<e[s].size();i++) dfs(e[s][i]);
		sorted.push_back(s);
	}
	inline void push_back(int a,int b){ e[a].push_back(b);
	}
	vector<vector<int> > Components(){
		for (int i=1;i<=n;i++) if (!mark[i]) dfs(i);

		reverse(sorted.begin(),sorted.end());
		for (int i=1;i<=n;i++) for (int j=0;j<e[i].size();j++) re[e[i][j]].push_back(i);
		for (int i=1;i<=n;i++) swap(e[i],re[i]);

		vector<vector<int> > ans;
		fill(mark+1,mark+n+1,false);
		for (int i=1;i<=n;i++) if (!mark[sorted[i-1]]){
			Glo.clear();
			dfs(sorted[i-1]);
			ans.push_back(Glo);
		}
		return(ans);
	}
};
