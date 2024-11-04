#include <stdio.h>

int arr[10][10] = {0}, visited[10] = {0};
int n, t, i, j, s1, s2;
char trans;

void closure(int i) {
    visited[i] = 1;
    for (j = 0; j < n; j++) {
        if (arr[i][j] == 1 && visited[j] != 1) {
            printf(", q%d", j);
            closure(j);
        }
    }
}

int main() {
    printf("\nEnter the number of states: ");
    scanf("%d", &n);
    
    printf("Enter number of transitions: ");
    scanf("%d", &t);
    
    printf("Enter transitions (format: state1 e state2 for epsilon transitions):\n");
    for (i = 0; i < t; i++) {
        scanf("%d %c %d", &s1, &trans, &s2);
        if (trans == 'e') {
            arr[s1][s2] = 1;
        }
    }
    
    printf("\nThe epsilon closures are:");
    for (i = 0; i < n; i++) {
        // Reset visited array for each state
        for (j = 0; j < n; j++) visited[j] = 0;

        printf("\nState q%d : {q%d", i, i);
        closure(i);
        printf("}");
    }
    
    printf("\n");
    return 0;
}

/*
Enter the number of states:
3
Enter number of transitions:
2
Enter transitions (format: state1 e state2 for epsilon transitions):
0 e 1
1 e 2

*/