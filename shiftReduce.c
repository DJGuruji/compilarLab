#include <stdio.h>
#include <string.h>

#define MAX 100

char stack[MAX];
int top = -1;

// Push a character onto the stack
void push(char symbol) {
    if (top < MAX - 1) {
        stack[++top] = symbol;
    }
}

// Pop the top character from the stack
void pop() {
    if (top >= 0) {
        top--;
    }
}

// Reduce the stack content based on the rules
int reduce() {
    // Check if 'id' is at the top of the stack
    if (top >= 1 && stack[top - 1] == 'i' && stack[top] == 'd') {
        pop(); // Remove 'd'
        stack[top] = 'E'; // Replace 'i' with 'E'
        return 1;
    }
    // Check if 'E+E' is at the top of the stack
    if (top >= 2 && stack[top] == 'E' && stack[top - 1] == '+' && stack[top - 2] == 'E') {
        pop(); pop(); // Remove '+' and 'E'
        stack[top] = 'E'; // Replace with 'E'
        return 1;
    }
    // Check if 'E*E' is at the top of the stack
    if (top >= 2 && stack[top] == 'E' && stack[top - 1] == '*' && stack[top - 2] == 'E') {
        pop(); pop(); // Remove '*' and 'E'
        stack[top] = 'E'; // Replace with 'E'
        return 1;
    }
    // Check if '(E)' is at the top of the stack
    if (top >= 2 && stack[top] == ')' && stack[top - 1] == 'E' && stack[top - 2] == '(') {
        pop(); pop(); // Remove ')' and '('
        stack[top] = 'E'; // Replace with 'E'
        return 1;
    }
    return 0; // No reduction happened
}

// Print the current content of the stack
void printStack() {
    for (int i = 0; i <= top; i++) {
        printf("%c", stack[i]);
    }
    printf("\n");
}

int main() {
    char input[MAX];
    int i = 0;

    printf("Enter the input string (use 'id' for identifier): ");
    scanf("%s", input);

    printf("\nInput: %s\n", input);
    printf("Stack operations:\n");

    while (i < strlen(input)) {
        // Shift operation
        push(input[i]);
        printStack();
        i++;

        // If 'd' follows 'i', treat it as 'id'
        if (input[i - 1] == 'i' && input[i] == 'd') {
            push(input[i]);
            printStack();
            i++;
        }

        // Try to reduce after each shift
        while (reduce()) {
            printStack(); // Print stack after successful reduction
        }
    }

    // Final check
    if (top == 0 && stack[top] == 'E') {
        printf("The input string is accepted by the grammar.\n");
    } else {
        printf("The input string is not accepted by the grammar.\n");
    }

    return 0;
}
