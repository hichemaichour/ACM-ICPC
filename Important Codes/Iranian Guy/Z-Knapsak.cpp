const int INF=1<<25;

struct min_every_k{
	vector<int> ans;
	deque<int> qu,where;
	int k;
	min_every_k(int s){ k=s;
	}
	void push_back(int s){
		while (qu.size() && qu.back() > s){
			qu.pop_back();
			where.pop_back();
		}

		qu.push_back(s);
		where.push_back(ans.size()+1);

		while (int(ans.size())+1-k >= where.front()){
			qu.pop_front();
			where.pop_front();
		}

		ans.push_back(qu.front());
	}
	int get_min(int last){
		return(ans[last-1]);
	}
	inline int size(){ return(ans.size());
	}
};

struct knapsak{
	vector<int> num,number,cost;
	void push_back(int x,int number=INF,int cost=1){
		this->num.push_back(x);
		this->number.push_back(number);
		this->cost.push_back(cost);
	}

	bool can_divide(int s){
		vector<bool> dyna;
		dyna.resize(s+1);
		dyna[0]=true;
		for (int i=0;i<num.size();i++) for (int j=num[i];j<dyna.size();j++)
			dyna[j]=dyna[j] | dyna[j-num[i]];
		return(dyna.back());
	}

	int min_cost_divide(int s){
		vector<int> dyna;
		dyna.resize(s+1);
		for (int i=0;i<dyna.size();i++) dyna[i]=INF;
		dyna[0]=0;
		for (int i=0;i<num.size();i++){
			vector<int> temp;
			temp.resize(dyna.size());
			for (int a=0;a<num[i];a++){
				min_every_k x(number[i]);
				for (int j=0;j*num[i]+a < dyna.size();j++){
					x.push_back(dyna[j*num[i]+a]-cost[i]*j);
					temp[j*num[i]+a]=x.get_min(x.size())+j*cost[i];
				}
			}
			for (int a=0;a<dyna.size();a++) dyna[a]=min(dyna[a],temp[a]);
		}
		return(dyna.back());
	}
};
