import java.util.*;

class Account {
        protected int accountNumber;
        protected String holderName;
        protected double balance;

        Account(int accno, String hName, double amt) {
                accountNumber = accno;
                holderName = hName;
                balance = amt;
        }

        public int getAccountNumber() {
                return accountNumber;
        }

        public String getHolderName() {
                return holderName;
        }

        public double getBalance() {
                return balance;
        }

        public void setBalance(double balance) {
                this.balance = balance;
        }

        public void updateName(String name) {
                holderName = name;
        }

        public void display() {
                System.out.println("Account Number: " + accountNumber);
                System.out.println("Holder Name: " + holderName);
                System.out.println("Balance: " + balance);
        }
}

class SavingsAccount extends Account {
        private double interestRate;

        public SavingsAccount(int accno, String hName, double amt, double rate) {
                super(accno, hName, amt);
                interestRate = rate;
        }

        public double calculateYearlyInterest() {
                return balance * interestRate / 100;
        }

        @Override
        public void display() {
                super.display();
                System.out.println("Interest Rate: " + interestRate + "%");
                System.out.println("Yearly Interest: " + calculateYearlyInterest());
        }
}

class CurrentAccount extends Account {
        public CurrentAccount(int accno, String hName, double amt) {
                super(accno, hName, amt);
        }

        @Override
        public void display() {
                System.out.println("Current Account Details:");
                super.display();
        }
}

class Manager {
        Account[] accounts;
        int count;

        Manager(int size) {
                accounts = new Account[size];
                count = 0;
        }

        void addAccount(Account acc) {
                if (count < accounts.length) {
                        accounts[count++] = acc;
                }
        }

        void displayAllAccounts() {
                for (int i = 0; i < count; i++) {
                        System.out.println("----------------");
                        accounts[i].display();
                }
        }
}

class Main8 {
        public static void main(String[] args) {
                Manager manager = new Manager(5);

                manager.addAccount(new SavingsAccount(101, "A", 50000, 4.5));
                manager.addAccount(new SavingsAccount(102, "B", 30000, 5.0));

                manager.addAccount(new CurrentAccount(201, "C", 40000));
                manager.addAccount(new CurrentAccount(202, "D", 60000));
                manager.addAccount(new CurrentAccount(203, "E", 25000));

                manager.displayAllAccounts();
        }
}

