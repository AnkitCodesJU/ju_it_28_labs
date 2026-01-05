#include<iostream>
#include<math.h>
using namespace std;
class Point{
public:
	int x,y,z;
	Point(const int &a,const int &b,const int &c){
		this->x=a;
		this->y=b;
		this->z=c;
}
	double distance(const Point* a) const{
        	return sqrt(pow(a->x - x, 2) + pow(a->y - y, 2) + pow(a->z - z, 2));
    		}
};
int main(){
	Point* p1=new Point(1,2,3);
	Point* p2=new Point(5,6,7);
	cout<<p1->distance(p2)<<endl;
}
