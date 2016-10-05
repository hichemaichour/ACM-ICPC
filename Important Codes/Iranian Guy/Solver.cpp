template <class T> 
class Solver{
	struct Equation{
		vector<T> answer,result;
		vector<vector<T> > num;
		int n;

		Equation(int s):n(s){
			num.resize(n+1);
			for (int i=1;i<=n;i++) num[i].resize(n+1);
			answer.resize(n+1);
			result.resize(n+1);
		}

		void solve(){
			vector<int> index;
			for (int i=1;i<=n;i++){
				int last=i;
				for (int j=i+1;j<=n;j++) if (!zero(num[j][i])) last=j;

				for (int j=1;j<=n;j++) swap(num[last][j],num[i][j]);
				swap(answer[last],answer[i]);

				if (!zero(num[i][i]))
					for (int j=1;j<=n;j++) if (j!=i){
						T zarib=num[j][i]/num[i][i];
						for (int k=1;k<=n;k++)
							num[j][k]-=zarib*num[i][k];
						answer[j]-=zarib*answer[i];
					}
			}
			for (int i=1;i<=n;i++) result[i]=answer[i]/num[i][i];
		}
	};

	struct StronglyConnected{
		int n;
		vector<int> sorted,Glo;
		vector<vector<int> > ans,e,re;
		vector<bool> mark;
		StronglyConnected(int s){
			n=s;
			mark.clear();
			mark.resize(n+1);
			e.clear(); re.clear();
			e.resize(n+1);
			re.resize(n+1);
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
			fill(mark.begin(),mark.end(),false);
			for (int i=1;i<=n;i++) if (!mark[sorted[i-1]]){
				Glo.clear();
				dfs(sorted[i-1]);
				ans.push_back(Glo);
			}
			return(ans);
		}
	};
	vector<vector<pair<int,T> > > e;
	vector<T> added;
	int n;
public:
	vector<T> result;
	Solver(int s){
		n=s;
		e.clear();
		e.resize(n+1);
		added.resize(n+1);
	}
	void addConstant(int x,T y){
		added[x]+=y;
	}
	void addVariable(int x,int y,T z){
		e[x].push_back(pair<int,T> (y,z));
	}
	void solve(){
		result.clear();
		result.resize(n+1);
		StronglyConnected mai(n);
		for (int i=1;i<=n;i++)
			for (int j=0;j<e[i].size();j++)
				mai.push_back(i,e[i][j].first);
		vector<vector<int> > component=mai.Components();
		cerr<<component.size()<<endl;
		vector<int> name(n+1);    
		for (int i=0;i<component.size();i++)
			for (int j=0;j<component[i].size();j++)
				name[component[i][j]]=j+1;

		vector<bool> mark(n+1);
		for (int i=component.size()-1;i>=0;i--){
			Equation mai(component[i].size());
			for (int j=0;j<component[i].size();j++){
				mai.num[name[component[i][j]]][name[component[i][j]]]=1;
				for (int k=0;k<e[component[i][j]].size();k++)
					if (!mark[e[component[i][j]][k].first])
						mai.num[name[component[i][j]]][name[e[component[i][j]][k].first]]-=e[component[i][j]][k].second;
					else
						mai.answer[name[component[i][j]]]+=result[e[component[i][j]][k].first]*e[component[i][j]][k].second;
				mai.answer[name[component[i][j]]]+=added[component[i][j]];
			}
			mai.solve();
			for (int j=0;j<component[i].size();j++){
				result[component[i][j]]=mai.result[name[component[i][j]]];
				mark[component[i][j]]=true;
			}
		}
	}
};
