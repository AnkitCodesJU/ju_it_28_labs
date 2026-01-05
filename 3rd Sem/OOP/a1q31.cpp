#include <iostream>
#include <cmath>
using namespace std;
class Complex{
private:
	double real,imag;
public:
	Complex():real(0),imag(0){}
	Complex(const double &x, const double &y) {
     	         real = x;
       		 imag = y;
        }
	Complex& operator=(const Complex& other){
		if(this!=&other){
			real=other.real;
			imag=other.imag;	
		}
		return *this;
	}
	Complex operator+(const Complex& b)const{
		double nr=real + b.real;
		double ni=imag + b.imag;
		return Complex(nr,ni);	
	}
	Complex operator-(const Complex& b)const{
		return Complex(real - b.real,imag-b.imag);
	}
	Complex operator*(const Complex& other)const{
		return Complex(
        	    real * other.real - imag * other.imag,
           	    real * other.imag + imag * other.real);
        }
	Complex operator/(const Complex &other)const{
		 double denom = other.real * other.real + other.imag * other.imag;
        	return Complex(
           		  (real * other.real + imag * other.imag) / denom,
          		  (imag * other.real - real * other.imag) / denom );
	}
	void operator()(const double &xx,const double &yy){
		real=xx;
		imag=yy;
	}
	void display(){
		char sign='+';
		if(imag<0) sign=' ';;
		cout<<real<<sign<<imag<<"i"<<endl;
	}
};
// TODO: Overload unary minus    ... implement setImag n setReal methods
int main(){
	Complex c1(4, 5);
    Complex c2;
    c2(2, -3);

    Complex sum = c1 + c2;
    Complex diff = c1 - c2;
    Complex prod = c1 * c2;
    Complex quot = c1 / c2;

    cout << "c1 = "; c1.display(); cout << endl;
    cout << "c2 = "; c2.display(); cout << endl;

    cout << "\nAddition: "; sum.display();
    cout << "\nSubtraction: "; diff.display();
    cout << "\nMultiplication: "; prod.display();
    cout << "\nDivision: "; quot.display();
    cout << endl;

    return 0;
}
