struct KMP{
	char st[MAX_N];
	int next[MAX_N],n;
	KMP(const string &s){
		for (int i=0;i<s.size();i++) st[i+1]=s[i];
		n=s.size();
		next[1]=next[0]=0;
		for (int i=2;i<=n;i++){
			next[i]=next[i-1];
			while (next[i] && st[next[i]+1]!=st[i]) next[i]=next[next[i]];
			if (st[next[i]+1]==st[i]) next[i]++;
		}
	}
	int IsIn(const string &s){
		int ans=0,pointer=0;
		for (int i=0;i<s.size();i++){
			while ((pointer==n) || (pointer && st[pointer+1]!=s[i])) pointer=next[pointer];
			if (st[pointer+1]==s[i]) pointer++;
			ans+=(pointer==n);
		}
		return(ans);
	}
};
