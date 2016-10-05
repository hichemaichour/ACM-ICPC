struct node{
	Pair e[MAX_ALPHA];
	node *next[MAX_ALPHA];
	bool child;
	int dep;
	inline int size(int s)const{ return(e[s].second-e[s].first+1);
	}
	node(int s=0,bool t=false){
		dep=s; child=t;
		for (int i=0;i<MAX_ALPHA;i++) e[i]=Pair(0,0);
		for (int i=0;i<MAX_ALPHA;i++) next[i]=0;
	}
	bool contain(int where,const string &st,int t){
		if (!child) return(false);
		int remain=st.size()-where-dep;
		if (remain==0) return(next[t]!=0);
		if (!next[st[dep+where]] || size(st[dep+where]) <= remain) return(false);
		return(st[e[st[dep+where]].first+remain] == t);
	}
	node* AddEdge(int where,const string &st,int t){
		if (!child) dep=st.size()-where;
		child=true;
		int remain=st.size()-where-dep;
		if (remain==0){
			e[t]=Pair(st.size(),INF);
			next[t]=new node();
			return(next[t]);
		}
		int what=st[where+dep];
		node *temp=new node(st.size()-where,true);
		temp->e[t]=Pair(st.size(),INF);
		temp->next[t]=new node();
		temp->e[st[e[what].first+remain]]=e[what];
		temp->e[st[e[what].first+remain]].first+=remain;
		temp->next[st[e[what].first+remain]]=next[what];
		next[what]=temp;
		e[what].second=e[what].first+remain-1;
		return(temp->next[t]);
	}
};

void fix(const string &st,node *&pointer,int where){
	while (pointer->child && pointer->size(st[pointer->dep+where])+pointer->dep+where <= st.size())
		pointer=pointer->next[st[pointer->dep+where]];
}

struct SuffixTree{
	vector<node*> where;
	string Mai;
	node *root;
	int start;
	void push_back(int s){
		while (start < where.size() && !where[start]->child) start++;
		for (int i=start; i<where.size();i++){
			fix(Mai,where[i],i);
			if (where[i]->contain(i,Mai,s)) break;
			else where[i]=where[i]->AddEdge(i,Mai,s);
		}
		if (root->next[s]) where.push_back(root);
		else  where.push_back(root->AddEdge(where.size(),Mai,s));
		Mai+=char(s);
	}
	SuffixTree(const string &s=""){ 
		root=new node(); start=0; Mai=""; where.clear();
		for (int i=0;i<s.size();i++) push_back(s[i]);
	}
};
