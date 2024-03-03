%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum { INT_TYPE, REAL_TYPE, BOOLEAN_TYPE, CHAR_TYPE, FUNCTION_TYPE } DataType;

typedef struct Parameter {
    DataType type;
    struct Parameter* next;
} Parameter;

typedef struct SymbolTableEntry {
    char* name;
    DataType type;
    int paramCount;
    Parameter* params;
    struct SymbolTableEntry* next;
} SymbolTableEntry;

SymbolTableEntry* symbolTable = NULL;

void yyerror(const char *s);
int yylex(void);

/* 辅助函数声明 */
SymbolTableEntry* createSymbol(char* name, DataType type, Parameter* params);
void addSymbol(char* name, DataType type, Parameter* params);
SymbolTableEntry* findSymbol(char* name);
int isFunction(SymbolTableEntry* entry);
void checkFunctionParameters(SymbolTableEntry* func, Parameter* calledParams, int calledParamCount);

/* 实现辅助函数 */
SymbolTableEntry* createSymbol(char* name, DataType type, Parameter* params) {
    SymbolTableEntry* entry = (SymbolTableEntry*)malloc(sizeof(SymbolTableEntry));
    entry->name = strdup(name);
    entry->type = type;
    entry->params = params;
    entry->next = symbolTable;
    symbolTable = entry;
    return entry;
}

void addSymbol(char* name, DataType type, Parameter* params) {
    SymbolTableEntry* newEntry = createSymbol(name, type, params);
    // 计算参数数量
    int count = 0;
    Parameter* param = params;
    while (param) {
        count++;
        param = param->next;
    }
    newEntry->paramCount = count;
}

SymbolTableEntry* findSymbol(char* name) {
    for (SymbolTableEntry* entry = symbolTable; entry != NULL; entry = entry->next) {
        if (strcmp(entry->name, name) == 0) {
            return entry;
        }
    }
    return NULL;
}

int isFunction(SymbolTableEntry* entry) {
    return entry && entry->type == FUNCTION_TYPE;
}

void checkFunctionParameters(SymbolTableEntry* func, Parameter* calledParams, int calledParamCount) {
    if (func->paramCount != calledParamCount) {
        yyerror("Incorrect number of parameters in function call");
        return;
    }

    Parameter* declaredParam = func->params;
    Parameter* calledParam = calledParams;
    while (declaredParam != NULL && calledParam != NULL) {
        if (declaredParam->type != calledParam->type) {
            yyerror("Parameter type mismatch in function call");
            return;
        }
        declaredParam = declaredParam->next;
        calledParam = calledParam->next;
    }
}

%}

%union {
    int ival; // 用于处理整数值
    char* sval; // 用于处理字符串
    DataType type; // 用于处理数据类型
    Parameter* param; // 用于处理参数
    SymbolTableEntry* symEntry; // 用于处理符号表条目
    Parameter* paramList; // 用于处理参数列表
    // 定义一个结构体处理 const_value
    struct {
        DataType type; // 这个类型用于区分是 NUMBER 还是 STRING
        union {
            int ival;
            char* sval;
        } value;
    } constVal;
}

%token PROGRAM CONST VAR PROCEDURE FUNCTION BEGIN END
%token INTEGER REAL BOOLEAN CHAR ARRAY
%token IF THEN FOR TO DO READ WRITE OF
%token PLUS MINUS OR MUL DIV MOD AND NOT ASSIGN
%token GREATER EQUAL LESS LE GE LG
%token SEMICOLON COMMA COLON QMARK LBRACKET RBRACKET LBRACE RBRACE LPAREN RPAREN DOT
%nonassoc LOWER_THAN_ELSE
%nonassoc ELSE
%token <sval> IDENTIFIER STRING
%token <ival> NUMBER
%type <type> type basic_type
%type <constVal> const_value
%type <sval> variable
%type <symEntry> idlist
%type <param> formal_parameter value_parameter var_parameter parameter parameter_list
%type <ival> expression simple_expression term factor
%type <paramList> expression_list

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
    : IDENTIFIER {
          $$ = createSymbol($1, SOME_TYPE, NULL); // 假设 createSymbol 返回 SymbolTableEntry* 类型
      }
    | idlist COMMA IDENTIFIER {
          SymbolTableEntry* entry = createSymbol($3, SOME_TYPE, NULL);
          entry->next = $1; // 假设 $1 是之前 idlist 的返回值，即 SymbolTableEntry* 类型
          $$ = entry;
      }
    ;


