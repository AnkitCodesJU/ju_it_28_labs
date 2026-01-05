#include<iostream>
using namespace std;
int maxi(const int &a,const int &b,const int &c){
	int m=a;
	if(b>m) m=b;
	if(c>m) m=c;
	return m;
}
int maxi(const int a[],const int &n){
	int m=a[0];
	for(int i=1;i<n;i++){
		if(a[i]>m) m=a[i];
}
	return m;
}
int main(){
	cout<<"CASE 1"<<endl;
	cout<<maxi(1,2,3)<<endl;
	int *a= new int[3];
	*a=1;*(a+1)=2;*(a+2)=3;
	cout<<"CASE 2"<<endl;
	cout<<maxi(a,3)<<endl;
}
