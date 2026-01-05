/* 12. Write a function Strcpy to copy one string to another with suitable formal parameters declarations. Following
 * points must be considered.
 * a) Source string must not get modified
 * b) Target string is allowed to get modified
 * c) The Pointers must be constant pointers.
 * Use it to copy some strings.  */
#include<iostream>
using namespace std;
char* s1=new char[3];
char* s2=new char[3];
void Strcpy( const char* const src, char* const dest){
        int i=0;
	while(src[i]!='\0'){
		dest[i]=src[i];
		i++;
	}
	dest[i]='\0';
}
	


int main(){

        s1[0]='a';s1[1]='b';s1[3]='\0';
        Strcpy(s1,s2);
        cout<<"Copied value "<<s1<< " to destination string which got "<<s2<<endl;
        return 0;

}
