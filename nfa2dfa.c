#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STATES 20
#define MAX_TRANS 50
#define MAX_SYMBOLS 10

char nfa[MAX_TRANS][3]; // Store NFA transitions
char dfa[MAX_TRANS][3]; // Store DFA transitions
char finalStates[MAX_STATES];
int nStates, nTransitions;

void addDfaTransition(char start, char symbol, char end) {
    for (int i = 0; i < MAX_TRANS; i++) {
        if (dfa[i][0] == '\0') { // Empty slot found
            dfa[i][0] = start;
            dfa[i][1] = symbol;
            dfa[i][2] = end;
            break;
        }
    }
}

void convertNfaToDfa() {
    for (int i = 0; i < nTransitions; i++) {
        char start = nfa[i][0];
        char symbol = nfa[i][1];
        char end = nfa[i][2];

        // If the transition symbol is not epsilon
        if (symbol != 'e') {
            addDfaTransition(start, symbol, end);
        }
    }
}

int main() {
    printf("Enter number of states: ");
    scanf("%d", &nStates);

    printf("Enter number of transitions: ");
    scanf("%d", &nTransitions);

    printf("Enter transitions (format: state symbol state):\n");
    for (int i = 0; i < nTransitions; i++) {
        scanf(" %c %c %c", &nfa[i][0], &nfa[i][1], &nfa[i][2]);
    }

    printf("Enter final states (as a string, e.g., q0q1): ");
    scanf("%s", finalStates);

    // Convert NFA to DFA
    convertNfaToDfa();

    printf("\nDFA Transitions:\n");
    for (int i = 0; i < MAX_TRANS; i++) {
        if (dfa[i][0] != '\0') {
            printf("%c %c %c\n", dfa[i][0], dfa[i][1], dfa[i][2]);
        }
    }

    printf("Final States: {%s}\n", finalStates);
    return 0;
}


/*
Enter number of states: 
3
Enter number of transitions: 
4
Enter transitions (format: state symbol state):
q0 a q1
q0 b q2
q1 a q0
q2 b q1
Enter final states (as a string, e.g., q0q1): 
q1

*/