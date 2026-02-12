class Complex {
        int real, imag;

        Complex() {
                real = 0;
                imag = 0;
        }

        Complex(int r) {
                real = r;
                imag = 0;
        }

        Complex(int r, int i) {
                real = r;
                imag = i;
        }

        Complex add(Complex c) {
                return new Complex(real + c.real, imag + c.imag);
        }

        Complex multiply(Complex c) {
                int r = real * c.real - imag * c.imag;
                int i = real * c.imag + imag * c.real;
                return new Complex(r, i);
        }

        void display() {
                if (imag >= 0)
                System.out.println(real + " + " + imag + "i");
                else
                System.out.println(real + " - " + (-imag) + "i");
        }

        public static void main(String[] args) {
                Complex c1 = new Complex(3, 2);
                Complex c2 = new Complex(4, -2);

                Complex sum = c1.add(c2);
                Complex product = c1.multiply(c2);

                sum.display();
                product.display();
        }
}

