#include<iostream>
#include<cmath>
using namespace std;
class Point{
private: 
	int x,y;
public:
	Point():x(0),y(0){}
        Point(const int &xx,const int &yy){
		x=xx;
		y=yy;
	}	
	void operator()(const int &xx ,const int &yy){
		x=xx;
		y=yy;
	}
	double operator-(const Point& p){
		double dx=x-p.x;
		double dy=y-p.y;
		return sqrt(dx*dx +dy*dy);
	}
};
int main(){
	Point p1(1,2);
	Point p2;
	p2(2,2);
	double distance=p1-p2;
	cout<<distance<<endl;
}
