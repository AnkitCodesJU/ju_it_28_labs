#include<iostream>
using namespace std;
#define num 6
void fact(const int &n)
{
int p=1;
for(int i=1;i<=n;i++){
        p*=i;
        cout<<i<<"! = "<<p<<endl;
}
}
int main(){
	int n=num;
	fact(n);
}
