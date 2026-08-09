# BroBank

## Overview

BroBank is a C-based banking application that processes deposits, withdrawals, and transfers between accounts. Transactions are submitted to a circular queue, successfully processed transactions are stored in an undo stack, and account transfers are represented as a graph that can be searched using BFS and DFS.

## Key Features

- Transaction Queue: Submits and processes banking transactions using a circular queue with capacity limits and validation.

- Undo System: Stores successful transactions on a stack and reverses the most recent transaction when requested.

- Account Graph: Records transfer relationships between accounts and supports BFS for shortest transfer paths and DFS for reachability.

## Technical Highlights

This project demonstrates modular C programming using structures, enumerations, arrays, queues, stacks, and graph traversal algorithms. The program uses a circular queue to manage pending transactions, a stack to track successful transactions for undo operations, and an adjacency matrix to represent account transfer connections. BFS uses a queue to find the fewest transfer edges between accounts, while DFS uses a stack to determine whether one account can reach another.

## Project Structure

* brobank.c - Implements the main BroBank functionality, including initialization, transaction submission, transaction processing, undo operations, BFS, and DFS.
* brobank.h - Defines the Transaction and BroBank structures, transaction types, constants, and function prototypes.
* adt.h - Defines the Stack and Queue structures and their function prototypes.

## Compile and Run

gcc -std=c11 -Wall -Wextra 03-brobank/brobank.c -o brobank
./brobank

## Example

A typical transaction workflow is:
1. Submit a transaction
2. Transaction is placed in the pending queue
3. Process the next transaction
4. Account balances are updated
5. Successful transaction is pushed onto the undo stack
6. Transfer relationships are recorded in the account graph

For example, a successful transfer from account 0 to account 1 updates both balances and creates a graph edge from account 0 to account 1.

The graph can then be searched using:
BFS: Find the fewest transfer edges between two accounts
DFS: Determine whether one account can reach another

## Design and Testing

One important design decision was separating the different data structures based on their purpose. The queue manages pending transactions in first-in, first-out order, the stack stores successful transactions for last-in, first-out undo operations, and the adjacency matrix represents transfer relationships between accounts.

A meaningful test was submitting a transfer between two accounts, processing it, and then using BFS or DFS to verify that the transfer relationship existed in the graph. The undo operation was also tested to confirm that the transfer reversed the balance changes and removed the corresponding graph edge.

One bug fixed was ensuring that invalid transactions were rejected before being added to the queue. The program checks for invalid account indices, negative transaction amounts, and a full queue. During processing, it also checks for insufficient funds and prevents transfers from an account to itself.

## Acknowledgments

This project was developed as part of coursework using standard C libraries and course-provided ADT concepts. ChatGPT and Copilot were used for understanding C syntax, debugging, data structures, and implementation concepts.
