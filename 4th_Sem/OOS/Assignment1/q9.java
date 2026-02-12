class Person {
        protected int age;
        protected double weight;
        protected double height;
        protected String dateOfBirth;
        protected String address;

        public Person(int age, double weight, double height, String dob, String address) {
                this.age = age;
                this.weight = weight;
                this.height = height;
                this.dateOfBirth = dob;
                this.address = address;
        }

        public int getAge() { return age; }
        public void setAge(int age) { this.age = age; }

        public double getWeight() { return weight; }
        public void setWeight(double weight) { this.weight = weight; }

        public double getHeight() { return height; }
        public void setHeight(double height) { this.height = height; }

        public String getDateOfBirth() { return dateOfBirth; }
        public void setDateOfBirth(String dob) { this.dateOfBirth = dob; }

        public String getAddress() { return address; }
        public void setAddress(String address) { this.address = address; }

        public void display() {
                System.out.println("Age: " + age);
                System.out.println("Weight: " + weight);
                System.out.println("Height: " + height);
                System.out.println("Date of Birth: " + dateOfBirth);
                System.out.println("Address: " + address);
        }
}

class Employee extends Person {
        protected double salary;
        protected String dateOfJoining;
        protected int experience;

        public Employee(int age, double weight, double height, String dob, String address,
                        double salary, String doj, int experience) {
                super(age, weight, height, dob, address);
                this.salary = salary;
                this.dateOfJoining = doj;
                this.experience = experience;
        }

        public double getSalary() { return salary; }
        public void setSalary(double salary) { this.salary = salary; }

        public String getDateOfJoining() { return dateOfJoining; }
        public void setDateOfJoining(String doj) { this.dateOfJoining = doj; }

        public int getExperience() { return experience; }
        public void setExperience(int exp) { this.experience = exp; }

        @Override
        public void display() {
                super.display();
                System.out.println("Salary: " + salary);
                System.out.println("Date of Joining: " + dateOfJoining);
                System.out.println("Experience: " + experience + " years");
        }
}

class Student extends Person {
        private int roll;
        private String[] subjects;
        private double[] marks;
        private int markCount;

        public Student(int age, double weight, double height, String dob, String address, int roll) {
                super(age, weight, height, dob, address);
                this.roll = roll;
                this.subjects = new String[10];
                this.marks = new double[10];
                this.markCount = 0;
        }

        public int getRoll() { return roll; }
        public void setRoll(int roll) { this.roll = roll; }

        public void addSubjectMark(String subject, double mark) {
                if (markCount < subjects.length) {
                        subjects[markCount] = subject;
                        marks[markCount] = mark;
                        markCount++;
                } else {
                        System.out.println("Cannot add more subjects.");
                }
        }

        public double calculateAverage() {
                if (markCount == 0) return 0;
                double sum = 0;
                for (int i = 0; i < markCount; i++) {
                        sum += marks[i];
                }
                return sum / markCount;
        }

        public String calculateGrade() {
                double avg = calculateAverage();
                if (avg >= 90) return "A";
                else if (avg >= 80) return "B";
                else if (avg >= 70) return "C";
                else if (avg >= 60) return "D";
                else return "F";
        }

        @Override
        public void display() {
                super.display();
                System.out.println("Roll Number: " + roll);
                for (int i = 0; i < markCount; i++) {
                        System.out.println(subjects[i] + ": " + marks[i]);
                }
                System.out.println("Grade: " + calculateGrade());
        }
}

class Technician extends Employee {
        public Technician(int age, double weight, double height, String dob, String address,
                        double salary, String doj, int experience) {
                super(age, weight, height, dob, address, salary, doj, experience);
        }

        @Override
        public void display() {
                System.out.println("Technician Details:");
                super.display();
        }
}

class Professor extends Employee {
        private String[] courses;
        private int courseCount;
        private String[] advisees;
        private int adviseeCount;

        public Professor(int age, double weight, double height, String dob, String address,
                        double salary, String doj, int experience) {
                super(age, weight, height, dob, address, salary, doj, experience);
                this.courses = new String[10];
                this.courseCount = 0;
                this.advisees = new String[10];
                this.adviseeCount = 0;
        }

        public void addCourse(String course) {
                if (courseCount < courses.length) {
                        courses[courseCount++] = course;
                }
        }

        public void removeCourse(String course) {
                int index = -1;
                for (int i = 0; i < courseCount; i++) {
                        if (courses[i].equals(course)) {
                                index = i;
                                break;
                        }
                }
                if (index != -1) {
                        for (int i = index; i < courseCount - 1; i++) {
                                courses[i] = courses[i + 1];
                        }
                        courses[--courseCount] = null;
                }
        }

        public void addAdvisee(String studentName) {
                if (adviseeCount < advisees.length) {
                        advisees[adviseeCount++] = studentName;
                }
        }

        public void removeAdvisee(String studentName) {
                int index = -1;
                for (int i = 0; i < adviseeCount; i++) {
                        if (advisees[i].equals(studentName)) {
                                index = i;
                                break;
                        }
                }
                if (index != -1) {
                        for (int i = index; i < adviseeCount - 1; i++) {
                                advisees[i] = advisees[i + 1];
                        }
                        advisees[--adviseeCount] = null;
                }
        }

        @Override
        public void display() {
                System.out.println("Professor Details:");
                super.display();
                System.out.print("Courses: [");
                for (int i = 0; i < courseCount; i++) {
                        System.out.print(courses[i] + (i < courseCount - 1 ? ", " : ""));
                }
                System.out.println("]");
                
                System.out.print("Advisees: [");
                for (int i = 0; i < adviseeCount; i++) {
                        System.out.print(advisees[i] + (i < adviseeCount - 1 ? ", " : ""));
                }
                System.out.println("]");
        }
}

class Main9 {
        public static void main(String[] args) {
                Student s1 = new Student(20, 65, 5.8, "2006-01-15", "ABC Colony", 101);
                s1.addSubjectMark("Math", 95);
                s1.addSubjectMark("Physics", 88);

                Student s2 = new Student(22, 70, 5.9, "2004-03-12", "DEF Colony", 102);
                s2.addSubjectMark("Chemistry", 78);
                s2.addSubjectMark("Biology", 82);

                Technician t1 = new Technician(30, 75, 5.10, "1996-05-20", "GHI Colony", 40000, "2020-06-01", 4);
                Professor p1 = new Professor(45, 80, 6.0, "1981-11-10", "JKL Colony", 90000, "2010-08-15", 15);

                p1.addCourse("OOS");
                p1.addCourse("DSA");
                p1.addAdvisee("Ankit");
                p1.addAdvisee("SRC");

                s1.display();
                System.out.println("----------------");
                s2.display();
                System.out.println("----------------");
                t1.display();
                System.out.println("----------------");
                p1.display();
        }
}
