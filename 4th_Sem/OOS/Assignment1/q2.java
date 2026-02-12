import  java.util.*;
class Student{
        String name;
        double  marks1,marks2,marks3;

        Student(String n,double m1,double m2,double m3){
                name = n;
                marks1 = m1;
                marks2 = m2;
                marks3 = m3;
        }
        double average(){
                return (marks1 + marks2 + marks3)/3.0;
        }
        void display(){
                double total = marks1 + marks2 + marks3;
                System.out.println(name + " has scored a total of "+ total +"/300");
        }
        public static void main(String args[]){
                Student student = new Student("Ankit",95,98,100);
                student.display();
                System.out.println(student.name + " has scored a total average of "+ student.average() +"/300");

        }
}
