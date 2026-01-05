#include <iostream>
#include <string>

using namespace std;

const double INTEREST_RATE = 0.05;
const double MIN_BALANCE = 1000.0;

static int globalAccountNumber = 1;

class SavingsAccount {
private:
        string accountHolderName;
        int accountNumber;
        double balance;

public:
        SavingsAccount(const string& name, const double& initialBalance)
                : accountHolderName(name), accountNumber(globalAccountNumber++) {
                if (initialBalance < MIN_BALANCE)
                        balance = MIN_BALANCE;
                else
                        balance = initialBalance;
        }

        void deposit(const double& amount) {
                if (amount > 0)
                        balance += amount;
        }

        bool withdraw(const double& amount) {
                if (amount <= 0) return false;
                if ((balance - amount) < MIN_BALANCE)
                        return false;
                balance -= amount;
                return true;
        }

        double calculateInterest() const {
                return balance * INTEREST_RATE;
        }

        void addInterest() {
                balance += calculateInterest();
        }

        void displayAccount() const {
                cout << "Account No: " << accountNumber
                     << ", Name: " << accountHolderName
                     << ", Balance: Rs. " << balance << endl;
        }

        int getAccountNumber() const { return accountNumber; }
        const string& getAccountHolderName() const { return accountHolderName; }
        double getBalance() const { return balance; }
};

int main() {
        SavingsAccount acc1("Ankit", 5000);
        SavingsAccount acc2("SRC", 1500);

        acc1.displayAccount();
        acc2.displayAccount();

        acc1.deposit(2000);
        acc2.withdraw(400);

        acc1.addInterest();
        acc2.addInterest();

        cout << "\nAfter transactions and interest added:\n";
        acc1.displayAccount();
        acc2.displayAccount();

        return 0;
}

