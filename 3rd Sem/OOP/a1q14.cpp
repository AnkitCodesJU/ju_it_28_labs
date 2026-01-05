#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

inline int add_inline(const int &a,const int &b,const int &c){return a+b+c;}
int add_normal(const int &a,const int &b,const int &c){
	return a+b+c;
}

int main(int argc,char* argv[]){
	if(argc!=4){cout<<"Usage: "<<argv[0]<<" num1 num2 num3"<<endl;return 1;}
	int x=atoi(argv[1]),y=atoi(argv[2]),z=atoi(argv[3]);
	const int N=100000000;
	int result=0;

	clock_t start=clock();
	for(int i=0;i<N;i++){
		result=add_inline(x,y,z);
	}
	clock_t end=clock();
	cout<<"Inline add time: "<<1000.0*(end-start)/CLOCKS_PER_SEC<<" ms"<<endl;

	start=clock();
	for(int i=0;i<N;i++){
		result=add_normal(x,y,z);
	}
	end=clock();
	cout<<"Normal add time: "<<1000.0*(end-start)/CLOCKS_PER_SEC<<" ms"<<endl;

	cout<<"Final result="<<result<<endl;
	return 0;
}

