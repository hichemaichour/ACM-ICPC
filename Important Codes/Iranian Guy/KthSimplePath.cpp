struct Graph{
	int n,dist[MAX_N],s,t,last[MAX_N],number[MAX_K][MAX_N][MAX_N],e[MAX_N][MAX_N];
	bool mark[MAX_N],bad[MAX_N],used[MAX_K][MAX_N][MAX_N];
	Graph(int S,int start,int end){
		n=S;
		s=start;
		t=end;
		for (int i=0;i<MAX_K;i++) for (int j=0;j<MAX_N;j++) for (int k=0;k<MAX_N;k++) 
			used[i][j][k]=number[i][j][k]=0;
	}
	vector<int> find(int s){
		vector<int> ans;
		while (s){
			ans.push_back(s);
			s=last[s];
		}
		return(ans);
	}
	void dij(int s){
		for (int i=1;i<=n;i++) mark[i]=false;
		for (int i=0;i<=n;i++) dist[i]=INF;
		for (int i=1;i<=n;i++) last[i]=0;
		dist[s]=0;
		while (s){
			mark[s]=true;
			for (int j=1;j<=n;j++) if (!bad[j] && dist[s]+e[j][s] < dist[j]){
				dist[j]=dist[s]+e[j][s];
				last[j]=s;
			}
			s=0;
			for (int i=1;i<=n;i++) if (!mark[i] && !bad[i] && dist[i] < dist[s]) s=i;
		}
	}
	vector<int> KthMinPath(int k){
		for (int i=1;i<=n;i++) bad[i]=false;
		dij(t);
		vector<vector<int> > path;
		vector<int> start;
		path.push_back(find(s));
		start.push_back(0);
		for (int i=1;i<k;i++){
			for (int j=start[i-1];j+1<path[i-1].size();j++){
				for (int x=1;x<=n;x++) bad[x]=false;
				for (int x=0;x<=j;x++) bad[path[i-1][x]]=true;
				int sum=0;
				for (int x=0;x<j;x++) sum+=e[path[i-1][x]][path[i-1][x+1]];
				dij(t);
				dist[path[i-1][j+1]]=INF;
				for (int x=1;x<=n;x++) number[i-1][j][x]=dist[x]+sum+e[path[i-1][j]][x];
			}
			int best=INF;
			for (int a=0;a<i;a++) for (int b=start[a];b+1<path[a].size();b++)
				for (int c=1;c<=n;c++) if (!used[a][b][c])
					best=min(best,number[a][b][c]);
			int A=-1,B=-1,C=-1;
			bool Find=false;
			for (int a=0;a<i;a++) for (int b=start[a];b+1<path[a].size();b++)
				for (int c=1;c<=n;c++) if (!used[a][b][c] && !Find && number[a][b][c]==best){
					Find=true;
					used[a][b][c]=true;
					A=a;
					B=b;
					C=c;
				}
				if (A==-1) return(vector<int>());
				for (int j=1;j<=n;j++) bad[j]=false;
				for (int j=0;j<=B;j++) bad[path[A][B]]=true;
				dij(t);
				path.push_back(vector<int>());
				start.push_back(B+1);
				for (int j=0;j<=B;j++) path.back().push_back(path[A][j]);
				vector<int> temp=find(C);
				for (int j=0;j<temp.size();j++) path.back().push_back(temp[j]);
		}
		return(path.back());
	}
};
