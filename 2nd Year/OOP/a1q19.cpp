#include<iostream>
#include<math.h>
using namespace std;
class Rectangle{
private:
	int a1,a2,a3,b1,b2,b3;
public:
	Rectangle(const int &pa1,const int &pa2,const int &pa3,const int &pb1,const int &pb2,const int &pb3){
		this->a1=pa1;
		this->a2=pa2;
		this->a3=pa3;
		this->b1=pb1;
		this->b2=pb2;
		this->b3=pb3;
	}
	int geta1()const{return a1;}
	int geta2()const{return a2;}
	int geta3()const{return a3;}
	int getb1()const{return b1;}
	int getb2()const{return b2;}
	int getb3()const{return b3;}
	void seta1(int ua1){a1=ua1;}
	void seta2(int ua2){a2=ua2;}
	void seta3(int ua3){a3=ua3;}
	void setb1(int ub1){b1=ub1;}
	void setb2(int ub2){b2=ub2;}
	void setb3(int ub3){b3=ub3;}

	 double area()const {
		double area = sqrt(pow(a1, 2) + pow(a2, 2) + pow(a3, 2));
		area += sqrt(pow(b1, 2) + pow(b2, 2) + pow(b3, 2));
		return area;


	}
};
int main(){
	Rectangle* r1=new Rectangle(2,3,1,-1,1,-1);
	cout<<r1->area()<<endl;
}
