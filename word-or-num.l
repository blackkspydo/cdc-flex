%{
	/*To check if a given string is a word or a digit*/
#undef yywrap
int yywrap(void) { return 1; }
void display(char[],int);
int flag;

%}

%%

[a-zA-Z]+ {
	int flag=1;
	display(yytext,flag);
	return 1;
}

[0-9]+ {
	int flag=0;
	display(yytext,flag);
	return 1;
}

.+ {
	int flag=-1;
	display(yytext,flag);
	return 1;
}

%%

void display(char a[],int flag)
{
	if(flag==1)
		printf("The given string = %s  is a word \n",a);
	if(flag==0)
		printf("The given string = %s  is a number \n",a);
	if(flag==-1)
		printf("The given string = %s  is everything \n",a);
}	

int main(void)
{
	printf("Enter a string: ");
	yylex();
	return 0;
}