#include <stdio.h>
#include <ctype.h>
#include <string.h>

#define MAX 10

char prod[MAX][MAX];
int n;

void findFirst(char, char[]);
void findFollow(char, char[]);
int hasEpsilon(char[]);

int main() {
    int i;
    char c, first[MAX], follow[MAX];

    printf("Enter number of productions: ");
    scanf("%d", &n);
    printf("Enter the productions:\n");
    for (i = 0; i < n; i++) {
        scanf("%s", prod[i]);
    }

    printf("Enter non-terminal: ");
    scanf(" %c", &c);

    findFirst(c, first);
    printf("First(%c) = { %s }\n", c, first);

    findFollow(c, follow);
    printf("Follow(%c) = { %s }\n", c, follow);

    return 0;
}

void findFirst(char c, char first[]) {
    int i, j = 0;
    first[0] = '\0';

    for (i = 0; i < n; i++) {
        if (prod[i][0] == c) {
            int k = 2;
            int epsilon_in_all = 1;

            while (prod[i][k]) {
                char next = prod[i][k];
                if (!isupper(next)) {
                    if (!strchr(first, next)) {
                        first[j++] = next;
                    }
                    epsilon_in_all = 0;
                    break;
                } else {
                    char temp[MAX];
                    findFirst(next, temp);

                    int has_epsilon = 0;
                    for (int m = 0; temp[m]; m++) {
                        if (temp[m] != 'e' && !strchr(first, temp[m])) {
                            first[j++] = temp[m];
                        }
                        if (temp[m] == 'e') {
                            has_epsilon = 1;
                        }
                    }

                    if (!has_epsilon) {
                        epsilon_in_all = 0;
                        break;
                    }
                }
                k++;
            }
            if (epsilon_in_all && !strchr(first, 'e')) {
                first[j++] = 'e';
            }
        }
    }
    first[j] = '\0';
}

void findFollow(char c, char follow[]) {
    int i, j = 0;
    follow[0] = '\0';

    if (prod[0][0] == c) follow[j++] = '$';

    for (i = 0; i < n; i++) {
        for (int k = 2; prod[i][k]; k++) {
            if (prod[i][k] == c) {
                char next = prod[i][k + 1];

                if (next && !isupper(next) && !strchr(follow, next)) {
                    follow[j++] = next;
                }

                if (next && isupper(next)) {
                    char firstNext[MAX];
                    findFirst(next, firstNext);
                    for (int m = 0; firstNext[m]; m++) {
                        if (firstNext[m] != 'e' && !strchr(follow, firstNext[m])) {
                            follow[j++] = firstNext[m];
                        }
                    }
                }

                if (!next || (next && strchr(prod[i] + k + 1, 'e'))) {
                    if (prod[i][0] != c) {
                        char followLHS[MAX];
                        findFollow(prod[i][0], followLHS);
                        for (int m = 0; followLHS[m]; m++) {
                            if (!strchr(follow, followLHS[m])) {
                                follow[j++] = followLHS[m];
                            }
                        }
                    }
                }
            }
        }
    }
    follow[j] = '\0';
}

int hasEpsilon(char first[]) {
    for (int i = 0; first[i]; i++) {
        if (first[i] == 'e') {
            return 1;
        }
    }
    return 0;
}
