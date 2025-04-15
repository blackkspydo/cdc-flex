#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX 100

char expr[MAX];
int i = 0, tempVar = 0;

typedef struct {
    char op;
    char arg1[10];
    char arg2[10];
    char result[10];
} Quadruple;

typedef struct {
    char op;
    char arg1[10];
    char arg2[10];
} Triple;

Quadruple quads[MAX];
Triple triples[MAX];
int quadIndex = 0;

char* newTemp() {
    char* temp = (char*)malloc(10);
    sprintf(temp, "t%d", tempVar++);
    return temp;
}

char* parseExpression(); 
char* parseTerm();
char* parseFactor();

char* parseFactor() {
    if (expr[i] == '(') {
        i++;
        char* temp = parseExpression();
        i++;  // skip ')'
        return temp;
    } else {
        char* op = (char*)malloc(2);
        op[0] = expr[i++];
        op[1] = '\0';
        return op;
    }
}

char* parseTerm() {
    char* left = parseFactor();
    while (expr[i] == '*' || expr[i] == '/') {
        char op = expr[i++];
        char* right = parseFactor();
        char* result = newTemp();

        // Store Quadruple
        strcpy(quads[quadIndex].result, result);
        quads[quadIndex].op = op;
        strcpy(quads[quadIndex].arg1, left);
        strcpy(quads[quadIndex].arg2, right);

        // Store Triple
        triples[quadIndex].op = op;
        strcpy(triples[quadIndex].arg1, left);
        strcpy(triples[quadIndex].arg2, right);

        quadIndex++;
        left = result;
    }
    return left;
}

char* parseExpression() {
    char* left = parseTerm();
    while (expr[i] == '+' || expr[i] == '-') {
        char op = expr[i++];
        char* right = parseTerm();
        char* result = newTemp();

        strcpy(quads[quadIndex].result, result);
        quads[quadIndex].op = op;
        strcpy(quads[quadIndex].arg1, left);
        strcpy(quads[quadIndex].arg2, right);

        triples[quadIndex].op = op;
        strcpy(triples[quadIndex].arg1, left);
        strcpy(triples[quadIndex].arg2, right);

        quadIndex++;
        left = result;
    }
    return left;
}

void printQuadruples() {
    printf("\nQuadruples:\n");
    printf("%-5s %-5s %-5s %-5s\n", "Op", "Arg1", "Arg2", "Result");
    for (int j = 0; j < quadIndex; j++) {
        printf("%-5c %-5s %-5s %-5s\n", quads[j].op, quads[j].arg1, quads[j].arg2, quads[j].result);
    }
}

void printTriples() {
    printf("\nTriples:\n");
    printf("%-5s %-5s %-5s %-5s\n", "Index", "Op", "Arg1", "Arg2");
    for (int j = 0; j < quadIndex; j++) {
        printf("%-5d %-5c %-5s %-5s\n", j, triples[j].op, triples[j].arg1, triples[j].arg2);
    }
}

int main() {
    printf("Enter an arithmetic expression (e.g., (a+b)*(c-d)): ");
    scanf("%s", expr);
    parseExpression();
    printQuadruples();
    printTriples();
    return 0;
}