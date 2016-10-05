struct WeightedMatching{
	int n,e[MAX_N][MAX_N],lab[2][MAX_N],hus[MAX_N];
	bool mark[2][MAX_N],used[MAX_N];
	WeightedMatching(int s){
		n=s;
		for (int i=0;i<MAX_N;i++) fill(e[i],e[i]+MAX_N,0);
		fill(used,used+MAX_N,false);
		fill(hus,hus+MAX_N,0);
		for (int i=0;i<=1;i++){ fill(lab[i],lab[i]+MAX_N,0); fill(mark[i],mark[i]+MAX_N,false);
		}
	}

	inline bool find(int s){
		if (mark[0][s]) return(false);
		mark[0][s]=true;
		for (int i=1;i<=n;i++) if (lab[0][s]+lab[1][i]==e[s][i]){
			mark[1][i]=true;
			if (!hus[i] || (hus[i] && find(hus[i]))){
				hus[i]=s;
				return(true);
			}
		}
		return(false);
	}

	int MaxMatching(){
		for (int i=1;i<=n;i++) for (int j=1;j<=n;j++) lab[1][j]=max(lab[1][j],e[i][j]);

		for (int count=1;count<=n;count++){
			bool Find=false;
			while (!Find){
				for (int i=0;i<=1;i++) for (int j=1;j<=n;j++) mark[i][j]=false;

				for (int i=1;i<=n;i++) if (!used[i] && find(i)){
					used[i]=true;
					Find=true;
					break;
				}
				if (Find) break;
				int kam=INF;
				for (int i=1;i<=n;i++) if (mark[0][i])
					for (int j=1;j<=n;j++) if (!mark[1][j])
						kam=min(kam,lab[0][i]+lab[1][j]-e[i][j]);

				for (int i=1;i<=n;i++){
					if (mark[0][i]) lab[0][i]-=kam;
					if (mark[1][i]) lab[1][i]+=kam;
				}

			}
		}
		int sum=0;
		for (int i=1;i<=n;i++) sum+=e[hus[i]][i];
		return(sum);
	}
};
