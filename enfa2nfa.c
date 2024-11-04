#include <stdio.h>
#include <string.h>

#define MAX_TRANS 50
#define MAX_STATES 20

char enfa[MAX_TRANS][3]; // Store ENFA transitions
char finalStates[MAX_STATES]; // Store final states
int nTransitions;

// Function to check if a character exists in a string
int isin(char c, char str[]) {
    for (int i = 0; i < strlen(str); i++)
        if (str[i] == c)
            return 1;
    return 0;
}

// Function to add a character to a string if it doesn't already exist
void add(char str[], char c) {
    if (!isin(c, str)) {
        int len = strlen(str);
        str[len] = c;
        str[len + 1] = '\0';
    }
}

// Recursive function to handle epsilon transitions
void addState(char start, char end) {
    for (int i = 0; i < nTransitions; i++) {
        if (enfa[i][0] == end) {
            if (enfa[i][1] != 'e') {
                printf("%c %c %c\n", start, enfa[i][1], enfa[i][2]);
            } else {
                addState(start, enfa[i][2]);
            }
        }
    }
}

int main() {
    printf("Enter number of transitions: ");
    scanf("%d", &nTransitions);

    printf("Enter transitions (format: state symbol state):\n");
    for (int i = 0; i < nTransitions; i++) {
        scanf(" %c %c %c", &enfa[i][0], &enfa[i][1], &enfa[i][2]);
    }

    printf("Enter final states (without spaces): ");
    scanf("%s", finalStates); // Enter final states as a single string

    printf("\nNFA transitions:\n");
    for (int i = 0; i < nTransitions; i++) {
        if (enfa[i][1] != 'e') {
            printf("%c %c %c\n", enfa[i][0], enfa[i][1], enfa[i][2]);
        } else {
            addState(enfa[i][0], enfa[i][2]);
        }
    }

    printf("Final States: {%s}\n", finalStates);
    return 0;
}


/*
Enter number of transitions: 4       
Enter transitions (format: state symbol state):
A a B
B e C
C b D
D e A
Enter final states (without spaces): C

*/