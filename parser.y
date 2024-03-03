%{
#include <stdio.h>
#include <stdlib.h>

void yyerror(const char *s);
int yylex(void);

/*枚举类型*/
typedef enum { INT_TYPE, REAL_TYPE, BOOLEAN_TYPE, CHAR_TYPE } DataType;

/*符号表*/
typedef struct SymbolTableEntry {
    char* name;
    DataType type;
    struct SymbolTableEntry* next;
} SymbolTableEntry;

/*符号表操作*/
SymbolTableEntry* symbolTable = NULL;

/*创建符号*/
SymbolTableEntry* createSymbol(char* name, DataType type) {
    SymbolTableEntry* entry = (SymbolTableEntry*)malloc(sizeof(SymbolTableEntry));
    entry->name = strdup(name);
    entry->type = type;
    entry->next = symbolTable;
    symbolTable = entry;
    return entry;
}

/*查找符号*/
SymbolTableEntry* findSymbol(char* name) {
    for (SymbolTableEntry* entry = symbolTable; entry != NULL; entry = entry->next) {
        if (strcmp(entry->name, name) == 0) {
            return entry;
        }
    }
    return NULL;
}

%}

%token PROGRAM CONST VAR PROCEDURE FUNCTION BEGIN END
%token INTEGER REAL BOOLEAN CHAR ARRAY
%token IF THEN FOR TO DO READ WRITE OF
%token PLUS MINUS OR MUL DIV MOD AND NOT ASSIGN
%token GREATER EQUAL LESS LE GE LG
%token SEMICOLON COMMA COLON QMARK LBRACKET RBRACKET LBRACE RBRACE LPAREN RPAREN DOT
%token NUMBER IDENTIFIER SINGLECHAR ERROR TEOF STRING
%nonassoc LOWER_THAN_ELSE
%nonassoc ELSE
%type <type_enum> type basic_type  /* 告诉YACC `type` 和 `basic_type` 返回一个类型枚举 */
%start program

%%
program
    : program_head SEMICOLON program_body DOT
    ;

program_head
    : PROGRAM IDENTIFIER LBRACKET idlist RBRACKET
    | PROGRAM IDENTIFIER
    ;

program_body
    : const_declarations var_declarations subprogram_declarations compound_statement
    ;

idlist
    : IDENTIFIER
    | idlist COMMA IDENTIFIER
    ;

const_declarations
    : /* empty */
    | CONST const_declaration SEMICOLON
    ;

const_declaration
    : IDENTIFIER EQUAL const_value
    | const_declaration SEMICOLON IDENTIFIER EQUAL const_value
    ;

const_value
    : NUMBER
    | MINUS NUMBER            /* 正负数(正负数的token流是符号吗？） */
    | PLUS NUMBER
    | STRING/* 字符中的单引号怎么做的？ */
    ;

var_declarations
    : /* empty */
    | VAR var_declaration SEMICOLON
    ;

var_declaration
    : idlist COLON type{
        /* 对于每个变量名，检查是否已经定义 */
       for (int i = 0; i < $1.count; ++i) {
           if (findSymbol($1.names[i])) {
               printf("Semantic error: variable %s is already defined\n", $1.names[i]);
           } else {
               createSymbol($1.names[i], $3);  /* 创建符号 */
           }
       }
    }
    | var_declaration SEMICOLON idlist COLON type{
        /* 同上 */
        for (int i = 0; i < $3.count; ++i) {
            if (findSymbol($3.names[i])) {
                printf("Semantic error: variable %s is already defined\n", $3.names[i]);
            } else {
                createSymbol($3.names[i], $5);  /* 同上 */
            }
        }
    }
    ;

type
    : basic_type  { $$ = $1; }
    | ARRAY LBRACKET period RBRACKET OF basic_type { $$ = ARRAY_TYPE; }
    ;

basic_type
    : INTEGER { $$ = INT_TYPE; }
    | REAL    { $$ = REAL_TYPE; }
    | BOOLEAN { $$ = BOOLEAN_TYPE; }
    | CHAR    { $$ = CHAR_TYPE; }
    ;

period
    : NUMBER DOT DOT NUMBER
    | period COMMA NUMBER DOT DOT NUMBER /* 对于NUMBER定义可能还有bug */
    ;

subprogram_declarations
    : /* empty */
    | subprogram_declarations subprogram SEMICOLON
    ;

subprogram
    : subprogram_head SEMICOLON subprogram_body
    ;

subprogram_head
    : PROCEDURE IDENTIFIER formal_parameter
    | FUNCTION IDENTIFIER formal_parameter COLON basic_type
    ;

formal_parameter
    : /* empty */
    | LPAREN parameter_list RPAREN
    ;

parameter_list
    : parameter
    | parameter_list SEMICOLON parameter
    ;

parameter
    : var_parameter
    | value_parameter
    ;

var_parameter
    : VAR value_parameter
    ;

value_parameter
    : idlist COLON basic_type
    ;

subprogram_body
    : const_declarations var_declarations compound_statement
    ;

compound_statement
    : BEGIN statement_list END
    ;

statement_list
    : statement
    | statement_list SEMICOLON statement
    ;

statement
    : /* empty */
    | variable ASSIGN expression{
        /* 检查变量是否已经定义，检查类型是否匹配 */
        SymbolTableEntry* var = findSymbol($1);
        if (!var) {
            printf("Semantic error: Undefined variable %s\n", $1);
        } else if (var->type != $3.type) {
            printf("Semantic error: Type mismatch in assignment to %s\n", $1);
        }
    }
    | FUNCTION ASSIGN expression /* 这里要func_id？？ */
    | procedure_call
    | compound_statement
    | IF expression THEN statement %prec LOWER_THAN_ELSE
    | IF expression THEN statement ELSE statement
    | FOR IDENTIFIER ASSIGN expression TO expression DO statement
    | READ LPAREN variable_list RPAREN
    | WRITE LPAREN expression_list RPAREN
    ;

variable_list
    : variable
    | variable_list COMMA variable
    ;

variable
    : IDENTIFIER id_varpart
    ;

id_varpart
    : /* empty */
    | LBRACKET expression RBRACKET
    ;

procedure_call
    : IDENTIFIER
    | IDENTIFIER LPAREN expression_list RPAREN
    ;

expression_list
    : expression
    | expression_list COMMA expression
    ;

expression
    : simple_expression
    | simple_expression relop simple_expression
    ;

relop
    : EQUAL
    | GREATER
    | LESS
    | LE
    | GE
    | LG
    ;

simple_expression
    : term
    | simple_expression addop term
    ;

addop
    : PLUS
    | MINUS
    | OR
    ;

term
    : factor
    | term mulop factor
    ;

mulop
    : MUL
    | DIV
    | MOD
    | AND
    ;

factor
    : NUMBER
    | variable
    | LPAREN expression RPAREN
    | IDENTIFIER LPAREN expression_list RPAREN
    | NOT factor
    | MINUS factor %prec UMINUS
    ;

%%

void yyerror(const char *s) {
    fprintf(stderr, "Error: %s\n", s);
}

int main(void) {
    // 假设你有一个函数setupLexerStream，它配置词法分析器从特定源读取输入
    // 例如，从文件、字符串或其他来源
    setupLexerStream(); // 你需要根据实际情况实现这个函数

    printf("Parsing your Pascal-S program...\n");
    yyparse();
    printf("Parsing complete.\n");
    return 0;
}

