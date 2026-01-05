#include<iostream>
using namespace std;
const float PI=22/7.0;
#define area(r) ((PI)*(r)*(r))
int main()
{
int r;
cout<<"Enter radius"<<endl;
cin>>r;
cout<<area(r)<<endl;
return 0;
}
