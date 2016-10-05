inline bool zero(double s){ return(abs(s) < EPS);
}

template <class T> struct Matrix{
	vector<vector<T> > num;
	int n;
	vector<T> & operator [] (int s){ return(num[s]);
	}
	Matrix(int n){
		num.resize(n+1);
		this->n=n;
		for (int i=0;i<num.size();i++) num[i].resize(n+1);
	}
	T determinant(){
		vector<vector<T> > x=num;
		T ans=1;
		for (int i=1;i<=n;i++){
			for (int j=i+1;j<=n;j++) 
				if (!zero(x[j][i])){
					swap(x[i],x[j]);
					ans*=-1;
				}
				if (zero(x[i][i])) return(0);
				for (int j=1;j<=n;j++) if (j!=i){
					T zarib=x[j][i]/x[i][i];
					for (int k=1;k<=n;k++) x[j][k]-=x[i][k]*zarib;
				}
		}
		for (int i=1;i<=n;i++) ans*=x[i][i];
		return(ans);
	}
};

template <class T>
Matrix<T> operator * (const Matrix<T> &a,const Matrix<T> &b){
	Matrix<T> ans(a.n);
	assert(a.n == b.n);
	for (int i=1;i<=a.n;i++)
		for (int j=1;j<=b.n;j++)
			for (int k=1;k<=b.n;k++)
				ans.num[i][j]=ans.num[i][j]+a.num[i][k]*b.num[k][j];
	return(ans);
}

template <class T>
Matrix<T> pow(const Matrix<T> &a,int b){
	if (b==0){
		Matrix<T> ans=a;
		for (int i=1;i<=ans.n;i++)
			for (int j=1;j<=ans.n;j++)
				ans.num[i][j]=i==j;
		return(ans);
	}
	Matrix<T> res=pow(a,b/2);
	res=res*res;
	if (b*2) res=res*a;
	return(res);
}

template <class T> struct Equation{
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
