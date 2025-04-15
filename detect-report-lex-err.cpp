#include <stdio.h>
#include <ctype.h>
#include <string.h>

int isValidOperator(char ch) {
    return ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '=' || ch == '(' || ch == ')';
}

int isDelimiter(char ch) {
    return isspace(ch) || isValidOperator(ch);
}

int isValidIdentifier(char *token) {
    if (!isalpha(token[0]) && token[0] != '_') return 0;
    for (int i = 1; token[i]; i++) {
        if (!isalnum(token[i]) && token[i] != '_')
            return 0;
    }
    return 1;
}

int isValidNumber(char *token) {
    int dotCount = 0;
    for (int i = 0; token[i]; i++) {
        if (token[i] == '.') {
            dotCount++;
            if (dotCount > 1) return 0;
        } else if (!isdigit(token[i])) {
            return 0;
        }
    }
    return 1;
}

void reportLexicalErrors(char *input) {
    char token[100];
    int i = 0, j = 0;
    int errorFound = 0;

    while (input[i] != '\0') {
        if (isDelimiter(input[i])) {
            if (j != 0) {
                token[j] = '\0';

                // Check if it starts with a digit and contains letters
                int hasAlpha = 0;
                for (int k = 0; token[k]; k++) {
                    if (isalpha(token[k])) {
                        hasAlpha = 1;
                        break;
                    }
                }

                if (isdigit(token[0])) {
                    if (hasAlpha) {
                        printf("Lexical Error: Invalid identifier '%s' (starts with digit).\n", token);
                        errorFound = 1;
                    } else if (!isValidNumber(token)) {
                        printf("Lexical Error: Invalid number '%s'.\n", token);
                        errorFound = 1;
                    }
                } else if (isalpha(token[0]) || token[0] == '_') {
                    if (!isValidIdentifier(token)) {
                        printf("Lexical Error: Invalid identifier '%s'.\n", token);
                        errorFound = 1;
                    }
                } else {
                    printf("Lexical Error: Unknown token '%s'.\n", token);
                    errorFound = 1;
                }
                j = 0;
            }

            // Handle single-character operators
            if (isValidOperator(input[i])) {
                // Valid operator — do nothing
            } else if (!isspace(input[i])) {
                printf("Lexical Error: Invalid character '%c'\n", input[i]);
                errorFound = 1;
            }

            i++;
        } else {
            token[j++] = input[i++];
        }
    }

    // Check the last token if any
    if (j != 0) {
        token[j] = '\0';

        int hasAlpha = 0;
        for (int k = 0; token[k]; k++) {
            if (isalpha(token[k])) {
                hasAlpha = 1;
                break;
            }
        }

        if (isdigit(token[0])) {
            if (hasAlpha) {
                printf("Lexical Error: Invalid identifier '%s' (starts with digit).\n", token);
                errorFound = 1;
            } else if (!isValidNumber(token)) {
                printf("Lexical Error: Invalid number '%s'.\n", token);
                errorFound = 1;
            }
        } else if (isalpha(token[0]) || token[0] == '_') {
            if (!isValidIdentifier(token)) {
                printf("Lexical Error: Invalid identifier '%s'.\n", token);
                errorFound = 1;
            }
        } else {
            printf("Lexical Error: Unknown token '%s'.\n", token);
            errorFound = 1;
        }
    }

    if (!errorFound)
        printf("No lexical errors found.\n");
}

int main() {
    char input[200];
    printf("Enter the input string: ");
    fgets(input, sizeof(input), stdin);
    input[strcspn(input, "\n")] = '\0';  // Remove newline
    reportLexicalErrors(input);
    return 0;
}