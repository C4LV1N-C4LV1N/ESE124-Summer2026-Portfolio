#include "adt.h"

void stackInit(Stack *s) {
    if (!s) return;
    s->top = -1;
}

int stackPush(Stack *s, int value) {
    if (!s) return 0;
    if (s->top >= CAPACITY - 1) return 0;
    s->top++;
    s->data[s->top] = value;
    return 1;
}

int stackPop(Stack *s, int *value) {
    if (!s || s->top < 0) return 0;
    if (value) *value = s->data[s->top];
    s->top--;
    return 1;
}

int stackIsEmpty(const Stack *s) {
    return !s || s->top < 0;
}

int stackIsFull(const Stack *s) {
    return s && s->top >= CAPACITY - 1;
}

void queueInit(Queue *q) {
    if (!q) return;
    q->front = 0;
    q->rear = -1;
    q->count = 0;
}

int enqueue(Queue *q, int value) {
    if (!q) return 0;
    if (q->count >= CAPACITY) return 0;
    q->rear = (q->rear + 1) % CAPACITY;
    q->data[q->rear] = value;
    q->count++;
    return 1;
}

int dequeue(Queue *q, int *value) {
    if (!q || q->count <= 0) return 0;
    if (value) *value = q->data[q->front];
    q->front = (q->front + 1) % CAPACITY;
    q->count--;
    return 1;
}

int queueIsEmpty(const Queue *q) {
    return !q || q->count <= 0;
}

int queueIsFull(const Queue *q) {
    return q && q->count >= CAPACITY;
}
