#include <stdio.h>
#include <stdlib.h>

#define STACK_CAPACITY 65535

typedef struct {
    void *element[STACK_CAPACITY];
    int count;
} STACK;

/**
 * Removes an element from the stack
 */
void *pop(STACK *stack);

/**
 * Adds an element into the stack
 */
void push(STACK *stack, void *element);

int main(int argc, char *argv[]){
    STACK stack;
    stack.count = 0;

    push(&stack, (void *) 1);
    push(&stack, (void *) 2);
    push(&stack, (void *) 3);
    push(&stack, (void *) 4);
    push(&stack, (void *) "Hello World");

    printf("Popped Value: %s\n", (char *) pop(&stack));
    printf("Popped Value: %d\n", (int) pop(&stack));
    printf("Popped Value: %d\n", (int) pop(&stack));
    printf("Popped Value: %d\n", (int) pop(&stack));
    printf("Popped Value: %d\n", (int) pop(&stack));

    return 0;
}

void push(STACK *stack, void *element) {
    if (stack == NULL) {
        printf("Error: Stack is null\n");
        exit(1);
    }

    stack->element[stack->count] = element;
    stack->count++;
}

void *pop(STACK *stack) {
    stack->count--;
    return stack->element[stack->count];
}
