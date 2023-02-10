#include <stdio.h>
#include <stdlib.h>

typedef struct Task {
    int low;
    int high;
} Task;

typedef struct Stack {
    Task *data;
    int capacity;
    int top;
} Stack;

// операции над стеком взяты из презентации
Stack *init_stack(int n) {
    Stack *new_stack = (Stack *)malloc(sizeof(Stack));
    new_stack->capacity = n;
    new_stack->top = 0;
    new_stack->data = (Task *)malloc(n * sizeof(Task));
    return new_stack;
}

int stack_empty(Stack *stack_ent) {
    if (stack_ent->top == 0) {
        return 1;
    } else {
        return 0;
    }
}

void push(Stack *stack_ent, int low, int high) {
    if (!(stack_ent->top == stack_ent->capacity)) {
        (stack_ent->data[stack_ent->top]).low = low;
        (stack_ent->data[stack_ent->top]).high = high;
        stack_ent->top++;
    }
}

Task pop(Stack *stack_ent) {
    stack_ent->top--;
    return stack_ent->data[stack_ent->top];
}

void swap(int *base, int ind1, int ind2) {
    int temp = base[ind1];
    base[ind1] = base[ind2];
    base[ind2] = temp;
}

// алгоритм из презентации
int partition(int *base, int low, int high) {
    int median = low;
    for (int i = low; i < high - 1; i++) {
        if (base[i] < base[high - 1]) {
            swap(base, i, median);
            median++;
        }
    }
    swap(base, median, high - 1);
    return median;
}

void quicksort(int *base, int arr_size) {
    Stack *stack_ent = (Stack *)init_stack(arr_size);
    push(stack_ent, 0, arr_size);
    while (!stack_empty(stack_ent)) {
        Task cur_task = pop(stack_ent);
        int low = cur_task.low;
        int high = cur_task.high;
        if (low < high) {
            int median = partition(base, low, high);
            push(stack_ent, low, median);
            push(stack_ent, median + 1, high);
        }
    }
    free(stack_ent->data);
    free(stack_ent);
}

int main(int argc, char **argv) {
    int n;
    scanf("%i", &n);
    int *arr = (int *)malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) {
        scanf("%i", &arr[i]);
    }
    quicksort(arr, n);
    for (int i = 0; i < n; i++) {
        printf("%i ", arr[i]);
    }
    free(arr);
    return 0;
}