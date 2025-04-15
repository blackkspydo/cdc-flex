#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <stdlib.h>

#define MAX 100

// Stack for characters (used in conversion)
char charStack[MAX];
int charTop = -1;

void pushChar(char c) {
    if (charTop < MAX - 1) {
        charStack[++charTop] = c;
    } else {
        printf("Error: Character stack overflow\n");
        exit(1);
    }
}

char popChar() {
    if (charTop >= 0) {
        return charStack[charTop--];
    } else {
        printf("Error: Character stack underflow\n");
        exit(1);
    }
}

char peekChar() {
    return charStack[charTop];
}

int isOperator(char c) {
    return c == '+' || c == '-' || c == '*' || c == '/' || c == '^';
}

int precedence(char c) {
    if (c == '^') return 3;
    if (c == '*' || c == '/') return 2;
    if (c == '+' || c == '-') return 1;
    return 0;
}

int isRightAssociative(char c) {
    return c == '^'; // Right-associative
}

// Reverse a string
void reverse(char* exp) {
    int i, j;
    char temp;
    for (i = 0, j = strlen(exp) - 1; i < j; i++, j--) {
        temp = exp[i];
        exp[i] = exp[j];
        exp[j] = temp;
    }
}

// Swap '(' with ')'
void swapParentheses(char* exp) {
    for (int i = 0; exp[i]; i++) {
        if (exp[i] == '(') exp[i] = ')';
        else if (exp[i] == ')') exp[i] = '(';
    }
}

// Convert infix to prefix (assumes space-separated tokens)
void infixToPrefix(char* infix, char* prefix) {
    reverse(infix);
    swapParentheses(infix);
    charTop = -1;

    char* token = strtok(infix, " ");
    char tempPrefix[MAX][MAX];
    int j = 0;

    while (token != NULL) {
        char c = token[0];

        if (isalnum(c)) {
            strcpy(tempPrefix[j++], token);
        }
        else if (c == '(') {
            pushChar(c);
        }
        else if (c == ')') {
            while (charTop != -1 && peekChar() != '(') {
                char op[2] = {popChar(), '\0'};
                strcpy(tempPrefix[j++], op);
            }
            popChar(); // Pop '('
        }
        else if (isOperator(c)) {
            while (charTop != -1 && (
                (precedence(peekChar()) > precedence(c)) ||
                (precedence(peekChar()) == precedence(c) && !isRightAssociative(c))
            )) {
                char op[2] = {popChar(), '\0'};
                strcpy(tempPrefix[j++], op);
            }
            pushChar(c);
        }

        token = strtok(NULL, " ");
    }

    while (charTop != -1) {
        char op[2] = {popChar(), '\0'};
        strcpy(tempPrefix[j++], op);
    }

    // Reverse the final result
    prefix[0] = '\0';
    for (int i = j - 1; i >= 0; i--) {
        strcat(prefix, tempPrefix[i]);
        if (i > 0) strcat(prefix, " ");
    }
}

// Evaluate prefix (assumes space-separated and digits only)
int evaluatePrefix(char* exp) {
    int intStack[MAX];
    int intTop = -1;

    // Tokenize in reverse
    char* tokens[MAX];
    int count = 0;

    char* token = strtok(exp, " ");
    while (token != NULL) {
        tokens[count++] = token;
        token = strtok(NULL, " ");
    }

    for (int i = count - 1; i >= 0; i--) {
        if (isdigit(tokens[i][0])) {
            intStack[++intTop] = atoi(tokens[i]);
        }
        else if (isOperator(tokens[i][0])) {
            if (intTop < 1) {
                printf("Error: Insufficient operands\n");
                exit(1);
            }
            int op1 = intStack[intTop--];
            int op2 = intStack[intTop--];
            int result;

            switch (tokens[i][0]) {
                case '+': result = op1 + op2; break;
                case '-': result = op1 - op2; break;
                case '*': result = op1 * op2; break;
                case '/': result = op1 / op2; break;
                case '^': result = (int)pow(op1, op2); break;
            }

            intStack[++intTop] = result;
        }
    }

    return intStack[intTop];
}



int isExpressionNumeric(char* prefix) {
    char exprCopy[MAX];
    strcpy(exprCopy, prefix);
    char* token = strtok(exprCopy, " ");
    while (token != NULL) {
        if (isalpha(token[0])) return 0;
        token = strtok(NULL, " ");
    }
    return 1;
}

int main() {
    char infix[MAX], prefix[MAX];

    printf("Enter an infix expression (space-separated, e.g., ( 5 + 3 ) * 2): ");
    fgets(infix, MAX, stdin);
    infix[strcspn(infix, "\n")] = '\0'; // remove newline

    infixToPrefix(infix, prefix);

    printf("Prefix Expression: %s\n", prefix);

    if (isExpressionNumeric(prefix)) {
        char evalPrefix[MAX];
        strcpy(evalPrefix, prefix); // Avoid modifying the original
        int result = evaluatePrefix(evalPrefix);
        printf("Evaluated Result: %d\n", result);
    } else {
        printf("Evaluation skipped: expression contains variables.\n");
    }

    return 0;
}
