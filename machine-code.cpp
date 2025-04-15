#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define MAX 100

typedef struct {
    char result[10];
    char arg1[10];
    char op;
    char arg2[10];
} TAC;

TAC code[MAX];
int count = 0;

// Function to parse expressions like t1=a*b (no spaces)
void parseTAC(char line[]) {
    TAC t;
    int i = 0, j = 0;

    // Extract result (e.g., "t1")
    while (line[i] != '=' && line[i] != '\0') {
        t.result[j++] = line[i++];
    }
    t.result[j] = '\0';
    i++; // skip '='

    // Extract arg1
    j = 0;
    while (isalnum(line[i])) {
        t.arg1[j++] = line[i++];
    }
    t.arg1[j] = '\0';

    // Operator
    t.op = line[i++];

    // Extract arg2
    j = 0;
    while (isalnum(line[i])) {
        t.arg2[j++] = line[i++];
    }
    t.arg2[j] = '\0';

    code[count++] = t;
}

void generateMachineCode() {
    printf("\nSimplified Machine Code:\n");
    for (int i = 0; i < count; i++) {
        printf("LOAD R0, %s\n", code[i].arg1);
        switch (code[i].op) {
            case '+': printf("ADD R0, %s\n", code[i].arg2); break;
            case '-': printf("SUB R0, %s\n", code[i].arg2); break;
            case '*': printf("MUL R0, %s\n", code[i].arg2); break;
            case '/': printf("DIV R0, %s\n", code[i].arg2); break;
        }
        printf("STORE %s, R0\n\n", code[i].result);
    }
}

int main() {
    int n;
    char line[50];

    printf("Enter number of three-address code statements: ");
    scanf("%d", &n);
    getchar(); // clear newline

    printf("Enter the TAC statements (e.g., t1=a+b):\n");
    for (int i = 0; i < n; i++) {
        fgets(line, sizeof(line), stdin);
        line[strcspn(line, "\n")] = '\0'; // Remove newline
        parseTAC(line);
    }

    generateMachineCode();
    return 0;
}