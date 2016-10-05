struct IncreasingSubsequence{
	int n,num[MAX_N];
	IncreasingSubsequence(int s){
		n=s; 
		for (int i=0;i<MAX_N;i++) num[i]=0;
	}
	int MaximumIncreasingSubsequence(){
		int best[MAX_N];
		for (int i=0;i<MAX_N;i++) best[i]=INF;
		best[0]=(*min_element(num+1,num+n+1))-1;
		for (int i=1;i<=n;i++)
			*lower_bound(best+1,best+n+1,num[i])=num[i];
		int ans=n;
		while (best[ans] == INF) ans--;
		return(ans);
	}
};
