#include<stdio.h>
#include<string.h>
struct student{
	char name[50];
	char address[100];
	int marks[5];//0 for maths and 1 for physics
};
void inputVal(struct student *s){
	printf("Enter name: \n");
	scanf("%s",s->name);
	printf("Enter address: \n");
	scanf("%s",s->address);
	int i;
	for(i=0;i<5;i++){
		printf("Enter marks for subject %d: \n",i+1);
		scanf("%d",&s->marks[i]);
	}
	
}
void printFailed(struct student *s,int n){
	printf("students who failed in minimum three subject \n");
	int i,j;
	for(i=0;i<5;i++){
		int fc=0;
		for(j=0;j<5;j++){
			if(s->marks[j]<40) fc++;
		}
		if(fc>=3){
			printf("Name: %s.Address: %s \n",s->name,s->address);
			}
		s++;	
	}
}
void printPassed(struct student *s,int n){
	int i,j;
	printf("students who passed in minimum three subject \n");
	for(i=0;i<5;i++){
		int fc=0;
		for(j=0;j<5;j++){
			if(s->marks[j]>40) fc++;
		}
		if(fc>=3){
			printf("Name: %s.Address: %s \n",s->name,s->address);
			}
		s++;	
	}
}
void max_in_maths(struct student *s,int n){
	int max_marks=-1;
	int i,j;
	struct student *max_student=NULL;
	for(i=0;i<n;i++){
		if(s->marks[0]>max_marks){
			max_marks=s->marks[0];
			max_student=s;
		}
		s++;
	}
	if(max_student!=NULL){
		printf("Student with maximum marks in maths : \n");
		printf("Name %s , Address %s,Marks: %d \n",max_student->name,max_student->address ,max_student->marks[0]);
	}
}

void min_in_phy(struct student *s,int n){
	int min_marks=101;
	int i,j;
	struct student *max_student=NULL;
	for(i=0;i<n;i++){
		if(s->marks[1]<min_marks){
			min_marks=s->marks[0];
			max_student=s;
		}
		s++;
	}
	if(max_student!=NULL){
		printf("Student with minimum marks in phy : \n");
		printf("Name %s , Address %s,Marks: %d \n",max_student->name,max_student->address ,max_student->marks[0]);
	}
}
void highest_avg(struct student *s,int n){
	float max=-1.0;
	int i,j;
	struct student *max_student=NULL;
	for(i=0;i<n;i++){
		float avg=0.0;
		for( j=0;j<5;j++)
		{
			avg+=(s+i)->marks[j];
			avg/=5.0;
			if(avg>max){
				max=avg;
				max_student=s;
			}
		}
	}
	printf("Name : %s,Average Marks: %f\n",max_student->name,max);	
}
int main(){
	int n;
	printf("Enter number of students ");
	scanf("%d",&n);
	struct student students[n];
	struct student *ptr=students;
	for(int i=0;i<n;i++){
		inputVal(ptr+i);
		
	}
	int choice,k;
	for(k=0;k<100;k++){
		printf("\n Menu \n");
		printf("1.Find the name of students who have passed and failed in minimum of 3 sujects\n");
		printf("2.Show the record of the student who has maximum marks in mathematics\n");
		printf("3.Show the record of the student who got minimum in physics\n");
		printf("4.Show the record of the student whose avg marks is maximum\n");
		printf("5.Print the record of student with name  and total \n");
		printf("0.Exit\n");
		printf("Enter choice\n");
		int choice;
		scanf("%d",&choice);
		switch(choice){
		case 1:
			printPassed(students,n);
			printFailed(students,n);
			break;
		case 2:
			max_in_maths(students,n);
			break;	
		case 3:
			min_in_phy(students,n);
			break;
		case 4:
			highest_avg(students, n);	
			break;
		case 5:
			printf("Records of students with total marks: \n");
			int i,j;
			for(i=0;i<n;i++){
				int total=0;
				for(j=0;j<n;j++){
					total+=students[i].marks[j];
				}
				printf("Name %s,Total Marks : %d \n",students[i].name,total);
			}	
			break;
		case 0:		
			printf("Exiting");
			break;
			
		default:
			printf("Invalid Choice \n");		
			}
			if(choice==0) break;
			
	}
	return 0;
}










