#include <iostream>
using namespace std;

inline int add(const int &a, const int &b = 0,const  int &c = 0) {
    return a + b + c;
}

int main() {
    cout << "Call with three args: add(5, 10, 15) = " << add(5, 10, 15) << endl;
    cout << "Call with two args:   add(5, 10) = " << add(5, 10) << endl;
    cout << "Call with one arg:    add(5) = " << add(5) << endl;
    return 0;
}

