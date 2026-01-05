#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct {
    char name[50];
    int accountNumber;
    double balance;
} SavingsAccount;

int nextAccountNumber = 1001;
double interestRate = 0.05;  




void createAccount(SavingsAccount *acc, const char *name, double balance) {
    strcpy(acc->name, name);
    acc->accountNumber = nextAccountNumber++;

    if (balance < 1000) {
        printf("Balance too low while creating account for %s. Setting to Rs. 1000.\n", name);
        balance = 1000;
    }
    acc->balance = balance;
}


void deposit(SavingsAccount *acc, double amount) {
    if (amount > 0) {
        acc->balance += amount;
        printf("Deposited Rs. %.2f into Account %d\n", amount, acc->accountNumber);
        printf("New Balance: Rs. %.2f\n", acc->balance);
    } else {
        printf("Invalid deposit amount!\n");
    }
}


void withdraw(SavingsAccount *acc, double amount) {
    if (amount > 0 && acc->balance - amount >= 1000) {
        acc->balance -= amount;
        printf("Withdrawal of Rs. %.2f successful from Account %d\n", amount, acc->accountNumber);
        printf("Remaining Balance: Rs. %.2f\n", acc->balance);
    } else {
        printf("Withdrawal failed for Account %d (Insufficient balance)\n", acc->accountNumber);
    }
}


double calculateInterest(SavingsAccount *acc) {
    double interest = acc->balance * interestRate;
    acc->balance += interest;
    return interest;
}


double applyInterest(SavingsAccount accounts[], int n) {
    double total = 0.0;
    for (int i = 0; i < n; i++) {
        total += calculateInterest(&accounts[i]);
    }
    return total;
}


void displayAccounts(SavingsAccount accounts[], int n) {
    printf("\n--- Account Details ---\n");
    for (int i = 0; i < n; i++) {
        printf("Acc.No: %d | Name: %s | Balance: Rs.%.2f\n",
               accounts[i].accountNumber, accounts[i].name, accounts[i].balance);
    }
    printf("\n");
}


void handleDeposit(SavingsAccount accounts[], int n) {
    int accNo; double amt;
    printf("Enter account number and amount to deposit: ");
    scanf("%d %lf", &accNo, &amt);
    for (int i = 0; i < n; i++) {
        if (accounts[i].accountNumber == accNo) {
            deposit(&accounts[i], amt);
            return;
        }
    }
    printf("Account not found!\n");
}

void handleWithdraw(SavingsAccount accounts[], int n) {
    int accNo; double amt;
    printf("Enter account number and amount to withdraw: ");
    scanf("%d %lf", &accNo, &amt);
    for (int i = 0; i < n; i++) {
        if (accounts[i].accountNumber == accNo) {
            withdraw(&accounts[i], amt);
            return;
        }
    }
    printf("Account not found!\n");
}

void handleDisplay(SavingsAccount accounts[], int n) {
    displayAccounts(accounts, n);
}

void handleApplyInterest(SavingsAccount accounts[], int n) {
    double total = applyInterest(accounts, n);
    printf("Total interest paid to all accounts: Rs. %.2f\n", total);
}

void handleChangeRate(SavingsAccount accounts[], int n) {
    printf("Enter new interest rate (e.g. 0.06 for 6%%): ");
    scanf("%lf", &interestRate);
    printf("Interest rate updated to %.2f%%\n", interestRate * 100);
    double total = applyInterest(accounts, n);
    printf("Recalculated and deposited new interest: Rs. %.2f\n", total);
}

void displayAccount(const SavingsAccount *acc) {
    printf("Acc.No: %d | Name: %s | Balance: Rs.%.2f\n",
           acc->accountNumber, acc->name, acc->balance);
}


int main() {
    srand(time(NULL));

    int n;
    printf("Enter number of accounts to create: ");
    if (scanf("%d", &n) != 1 || n <= 0) {
        printf("Invalid number of accounts!\n");
        return 1;
    }

    SavingsAccount accounts[n];

    for (int i = 0; i < n; i++) {
    int balance = (rand() % (100000 - 1000 + 1)) + 1000;
    printf("Enter name for User_%d: ", i + 1);
    char name[50];
    scanf("%s", name);
    createAccount(&accounts[i], name, balance);

    printf("Account created successfully:\n");
    displayAccount(&accounts[i]);
    printf("\n");
}

    int choice;
    do {
        printf("\n====== Bank Menu ======\n");
        printf("1. Deposit\n");
        printf("2. Withdraw\n");
        printf("3. Display Accounts\n");
        printf("4. Apply Interest\n");
        printf("5. Change Interest Rate\n");
        printf("6. Exit\n");
        printf("Enter choice: ");
        if (scanf("%d", &choice) != 1) {
            printf("Invalid input! Exiting...\n");
            break;
        }

        switch (choice) {
            case 1: handleDeposit(accounts, n); break;
            case 2: handleWithdraw(accounts, n); break;
            case 3: handleDisplay(accounts, n); break;
            case 4: handleApplyInterest(accounts, n); break;
            case 5: handleChangeRate(accounts, n); break;
            case 6: printf("Exiting...\n"); break;
            default: printf("Invalid choice!\n");
        }
    } while (choice != 6);

    return 0;
}
