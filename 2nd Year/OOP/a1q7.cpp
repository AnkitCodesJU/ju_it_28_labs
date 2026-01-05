#include<iostream>
using namespace std;
#define num 6
int factorial(const int &n){
	if(n==0 || n==1) return 1;
	return n*factorial(n-1);
}
int main()
{
const int a= num;
int b=factorial(a);
cout<<b<<endl;
return 0;
}
