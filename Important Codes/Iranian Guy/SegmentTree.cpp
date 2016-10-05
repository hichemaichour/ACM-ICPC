template <class Type,class Int=unsigned int,Int End=INT_MAX/2,Type Default=0>
class add_sum_tree{
	class node{
	public:
		Type Itself,Itschilds;
		node *next[2];
		node(){ Itself=0,Itschilds=0; next[0]=next[1]=0;
		}
		node* child(int s){
			if (!next[s]) next[s]=new node();
			return(next[s]);
		}
	}*root;
public:
	add_sum_tree(){ root=new node(); root->Itself=Default;
	}
	void add(Int where,const Type &s){
		Int A=0,B=End;
		node *temp=root;
		Int Mid;
		while (B>where){
			temp->Itschilds+=(where-A+1)*s;
			Mid=(A+B)/2;
			if (Mid >= where){
				temp=temp->child(0);
				B=Mid;
			}else{
				temp->child(0)->Itself+=s;
				temp=temp->child(1);
				A=Mid+1;
			}
		}
		temp->Itself+=s;
	}
	void add(Int a,Int b,const Type &s){
		add(b,s);
		if (a) add(a-1,Type(0)-s);
	}
	Type sum(Int where){
		Int A=0,B=End,Mid;
		Type ans=0;
		node *temp=root;
		while (B>where){
			ans+=temp->Itself*(where-A+1);
			Mid=(A+B)/2;
			if (Mid >= where){
				temp=temp->child(0);
				B=Mid;
			}else{
				if (temp->next[0])
					ans+=(temp->next[0]->Itself)*(Mid-A+1)+temp->next[0]->Itschilds;
				temp=temp->child(1);
				A=Mid+1;
			}
		}
		ans+=temp->Itschilds+temp->Itself*(B-A+1);
		return(ans);
	}
	Type sum(Int a,Int b){
		if (a) return(sum(b)-sum(a-1));
		return(sum(b));
	}
};

template <class Type,class Int=unsigned int,Int End=INT_MAX/2,Type Default=0>
class min_max_tree{
	class node{
	public:
		Int x,y;
		Type _min,_max;
		node *next[2];
		node(){
		}
		node(Int a,Int b,Type Min,Type Max){ x=a; y=b; _min=Min; _max=Max; next[0]=next[1]=0;
		}
		node *child(int s){
			if (!next[s]){
				if (s==0) next[s]=new node(x,(x+y)/2,_min,_max);
				else next[s]=new node((x+y)/2+1,y,_min,_max);
			}
			return(next[s]);
		}
		void set(Int a,Int b,const Type &s){
			a=std::max(a,x); b=std::min(b,y);
			if (x==a && y==b){
				_min=_max=s;
				next[0]=next[1]=0;
				return;
			}
			if (a <= (x+y)/2) child(0)->set(a,b,s);
			if (b > (x+y)/2) child(1)->set(a,b,s);
			_max=std::max(child(0)->_max,child(1)->_max);
			_min=std::min(child(0)->_min,child(1)->_min);
		}
		Type max(Int a,Int b){
			a=::max(x,a); b=std::min(y,b);
			if ((a==x && b==y) || (!next[0] && !next[1])) return(_max);
			if (a > (x+y)/2) return(child(1)->max(a,b));
			if (b <= (x+y)/2) return(child(0)->max(a,b));
			return(std::max(child(0)->max(a,b),child(1)->max(a,b)));
		}
		Type min(Int a,Int b){
			a=std::max(x,a); b=std::min(y,b);
			if ((a==x && b==y) || (!next[0] && !next[1])) return(_min);
			if (a > (x+y)/2) return(child(1)->min(a,b));
			if (b <= (x+y)/2) return(child(0)->min(a,b));
			return(std::min(child(0)->min(a,b),child(1)->min(a,b)));
		}
	}*root;
public:
	min_max_tree(){ root=new node(0,End,Default,Default);
	}
	void set(Int a,Int b,Type c){ root->set(a,b,c);
	}
	inline Type max(Int a,Int b){ return(root->max(a,b));
	}
	inline Type min(Int a,Int b){ return(root->min(a,b));
	}
};


// we can add or remove numbers from intervals, and get number of elemens with positive value
class true_false_tree{
public:
	struct node{
		Pair Min;
		int Itself,x,y;
		node *next[2];
		node(int a,int b){ x=a; y=b; Itself=0; next[0]=next[1]=0; Min=Pair(b-a+1,0);
		}
		void relax(){
			if (!next[0] && !next[1]) Min=Pair(y-x+1,Itself);
			if (child(0)->Min.second == child