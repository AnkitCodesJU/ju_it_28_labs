#include<iostream>
using namespace std;
char* s1=new char[3];
char* s2=new char[3];
void swap( char &a,char &b){
        char temp=a;
        a=b;
        b=temp;
}

int main(){

        s1[0]='a';s1[1]='b';
	s2[0]='c';s2[1]='d';s1[3]='\0';
	s2[3]='\0';
	
        cout<<"Before Swaping: "<<s1<<" "<<s2<<endl;
        
        swap(s1,s2);
        cout<<"after swapping: "<<s1<<" "<<s2<<endl;
        return 0;
}

