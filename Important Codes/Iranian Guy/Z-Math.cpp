long long mod(long long s,long long t){ return(((s%t)+t)%t);
}

bool axbyc(long long a,long long b,long long c,long long &x,long long &y){
	if (a > b) 
		return(axbyc(b,a,c,y,x));

	if (a == 0){
		x=y=0;
		if (c % b != 0) return(false);
		else{
			x=0; y=c/b;
			return(true);
		}
	}

	if (!axbyc(b%a,a,c,x,y))
		return(false);

	// x*(b%a) + y*a = c --> x*b - x *((b/a)*a) + y*a = c
	// -> x*b + (y-x*(b/a)) * a = c
	long long Y=mod(x,a);
	long long X=(c-Y*b)/a;
	x=X; y=Y;
	return(true);
}

bool firstNumber(vector<pair<int,int> > all,long long &res){ 
	//   res % all[i].firsh will be all[i].second if it returns true

	vector<pair<long long,long long> > conditions;
	for (int i=0;i<all.size();i++){
		for (int j=2;j*j<=all[i].first;j++){
			bool find=false;
			while (all[i].first%j == 0){
				if (find)
					conditions.back().first*=j;
				else
					conditions.push_back(pair<long long,long long>(j,0));
				conditions.back().second=all[i].second%conditions.back().first;
				find=true;
				all[i].first/=j;
			}
		}
		if (all[i].first > 1)
			conditions.push_back(pair<long long,long long>(all[i].first,all[i].second%all[i].first));
	}

	for (int i=0;i<conditions.size();i++)
		for (int j=0;j<conditions.size();j++) if (i < conditions.size() && j!=i && conditions[j].first % conditions[i].first == 0){
			if (conditions[j].second % conditions[i].first != conditions[i].second) return(false);
			swap(conditions.back(),conditions[i]);
			conditions.pop_back();
			i--;
		}

		while (conditions.size() > 1){
			pair<long long,long long> x=conditions.back();
			conditions.pop_back();
			pair<long long,long long> y=conditions.back();
			conditions.pop_back();

			long long a,b;
			if (y.second < x.second) swap(x,y);
			axbyc(x.first,y.first,y.second-x.second,a,b);
			conditions.push_back(pair<long long,long long>(x.first*y.first,mod(x.first*a+x.second,x.first*y.first)));
		}
		res=conditions[0].second;
		return(true);
}
