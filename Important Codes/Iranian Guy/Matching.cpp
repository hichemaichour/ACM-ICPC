struct Matching{
	int n,hus[MAX_N];
	bool mark[MAX_N];
	bool e[MAX_N][MAX_N];
	Matching(int s){
		for (int i=0;i<MAX_N;i++) fill(e[i],e[i]+MAX_N,false); 
		n=s;
		fill(hus,hus+MAX_N,0);
	}
	inline bool find(int s){
		if (mark[s]) return(false);
		mark[s]=true;
		for (int i=1;i<=n;i++) if (e[s][i]){
			if (!hus[i] || (hus[i] && find(hus[i]))){
				hus[i]=s;
				return(true);
			}
		}
		return(false);
	}
	int MaxMatching(){
		int ans=0;
		for (int i=1;i<=n;i++){
			fill(mark+1,mark+n+1,false);
			ans+=find(i);
		}
		return(ans);
	}
};
