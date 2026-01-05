#include<iostream>
using namespace std;
int num1=2;
int num2=3;
void swapval(int a,int b){//doesn't change values a and b as call by value function fails to commit change to the actual parameter
	int temp=a;
	a=b;
	b=temp;
}
void swapref(int &a,int &b){//Changes the actual parameter as well coz &a and &b refer to the same memory location or address as that of the actual parameter
	int temp=a;
	a=b;
	b=temp;
}

int main(){
	cout<<"Before swapping"<<endl;
	cout<<num1<<" "<<num2<<endl;
	
	cout<<"Call by Value"<<endl;
	swapval(num1,num2);
	cout<<num1<<" "<<num2<<endl;
	
	cout<<"Call by Reference"<<endl;
	swapref(num1,num2);
	cout<<num1<<" "<<num2<<endl;
	return 0;
}
