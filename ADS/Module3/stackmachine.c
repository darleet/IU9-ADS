#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 1000000

// для всех ключевых слов я предварительно
// вычислил их хэш при помощи calc_hash(),
// чтобы получить красивый switch case
#define CONST 92480
#define ADD 5540
#define SUB 7046
#define MUL 6576
#define DIV 5818
#define MAX 6508
#define MIN 6530
#define NEG 6587
#define DUP 5860
#define SWAP 28292

typedef struct Stack {
    int *arr;
    int capacity;
    int top;
} Stack;

Stack *init_stack(int n) {
    Stack *new_stack = (Stack *)malloc(sizeof(Stack));
    new_stack->capacity = n;
    new_stack->top = 0;
    new_stack->arr = (int *)malloc(n * sizeof(int));
    return new_stack;
}

void push(Stack *stack_ent, int x) {
    if (!(stack_ent->top == stack_ent->capacity)) {
        stack_ent->arr[stack_ent->top] = x;
        stack_ent->top++;
    }
}

int pop(Stack *stack_ent) {
    stack_ent->top--;
    return stack_ent->arr[stack_ent->top];
}

int calc_hash(char *str) {
    int hash = *str;
    int length = strlen(str);
    for(int i = 0; i < length; i++) {
        hash = (hash << 2) + *str;
        str++;
    }
    return hash;
}

void handler(Stack *stack_ent, char *command) {
    int a, b;
    switch (calc_hash(command)) {
        case CONST:
            int x;
            scanf("%i", &x);
            push(stack_ent, x);
            break;

        case ADD:
            a = pop(stack_ent);
            b = pop(stack_ent);
            push(stack_ent, a + b);
            break;

        case SUB:
            a = pop(stack_ent);
            b = pop(stack_ent);
            push(stack_ent, a - b);
            break;
        
        case MUL:
            a = pop(stack_ent);
            b = pop(stack_ent);
            push(stack_ent, a * b);
            break;
        
        case DIV:
            a = pop(stack_ent);
            b = pop(stack_ent);
            push(stack_ent, a / b);
            break;
        
        case MAX:
            a = pop(stack_ent);
            b = pop(stack_ent);
            push(stack_ent, a > b ? a : b);
            break;
        
        case MIN:
            a = pop(stack_ent);
            b = pop(stack_ent);
            push(stack_ent, a < b ? a : b);
            break;
        
        case NEG:
            a = pop(stack_ent);
            push(stack_ent, -a);
            break;
        
        case DUP:
            a = pop(stack_ent);
            push(stack_ent, a);
            push(stack_ent, a);
            break;
        
        case SWAP:
            a = pop(stack_ent);
            b = pop(stack_ent);
            push(stack_ent, a);
            push(stack_ent, b);
            break;
        
        default:
            break;
    }
}

int main(int argc, char **argv) {
    char *command = (char *)malloc(BUFFER_SIZE * sizeof(char));
    Stack *stack_ent = (Stack *)init_stack(BUFFER_SIZE);
    scanf("%s", command);
    while(strcmp(command, "END") != 0) {
        handler(stack_ent, command);
        scanf("%s", command);
    }
    printf("%i", pop(stack_ent));
    free(command);
    free(stack_ent->arr);
    free(stack_ent);
    return 0;
}