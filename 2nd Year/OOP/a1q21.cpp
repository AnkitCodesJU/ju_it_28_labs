#include <iostream>
using namespace std;

class Vector {

        public:
                int size;
                int *arr;

        public:

                Vector(const int s) {
                        size = s;
                        arr = new int[size];
                        for (int i = 0; i < size; i++) {
                                arr[i] = 0;
                        }
                }

                Vector(const int s, const int val) {
                        size = s;
                        arr = new int[size];
                        for (int i = 0; i < size; i++) {
                                arr[i] = val;
                        }
                }

                Vector(const Vector& v) {
                        size = v.size;
                        arr = new int[size];
                        for (int i = 0; i < size; i++)
                                arr[i] = v.arr[i];
                }

                Vector& operator=(const Vector& v) {
                        if (this == &v) return *this;
                        delete[] arr;
                        size = v.size;
                        arr = new int[size];
                        for (int i = 0; i < size; ++i)
                                arr[i] = v.arr[i];
                        return *this;
                }

                ~Vector() {
                        delete[] arr;
                }

                Vector add(const Vector& v) const {
                        if (size != v.size) {
                                cout << "Size mismatch in addition\n" << endl;
                                return Vector(0);
                        }

                        Vector ans(size);
                        for (int i = 0; i < size; i++) {
                                ans.arr[i] = this->arr[i] + v.arr[i];
                        }
                        return ans;
                }

                Vector substract(const Vector& v) const {
                        if (size != v.size) {
                                cout << "Size mismatch in substraction\n" << endl;
                                return Vector(0);
                        }

                        Vector ans(size);
                        for (int i = 0; i < size; i++) {
                                ans.arr[i] = this->arr[i] - v.arr[i];
                        }
                        return ans;
                }

                bool isEqual(const Vector& v) const {
                        if (size != v.size) {
                                cout << "Size mismatch in equality\n" << endl;
                                return false;
                        }

                        for (int i = 0; i < size; i++) {
                                if (this->arr[i] != v.arr[i])
                                        return false;
                        }
                        return true;
                }

                bool isLessThan(const Vector& v) const {
                        if (size != v.size) {
                                cout << "Size mismatch in lesser than function\n" << endl;
                                return false;
                        }

                        for (int i = 0; i < size; i++) {
                                if (this->arr[i] >= v.arr[i])
                                        return false;
                        }
                        return true;
                }

                bool isGreaterThan(const Vector& v) const {
                        if (size != v.size) {
                                cout << "Size mismatch in greater than function\n" << endl;
                                return false;
                        }

                        for (int i = 0; i < size; i++) {
                                if (this->arr[i] <= v.arr[i])
                                        return false;
                        }
                        return true;
                }
};

int main() {
        Vector a(5, 0);
        Vector b(5, 1);

        a.arr[0] = 4;
        a.arr[1] = 5;
        a.arr[2] = 2;
        a.arr[3] = 7;
        a.arr[4] = 18;

        cout << "A : 4 5 2 7 18" << endl;
        cout << "B : 1 1 1 1 1" << endl;

        Vector c(5, 0);
        c = a.add(b);

        cout << "Resultant array after A + B" << endl;
        for (int i = 0; i < 5; i++) {
                cout << c.arr[i] << " ";
        }
        cout << endl;

        Vector d(5, 0);
        d = a.substract(b);

        cout << "Resultant array after A - B" << endl;
        for (int i = 0; i < 5; i++) {
                cout << d.arr[i] << " ";
        }
        cout << endl;

        bool alessb = a.isLessThan(b);
        bool agreaterb = a.isGreaterThan(b);
        bool aequalb = a.isEqual(b);

        cout << "0 means false, 1 means true" << endl;
        cout << "Vector A less than Vector B?  - " << alessb << endl;
        cout << "Vector A greater than Vector B?  - " << agreaterb << endl;
        cout << "Vector A equal to Vector B?  - " << aequalb << endl;

        return 0;
}

