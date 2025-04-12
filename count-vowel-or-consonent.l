%{
    /* To count vowels and consonants in the given string */
    int yywrap() {
        return 1;
    }

    int vowels = 0;
    int consonants = 0;
%}

%%

[aAeEiIoOuU] {  /* Vowel characters */
    vowels++;
}

[b-df-hj-np-tv-z] {  /* Lowercase consonants */
    consonants++;
}

[B-DF-HJ-NP-TV-Z] {  /* Uppercase consonants */
    consonants++;
}

\n  { /* Terminate scanning on newline */
    yyterminate();
}

.   { /* Ignore other characters */ }
%%

int main() {
    printf("Enter a string: ");
    fflush(stdout);  // Ensure prompt is displayed before input
    yylex();
    
    // Output the counts
    printf("Vowels: %d\n", vowels);
    printf("Consonants: %d\n", consonants);
    
    return 0;
}