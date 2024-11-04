#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100

char input[MAX];          // Input string
int currentIndex = 0;    // Current index in input

// Function prototypes
void E();  // Parse E
void T();  // Parse T
void F();  // Parse F
void match(char expected);  // Function to match expected characters

// Entry point for the parser
int main() {
    printf("Enter the input string (use 'i' for identifier): ");
    scanf("%s", input);

    // Start parsing
    E();

    // If we have consumed the entire input, it's accepted
    if (input[currentIndex] == '\0') {
        printf("The input string is accepted by the grammar.\n");
    } else {
        printf("The input string is not accepted by the grammar.\n");
    }

    return 0;
}

// Match the expected character and advance the index
void match(char expected) {
    if (input[currentIndex] == expected) {
        currentIndex++; // Advance to the next character
    } else {
        printf("Syntax error: expected '%c', found '%c'.\n", expected, input[currentIndex]);
        exit(1);
    }
}

// Parse E -> E + T | T
void E() {
    T(); // Parse the first T

    // Handle the addition operation
    while (input[currentIndex] == '+') {
        match('+'); // Consume '+'
        T(); // Parse the next T
    }
}

// Parse T -> T * F | F
void T() {
    F(); // Parse the first F

    // Handle the multiplication operation
    while (input[currentIndex] == '*') {
        match('*'); // Consume '*'
        F(); // Parse the next F
    }
}

// Parse F -> (E) | id
void F() {
    if (input[currentIndex] == '(') {
        match('('); // Consume '('
        E(); // Parse the enclosed E
        match(')'); // Consume ')'
    } else if (input[currentIndex] == 'i') {
        match('i'); // Consume identifier
    } else {
        printf("Syntax error: unexpected character '%c'.\n", input[currentIndex]);
        exit(1);
    }
}
