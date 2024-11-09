#include <stdio.h>
#include <ctype.h>
#include <string.h>

int is_keyword(const char *str) {
    return strcmp(str, "int") == 0 || strcmp(str, "float") == 0 || strcmp(str, "char") == 0;
}

void process_file(FILE *file) {
    char ch, buffer[256];
    int i = 0, in_comment = 0;

    while ((ch = fgetc(file)) != EOF) {
        if (in_comment) {  // If inside multi-line comment
            if (ch == '*' && (ch = fgetc(file)) == '/') {
                in_comment = 0;
                printf("multi-line comment end\n");
            }
        } 
        else if (ch == '/' && (ch = fgetc(file)) == '/') {  // Single-line comment
            printf("single-line comment\n");
            while ((ch = fgetc(file)) != EOF && ch != '\n');
        }
        else if (ch == '/' && ch == '*') {  // Multi-line comment start
            in_comment = 1;
            printf("multi-line comment start\n");
        }
        else if (isalpha(ch) || ch == '_') {  // Keyword or identifier
            buffer[i++] = ch;
            while ((ch = fgetc(file)) != EOF && (isalnum(ch) || ch == '_')) {
                buffer[i++] = ch;
            }
            buffer[i] = '\0';
            i = 0;
            ungetc(ch, file);
            printf("%s: %s\n", is_keyword(buffer) ? "keyword" : "identifier", buffer);
        }
        else if (isdigit(ch)) {  // Number
            buffer[i++] = ch;
            while ((ch = fgetc(file)) != EOF && isdigit(ch)) {
                buffer[i++] = ch;
            }
            buffer[i] = '\0';
            i = 0;
            ungetc(ch, file);
            printf("number: %s\n", buffer);
        }
        else if (ch == '+') printf("plus operator\n");
        else if (ch == '-') printf("minus operator\n");
        else if (ch == '*') printf("minus operator\n");
        else if (ch == '/') printf("minus operator\n");
        else if (ch == ';') printf("semicolon\n");
        else if (!isspace(ch)) printf("unknown character: %c\n", ch);
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
