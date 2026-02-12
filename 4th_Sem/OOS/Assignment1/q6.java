import  java.util.*;
class Employee {
        String name;
        int id;
        String address;
        double salary;

        Employee(String name, int id, String address, double salary) {
                this.name = name;
                this.id = id;
                this.address = address;
                this.salary = salary;
        }

        double yearlySalary() {
                return salary * 12;
        }
}

class Dept {
        String name;
        String location;
        Employee[] employees;
        int count;

        Dept(String name, String location, int size) {
                this.name = name;
                this.location = location;
                employees = new Employee[size];
                count = 0;
        }

        void add(Employee e) {
                if (count < employees.length) {
                        employees[count++] = e;
                }
        }

        void remove(int id) {
                for (int i = 0; i < count; i++) {
                        if (employees[i].id == id) {
                                for (int j = i; j < count - 1; j++) {
                                        employees[j] = employees[j + 1];
                                }
                                employees[--count] = null;
                                break;
                        }
                }
        }

        double yearlyExpenditure() {
                double total = 0;
                for (int i = 0; i < count; i++) {
                        total += employees[i].yearlySalary();
                }
                return total;
        }

        public static void main(String[] args) {
                Dept it = new Dept("Information Technology", "Block A", 5);

                it.add(new Employee("A", 1, "City1", 30000));
                it.add(new Employee("B", 2, "City2", 35000));
                it.add(new Employee("C", 3, "City3", 40000));
                it.add(new Employee("D", 4, "City4", 32000));
                it.add(new Employee("E", 5, "City5", 38000));

                System.out.println(it.yearlyExpenditure());
        }
}

