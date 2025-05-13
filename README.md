# ATM-SYSTEM-INTERFACE
## Authors
[Andrew Guerra] [Joshua Jaime]

## Course
COMPSCI-2-39452

## Date
05/12/25

Project Description
This project simulates a simplified ATM system interface using C++
It allows users to: 
- Create accounts with a Username and Password
- Deposit or withdraw from money from their checking and savings accounts
- Borrow money from their credit account (Only allows them to borrow 1000$ MAX)
- Repay the credit balance (AKA debt)
- View all the Users account balances and available credit

  Classes used
  BankAccount : Base class for shared logic (deposit and withdraw)
  CheckingAccount and SavingsAccount : Account types
  CreditAccount : Handles borrowing with a $1000 limit and repayment
  User: Stores credentials and all 3 account types
  Bank: Controls user registration, login, and operations

  HOW TO RUN
  1.  Please click on BankFInalProjectComsci.cpp and on the top right should be download raw file.
  2.  Either download a IDE or use this website https://www.onlinegdb.com/online_c++_compiler
  3.  Follow the on-screen menu to create users, log in, and manage accounts.
 
  Some things we can improve on in the future
  - File-based data saving/loading
  - GUI version using SFML
  - Interest calculation for savings
  - Admin account for user management

 To whoever is reading this we hope that this project shows that we tried our best and had fun doing so. This project showed us the main reason to why we wanted to be involved with computers and it also shows how much we can improve in the future. :)
