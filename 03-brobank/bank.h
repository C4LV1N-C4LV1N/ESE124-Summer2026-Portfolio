#ifndef BANK_H
#define BANK_H
#include "adt.h"
#define BROBANK_MAX_ACCOUNTS 16

typedef enum { TX_DEPOSIT, TX_WITHDRAW, TX_TRANSFER } TransactionType;
typedef struct { TransactionType type; int from, to; double amount; } Transaction;

typedef struct {
    double balances[BROBANK_MAX_ACCOUNTS];
    int account_count;
    Transaction pending[CAPACITY];
    int p_front, p_rear, p_count;
    Transaction undo[CAPACITY];
    int undo_top;
    int graph[BROBANK_MAX_ACCOUNTS][BROBANK_MAX_ACCOUNTS];
} BroBank;

void bank_init(BroBank *bank, int account_count);
int bank_submit(BroBank *bank, Transaction tx);
int bank_process_next(BroBank *bank);
int bank_undo(BroBank *bank);
int bank_bfs(const BroBank *bank, int source, int destination);
int bank_dfs(const BroBank *bank, int source, int destination);

#endif