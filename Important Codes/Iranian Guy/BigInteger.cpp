class BigInteger{
public:
	vector<int> num;
	bool neg;

	inline void relax(){
		for (int i=0;i+1<(int)num.size();i++){
			num[i+1]+=num[i]/10;
			num[i]%=10;
		}

		if (num.size())
			while (num.back() >= 10){
				num.push_back(num.back()/10);
				num[num.size()-2]%=10;
			}

			while (num.size() > 1 && num.back() == 0) num.pop_back();
			if (num.size() == 1 && num[0] == 0) neg=false;
	}

	bool operator < (BigInteger s)const{
		if (neg != s.neg) return(neg);
		if (num.size() != s.num.size())
			return((num.size() < s.num.size())^neg);
		for (int i=num.size()-1;i>=0;i--)
			if (num[i] != s.num[i])
				return((num[i] < s.num[i])^neg);
		return(false);
	}

	BigInteger negative()const{
		BigInteger ans=*this;
		ans.neg=!ans.neg;
		ans.relax();
		return(ans);
	}

	BigInteger(int s=0){
		num.clear();
		neg=s < 0;
		num.push_back(abs(s));
		relax();
	}

	BigInteger operator + (BigInteger s)const{
		if (s.neg) return(operator - (s.negative()));
		if (neg) return(s - negative());
		BigInteger ans=*this;
		if (ans.num.size() < s.num.size()) ans.num.resize(s.num.size());
		for (int i=0;i<(int)s.num.size();i++) 
			ans.num[i]+=s.num[i];
		ans.relax();
		return(ans);
	}

	BigInteger operator - (BigInteger s)const{
		if (s.neg) return(operator + (s.negative()));
		if (neg) return((s+negative()).negative());
		if (operator < (s))
			return((s-(*this)).negative());
		BigInteger ans=*this;
		for (int i=0;i<(int)ans.num.size();i++){
			if (i < s.num.size())
				ans.num[i] -= s.num[i];
			if (ans.num[i] < 0){
				ans.num[i+1]--;
				ans.num[i]+=10;
			}
		}
		ans.relax();
		return(ans);
	}

	BigInteger operator * (BigInteger s)const{
		if (neg) return((negative()*s).negative());
		if (s.neg) return((operator * (s.negative())).negative());
		BigInteger ans;
		ans.num.resize(s.num.size()+num.size()-1);
		for (int i=0;i<(int)num.size();i++)
			for (int j=0;j<(int)s.num.size();j++)
				ans.num[i+j]+=num[i]*s.num[j];
		ans.relax();
		return(ans);
	}

	BigInteger operator / (BigInteger s)const{
		if (s.num.size() == 1 && s.num[0] == 0) 
			throw ("BigInteger : division by zero!!");

		if (neg) return((negative()/s).negative());
		if (s.neg) return((operator / (s.negative())).negative());
		BigInteger ans;
		ans.num.resize(max((int)num.size()-(int)s.num.size()+2,1));
		BigInteger sum;
		for (int i=(int)ans.num.size()-1;i>=0;i--){

			BigInteger x;
			x.num.resize(s.num.size()+i);
			for (int j=0;j<(int)s.num.size();j++)
				x.num[j+i]=s.num[j];
			x.relax();

			while (true){
				sum=sum+x;
				if (operator < (sum)){
					sum=sum-x;
					break;
				}
				ans.num[i]++;
			}
		}
		ans.relax();
		return(ans);
	}

	BigInteger operator % (BigInteger s)const{
		if (neg) return((negative()%s).negative());
		if (s.neg) return(operator % (s.negative()));
		return(operator - (s 
			* (operator / (s))));
	}
};

long long intValue(BigInteger s){
	long long ans=0;
	for (int i=(int)s.num.size()-1;i>=0;i--) ans=ans*10+s.num[i];
	if (s.neg) return(ans*-1);
	else return(ans);
}

ostream & operator << (ostream & tout,BigInteger s){
	if (s.neg) tout<<'-';
	for (int i=(int)s.num.size()-1;i>=0;i--)
		tout<<s.num[i];
	return(tout);
}

BigInteger gcd(BigInteger a,BigInteger b){
	if (a.neg) return(gcd(a.negative(),b));
	if (b.neg) return(gcd(a,b.negative()));
	if (a < b) swap(a,b);
	if (b.num.size() == 1 && b.num[0] == 0) return(a);
	return(gcd(b,a%b));
}

class Rational{
public:
	BigInteger a,b;
	Rational(BigInteger a,BigInteger b):a(a),b(b){
		BigInteger temp=gcd(a,b);
		a=a/temp;
		b=b/temp;
		if (a.neg){
			a=a.negative();
			b=b.negative();
		}
	}
	Rational(long long s){
		a=s;
		b=1;
	}
	Rational operator + (Rational s)const{
		return(Rational(a*s.b+b*s.a,b*s.b));
	}
	Rational operator - (Rational s)const{
		return(Rational(a*s.b-b*s.a,b*s.b));
	}
	Rational operator * (Rational s)const{
		return(Rational(a*s.a,b*s.b));
	}
	Rational operator / (Rational s)const{
		return(Rational(a*s.b,b*s.a));
	}
};

long double doubleValue(Rational s){
	BigInteger x=s.a;
	for (int i=1;i<=2;i++) x=x*1000000;
	stringstream tin;
	tin<<(x/s.b);
	string temp;
	tin>>temp;
	while (temp.size() < 13) temp='0'+temp;
	string New;
	for (int i=0;i<temp.size();i++){
		if (i+12 == temp.size())
			New+='.';
		New+=temp[i];
	}
	stringstream gin;
	gin<<New;
	long double ans;
	gin>>ans;
	return(ans);
}
