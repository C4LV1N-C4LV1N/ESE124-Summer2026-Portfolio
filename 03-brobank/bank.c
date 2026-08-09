#include <stdio.h>
#include <string.h>
#include "bank.h"

void bank_init(BroBank *bank, int account_count) {
    if (!bank) return;
    memset(bank, 0, sizeof *bank);
    bank->account_count = account_count;
    bank->p_rear = -1;
    bank->undo_top = -1;
}

int bank_submit(BroBank *bank, Transaction tx) {
    if (!bank) return 0;
    if (tx.from < 0 || tx.from >= bank->account_count) return 0;
    if (tx.to < 0 || tx.to >= bank->account_count) return 0;
    if (tx.amount < 0.0) return 0;
    if (bank->p_count >= CAPACITY) return 0;

    bank->p_rear = (bank->p_rear + 1) % CAPACITY;
    bank->pending[bank->p_rear] = tx;
    bank->p_count++;
    return 1;
}

int bank_process_next(BroBank *bank) {
    if (!bank) return 0;
    if (bank->p_count <= 0) return 0;

    Transaction tx = bank->pending[bank->p_front];
    bank->p_front = (bank->p_front + 1) % CAPACITY;
    bank->p_count--;

    if (tx.from < 0 || tx.from >= bank->account_count) return 0;
    if (tx.to < 0 || tx.to >= bank->account_count) return 0;

    switch (tx.type) {
        case TX_DEPOSIT:
            bank->balances[tx.to] += tx.amount;
            break;
        case TX_WITHDRAW:
            if (bank->balances[tx.from] + 1e-9 < tx.amount) return 0;
            bank->balances[tx.from] -= tx.amount;
            break;
        case TX_TRANSFER:
            if (tx.from == tx.to) return 0;
            if (bank->balances[tx.from] + 1e-9 < tx.amount) return 0;
            bank->balances[tx.from] -= tx.amount;
            bank->balances[tx.to] += tx.amount;
            bank->graph[tx.from][tx.to] = 1;
            break;
        default:
            return 0;
    }

    if (bank->undo_top + 1 < CAPACITY) {
        bank->undo_top++;
        bank->undo[bank->undo_top] = tx;
    }
    return 1;
}

int bank_undo(BroBank *bank) {
    if (!bank) return 0;
    if (bank->undo_top < 0) return 0;

    Transaction tx = bank->undo[bank->undo_top];
    bank->undo_top--;

    switch (tx.type) {
        case TX_DEPOSIT:
            bank->balances[tx.to] -= tx.amount;
            break;
        case TX_WITHDRAW:
            bank->balances[tx.from] += tx.amount;
            break;
        case TX_TRANSFER:
            bank->balances[tx.to] -= tx.amount;
            bank->balances[tx.from] += tx.amount;
            bank->graph[tx.from][tx.to] = 0;
            break;
        default:
            return 0;
    }
    return 1;
}

int bank_bfs(const BroBank *bank, int source, int destination) {
    if (!bank) return -1;
    int n = bank->account_count;
    if (source < 0 || source >= n) return -1;
    if (destination < 0 || destination >= n) return -1;
    if (source == destination) return 0;

    int visited[BROBANK_MAX_ACCOUNTS] = {0};
    int dist[BROBANK_MAX_ACCOUNTS];
    for (int i = 0; i < n; ++i) dist[i] = -1;

    Queue q;
    queueInit(&q);
    enqueue(&q, source);
    visited[source] = 1;
    dist[source] = 0;

    int cur;
    while (!queueIsEmpty(&q)) {
        dequeue(&q, &cur);
        for (int i = 0; i < n; ++i) {
            if (bank->graph[cur][i] && !visited[i]) {
                visited[i] = 1;
                dist[i] = dist[cur] + 1;
                if (i == destination) return dist[i];
                enqueue(&q, i);
            }
        }
    }
    return -1;
}

int bank_dfs(const BroBank *bank, int source, int destination) {
    if (!bank) return 0;
    int n = bank->account_count;
    if (source < 0 || source >= n) return 0;
    if (destination < 0 || destination >= n) return 0;
    if (source == destination) return 1;

    int visited[BROBANK_MAX_ACCOUNTS] = {0};
    Stack s;
    stackInit(&s);
    stackPush(&s, source);
    visited[source] = 1;

    int cur;
    while (!stackIsEmpty(&s)) {
        stackPop(&s, &cur);
        for (int i = 0; i < n; ++i) {
            if (bank->graph[cur][i] && !visited[i]) {
                if (i == destination) return 1;
                visited[i] = 1;
                stackPush(&s, i);
            }
        }
    }
    return 0;
}
