import java.util.*;
class BankAccount {
        int accountNumber;
        float balance;
        String ownerName;

        BankAccount(int accNo, String name, float bal) {
                accountNumber = accNo;
                ownerName = name;
                balance = bal;
        }

        float getBalance() {
                return balance;
        }

        void add(float amount) {
                balance = balance + amount;
        }

        void subtract(float amount) {
                if (amount <= balance)
                balance = balance - amount;
        }

        void print() {
                System.out.println(accountNumber + "  " + ownerName + "  " + balance);
        }
}

class AccountManager {
        BankAccount accounts[];
        int count;

        AccountManager(int size) {
                accounts = new BankAccount[size];
                count = 0;
        }

        void create(int accNo, String name, float bal) {
                accounts[count++] = new BankAccount(accNo, name, bal);
        }

        void delete(int accNo) {
                for (int i = 0; i < count; i++) {
                        if (accounts[i].accountNumber == accNo) {
                                accounts[i] = accounts[count - 1];
                                count--;
                                break;
                        }
                }
        }

        void deposit(int accNo, float amount) {
                for (int i = 0; i < count; i++) {
                        if (accounts[i].accountNumber == accNo) {
                                accounts[i].add(amount);
                                break;
                        }
                }
        }

        void withdraw(int accNo, float amount) {
                for (int i = 0; i < count; i++) {
                        if (accounts[i].accountNumber == accNo) {
                                accounts[i].subtract(amount);
                                break;
                        }
                }
        }

        void printAll() {
                for (int i = 0; i < count; i++)
                accounts[i].print();
        }
}

class Bank {
        public static void main(String[] args) {
                AccountManager am = new AccountManager(10);

                am.create(101, "Aman", 5000);
                am.create(102, "Iman", 3000);
                am.create(103, "Tyrion", 7000);
                am.create(104, "SRC", 4000);
                am.create(105, "AKS", 6000);

                am.printAll();
        }
}
