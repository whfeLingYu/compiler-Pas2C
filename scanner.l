%{
#define YYSTYPE char *
#include "y.tab.h"
int cur_line = 1;
void yyerror(const char *msg);
void unrecognized_char(char c);
%}

OPERATOR        [-/+*()=;]
DIGIT [1-9][0-9]*|0
NUM {DIGIT}*(\.{DIGIT})?(E(\+|-)?{DIGIT})?
IDENTIFIER      [_a-zA-Z][_a-zA-Z0-9]*
WHITESPACE      [ \t]*

%%
{OPERATOR}      { return yytext[0]; }
{NUM}       	{ yylval = strdup(yytext); return T_IntConstant; }
{IDENTIFIER}    { yylval = strdup(yytext); return T_Identifier; }
{WHITESPACE}    { /* ignore every whitespcace */ }
\n              { cur_line++; }
.               { unrecognized_char(yytext[0]); }
%%

int yywrap(void) { 
    return 1;
}

void unrecognized_char(char c) {
    char buf[32] = "Unrecognized character: ?";
    buf[24] = c;
    yyerror(buf);
}

void yyerror(const char *msg) {
	printf("incorrect syntax!\n");
	printf("the program terminated\n");
	system("pause");
    exit(1);
}