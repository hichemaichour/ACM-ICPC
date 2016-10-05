struct sat{
	bool ans[MAX_N];
	vector<vector<int> > constrains;
	vector<vector<bool> > values;
	vector<int> check[MAX_N];
	int n;
	sat(int s):n(s){
		fill(ans ,ans +MAX_N,false);
		for (int i=0;i<MAX_N;i++) check[i].clear();
		constrains.clear();
		values.clear();
	}
	inline bool good(int s){
		for (int i=0;i<check[s].size();i++){
			bool find=false;
			for (int j=0;j<constrains[check[s][i]].size();j++)
				find|=values[check[s][i]][j] == ans[constrains[check[s][i]][j]];
			if (!find) return(false);
		}
		return(true);
	}
	bool bt(int s){
		if (s > n) return(true);
		ans[s]=true;
		if (good(s))
			if (bt(s+1))
				return(true);
		ans[s]=false;
		if (good(s))
			if (bt(s+1))
				return(true);
		return(false);
	}
	void push_back(const vector<int> &a,const vector<bool> &b){
		constrains.push_back(a);
		values.push_back(b);
		check[*max_element(a.begin(),a.end())].push_back(values.size()-1);
	}
	bool relax(){
		return(bt(1));
	}
};
