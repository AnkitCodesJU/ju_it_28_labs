#include<iostream>
using namespace std;
#define low 0
#define high 100
int main()
{
double f;
for(int i=low;i<=high;i++){
	f=((9.0*i)/5.0)+32;
	cout<<i<<"C ="<<f<<"F"<<endl;
}

return 0;
}
