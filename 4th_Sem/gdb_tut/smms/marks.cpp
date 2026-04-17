#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <stdexcept>
#include <algorithm>
#include <iomanip>

using namespace std;

struct Student {
    string rollNo;
    string name;
    int math;
    int physics;
    int chemistry;
    int total;
};



vector<Student> loadData(const string& filename) {
    vector<Student> students;
    ifstream file;
    
    try {
        file.open(filename);
        if (!file.is_open()) {
            throw runtime_error("Error: Could not open " + filename + ". Ensure the file exists.");
        }

        string line, word;
        getline(file, line); 

        while (getline(file, line)) {
            stringstream ss(line);
            Student s;
            
            getline(ss, s.rollNo, ',');
            getline(ss, s.name, ',');
            
            getline(ss, word, ','); s.math = stoi(word);
            getline(ss, word, ','); s.physics = stoi(word);
            getline(ss, word, ','); s.chemistry = stoi(word);
            getline(ss, word, ','); s.total = stoi(word);
            
            students.push_back(s);
        }
    } catch (const exception& e) {
        cerr << e.what() << endl;
    }
    return students;
}

void saveData(const string& filename, const vector<Student>& students) {
    ofstream file;
    try {
        file.open(filename);
        if (!file.is_open()) {
            throw runtime_error("Error: Could not open " + filename + " for writing.");
        }

        file << "RollNo,Name,Math,Physics,Chemistry,Total\n";
        for (const auto& s : students) {
            file << s.rollNo << "," << s.name << "," 
                 << s.math << "," << s.physics << "," 
                 << s.chemistry << "," << s.total << "\n";
        }
    } catch (const exception& e) {
        cerr << e.what() << endl;
    }
}



void updateStudentSubject(Student& s, char subjectCode) {
    int marks;
    cout << "Enter new marks for " << s.name << " (Roll: " << s.rollNo << "): ";
    cin >> marks;
    
    if (subjectCode == 'M') s.math = marks;
    else if (subjectCode == 'P') s.physics = marks;
    else if (subjectCode == 'C') s.chemistry = marks;
    
    s.total = s.math + s.physics + s.chemistry; 
    
    cout << "Updated -> " << s.name << " | Roll: " << s.rollNo 
         << " | New Marks: " << marks << " | New Total: " << s.total << "\n";
}

int getSubjectMarks(const Student& s, char subjectCode) {
    if (subjectCode == 'M') return s.math;
    if (subjectCode == 'P') return s.physics;
    if (subjectCode == 'C') return s.chemistry;
    return -1;
}


bool compareStudents(const Student& a, const Student& b) {
    if (a.total != b.total) {
        return a.total > b.total; 
    }
    return a.rollNo < b.rollNo;   
}



int main() {
    string filename = "marks.csv";
    vector<Student> students = loadData(filename);

    if (students.empty()) {
        cout << "No data loaded. Please check your CSV file.\n";
        return 1;
    }

    int choice;
    while (true) {
        cout << "\n=== Marks Management System ===\n";
        cout << "1. Update Marks\n";
        cout << "2. View Marks\n";
        cout << "3. Sort Database (By Total)\n";
        cout << "4. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        if (choice == 1) {
            char code;
            string roll;
            cout << "Enter Subject Code (M = Math, P = Physics, C = Chemistry): ";
            cin >> code;
            code = toupper(code);

            if (code != 'M' && code != 'P' && code != 'C') {
                cout << "Invalid Subject Code!\n";
                continue; 
            }

            cout << "Enter Student Roll No: ";
            cin >> roll;

            bool found = false;
            for (auto& s : students) {
                if (s.rollNo == roll) {
                    updateStudentSubject(s, code);
                    found = true;
                    break;
                }
            }

            if (!found) {
                cout << "Error: Student with Roll No '" << roll << "' not found.\n";
            } else {
                saveData(filename, students);
                cout << "\nUpdate saved successfully to CSV!\n";
            }

        } else if (choice == 2) {
            int viewChoice;
            cout << "\n--- View Options ---\n";
            cout << "1) View a subject by code for ONE student\n";
            cout << "2) View a subject by code for ALL students\n";
            cout << "3) View ALL subjects for ONE student\n";
            cout << "4) View entire CSV content\n";
            cout << "Select option: ";
            cin >> viewChoice;

            if (viewChoice == 1) {
                char code; string roll;
                cout << "Subject Code (M/P/C): "; cin >> code;
                cout << "Enter Roll No: "; cin >> roll;
                code = toupper(code);
                
                for (const auto& s : students) {
                    if (s.rollNo == roll) {
                        cout << s.name << " scored " << getSubjectMarks(s, code) << " in subject " << code << ".\n";
                    }
                }
            } 
            else if (viewChoice == 2) {
                char code;
                cout << "Subject Code (M/P/C): "; cin >> code;
                code = toupper(code);
                cout << "--- " << code << " Marks ---\n";
                for (const auto& s : students) {
                    cout << "Roll: " << s.rollNo << " | Name: " << s.name << " | Marks: " << getSubjectMarks(s, code) << "\n";
                }
            } 
            else if (viewChoice == 3) {
                string roll;
                cout << "Enter Roll No: "; cin >> roll;
                for (const auto& s : students) {
                    if (s.rollNo == roll) {
                        cout << "--- Report Card for " << s.name << " ---\n";
                        cout << "Math: " << s.math << "\nPhysics: " << s.physics << "\nChemistry: " << s.chemistry << "\nTotal: " << s.total << "\n";
                    }
                }
            } 
            else if (viewChoice == 4) {
                cout << left << setw(10) << "RollNo" << setw(15) << "Name" << setw(10) << "Math" << setw(10) << "Physics" << setw(10) << "Chemistry" << setw(10) << "Total" << "\n";
                cout << string(65, '-') << "\n";
                for (const auto& s : students) {
                    cout << left << setw(10) << s.rollNo << setw(15) << s.name << setw(10) << s.math << setw(10) << s.physics << setw(10) << s.chemistry << setw(10) << s.total << "\n";
                }
            } else {
                cout << "Invalid view option.\n";
            }

        } else if (choice == 3) {
            
            sort(students.begin(), students.end(), compareStudents);
            saveData(filename, students);
            cout << "\nDatabase successfully sorted by Total Marks (with Roll No. tie-breakers) and saved to CSV!\n";

        } else if (choice == 4) {
            break;
        } else {
            cout << "Invalid choice.\n";
        }
    }

    return 0;
}