
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

char expr[100];
int i = 0, tempVar = 1;


char* parseExpression();
char* parseFactor();
char* parseTerm();

char* newTemp() {
    char* temp = (char*)malloc(10);
    sprintf(temp, "t%d", tempVar++);
    return temp;
}

void generateTAC(char* result, char op, char* arg1, char* arg2) {
    printf("%s = %s %c %s\n", result, arg1, op, arg2);
}

char* parseFactor() {
    if (expr[i] == '(') {
        i++;
        char* temp = parseExpression();
        i++;
        return temp;
    } else {
        char* operand = (char*)malloc(10);
        operand[0] = expr[i++];
        operand[1] = '\0';
        return operand;
    }
}

char* parseTerm() {
    char* left = parseFactor();
    while (expr[i] == '*' || expr[i] == '/') {
        char op = expr[i++];
        char* right = parseFactor();
        char* temp = newTemp();
        generateTAC(temp, op, left, right);
        left = temp;
    }
    return left;
}

char* parseExpression() {
    char* left = parseTerm();
    while (expr[i] == '+' || expr[i] == '-') {
        char op = expr[i++];
        char* right = parseTerm();
        char* temp = newTemp();
        generateTAC(temp, op, left, right);
        left = temp;
    }
    return left;
}

int main() {
    printf("Enter an arithmetic expression: ");
    scanf("%s", expr);
    printf("\nThree-Address Code:\n");
    parseExpression();
    return 0;
}
