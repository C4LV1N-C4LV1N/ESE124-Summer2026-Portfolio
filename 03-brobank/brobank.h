#ifndef BROBANK_H
#define BROBANK_H
#include "adt.h"
#define BROBANK_MAX_ACCOUNTS 16
typedef enum { TX_DEPOSIT, TX_WITHDRAW, TX_TRANSFER } TransactionType;
typedef struct { TransactionType type; int from, to; double amount; } Transaction;
typedef struct {
    double balances[BROBANK_MAX_ACCOUNTS]; int account_count;
    Transaction pending[CAPACITY]; int p_front, p_rear, p_count;
    Transaction undo[CAPACITY]; int undo_top;
    int graph[BROBANK_MAX_ACCOUNTS][BROBANK_MAX_ACCOUNTS];
} BroBank;
void brobank_init(BroBank *bank, int account_count);
int brobankSubmit(BroBank *bank, Transaction tx);
int brobankProcessNext(BroBank *bank);
int brobankUndo(BroBank *bank);
int brobankBFS(const BroBank *bank, int source, int destination);
int brobankDFS(const BroBank *bank, int source, int destination);
#endif