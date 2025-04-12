%{ 
#include <stdio.h> 
#include <string.h> 
int i = 0; 
%} 

%% 
[a-zA-Z0-9]+  { i++; }  // Matches valid words (non-empty)
[\t\r ]+      { }       // Ignore spaces and tabs
\n            { printf("The total number of words are: %d\n", i); i = 0; }  // Print word count and reset for new line

%% 

int yywrap(void) { return 1; } 

int main() {    
    printf("Enter text (Ctrl+D to end):\n");
    yylex();  // Start lexical analysis
    return 0; 
}
