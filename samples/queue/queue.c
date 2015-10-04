#include <stdio.h>
#include <stdlib.h>

typedef struct Node{
    void *element;
    struct Node *next;
} Node;

typedef struct {
    Node *head;
    Node *tail;
} Queue;

void enqueue(Queue *queue, Node *node);
Node *dequeue(Queue *queue);

int main(int argc, char *argv[]) {
    Queue q;
    q.head = NULL;
    q.tail = NULL;

    Node n1;
    n1.element = (void *) "John";
    
    Node n2;
    n2.element = (void *) "Smith";

    Node n3;
    n3.element = (void *) "Kevin";

    Node n4;
    n4.element = (void *) "Paulsen";

    enqueue(&q, &n1);
    enqueue(&q, &n2);
    enqueue(&q, &n3);
    enqueue(&q, &n4);

    printf("%s\n", (char *) dequeue(&q)->element);
    printf("%s\n", (char *) dequeue(&q)->element);
    printf("%s\n", (char *) dequeue(&q)->element);
    printf("%s\n", (char *) dequeue(&q)->element);

    return 0;
}

void enqueue(Queue *queue, Node *node) {
    if (queue->head == NULL && queue->tail == NULL) {
        queue->head = node;
        queue->tail = node;
    } else {
        queue->tail->next = node;
        queue->tail = node;
    }
}

Node *dequeue(Queue *queue) {
    Node *result = queue->head;
    queue->head = result->next;
    return result;
}
