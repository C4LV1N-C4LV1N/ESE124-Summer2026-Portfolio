# BroBank

## Overview

BroBank is a modular C banking application that allows users to securely access and manage their account using a 3-digit PIN lock. After logging in, users can make deposits, withdrawals, undo their most recent action, and calculate interest. The program updates the account balance after each transaction, saves the balance when the user exits, and records the complete transaction history, including transactions that were later undone.

## Key Features

- 3-Digit PIN Security: Users must enter a valid 3-digit PIN before accessing their account.

- Account Management: Supports deposits, withdrawals, and undo operations while keeping the account balance updated.

- Persistent Records: Saves the account balance when the program exits and writes all transactions, including undone transactions, to a .txt history file.

- Interest Rate Calculator: Calculates the potential growth of the account based on an interest rate and time period.

- Transaction History: Maintains a record of deposits, withdrawals, and undos instead of erasing an undone transaction from the history.

## Technical Highlights

BroBank demonstrates modular C programming, functions, structures, input validation, file I/O, and abstract data types. A stack is used to support the undo feature because the most recent successful transaction must be reversed first. File persistence allows the account balance to be restored between program sessions, while a transaction history text file provides a permanent record of account activity. The project also includes testing for valid transactions, invalid input, undo behavior, and persistence.

## Project Structure

- brobank.c - Contains the main banking logic, including account actions, balance updates, PIN access, undo functionality, interest calculations, and transaction history.

- brobank.h - Contains BroBank structures, constants, and function prototypes.

- adt.c - Implements the stack and queue operations used by the project.

- adt.h - Defines the stack and queue abstract data types and their function prototypes.

- main.c - Handles program execution, user interaction, menu selection, and the overall BroBank workflow.

## Compile and Run

make
./brobank

[Adjust the command if needed and explain any required input files.]

## Example

A typical BroBank session follows this workflow:

=== BroBank ===

Enter your 3-digit PIN: ***
Access granted.

1. Deposit
2. Withdraw
3. Undo
4. Interest Rate Calculator
5. Show Balance
6. Quit

Choose an action: 1

Enter deposit amount: $100.00
Deposit successful.
Current balance: $100.00


If the user later withdraws money and chooses Undo, the balance is restored to its previous value. The undo is also recorded in the transaction history rather than deleting the original transaction.


transactions.txt:

Deposit: +$100.00
Withdraw: -$25.00
Undo: +$25.00

When the user selects Quit, the current balance is saved so it can be loaded the next time BroBank runs.

## Design and Testing

One important design decision was using a stack for the undo system. Since an undo should reverse the most recent successful transaction first, the stack's LIFO behavior matches the requirements naturally. The program also separates the account balance from the transaction history, allowing an undone transaction to remain in the .txt history file for accurate record keeping.

A meaningful test was performing a deposit, followed by a withdrawal, and then undoing the withdrawal. The expected result was that the original balance after the deposit would be restored. Additional tests checked invalid PIN input, insufficient funds, multiple transactions, quitting and reloading the saved balance, and ensuring that undone transactions remained in the history file.

One bug fixed was ensuring that an undone transaction was not removed from the transaction history. The balance is reversed and the undo is recorded as a new history entry, preserving a complete record of what happened during the account session.

## Acknowledgments

This project was developed using course materials and standard C libraries. ChatGPT and Copilot were used for programming guidance, debugging assistance, and explanations of C programming concepts in accordance with course policy. No external libraries or copied solution files were used.
