#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 4
#define CMD_BUFF_SIZE 100

// для всех ключевых слов я предварительно
// вычислил их хэш при помощи calc_hash(),
// чтобы получить красивый switch case
#define ENQ 5913
#define DEQ 5797
#define EMPTY 94953

// операции над очередью взяты из презентации
typedef struct Queue {
    long *data;
    int capacity;
    int count;
    int head;
    int tail;
} Queue;

Queue *init_queue(int n) {
    Queue *new_queue = (Queue *)malloc(sizeof(Queue));
    new_queue->data = (long *)malloc(n * sizeof(long));
    new_queue->capacity = n;
    new_queue->count = 0;
    new_queue->head = 0;
    new_queue->tail = 0;
    return new_queue;
}

int queue_empty(Queue *q_ent) {
    if (q_ent->count == 0) {
        return 1;
    } 
    return 0;
}

void enqueue(Queue *q_ent, long x) {
    if (q_ent->count == q_ent->capacity) {
        long *new_buff = (long *)malloc(2 * q_ent->capacity * sizeof(long));
        int new_tail = 0;
        for (int i = 0; i < q_ent->count; i++) {
            if (q_ent->head == q_ent->capacity) {
                q_ent->head = 0;
            }
            new_buff[i] = q_ent->data[q_ent->head];
            q_ent->head++;
            new_tail++;
        }
        free(q_ent->data);
        q_ent->data = new_buff;
        q_ent->head = 0;
        q_ent->tail = new_tail;
        q_ent->capacity *= 2;
    }
    q_ent->data[q_ent->tail] = x;
    q_ent->tail++;
    if (q_ent->tail == q_ent->capacity) {
        q_ent->tail = 0;
    }
    q_ent->count++;
}

long dequeue(Queue *q_ent) {
    long x;
    if (!queue_empty(q_ent)) {
        x = q_ent->data[q_ent->head];
        q_ent->head++;
        q_ent->count--;
    } else {
        x = -1;
    }
    if (q_ent->head == q_ent->capacity) {
        q_ent->head = 0;
    }
    return x;
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

void handler(Queue *q_ent, char *command) {
    switch (calc_hash(command)) {
        case ENQ:
            long x;
            scanf("%li", &x);
            enqueue(q_ent, x);
            break;
        
        case DEQ:
            printf("%li\n", dequeue(q_ent));
            break;
        
        case EMPTY:
            if (queue_empty(q_ent)) {
                printf("true\n");
            } else {
                printf("false\n");
            }
        
        default:
            break;
    }
}

int main(int argc, char **argv) {
    char *command = (char *)malloc((CMD_BUFF_SIZE + 1) * sizeof(char));
    Queue *q_ent = (Queue *)init_queue(BUFFER_SIZE);
    scanf("%s", command);
    while(strcmp(command, "END") != 0) {
        handler(q_ent, command);
        scanf("%s", command);
    }
    free(command);
    free(q_ent->data);
    free(q_ent);
    return 0;
}