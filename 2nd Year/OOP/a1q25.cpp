#include <iostream>
using namespace std;

class Complex {
private:
        float real;
        float imag;

public:
        Complex() : real(0.0f), imag(0.0f) {}

        Complex(const float& r, const float& i) : real(r), imag(i) {}  

        Complex(const Complex& c) : real(c.real), imag(c.imag) {} 

        Complex& operator=(const Complex& c) { 
                if (this != &c) {
                        real = c.real;
                        imag = c.imag;
                }
                return *this;
        }

        void setReal(const float& r) {
                real = r;
        }

        void setImg(const float& i) {
                imag = i;
        }

        float getReal() const {
                return real;
        }

        float getImg() const {
                return imag;
        }

        void disp() const {
                if (imag >= 0)
                        cout << real << " + " << imag << "i" << endl;
                else
                        cout << real << " - " << -imag << "i" << endl;
        }

        Complex sum(const Complex& c) const {
                return Complex(real + c.real, imag + c.imag);
        }
};

int main() {
        Complex c1(2.5f, 3.5f);
        Complex c2(4.0f, -1.5f);

        Complex c3; 
        c3 = c1.sum(c2);

        cout << "Complex number 1: "; c1.disp();
        cout << "Complex number 2: "; c2.disp();
        cout << "Sum of complex numbers: "; c3.disp();

        return 0;
}

