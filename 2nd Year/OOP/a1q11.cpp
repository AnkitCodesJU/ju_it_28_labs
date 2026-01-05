#include<iostream>
using namespace std;
#define num 6
int fact(const int &n){
        int i,p=1;
	for(i=1;i<=n;i++){
		p*=i;		
}	return p;
}

int main(){
        int n=num;
	cout<<fact(n)<<endl;
        return 0;
}
