#include <iostream>
#include <algorithm>

using namespace std;

class IntArray {
private:
        int size;
        int* arr;

public:
        IntArray() : size(0), arr(NULL) {}

        IntArray(const int& s) : size(s), arr(new int[s]) {
                for (int i = 0; i < size; i++)
                        arr[i] = 0;
        }

        IntArray(const int& s, const int& val) : size(s), arr(new int[s]) {
                for (int i = 0; i < size; i++)
                        arr[i] = val;
        }

        IntArray(const IntArray& v) : size(v.size), arr(new int[v.size]) {
                for (int i = 0; i < size; i++)
                        arr[i] = v.arr[i];
        }

        IntArray& operator=(const IntArray& v) {
                if (this == &v) return *this;
                delete[] arr;
                size = v.size;
                arr = new int[size];
                for (int i = 0; i < size; i++)
                        arr[i] = v.arr[i];
                return *this;
        }

        ~IntArray() {
                delete[] arr;
        }

        IntArray add(const IntArray& v) const {
                if (size != v.size) {
                        cout << "Size mismatch for addition." << endl;
                        return IntArray(0);
                }
                IntArray result(size);
                for (int i = 0; i < size; i++) {
                        result.arr[i] = arr[i] + v.arr[i];
                }
                return result;
        }

        void reverse() {
                for (int i = 0; i < size / 2; i++) {
                        std::swap(arr[i], arr[size - 1 - i]);
                }
        }

        void sort() {
                std::sort(arr, arr + size);
        }

        void print() const {
                for (int i = 0; i < size; i++)
                        cout << arr[i] << " ";
                cout << endl;
        }

        int getSize() const {
                return size;
        }

        int get(int index) const {
                if (index >= 0 && index < size)
                        return arr[index];
                cout << "Error: Index out of range in get()" << endl;
                return -1;
        }

        void set(int index, int value) {
                if (index >= 0 && index < size)
                        arr[index] = value;
                else
                        cout << "Error: Index out of range in set()" << endl;
        }
};

int main() {
        IntArray arr1(3);
        arr1.set(0, 1);
        arr1.set(1, 2);
        arr1.set(2, 3);

        cout << "Array 1: ";
        arr1.print();

        IntArray arr2 = arr1;

        cout << "Array 2 (copy of Array 1): ";
        arr2.print();

        arr2.reverse();

        cout << "Array 2 after reversing: ";
        arr2.print();

        cout << "Array 1 after reversing Array 2: ";
        arr1.print();

        return 0;
}