const_declarations
    : /* empty */
    | CONST const_declaration SEMICOLON
    ;

const_declaration
    : IDENTIFIER EQUAL const_value {
          if (findSymbol($1)) {
              yyerror("Identifier already declared");
          } else {
              // 根据const_value的类型来决定是哪种DataType
              DataType type = $3.type; // 假设const_value已经确定了类型
              addSymbol($1, type, 0, NULL);
          }
    }
    | const_declaration SEMICOLON IDENTIFIER EQUAL const_value {
        SymbolTableEntry* found = findSymbol($3);
        if (found) {
            yyerror("Duplicate identifier");
        } else {
            addSymbol($3, $5.type, 0, NULL);
        }
      }
    ;

const_value
    : NUMBER {
          $$ = (YYSTYPE) {.type = INT_TYPE, .value.ival = $1};
      }
    | MINUS NUMBER {
          $$ = (YYSTYPE) {.type = INT_TYPE, .value.ival = -$2};
      }
    | PLUS NUMBER {
          $$ = (YYSTYPE) {.type = INT_TYPE, .value.ival = $2};
      }
    | STRING {
          $$ = (YYSTYPE) {.type = STRING_TYPE, .value.sval = strdup($1)};
      }
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
    : PROCEDURE IDENTIFIER formal_parameter {
        addSymbol($2, PROCEDURE_TYPE, $3.paramList);
    }
    | FUNCTION IDENTIFIER formal_parameter COLON basic_type {
        addSymbol($2, $5, $3.paramList);
    }
    ;


formal_parameter
    : /* empty */ { $$ = createParamList(); }
    | LPAREN parameter_list RPAREN { $$ = $2; }
    ;

parameter_list
    : parameter { $$ = createParamList(); addParam($$, $1.type); }
    | parameter_list SEMICOLON parameter { addParam($1, $3.type); $$ = $1; }
    ;

parameter
    : var_parameter
    | value_parameter
    ;

var_parameter
    : VAR value_parameter { $$ = $2; $$->isVar = TRUE; }
    ;

value_parameter
    : idlist COLON basic_type {
        // 对于每个idlist中的标识符，设置其类型
        for (int i = 0; i < $1.count; ++i) {
            setParamType($1.names[i], $3);
        }
        $$ = $3; // 假设这里$3是从basic_type传递来的类型
    }
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
    : IDENTIFIER {
        SymbolTableEntry* func = findSymbol($1);
        if (!func || !isFunction(func)) {
            yyerror("Undefined function or identifier is not a function");
        } else if (func->paramCount != 0) {
            yyerror("Function expects parameters");
        }
      }
    | IDENTIFIER LPAREN expression_list RPAREN {
        SymbolTableEntry* func = findSymbol($1);
        if (!func || !isFunction(func)) {
            yyerror("Undefined function or identifier is not a function");
        } else {
            checkFunctionParameters(func, $3);
        }
      }
    ;


expression_list
    : expression{
        $$ = createParamList();
        addParam($$, $1.type);
    }
    | expression_list COMMA expression{
        addParam($1, $3.type);
        $$ = $1;
    }
    ;

expression
    : simple_expression
    | simple_expression relop simple_expression {
        // 检查两个simple_expression的类型是否兼容
        if (!areTypesCompatible($1.type, $3.type)) {
            yyerror("Type mismatch in relational operation");
        }
      }
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
    | simple_expression addop term {
        // 检查simple_expression和term的类型是否兼容
        if (!areTypesCompatible($1.type, $3.type)) {
            yyerror("Type mismatch in addition/subtraction operation");
        }
      }
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
    | variable{
        SymbolTableEntry* var = findSymbol($1);
        if (!var) {
            yyerror("Undefined variable");
        }
      }
    | LPAREN expression RPAREN{
        $$ = $2;
      }
    | IDENTIFIER LPAREN expression_list RPAREN{
        SymbolTableEntry* func = findSymbol($1);
        if (!func || !isFunction(func)) {
            yyerror("Undefined function or identifier is not a function");
        } else {
            checkFunctionParameters(func, $3);
        }
      }
    | NOT factor{
        if ($2.type != BOOLEAN_TYPE) {
            yyerror("Type mismatch in NOT operation");
        }
      }
    | MINUS factor %prec UMINUS{
        if ($2.type != INT_TYPE && $2.type != REAL_TYPE) {
            yyerror("Type mismatch in unary minus operation");
        }
      }
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