#include <stdio.h>
#include <ctype.h>
#include <string.h>

int COMMENT = 0;  // To track multi-line comment state

int is_keyword(const char *str) {
    return strcmp(str, "int") == 0 || strcmp(str, "float") == 0 || strcmp(str, "char") == 0;
}

int is_identifier_start(char ch) {
    return isalpha(ch) || ch == '_';
}

int is_identifier_part(char ch) {
    return isalnum(ch) || ch == '_';
}

void process_file(FILE *file) {
    char ch;
    char buffer[256];
    int i = 0;

    while ((ch = fgetc(file)) != EOF) {
        // Handle single-line comment
        if (ch == '/' && (ch = fgetc(file)) == '/') {
            printf("single-line comment\n");
            while ((ch = fgetc(file)) != EOF && ch != '\n');
        }
        // Handle multi-line comment start
        else if (ch == '/' && (ch = fgetc(file)) == '*') {
            COMMENT = 1;
            printf("multi-line comment start\n");
            while (COMMENT && (ch = fgetc(file)) != EOF) {
                if (ch == '*' && (ch = fgetc(file)) == '/') {
                    COMMENT = 0;
                    printf("multi-line comment end\n");
                }
            }
        }
        // Handle keywords and identifiers
        else if (is_identifier_start(ch)) {
            buffer[i++] = ch;
            while ((ch = fgetc(file)) != EOF && is_identifier_part(ch)) {
                buffer[i++] = ch;
            }
            buffer[i] = '\0';
            i = 0;
            ungetc(ch, file);
            if (!COMMENT) {
                if (is_keyword(buffer)) {
                    printf("keyword: %s\n", buffer);
                } else {
                    printf("identifier: %s\n", buffer);
                }
            }
        }
        // Handle numbers
        else if (isdigit(ch)) {
            buffer[i++] = ch;
            while ((ch = fgetc(file)) != EOF && isdigit(ch)) {
                buffer[i++] = ch;
            }
            buffer[i] = '\0';
            i = 0;
            ungetc(ch, file);
            if (!COMMENT) {
                printf("number: %s\n", buffer);
            }
        }
        // Handle operators and other symbols
        else if (ch == '+') {
            if (!COMMENT) printf("plus operator\n");
        }
        else if (ch == '-') {
            if (!COMMENT) printf("minus operator\n");
        }
        else if (ch == ';') {
            if (!COMMENT) printf("semicolon\n");
        }
        else if (!isspace(ch)) {
            if (!COMMENT) printf("unknown character: %c\n", ch);
        }
    }
}

int main() {
    FILE *file = fopen("input.c", "r");
    if (!file) {
        printf("Could not open the file input.c\n");
        return 1;
    }

    process_file(file);
    fclose(file);
    return 0;
}
