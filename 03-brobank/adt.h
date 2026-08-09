#ifndef ADT_H
#define ADT_H
#define CAPACITY 64
typedef struct { int data[CAPACITY]; int top; } Stack;
typedef struct { int data[CAPACITY]; int front, rear, count; } Queue;
void stackInit(Stack *s);
int stackPush(Stack *s, int value);
int stackPop(Stack *s, int *value);
int stackIsEmpty(const Stack *s);
int stackIsFull(const Stack *s);
void queueInit(Queue *q);
int enqueue(Queue *q, int value);
int dequeue(Queue *q, int *value);
int queueIsEmpty(const Queue *q);
int queueIsFull(const Queue *q);
#endif