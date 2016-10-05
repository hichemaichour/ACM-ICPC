class MinCostFlow{
	int n,destination;
	vector<int> c,f,start,end,cost,left,right,e;
	vector<vector<int> > next,prev;
	vector<bool> mark;
	map<int,int> cap;
	static const int INF=1<<25;

	int dfs(int s,int t){
		if (s == destination) return(t);
		if (mark[s]) return(0);
		mark[s]=true;
		int temp=0;
		for (int i=0;i<next[s].size();i++)
			if (c[next[s][i]] > f[next[s][i]])
				if (temp = dfs(end[next[s][i]],min(t,c[next[s][i]]-f[next[s][i]]))){
					f[next[s][i]]+=temp;
					return(temp);
				}
				for (int i=0;i<prev[s].size();i++)
					if (f[prev[s][i]])
						if (temp=dfs(start[prev[s][i]],min(t,f[prev[s][i]]))){
							f[prev[s][i]]-=temp;
							return(temp);
						}
						return(0);
	}
	void relax(){
		int count=n+1;
		n+=cap.size();

		next.resize(n+1);
		prev.resize(n+1);
		mark.resize(n+1);

		map<int,int> New;

		int number=start.size();

		for (map<int,int> :: iterator i=cap.begin();i!=cap.end();i++,count++){
			New[i->first]=count;
			push_back(i->first,count,i->second,0);
		}
		for (int i=0;i<number;i++) if (New.find(start[i]) != New.end())
			start[i]=New[start[i]];
		for (int i=0;i<start.size();i++){
			next[start[i]].push_back(i);
			prev[end[i]]  .push_back(i);
		}
	}
	bool findCycle(){
		vector<int> dist,last;
		dist.resize(n+1); last.resize(n+1);
		fill(dist.begin(),dist.end(),0);
		fill(last.begin(),last.end(),-1);

		for (int count=1;count<=n+5;count++)
			for (int i=0;i<e.size();i++) dist[right[i]]=min(dist[right[i]],dist[left[i]]+e[i]);
		bool find=false;
		for (int count=1;count<=n+5;count++)
			for (int i=0;i<e.size();i++)
				if (dist[right[i]] > dist[left[i]]+e[i]){
					find=true;
					dist[right[i]]=dist[left[i]]+e[i];
					last[right[i]]=i;
				}
				if (!find) return(false);
				fill(e.begin(),e.end(),0);
				for (int i=1;i<=n;i++) if (last[i]>=0) e[last[i]]=1;

				for (int i=0;i<e.size();i++) if (e[i]){
					int temp=i,count=0;
					bool good=false;
					vector<int> Temp;
					while (count <= n){
						count++;
						Temp.push_back(temp);
						if (last[left[temp]]==-1) break;
						if (last[left[temp]]==i){
							good=true;
							break;
						}
						temp=last[left[temp]];
					}
					if (good){
						fill(e.begin(),e.end(),0);
						for (int i=0;i<Temp.size();i++) e[Temp[i]]=1;
						break;
					}
				}
				return(true);
	}
	inline bool can(){
		e.clear(); left.clear(); right.clear();
		for (int i=0;i<start.size();i++){
			if (c[i] > f[i]){
				e.push_back(cost[i]);
				left.push_back(start[i]);
				right.push_back(end[i]);
			}
			if (f[i]){
				e.push_back(-cost[i]);
				left.push_back(end[i]);
				right.push_back(start[i]);
			}
		}
		if (!findCycle()) return(false);
		int count=0,Min=INF;
		for (int i=0;i<start.size();i++){
			if (c[i] > f[i]){
				if (e[count]) Min=min(Min,c[i]-f[i]);
				count++;
			}
			if (f[i]){
				if (e[count]) Min=min(Min,f[i]);
				count++;
			}
		}
		count=0;
		for (int i=0;i<start.size();i++){
			int temp=f[i];
			if (c[i] > temp){
				if (e[count]) f[i]+=Min;
				count++;
			}
			if (temp){
				if (e[count]) f[i]-=Min;
				count++;
			}
		}
		return(true);    
	}
public:
	MinCostFlow(int n){
		destination=0;
		this->n=n;
		c.clear(); f.clear(); start.clear(); end.clear(); next.clear(); prev.clear();
		mark.resize(n+1);
		next.resize(n+1);
		prev.resize(n+1);
	}
	void push_back(int left,int right,int C,int Cost){
		cost.push_back(Cost);
		c.push_back(C);
		f.push_back(0);
		start.push_back(left);
		end.push_back(right);
	}
	int minCostFlow(int start,int end){
		relax();
		destination=end;
		fill(mark.begin(),mark.end(),false);
		int ans=0,temp=0;
		while (temp=dfs(start,INF)){
			ans+=temp;
			fill(mark.begin(),mark.end(),false);
		}
		int ret=0;
		while (can())
			;
		for (int i=0;i<f.size();i++) ret+=f[i]*cost[i];
		return(ret);
	}
	void setLimit(int s,int t){
		cap[s]=t;
	}
};
