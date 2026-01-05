#include<iostream>
#include<vector>
using namespace std;
void print(const int* const a){
	for(int i=0;i<=2;i++) cout<<*(a+i)<<" ";
	cout<<"\n";
}
void print(const int* const * const a){


//const int * wil prohibit memory write on **a(no value can chane)
//const * will prohibit memory write on *a(no row can be change to any other *int 
//const a will prohibit a to have any other **int pointer 


	for(int i=0;i<2;i++){
		for(int j=0;j<2;j++) cout<<a[i][j]<<" ";
		cout<<"\n";	
	}
	cout<<"\n";
}
int main(){
	const int row_in_1d=3;
	int* v=new int[row_in_1d];
	v[0]=1;v[1]=2;*(v+2)=3;
	print(v);
	const int row_in_2d=2;
	int **a=new int*[row_in_2d];
	const int col_in_2d=2;
	a[0]=new int[col_in_2d];
	a[1]=new int[col_in_2d];
	a[0][0]=1;a[0][1]=2;a[1][0]=3;a[1][1]=4;
	print(a);
}
