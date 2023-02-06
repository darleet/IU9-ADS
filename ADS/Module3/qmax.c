#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 1000000

// для всех ключевых слов я предварительно
// вычислил их хэш при помощи calc_hash(),
// чтобы получить красивый switch case
#define ENQ 5913
#define DEQ 5797
#define MAX 6508
#define EMPTY 94953

// структура связки числа с мин. элементом
typedef struct ext_long {
    long value;
    long max;
} ext_long;

// структура "стек"
typedef struct Stack {
    ext_long *data;
    int top;
} Stack;

// структура "очередь"
typedef struct Queue {
    Stack *s1;
    Stack *s2;
    int capacity;
    int counter;
} Queue;

long max(long a, long b) {
    if (a > b) {
        return a;
    }
    return b;
}

// проверка стека на пустоту
int stack_empty(Stack *st_ent) {
    if (st_ent->top == 0) {
        return 1;
    }
    return 0;
}

// добавление элемента в стек
void push(Stack *st_ent, long x) {
    st_ent->data[st_ent->top].value = x;
    if (stack_empty(st_ent)) {
        st_ent->data[st_ent->top].max = x;
    } else {
        long max_el = max(x, st_ent->data[st_ent->top - 1].max);
        st_ent->data[st_ent->top].max = max_el;
    }
    st_ent->top++;
}

// удаление элемента из стека
long pop(Stack *st_ent) {
    if (!stack_empty(st_ent)) {
        st_ent->top--;
        return st_ent->data[st_ent->top].value;
    }
    return -1;
}

long stack_max(Stack *st_ent) {
    if (!stack_empty(st_ent)) {
        return st_ent->data[st_ent->top - 1].max;
    }
    return -1;
}

Stack *init_stack(int n) {
    Stack *new_stack = (Stack *)malloc(sizeof(Stack));
    new_stack->data = (ext_long *)malloc(n * sizeof(ext_long));
    new_stack->top = 0;
    return new_stack;
}

// проверка очереди на пустоту
int queue_empty(Queue *queue_ent) {
    if (stack_empty(queue_ent->s1) && stack_empty(queue_ent->s2)) {
        return 1;
    }
    return 0;
}

// добавление элемента в очередь
void enqueue(Queue *queue_ent, long x) {
    if (queue_ent->counter < queue_ent->capacity) {
        push(queue_ent->s1, x);
        queue_ent->counter++;
    }
}

// удаление элемента из очереди
long dequeue(Queue *queue_ent) {
    if (!queue_empty(queue_ent)) {
        if (stack_empty(queue_ent->s2)) {
            while (!stack_empty(queue_ent->s1)) {
                long element = pop(queue_ent->s1);
                push(queue_ent->s2, element);
            }
        }
        queue_ent->counter--;
        return pop(queue_ent->s2);
    }
    return -1;
}

long queue_max(Queue *queue_ent) {
    if (queue_empty(queue_ent)) {
        return -1;
    } else if (stack_empty(queue_ent->s1)) {
        return stack_max(queue_ent->s2);
    } else if (stack_empty(queue_ent->s2)) {
        return stack_max(queue_ent->s1);
    } else {
        return max(stack_max(queue_ent->s1), stack_max(queue_ent->s2));
    }
    
}

Queue *init_queue(int n) {
    Queue *new_queue = (Queue *)malloc(sizeof(Queue));
    new_queue->s1 = init_stack(n);
    new_queue->s2 = init_stack(n);
    new_queue->capacity = n;
    new_queue->counter = 0;
    return new_queue;
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

void handler(Queue *queue_ent, char *command) {
    switch (calc_hash(command)) {
        case ENQ:
            long x;
            scanf("%li", &x);
            enqueue(queue_ent, x);
            break;
        
        case DEQ:
            printf("%li\n", dequeue(queue_ent));
            break;
        
        case MAX:
            printf("%li\n", queue_max(queue_ent));
            break;
        
        case EMPTY:
            if (queue_empty(queue_ent)) {
                printf("true\n");
            } else {
                printf("false\n");
            }
        
        default:
            break;
    }
}

int main(int argc, char **argv) {
    char *command = (char *)malloc(BUFFER_SIZE * sizeof(char));
    Queue *queue_ent = (Queue *)init_queue(BUFFER_SIZE);
    scanf("%s", command);
    while(strcmp(command, "END") != 0) {
        handler(queue_ent, command);
        scanf("%s", command);
    }
    free(command);
    free(queue_ent->s1->data);
    free(queue_ent->s1);
    free(queue_ent->s2->data);
    free(queue_ent->s2);
    free(queue_ent);
    return 0;
}