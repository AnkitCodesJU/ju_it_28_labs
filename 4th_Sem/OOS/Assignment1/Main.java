import java.util.*;

class Student {
        private String name;
        private int rollNo;
        private String[] subjects;

        Student(String name, int rollNo, String[] subjects) {
                this.name = name;
                this.rollNo = rollNo;
                this.subjects = subjects;
        }

        public String getName() {
                return name;
        }

        public int getRollNo() {
                return rollNo;
        }

        public String[] getSubjects() {
                return subjects;
        }

        public void setName(String name) {
                this.name = name;
        }

        public void setRollNo(int rollNo) {
                this.rollNo = rollNo;
        }

        public void setSubjects(String[] subjects) {
                this.subjects = subjects;
        }
}

class TabulationSheet {
        private String subjectName;
        private List<Integer> rollNos;
        private List<Integer> marksList;

        TabulationSheet(String subjectName) {
                this.subjectName = subjectName;
                rollNos = new ArrayList<>();
                marksList = new ArrayList<>();
        }

        public void addMarks(int rollNo, int marks) {
                rollNos.add(rollNo);
                marksList.add(marks);
        }

        public int getMarks(int rollNo) {
                int index = rollNos.indexOf(rollNo);
                if (index != -1) {
                        return marksList.get(index);
                }
                return 0;
        }

        public String getSubjectName() {
                return subjectName;
        }
}

class MarkSheet {
        private String studentName;
        private int rollNo;
        private List<String> subjects;
        private List<Integer> marksList;

        MarkSheet(String studentName, int rollNo) {
                this.studentName = studentName;
                this.rollNo = rollNo;
                subjects = new ArrayList<>();
                marksList = new ArrayList<>();
        }

        public void addSubjectMarks(String subject, int marks) {
                subjects.add(subject);
                marksList.add(marks);
        }

        public void printMarkSheet() {
                System.out.println("Mark Sheet for " + studentName + " (Roll No: " + rollNo + ")");
                for (int i = 0; i < subjects.size(); i++) {
                        System.out.println(subjects.get(i) + ": " + marksList.get(i));
                }
                System.out.println();
        }
}

public class Main {
        public static void main(String[] args) {
                String[] subjects = { "Math", "Physics", "Chemistry", "Biology", "English" };

                Student s1 = new Student("Alice", 101, subjects);
                Student s2 = new Student("Bob", 102, subjects);
                Student s3 = new Student("Charlie", 103, subjects);

                TabulationSheet mathSheet = new TabulationSheet("Math");
                TabulationSheet physicsSheet = new TabulationSheet("Physics");
                TabulationSheet chemistrySheet = new TabulationSheet("Chemistry");
                TabulationSheet biologySheet = new TabulationSheet("Biology");
                TabulationSheet englishSheet = new TabulationSheet("English");

                mathSheet.addMarks(101, 85);
                mathSheet.addMarks(102, 78);
                mathSheet.addMarks(103, 92);

                physicsSheet.addMarks(101, 90);
                physicsSheet.addMarks(102, 80);
                physicsSheet.addMarks(103, 85);

                chemistrySheet.addMarks(101, 88);
                chemistrySheet.addMarks(102, 82);
                chemistrySheet.addMarks(103, 91);

                biologySheet.addMarks(101, 76);
                biologySheet.addMarks(102, 89);
                biologySheet.addMarks(103, 84);

                englishSheet.addMarks(101, 92);
                englishSheet.addMarks(102, 87);
                englishSheet.addMarks(103, 90);

                MarkSheet ms1 = new MarkSheet(s1.getName(), s1.getRollNo());
                MarkSheet ms2 = new MarkSheet(s2.getName(), s2.getRollNo());
                MarkSheet ms3 = new MarkSheet(s3.getName(), s3.getRollNo());

                TabulationSheet[] sheets = { mathSheet, physicsSheet, chemistrySheet, biologySheet, englishSheet };
                MarkSheet[] marksheets = { ms1, ms2, ms3 };

                Student[] students = { s1, s2, s3 };

                for (int i = 0; i < students.length; i++) {
                        for (TabulationSheet ts : sheets) {
                                marksheets[i].addSubjectMarks(ts.getSubjectName(),
                                                ts.getMarks(students[i].getRollNo()));
                        }
                }

                for (MarkSheet ms : marksheets) {
                        ms.printMarkSheet();
                }
        }
}
