%{
    #include <stdio.h>
    #include <string.h>
%}

%%

"int"|"char"|"return"|"if"|"else"|"while"|"for"|"do"|"break"|"continue"|"switch"|"case" {
    printf("KEYWORD: %s\n", yytext);
}

[a-zA-Z_][a-zA-Z0-9_]* {
    printf("IDENTIFIER: %s\n", yytext);
}

[0-9]+ {
    printf("NUMBER: %s\n", yytext);
}

[+\-*/=;{}()\[\]] {
    printf("SYMBOL: %s\n", yytext);
}

[\t\n ]+  { /* Ignore Whitespace */ }

. {
    printf("UNKNOWN: %s\n", yytext);
}

%%

int main() {
    printf("Enter input (Ctrl+C to end):\n");
    yylex();
    return 0;
}

int yywrap() {
    return 1;  // End of input
}
