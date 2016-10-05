string firstCycle(string s){
	vector<int> Glo;
	vector<bool> mark(s.size(),true);
	for (int i=0;i<s.size();i++) Glo.push_back(i);
	for (int i=0;i<s.size();i++){
		char Min=s[(Glo[0]+i)%s.size()];
		for (int j=0;j<Glo.size();j++)
			Min=min(Min,s[(Glo[j]+i)%s.size()]);

		for (int j=0;j<Glo.size();j++)
			if (s[(Glo[j]+i)%s.size()] != Min) mark[Glo[j]]=false;

		for (int j=0;j<Glo.size();j++) if (mark[Glo[j]])
			mark[(Glo[j]+i+1)%s.size()]=false;
		for (int j=0;j<Glo.size();j++)
			if (!mark[Glo[j]]){
				swap(Glo.back(),Glo[j]);
				Glo.pop_back();
				j--;
			}
	}
	return(s.substr(Glo[0])+s.substr(0,Glo[0]));
}
