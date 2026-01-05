#include <iostream>
#include <string>

using namespace std;

#define SUBJECTS 5

class GradeCard {
        static const string department;
        string studentName;
        int rollNumber;
        int semester;
        int marks[SUBJECTS];
        float cgpa;

        void calculateCGPA() {
                int total = 0;
                for (int i = 0; i < SUBJECTS; i++)
                        total += marks[i];
                cgpa = (float)total / SUBJECTS / 10.0f;
        }

public:
        GradeCard(const string& name, const int& roll, const int& sem, const int m[SUBJECTS])
                : studentName(name), rollNumber(roll), semester(sem) {
                for (int i = 0; i < SUBJECTS; i++) {
                        marks[i] = m[i];
                }
                calculateCGPA();
        }

        float getCGPA() const { return cgpa; }
        string getName() const { return studentName; }
        int getRollNumber() const { return rollNumber; }

        void display() const {
                cout << "Dept: " << department << ", Name: " << studentName
                     << ", Roll: " << rollNumber << ", Semester: " << semester
                     << ", CGPA: " << cgpa << endl;
        }
};

const string GradeCard::department = "IT";

int main() {
        const int numStudents = 3;
        const int semester = 3;

        GradeCard* students[numStudents];

        int marks1[SUBJECTS] = {100, 100, 100, 100, 100};
        int marks2[SUBJECTS] = {75, 80, 72, 68, 70};
        int marks3[SUBJECTS] = {95, 98, 100, 97, 96};

        students[0] = new GradeCard("Ankit", 101, semester, marks1);
        students[1] = new GradeCard("SRC", 102, semester, marks2);
        students[2] = new GradeCard("UPI", 103, semester, marks3);

        for (int i = 0; i < numStudents; i++) {
                students[i]->display();
        }

        const GradeCard* topStudent = students[0];
        for (int i = 1; i < numStudents; i++) {
                if (students[i]->getCGPA() > topStudent->getCGPA()) {
                        topStudent = students[i];
                }
        }

        cout << "\nStudent with highest CGPA:" << endl;
        cout << "Name: " << topStudent->getName()
             << ", Roll Number: " << topStudent->getRollNumber()
             << ", CGPA: " << topStudent->getCGPA() << endl;

        for (int i = 0; i < numStudents; i++) {
                delete students[i];
        }

        return 0;
}

