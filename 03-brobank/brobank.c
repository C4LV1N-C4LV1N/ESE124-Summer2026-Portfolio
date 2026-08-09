#include <string.h>
#include "brobank.h"
void brobank_init(BroBank *bank, int account_count) {
    if (!bank) return; 
    memset(bank, 0, sizeof *bank);
    bank->account_count = account_count; bank->p_rear = -1;
    bank->undo_top = -1;
}
int brobankSubmit(BroBank *bank, Transaction tx) {
    /* TODO: validate and enqueue transaction. */
    if (!bank) return 0;        // fail if bank pointer is missing

    if (tx.from < 0 || tx.from >= bank->account_count) return 0;        // invalid source account
    if (tx.to < 0 || tx.to >= bank->account_count) return 0;        // invalid destination account
    if (tx.amount < 0.0) return 0;      // negative amounts are invalid

    if (bank->p_count >= CAPACITY) return 0;        // reject if the queue is full

    bank->p_rear = (bank->p_rear + 1) % CAPACITY;       // increment rear with wrap (circular buffer)
    bank->pending[bank->p_rear] = tx;       // store the transaction at rear index
    bank->p_count++;        // increment number of pending items
    return 1;       // success
}

int brobankProcessNext(BroBank *bank) {
    /* TODO: dequeue, validate, update balances, push successful undo. */
    if (!bank) return 0;        // null check (missing pointer)
    if (bank->p_count <= 0) return 0;       // return if there is nothing to process

    Transaction tx = bank->pending[bank->p_front];      // fetch transaction at front
    bank->p_front = (bank->p_front + 1) % CAPACITY;     // advance front with wrap
    bank->p_count--;        // decrement pending count

    if (tx.from < 0 || tx.from >= bank->account_count) return 0;        // re-validate accounts
    if (tx.to < 0 || tx.to >= bank->account_count) return 0;

    switch (tx.type) {      // handle transaction types
        case TX_DEPOSIT:
            bank->balances[tx.to] += tx.amount;       // add money to the 'to' account
            break;
        case TX_WITHDRAW:
            if (bank->balances[tx.from] + 1e-9 < tx.amount) return 0;       // reject if insufficient funds
            bank->balances[tx.from] -= tx.amount;       // subtract amount
            break;
        case TX_TRANSFER:
            if (tx.from == tx.to) return 0;     // disallow self-transfer
            if (bank->balances[tx.from] + 1e-9 < tx.amount) return 0;       // require sufficient funds
            bank->balances[tx.from] -= tx.amount;       // move money
            bank->balances[tx.to] += tx.amount;

            bank->graph[tx.from][tx.to] = 1;        // record an edge in the adjacency matrix representing a transfer from->to
            break;
        default:        // return if unknown type
            return 0;
    }

    if (bank->undo_top + 1 < CAPACITY) {        // push successful transaction onto the undo stack is space available
        bank->undo_top++;
        bank->undo[bank->undo_top] = tx;
    }
    return 1;
}

int brobankUndo(BroBank *bank) {
    /* TODO: reverse most recent successful transaction. */
    if (!bank) return 0;
    if (bank->undo_top < 0) return 0;       // nothing to undo
    Transaction tx = bank->undo[bank->undo_top];        // pop last successful tx
    bank->undo_top--;

    switch (tx.type) {      // reverse based on type:
        case TX_DEPOSIT:
            bank->balances[tx.from] -= tx.amount;       // subtract deposit amount
            break;
        case TX_WITHDRAW:
            bank->balances[tx.from] += tx.amount;       // restore withdrawn amount
            break;
        case TX_TRANSFER:
            bank->balances[tx.to] -= tx.amount;     // move funds back
            bank->balances[tx.from] += tx.amount;

            bank->graph[tx.from][tx.to] = 0;        // remove the recorded transfer edge
            break;
        default:
            return 0;
    }
    return 1;
}

int brobankBFS(const BroBank *bank, int source, int destination) {
    /* TODO: fewest transfer edges. */
    if (!bank) return -1;
    int n = bank->account_count;        // validate indices
    if (source < 0 || source >= n) return -1;
    if (destination < 0 || destination >= n) return -1;
    if (source == destination) return 0;
    int visited[BROBANK_MAX_ACCOUNTS] = {0};        // initialize BFS arrays
    int dist[BROBANK_MAX_ACCOUNTS];
    for (int i = 0; i < n; ++i) dist[i] = -1;
    Queue q; queueInit(&q);     // start BFS from source
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
    return -1;      // destination is not reachable
}

int brobankDFS(const BroBank *bank, int source, int destination) {
    /* TODO: reachability. */
    if (!bank) return 0;        // check for missing pointer
    int n = bank->account_count;
    if (source < 0 || source >= n) return 0;
    if (destination < 0 || destination >= n) return 0;
    if (source == destination) return 1;        
    int visited[BROBANK_MAX_ACCOUNTS] = {0};        // DFS using stack
    Stack s; stackInit(&s);
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
    return 0;       // not reachable
}