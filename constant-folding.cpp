// WRITE A PROGRAM TO PERFORM CONSTANT FOLDING AND CONSTANT PROPAGATION IN INTERMEDIATE CODE GENERATION PROGRAM:
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define MAX 100

typedef struct {
    char result[10], op1[10], op[5], op2[10];
} Statement;

typedef struct {
    char name[10];
    int value;
    int valid;
} Constant;

int isNumber(char *str) {
    for (int i = 0; str[i]; i++) {
        if (!isdigit(str[i])) return 0;
    }
    return 1;
}

int getConstantValue(Constant constTable[], int count, char *name, int *val) {
    for (int i = 0; i < count; i++) {
        if (strcmp(constTable[i].name, name) == 0 && constTable[i].valid) {
            *val = constTable[i].value;
            return 1;
        }
    }
    return 0;
}

int compute(char *op, int val1, int val2) {
    if (strcmp(op, "+") == 0) return val1 + val2;
    if (strcmp(op, "-") == 0) return val1 - val2;
    if (strcmp(op, "*") == 0) return val1 * val2;
    if (strcmp(op, "/") == 0 && val2 != 0) return val1 / val2;
    return 0;
}

int main() {
    Statement stmts[MAX];
    Constant constTable[MAX];
    int n;

    printf("Enter number of statements: ");
    scanf("%d", &n);
    getchar();

    for (int i = 0; i < n; i++) {
        printf("Enter statement %d (e.g., t1 = a + b): ", i + 1);
        scanf("%s = %s %s %s", stmts[i].result, stmts[i].op1, stmts[i].op, stmts[i].op2);
    }

    printf("\nAfter Constant Folding and Propagation:\n");

    int constCount = 0;

    for (int i = 0; i < n; i++) {
        int val1, val2, isConst1 = 0, isConst2 = 0;

        if (isNumber(stmts[i].op1)) {
            val1 = atoi(stmts[i].op1);
            isConst1 = 1;
        } else if (getConstantValue(constTable, constCount, stmts[i].op1, &val1)) {
            isConst1 = 1;
        }

        if (isNumber(stmts[i].op2)) {
            val2 = atoi(stmts[i].op2);
            isConst2 = 1;
        } else if (getConstantValue(constTable, constCount, stmts[i].op2, &val2)) {
            isConst2 = 1;
        }
        if (isConst1 && isConst2) {
            int result = compute(stmts[i].op, val1, val2);
            printf("%s = %d\n", stmts[i].result, result);

            strcpy(constTable[constCount].name, stmts[i].result);
            constTable[constCount].value = result;
            constTable[constCount].valid = 1;
            constCount++;
        } else {
            char left[10], right[10];

            if (isConst1) sprintf(left, "%d", val1);
            else strcpy(left, stmts[i].op1);

            if (isConst2) sprintf(right, "%d", val2);
            else strcpy(right, stmts[i].op2);

            printf("%s = %s %s %s\n", stmts[i].result, left, stmts[i].op, right);

            strcpy(constTable[constCount].name, stmts[i].result);
            constTable[constCount].valid = 0;
            constCount++;
        }
    }

    return 0;
}