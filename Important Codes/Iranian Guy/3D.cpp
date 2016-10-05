struct Point{
	double x,y,z;
	Point (double a=0,double b=0,double c=0){ x=a; y=b; z=c;
	}
	Point operator + (Point s){ return(Point(x+s.x,y+s.y,z+s.z));
	}
	Point operator - (Point s){ return(Point(x-s.x,y-s.y,z-s.z));
	}
	void operator += (Point s){ *this=*this+s;
	}
	void operator -= (Point s){ *this=*this-s;
	}
	double Dot(Point s){ return(x*s.x +y*s.y +z*s.z);
	}
	double Cross(Point s){ return(x*s.x + y*s.y + z*s.z);
	}
	Point operator * (double s){ return(Point(x*s,y*s,z*s));
	}
	Point operator / (double s){ return(Point(x/s,y/s,z/s));
	}
	inline friend ostream & operator << (ostream & tout, Point s){
		return(tout<<'('<<s.x<<','<<s.y<<','<<s.z<<')');
	}
};

struct Line{
	Point A,B;
	Line (Point a,Point b){ A=a; B=b;
	}
};

inline double abs(Point s){ return(sqrt(pow(s.x,2)+pow(s.y,2)+pow(s.z,2)));
}

struct Plane{
	Point Vector,one;
	inline Point RandomPoint(){
		Point A(rand()%100,rand()%100,rand()%100),B(rand()%100,rand()%100,rand()%100);
		return(A-B*(Vector.Dot(A)/Vector.Dot(B))+one);
	}
	inline bool IsOn(Point s){
		return(abs(Vector.Dot(s-one)) < EPS);
	}
	inline Line RandomLine(){ return(Line(RandomPoint(),RandomPoint()));
	}
	inline Point Intersect(Line s){
		if (IsOn(s.A)) return(s.A);
		return(s.A-s.B*((Vector.Dot(s.A)-Vector.Dot(one))/Vector.Dot(s.B)));
	}
	inline Line Intersect (Plane s){
		return(Line(Intersect(s.RandomLine()),
			Intersect(s.RandomLine())));
	}
};
