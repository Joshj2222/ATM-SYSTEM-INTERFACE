//============================================================================================
//Project Title  : ATM SYSTEM INTERFACE 
//Authors        : [Andrew Guerra] [Joshua Jaime] 
//Date           : Started 04/29/25 Finished 05/12/25
//Course         : COMPSCI 2  39452
// ===========================================================================================
// Project Description : This project simulates a simplified ATM System Interface in C++.
// Features: The ability to create an account with password creation to protect your account. Has 3 accounts (Checkings, Savings, credit).
// Allows the user to borrow money from their credit account (up to 1000$) and allows the user to repay the credit balance and view all account balances and available credit 
#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <limits>
// ================ BANK ACCOUNT CLASSES ================
// Here is where the base class for all accounts starts
using namespace std;

class BankAccount {
private:
    string accountNumber;
    double balance;

public:
    BankAccount(string accNum, double initialBalance); 
    virtual ~BankAccount() {}  
    virtual bool deposit(double amount);
    virtual bool withdraw(double amount);
    double getBalance() const;
    string getAccountNumber() const;
};

// This will intialize the account with a number and a balance.
BankAccount::BankAccount(string accNum, double initialBalance) {
    accountNumber = accNum;
    balance = initialBalance;
}
//Deposit can only be a positve amount
bool BankAccount::deposit(double amount) {
    if (amount > 0) {
        balance += amount;
        cout << fixed << setprecision(2);
        cout << "Amount deposited: $" << amount << endl;
        return true;
    } else {
        return false;
    }
}
// Withdraw will fail if the balance has a insufficient balance.
bool BankAccount::withdraw(double amount) {
    if (amount > balance) {
        cout << "ERROR: Amount exceeds your balance" << endl;
        return false;
    } else {
        balance -= amount;
        cout << "Amount withdrawn: $" << amount << endl;
        return true;
    }
}

double BankAccount::getBalance() const {
    return balance;
}

string BankAccount::getAccountNumber() const {
    return accountNumber;
}
// ==================== CHECKING ACCOUNT =====================
class CheckingAccount : public BankAccount {
public:
    CheckingAccount(string accNum, double initialBalance);
    bool deposit(double amount);
    bool withdraw(double amount);
};

CheckingAccount::CheckingAccount(string accNum, double initialBalance)
    : BankAccount(accNum, initialBalance) {}

bool CheckingAccount::deposit(double amount) {
    return BankAccount::deposit(amount);
}

bool CheckingAccount::withdraw(double amount) {
    return BankAccount::withdraw(amount);
}
// =============== SAVINGS ACCOUNT ===================
class SavingsAccount : public BankAccount {
public:
    SavingsAccount(string accNum, double initialBalance);
    bool deposit(double amount);
    bool withdraw(double amount);
};

SavingsAccount::SavingsAccount(string accNum, double initialBalance)
    : BankAccount(accNum, initialBalance) {}

bool SavingsAccount::deposit(double amount) {
    return BankAccount::deposit(amount);
}

bool SavingsAccount::withdraw(double amount) {
    return BankAccount::withdraw(amount);
}
// ================== CREDIT ACCOUNT ==========================
class CreditAccount : public BankAccount {
private:
    double creditLimit; // Here is our max credit 
    double creditOwed;  // Here is how much the user owes.

public:
    CreditAccount(string accNum, double creditBalance);
    bool deposit(double amount) override; // Deposit = Repayment
    double getCreditOwed() const; // Balance logic
    double getAvailableCredit() const; // Balance logic
};

CreditAccount::CreditAccount(string accNum, double creditBalance)
    : BankAccount(accNum, 0.0) {
    creditLimit = 1000;
    if (creditBalance > creditLimit) {
        cout << "WARNING: Credit owed exceeds limit. Setting to max allowed ($1000)." << endl;
        creditOwed = creditLimit;
    } else {
        creditOwed = creditBalance;
    }
}
// Whenever you deposit to your credit account it means that your paying off your debt.
bool CreditAccount::deposit(double amount) {
    if (amount > creditOwed) {
        cout << "ERROR: Amount deposited exceeds credit owed." << endl;
        return false;
    } else {
        creditOwed -= amount;
        cout << "Money has been deposited on your credit account. Credit Owed balance is $" << creditOwed << endl;
        return true;
    }
}

double CreditAccount::getCreditOwed() const {
    return creditOwed;
}

double CreditAccount::getAvailableCredit() const {
    return creditLimit - creditOwed;
}
// ==================== USER CLASS =========================
class User {
private:
    string username;
    string password;
    CheckingAccount checking;
    SavingsAccount savings;
    CreditAccount credit;

public:
    User(string uname, string pass)
        : username(uname), password(pass),
          checking(uname + "_C", 0),
          savings(uname + "_S", 0),
          credit(uname + "_CR", 0) {}
// Verifiy credentials
    bool verifyPassword(string pass) const {
        return pass == password;
    }
// Displays all balances for ALL account types.
    void displayAccounts() const {
        cout << "Checking: $" << checking.getBalance() << endl;
        cout << "Savings: $" << savings.getBalance() << endl;
        cout << "Credit owed: $" << credit.getCreditOwed() << endl;
        cout << "Available credit: $" << credit.getAvailableCredit() << endl;
    }

