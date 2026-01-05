#include<iostream>
#include<cstdlib>
using namespace std;
inline int add(const int &a,const int &b,const int &c){
	return a+b+c;
}
int main(int argc, char* argv[]) {
if (argc != 4) {
cout << "Usage: " << argv[0] << " num1 num2 num3" << endl;
return 1;
}
cout << "Sum = " << add(atoi(argv[1]), atoi(argv[2]), atoi(argv[3])) << endl;
return 0;
}
