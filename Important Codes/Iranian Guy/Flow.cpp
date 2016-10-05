class Flow{
	int n,destination;
	vector<int> c,f,start,end;
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
			push_back(i->first,count,i->second);
		}
		for (int i=0;i<number;i++) if (New.find(start[i]) != New.end())
			start[i]=New[start[i]];
		for (int i=0;i<start.size();i++){
			next[start[i]].push_back(i);
			prev[end[i]]  .push_back(i);
		}
	}

public:
	Flow(int n){
		destination=0;
		this->n=n;
		c.clear(); f.clear(); start.clear(); end.clear(); next.clear(); prev.clear();
		mark.resize(n+1);
		next.resize(n+1);
		prev.resize(n+1);
	}
	void push_back(int left,int right,int C){
		c.push_back(C);
		f.push_back(0);
		start.push_back(left);
		end.push_back(right);
	}
	int maxFlow(int start,int end){
		relax();
		destination=end;
		fill(mark.begin(),mark.end(),false);
		int ans=0,temp=0;
		while (temp=dfs(start,INF)){
			ans+=temp;
			fill(mark.begin(),mark.end(),false);
		}
		return(ans);
	}
	void setLimit(int s,int t){
		cap[s]=t;
	}
};