    CheckingAccount& getChecking() { return checking; }  // ✅ Added
    SavingsAccount& getSavings() { return savings; }      // ✅ Added
    CreditAccount& getCredit() { return credit; }         // ✅ Added

    BankAccount& getAccount(char type) {
        if (type == 'C' || type == 'c') return checking;
        else if (type == 'S' || type == 's') return savings;
        else if (type == 'R' || type == 'r') return credit;
        else {
            cout << "Invalid Response!!!" << endl;  
            return checking;  // fallback to prevent crash
        }
    }
};
// ===================== BANK CLASS ========================
class Bank {
private:
    vector<User> users;
    User* currentUser = nullptr;
// Account creation.
public:
    void createAccount() {
        string uname, pass;
        cout << "Enter a username: ";
        cin >> uname;
        cout << "Set a password: ";
        cin >> pass;

        users.emplace_back(uname, pass);
        cout << "Account created successfully!\n";
    }
// Log in with a user and password.
    bool login(string username, string password) {
        for (auto& user : users) {
            if (user.verifyPassword(password)) {
                currentUser = &user;
                cout << "Login successful!\n";
                return true;
            }
        }
        cout << "Login failed: Incorrect username or password.\n";
        return false;
    }
// Logout user
    void logout() {
        currentUser = nullptr;
        cout << "Logged out successfully.\n";
    }
// To deposit funds to checkings/savings/credit.
    void depositMoney() {
        if (!currentUser) {
            cout << "Please log in first.\n";
            return;
        }

        char type;
        double amount;
        cout << "Enter account type (C = Checking, S = Savings, R = Credit): ";
        cin >> type;
        cout << "Enter amount to deposit: $";
        cin >> amount;

        if (type == 'C' || type == 'c') {
            currentUser->getChecking().deposit(amount);
        } else if (type == 'S' || type == 's') {
            currentUser->getSavings().deposit(amount);
        } else if (type == 'R' || type == 'r') {
            currentUser->getCredit().deposit(amount);
        } else {
            cout << "Invalid account type.\n";
        }
    }
// Withdraw funds from ONLY your checking/savings account.
    void withdrawMoney() {
        if (!currentUser) {
            cout << "Please log in first.\n";
            return;
        }

        char type;
        double amount;
        cout << "Enter account type (C = Checking, S = Savings): ";
        cin >> type;
        cout << "Enter amount to withdraw: $";
        cin >> amount;

        if (type == 'C' || type == 'c') {
            currentUser->getChecking().withdraw(amount);
        } else if (type == 'S' || type == 's') {
            currentUser->getSavings().withdraw(amount);
        } else if (type == 'R' || type == 'r') {
            cout << "Withdrawals from credit accounts are not allowed.\n";
        } else {
            cout << "Invalid account type.\n";
        }
    }
// Pay credit balance.
    void payCredit() {
        if (!currentUser) {
            cout << "Please log in first.\n";
            return;
        }

        double amount;
        cout << "Enter amount to repay on credit account: $";
        cin >> amount;
        currentUser->getCredit().deposit(amount);  
    }
// View your current account balance.
    void displayAccounts() {
        if (!currentUser) {
            cout << "Please log in first.\n";
            return;
        }

        currentUser->displayAccounts();
    }
// Main application loop.
    void run() {
        bool running = true;

        while (running) {
            cout << "\n===== Bank App Main Menu =====" << endl;
            cout << "1. Create Account" << endl;
            cout << "2. Login" << endl;
            cout << "3. Deposit Money" << endl;
            cout << "4. Withdraw Money" << endl;
            cout << "5. Pay Your Credit" << endl;
            cout << "6. Display Your Accounts" << endl;
            cout << "7. Log Out" << endl;
            cout << "8. Exit" << endl;

            int userOption;
            cout << "Please choose (1-8): ";
            cin >> userOption;

            switch (userOption) {
                case 1:
                    createAccount();
                    break;
                case 2: {
                    string username, password;
                    cout << "Username: ";
                    cin >> username;
                    cout << "Password: ";
                    cin >> password;
                    login(username, password);
                    break;
                }
                case 3:
                    depositMoney();
                    break;
                case 4:
                    withdrawMoney();
                    break;
                case 5:
                    payCredit();
                    break;
                case 6:
                    displayAccounts();
                    break;
                case 7:
                    logout();
                    break;
                case 8:
                    cout << "Thank you for using the ATM. Goodbye!" << endl;
                    running = false;
                    break;
                default:
                    cout << "Invalid choice. Please try again." << endl;
                    break;
            }
        }
    }
};
// ===================== MAIN ==========================
int main()
{
    Bank bank;
    bank.run();
    return 0;
}
