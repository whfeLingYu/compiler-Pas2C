%{
#include "AST.h"
#include "yacc.tab.h"

//外部变量声明
extern int yylineno;
extern int yyleng;
extern int yycolumn;

typedef enum { INT_TYPE, REAL_TYPE, BOOLEAN_TYPE, CHAR_TYPE, FUNCTION_TYPE } DataType;

//语法错误信息
vector<string> syntaxErrorInformation;
bool haveSemanticError=false;

//定义语法树
AST* ParseTree=NULL;

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

void yyerror(const char *s, YYLTYPE *loc);
void yyerror(const char *s, int line, int col);
void yyerror(const char *s, int startLine, int startCol, int endLine, int endCol);
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



%token PROGRAM CONST VAR PROCEDURE FUNCTION BEGIN END
%token INTEGER REAL BOOLEAN CHAR ARRAY
%token IF THEN FOR TO DO READ WRITE OF
%token PLUS MINUS OR MUL DIV MOD AND NOT ASSIGN
%token GREATER EQUAL LESS LE GE LG
%token SEMICOLON COMMA COLON QMARK LBRACKET RBRACKET LBRACE RBRACE LPAREN RPAREN DOT
%token IDENTIFIER NUMBER STRING
%nonassoc LOWER_THAN_ELSE
%nonassoc ELSE


%start program

%locations

%%
program:
    program_head SEMICOLON program_body DOT{//正常语法，建立语法树
        ParseTree = $$ = new AST;//建立根节点
        $$->token = "program";
        $$->children.push_back($1);//将program_head的语法树节点作为根节点的子节点
        $$->children.push_back($2);
        $$->children.push_back($3);//将program_body的语法树节点作为根节点的子节点
        $$->children.push_back($4);
        if(yylex())//如果还有其他语法树节点
            yyerror("extra tokens at the end of the program",@4.last_line, @4.last_column+1);
    }
    |program_head error program_body DOT{//语法错误，缺少分号
        yyerror("missing semicolon", @2.last_line, @2.last_column+1);
        ParseTree=$$=new AST;
        $$->token = "program";
    }
    |program_head SEMICOLON error DOT{//语法错误，缺少program_body
        yyerror("fatal error in program boady");
        ParseTree=$$=new AST;
        $$->token = "program";
    }
    |program_head SEMICOLON program_body error{//语法错误，缺少点号
        yyerror("missing dot", @4.last_line, @4.last_column+1);
        ParseTree=$$=new AST;
        $$->token = "program";
    }
    |error SEMICOLON program_body DOT{//语法错误，缺少program_head
        yyerror("fatal error in program head, maybe missing keyword \"program\"", @1.first_line, @1.first_column, @1.last_line, @1.last_column);
        ParseTree=$$=new AST;
        $$->token = "program";
    }
    |error program_head SEMICOLON program_body DOT{//语法错误，program_head前面有多余的字符
        yyerror("extra tokens before program head",@$.first_line, @$.first_column, @2.first_line, @2.first_column-1);
        ParseTree=$$=new AST;
        $$->token = "program";
    }
    |error program_head error program_body DOT{ //program_head前包含非法记号、缺失分号
        yyerror("invalid token before program head, maybe missing keyword \"program\"", @$.first_line, @$.first_column, @2.first_line, @2.first_column-1);
        yerror("missing semicolon", @2.last_line, @2.last_column+1);
        ParseTree=$$=new AST
        $$->token="program";
    }
    |error program_head SEMICOLON program_body error{ //program_head前包含非法记号、缺失点号
        yyerror("invalid token before program head, maybe missing keyword \"program\"", @$.first_line, @$.first_column, @2.first_line, @2.first_column-1);
        yyerror("missing dot", @4.last_line, @4.last_column+1);
        ParseTree=$$=new Type;
        $$->token = "program";

    }
    |error program_head SEMICOLON error DOT{ //ERROR program_head前包含非法记号、program_body缺失
        yyerror("invalid token before program head, maybe missing keyword \"program\"", @$.first_line, @$.first_column, @2.first_line, @2.first_column-1);
        yyerror("fatal error in program body", @3.last_line, @3.last_column+1, @5.first_line, @5.first_column-1);
        ParseTree=$$=new AST;
        $$->token = "program";
    }
    ;

program_head
    : PROGRAM IDENTIFIER LBRACKET idlist RBRACKET{//正常
         $$=new AST;
         $$->token = "program_head";
         $$->children.push_back($1); $$->children.push_back($2);
         $$->children.push_back($3); $$->children.push_back($4);
         $$->children.push_back($5);
     }
     | PROGRAM error LBRACKET idlist RBRACKET{//语法错误，缺少标识符
         yyerror("missing program name", @1.last_line, @1.last_column+1);
         $$=new AST;
         $$->token = "program_head";
     }
     | PROGRAM IDENTIFIER LBRACKET error RBRACKET{//语法错误，idlist识别失败
         yyerror("program identifier list missing or imcomplete", @4.first_line, @4.first_column, @4.last_line, @4.last_column);
         $$=new AST;
         $$->token = "program_head";
     }
     | PROGRAM IDENTIFIER LBRACKET idlist error{//语法错误，缺少右中括号
         yyerror("missing right bracket", @4.last_line, @4.last_column+1);
         $$=new AST;
         $$->token = "program_head";
     }
    | PROGRAM IDENTIFIER {//正常
        $$=new AST;
        $$->token="program_head";
        $$->children.push_back($1);
        $$->children.push_back($2);
    }
    | PROGRAM error{//语法错误，缺少标识符
        yyerror("missing program name",  @1.first_line, @1.first_column, @1.last_line, @1.last_column);
        $$=new AST;
        $$->token="program_head";
    }
    | PROGRAM IDENTIFIER LBRACKET error{//语法错误，缺少idlist
        yyerror("program identifier list missing or imcomplete",@1.first_line, @1.first_column, @2.last_line, @2.last_column);
        $$=new AST;
        $$->token="program_head";
    }
    ;

program_body
    : const_declarations var_declarations subprogram_declarations compound_statement{//正常
        $$=new AST;
        $$->token="program_body";
        $$->children.push_back($1);
        $$->children.push_back($2);
        $$->children.push_back($3);
        $$->children.push_back($4);
    }
    ;

idlist
    : IDENTIFIER {//正常
        $$=new AST;
        $$->token="idlist";
        $$->children.push_back($1);

        //语义分析：
        $$ = createSymbol($1, SOME_TYPE, NULL); // 假设 createSymbol 返回 SymbolTableEntry* 类型
      }
    | idlist COMMA IDENTIFIER {//正常
        $$=new AST;
        $$->token="idlist";
        $$->children.push_back($1);
        $$->children.push_back($2);
        $$->children.push_back($3);

        //语义分析：
        SymbolTableEntry* entry = createSymbol($3, SOME_TYPE, NULL);
        entry->next = $1; // 假设 $1 是之前 idlist 的返回值，即 SymbolTableEntry* 类型
        $$ = entry;
      }
    ;


const_declarations
    : /* empty */{//正常
        $$=new AST;
        $$->token="const_declarations";
    }
    | CONST const_declaration SEMICOLON{//正常
        $$=new AST;
        $$->token="const_declarations";
        $$->children.push_back($1);
        $$->children.push_back($2);
        $$->children.push_back($3);
    }
    | CONST error SEMICOLON{//语法错误，缺少const_declaration
        yyerror("fatal error in const declarations", @2.first_line, @2.first_column, @2.last_line, @2.last_column);
        $$=new AST
        $$->token="const_declarations";
    }
    | CONST const_declaration error{//语法错误，缺少分号
        yyerror("missing a semicolon here", @2.first_line, @2.first_column, @2.last_line, @2.last_column);
        $$=new AST;
        $$->token="const_declarations";
    }
    ;

const_declaration
    : IDENTIFIER EQUAL const_value {//正常
            $$=new AST;
            $$->token="const_declaration";
            $$->children.push_back($1);
            $$->children.push_back($2);
            $$->children.push_back($3);

          //语义分析：
          if (findSymbol($1)) {
              yyerror("Identifier already declared");
          } else {
              // 根据const_value的类型来决定是哪种DataType
              DataType type = $3.type; // 假设const_value已经确定了类型
              addSymbol($1, type, 0, NULL);
          }
    }
    | const_declaration SEMICOLON IDENTIFIER EQUAL const_value {//正常
        $$=new AST;
        $$->token="const_declaration";
        $$->children.push_back($1);
        $$->children.push_back($2);
        $$->children.push_back($3);
        $$->children.push_back($4);
        $$->children.push_back($5);

        //语义分析：
        SymbolTableEntry* found = findSymbol($3);
        if (found) {
            yyerror("Duplicate identifier");
        } else {
            addSymbol($3, $5.type, 0, NULL);
        }
      }
    | const_declaration SEMICOLON IDENTIFIER EQUAL error{//语法错误，缺少const_value
        yyerror("constant definition missing initial r-value", @4.first_line, @4.first_column, @4.last_line, @4.last_column);
        $$=new AST;
        $$->token="const_declaration";
    }
    | const_declaration error IDENTIFIER EQUAL const_value{//语法错误，缺少分号
        yyerror("missing a semicolon", @1.first_line, @1.first_column, @1.last_line, @1.last_column+1);
        $$=new AST;
        $$->token="const_declaration";
    }
    | const_declaration SEMICOLON IDENTIFIER error const_value{//语法错误，缺少等号
        yyerror("missing equal sign",@3.first_line, @3.first_column, @3.last_line, @3.last_column);
        $$=new AST;
        $$->token="const_declaration";
    }
    | IDENTIFIER EQUAL error{//语法错误，缺少const_value
        yyerror("constant definition missing initial r-value", @3.first_line, @3.first_column, @3.last_line, @3.last_column);
        $$=new AST
        $$->token="const_declaration";
    }
    | IDENTIFIER error const_value{//语法错误，缺少等号
        yyerror("missing equal sign", @2.first_line, @2.first_column, @2.last_line, @2.last_column);
        $$=new AST;
        $$->token="const_declaration";
    }
    ;

const_value
    : NUMBER {//正常
        $$=new AST;
        $$->token="const_value";
        $$->children.push_back($1);

        //语义分析：
        $$ = (YYSTYPE) {.type = INT_TYPE, .value.ival = $1};
      }
    | MINUS NUMBER {//正常
        $$=new AST;
        $$->token="const_value";
        $$->children.push_back($1);
        $$->children.push_back($2);

        //语义分析：
        $$ = (YYSTYPE) {.type = INT_TYPE, .value.ival = -$2};
      }
    | PLUS NUMBER {//正常
        $$=new AST;
        $$->token="const_value";
        $$->children.push_back($1);
        $$->children.push_back($2);

        //语义分析：
        $$ = (YYSTYPE) {.type = INT_TYPE, .value.ival = $2};
      }
    | STRING {//正常,字符串处理不一定正确，词法分析做todo
        $$=new AST;
        $$->token="const_value";
        $$->children.push_back($1);

        //语义分析：
        $$ = (YYSTYPE) {.type = STRING_TYPE, .value.sval = strdup($1)};
      }
    ;


var_declarations
    : /* empty */{//正常
        $$=new AST;
        $$->token="var_declarations";
    }
    | VAR var_declaration SEMICOLON{//正常
        $$=new AST;
        $$->token="var_declarations";
        $$->children.push_back($1);
        $$->children.push_back($2);
        $$->children.push_back($3);
    }
    | VAR error SEMICOLON{//语法错误，缺少var_declaration
        yyerror("fatal error in var declarations", @1.first_line, @1.first_column, @1.last_line, @1.last_column);
        $$=new AST;
        $$->token="var_declarations";
    }
    | VAR var_declaration error{//语法错误，缺少分号
        yyerror("missing a semicolon",@2.last_line, @2.last_column+1);
        $$=new AST
        $$->token="var_declarations";
    }
    ;

var_declaration
    : idlist COLON type{//正常
        $$=new AST;
        $$->token="var_declaration";
        $$->children.push_back($1);
        $$->children.push_back($2);
        $$->children.push_back($3);

        //语义分析：
        /* 对于每个变量名，检查是否已经定义 */
       for (int i = 0; i < $1.count; ++i) {
           if (findSymbol($1.names[i])) {
               printf("Semantic error: variable %s is already defined\n", $1.names[i]);
           } else {
               createSymbol($1.names[i], $3);  /* 创建符号 */
           }
       }
    }
    | var_declaration SEMICOLON idlist COLON type{//正常
        $$=new AST;
        $$->token="var_declaration";
        $$->children.push_back($1);
        $$->children.push_back($2);
        $$->children.push_back($3);
        $$->children.push_back($4);
        $$->children.push_back($5);

        //语义分析：
        /* 同上 */
        for (int i = 0; i < $3.count; ++i) {
            if (findSymbol($3.names[i])) {
                printf("Semantic error: variable %s is already defined\n", $3.names[i]);
            } else {
                createSymbol($3.names[i], $5);  /* 同上 */
            }
        }
    }
    | idlist error type{//语法错误，缺少冒号
        yyerror("missing colon", @1.last_line, @1.last_column+1);
        $$=new AST
        $$->token="var_declaration";
    }
    | idlist COLON error{//语法错误，缺少type
        yyerror("missing type", @3.last_line, @3.last_column+1);
        $$=new AST;
        $$->token="var_declaration";
    }
    | var_declaration error idlist COLON type{//语法错误，缺少分号
        yyerror("missing a semicolon", @1.last_line, @1.last_column+1);
        $$=new AST;
        $$->token="var_declaration";
    }
    | var_declaration SEMICOLON idlist error type{//语法错误，缺少冒号
        yyerror("missing colon", @3.last_line, @3.last_column+1);
        $$=new AST;
        $$->token="var_declaration";
    }
    | var_declaration SEMICOLON idlist COLON error{//语法错误，缺少type
        yyerror("missing type", @4.last_line, @4.last_column+1);
        $$=new AST;
        $$->token="var_declaration";
    }
    ;

type
    : basic_type  { // 正常
        $$=new AST;
        $$->token="type";
        $$->children.push_back($1);

        // 语义分析：
        $$ = $1;
     }
    | ARRAY LBRACKET period RBRACKET OF basic_type { // 正常
        $$=new AST;
        $$->token="type";
        $$->children.push_back($1);
        $$->children.push_back($2);
        $$->children.push_back($3);
        $$->children.push_back($4);
        $$->children.push_back($5);
        $$->children.push_back($6);

        // 语义分析：
        $$ = ARRAY_TYPE;
     }
     | ARRAY error period RBRACKET OF basic_type { // 语法错误，缺少左中括号
        yyerror("missing left bracket", @1.last_line, @1.last_column+1);
        $$=new AST;
        $$->token="type";
     }
     | ARRAY LBRACKET period RBRACKET error basic_type { // 语法错误，缺少OF
        yyerror("missing keyword \"OF\"", @4.last_line, @4.last_column+1, @6.first_line, @6.first_column-1);
        $$=new AST;
        $$->token="type";
     }
     |ARRAY LBRACKET period RBRACKET OF error{//语法错误，缺少basic_type
        yyerror("missing base type keyword", @5.last_line, @5.last_column+1);
        $$=new AST;
        $$->token="type";
    }
    |ARRAY error{//语法错误，不完整的ARRAY
        yyerror("incomplete array type", &@$);
        $$=new AST
        $$->token="type";
    }
    |ARRAY LBRACKET error{//语法错误，不完整的ARRAY
        yyerror("incomplete array type", &@$);
        $$=new AST
        $$->token="type";
    }
    |ARRAY LBRACKET period error{//语法错误，不完整的ARRAY
        yyerror("incomplete array type", &@$);
        $$=new AST
        $$->token="type";
    }
    ;

basic_type
    : INTEGER { // 正常
        $$=new AST;
        $$->token="basic_type";
        $$->children.push_back($1);

        // 语义分析：
        $$ = INT_TYPE;
    }
    | REAL    { // 正常
        $$=new AST;
        $$->token="basic_type";
        $$->children.push_back($1);

        // 语义分析：
        $$ = REAL_TYPE;
    }
    | BOOLEAN { // 正常
        $$=new AST;
        $$->token="basic_type";
        $$->children.push_back($1);

        // 语义分析：
        $$ = BOOLEAN_TYPE;
    }
    | CHAR    { // 正常
        $$=new AST;
        $$->token="basic_type";
        $$->children.push_back($1);

        // 语义分析：
        $$ = CHAR_TYPE;
    }
    ;

period
    : NUMBER DOT DOT NUMBER{//正常
        $$=new AST;
        $$->token="period";
        $$->children.push_back($1);
        $$->children.push_back($2);
        $$->children.push_back($3);
        $$->children.push_back($4);
    }
    | period COMMA NUMBER DOT DOT NUMBER /* 对于NUMBER定义可能还有bug */{//正常
        $$=new AST;
        $$->token="period";
        $$->children.push_back($1);
        $$->children.push_back($2);
        $$->children.push_back($3);
        $$->children.push_back($4);
        $$->children.push_back($5);
    }
    |period error NUMBER DOT DOT NUMBER{//语法错误，缺少逗号
        yyerror("missing comma", @1.last_line, @1.last_column+1);
        $$=new AST;
        $$->token="period";
    }
    |period COMMA NUMBER error NUMBER{//语法错误，缺少点号
        yyerror("missing dot..", @3.last_line, @3.last_column+1);
        $$=new AST;
        $$->token="period";
    }
    ;

subprogram_declarations
    : /* empty */{//正常
        $$=new AST;
        $$->token="subprogram_declarations";
    }
    | subprogram_declarations subprogram SEMICOLON{//正常
        $$=new AST;
        $$->token="subprogram_declarations";
        $$->children.push_back($1);
        $$->children.push_back($2);
        $$->children.push_back($3);
    }
    | subprogram_declarations subprogram error{//语法错误，缺少分号
        yyerror("missing a semicolon", @2.last_line, @2.last_column+1);
        $$=new AST;
        $$->token="subprogram_declarations";
    }
    ;

subprogram
    : subprogram_head SEMICOLON subprogram_body{//正常
        $$=new AST;
        $$->token="subprogram";
        $$->children.push_back($1);
        $$->children.push_back($2);
        $$->children.push_back($3);
    }
    | subprogram_head error subprogram_body{//语法错误，缺少分号
        yyerror("missing semicolon", @1.last_line, @1.last_column+1);
        $$=new AST;
        $$->token="subprogram";
    }
    ;

subprogram_head
    : PROCEDURE IDENTIFIER formal_parameter {//正常
        $$=new AST;
        $$->token="subprogram_head";
        $$->children.push_back($1);
        $$->children.push_back($2);
        $$->children.push_back($3);

        //语义分析：
        addSymbol($2, PROCEDURE_TYPE, $3.paramList);
    }
    | FUNCTION IDENTIFIER formal_parameter COLON basic_type {//正常
        $$=new AST;
        $$->token="subprogram_head";
        $$->children.push_back($1);
        $$->children.push_back($2);
        $$->children.push_back($3);
        $$->children.push_back($4);
        $$->children.push_back($5);

        //语义分析：
        addSymbol($2, $5, $3.paramList);
    }
    | PROCEDURE error formal_parameter {//语法错误，缺少标识符
        yyerror("missing procedure name", @1.last_line, @1.last_column+1);
        $$=new AST;
        $$->token="subprogram_head";
    }
    | FUNCTION error formal_parameter COLON basic_type{//语法错误，函数名缺失
        yyerror("missing function name", @1.last_line, @1.last_column+1);
        $$=new AST;
        $$->token="subprogram_head";
    }
    |FUNCTION IDENTIFIER formal_parameter error basic_type{//语法错误，缺少冒号
        yyerror("missing colon", @3.last_line, @3.last_column+1);
        $$=new AST
        $$->token="subprogram_head";
    }
    |FUNCTION IDENTIFIER formal_parameter COLON error{//语法错误，缺少basic_type
        yyerror("missing base type keyword", @4.last_line, @4.last_column+1);
        $$=new AST
        $$->token="subprogram_head";
    }
    |FUNCTION error{//语法错误，函数头不完整
        yyerror("incomplete function head", &@$);
        $$=new AST
        $$->token="subprogram_head";
    }
    ;


formal_parameter
    : /* empty */ {//正常
        $$=new AST;
        $$->token="formal_parameter";

        // 语义分析：
        $$ = createParamList();
     }
    | LPAREN parameter_list RPAREN {//正常
        $$=new AST;
        $$->token="formal_parameter";
        $$->children.push_back($1);
        $$->children.push_back($2);
        $$->children.push_back($3);

        // 语义分析：
        $$ = $2;
     }
    | LPAREN error RPAREN {//语法错误，缺少parameter_list
        yyerror("incomplete formal parameter list", &@$);
        $$=new AST;
        $$->token="formal_parameter";
    }
    | LPAREN parameter_list error{//语法错误，缺少右括号
        yyerror("missing right bracket", @2.last_line, @2.last_column+1);
        $$=new AST;
        $$->token="formal_parameter";
    }
    | LPAREN error{//语法错误，缺少parameter_list
        yyerror("incomplete formal parameter list", &@$);
        $$=new AST;
        $$->token="formal_parameter";
    }
    ;

parameter_list
    : parameter {//正常
        $$=new AST;
        $$->token="parameter_list";
        $$->children.push_back($1);

        // 语义分析：
        $$ = createParamList(); addParam($$, $1.type);
        }
    | parameter_list SEMICOLON parameter {//正常
        $$=new AST;
        $$->token="parameter_list";
        $$->children.push_back($1);
        $$->children.push_back($2);
        $$->children.push_back($3);

        // 语义分析：
        addParam($1, $3.type); $$ = $1;
        }
    | parameter_list error parameter{//语法错误，缺少分号
        yyerror("missing semicolon", @1.last_line, @1.last_column+1);
        $$=new AST;
        $$->token="parameter_list";
    }
    ;

parameter
    : var_parameter{//正常
        $$=new AST;
        $$->token="parameter";
        $$->children.push_back($1);

        // 语义分析：
        $$ = $1;
    }
    | value_parameter{//正常
        $$=new AST;
        $$->token="parameter";
        $$->children.push_back($1);

        // 语义分析：
        $$ = $1;
    }
    ;

var_parameter
    : VAR value_parameter {//正常
        $$=new AST;
        $$->token="var_parameter";
        $$->children.push_back($1);
        $$->children.push_back($2);

        // 语义分析：
        $$ = $2; $$->isVar = TRUE;
    }
    | VAR error{//语法错误，缺少value_parameter
        yyerror("incomplete refereced parameter list", &@$);
        $$=new AST
        $$->token="var_parameter";
    }
    ;

value_parameter
    : idlist COLON basic_type {//正常
        $$=new AST;
        $$->token="value_parameter";
        $$->children.push_back($1);
        $$->children.push_back($2);
        $$->children.push_back($3);

        // 语义分析：
        // 对于每个idlist中的标识符，设置其类型
        for (int i = 0; i < $1.count; ++i) {
            setParamType($1.names[i], $3);
        }
        $$ = $3; // 假设这里$3是从basic_type传递来的类型
    }
    | idlist error basic_type{//语法错误，缺少冒号
        yyerror("missing colon", @1.last_line, @1.last_column+1);
        $$=new AST
        $$->token="value_parameter";
    }
    | idlist COLON error{//语法错误，缺少basic_type
        yyerror("missing base type keyword", @2.last_line, @2.last_column+1);
        $$=new AST
        $$->token="value_parameter";
    }
    | idlist error{//语法错误，缺少basic_type
        yyerror("missing base type keyword", @1.last_line, @1.last_column+1);
        $$=new AST
        $$->token="value_parameter";
    }
    ;

subprogram_body
    : const_declarations var_declarations compound_statement{//正常
        $$=new AST;
        $$->token="subprogram_body";
        $$->children.push_back($1);
        $$->children.push_back($2);
        $$->children.push_back($3);
    }
    ;

compound_statement
    : BEGIN statement_list END{//正常
        $$=new AST;
        $$->token="compound_statement";
        $$->children.push_back($1);
        $$->children.push_back($2);
        $$->children.push_back($3);
    }
    ;

statement_list
    : statement{//正常
        $$=new AST;
        $$->token="statement_list";
        $$->children.push_back($1);
    }
    | statement_list SEMICOLON statement{//正常
        $$=new AST;
        $$->token="statement_list";
        $$->children.push_back($1);
        $$->children.push_back($2);
        $$->children.push_back($3);
    }
    | statement_list error statement{//语法错误，缺少分号
        yyerror("missing semicolon", @1.last_line, @1.last_column+1);
        $$=new AST;
        $$->token="statement_list";
    }
    ;

statement
    : /* empty */{//正常
        $$=new AST;
        $$->token="statement";
    }
    | variable ASSIGN expression{//正常
        $$=new AST;
        $$->token="statement";
        $$->children.push_back($1);
        $$->children.push_back($2);
        $$->children.push_back($3);

        // 语义分析：
        /* 检查变量是否已经定义，检查类型是否匹配 */
        SymbolTableEntry* var = findSymbol($1);
        if (!var) {
            printf("Semantic error: Undefined variable %s\n", $1);
        } else if (var->type != $3.type) {
            printf("Semantic error: Type mismatch in assignment to %s\n", $1);
        }
    }
    | FUNCTION ASSIGN expression /* 这里要func_id？？ */{//正常
        $$=new AST;
        $$->token="statement";
        $$->children.push_back($1);
        $$->children.push_back($2);
        $$->children.push_back($3);

        // 语义分析：
        SymbolTableEntry* func = findSymbol($1);
        if (!func || !isFunction(func)) {
            printf("Semantic error: Undefined function or identifier is not a function\n");
        } else if (func->paramCount != 0) {
            printf("Semantic error: Function expects parameters\n");
        }
    }
    | procedure_call{//正常
        $$=new AST;
        $$->token="statement";
        $$->children.push_back($1);
    }
    | compound_statement{//正常
        $$=new AST;
        $$->token="statement";
        $$->children.push_back($1);
    }
    | IF expression THEN statement else_part{//正常
        $$=new AST;
        $$->token="statement";
        $$->children.push_back($1);
        $$->children.push_back($2);
        $$->children.push_back($3);
        $$->children.push_back($4);
    }
    |IF expression error statement else_part{//语法错误，缺少THEN
        yyerror("missing keyword \"then\"", @1.last_line, @1.last_column+1);
        $$=new AST;
        $$->token="statement";
    }
    | FOR IDENTIFIER ASSIGN expression TO expression DO statement{//正常
        $$=new AST;
        $$->token="statement";
        $$->children.push_back($1);
        $$->children.push_back($2);
        $$->children.push_back($3);
        $$->children.push_back($4);
        $$->children.push_back($5);
        $$->children.push_back($6);
        $$->children.push_back($7);
    }
    | FOR IDENTIFIER ASSIGN expression TO expression error statement{//语法错误，缺少DO
        yyerror("missing keyword \"do\"", @6.last_line, @6.last_column+1);
        $$=new AST;
        $$->token="statement";
    }
    |FOR IDENTIFIER error expression TO expression DO statement{//语法错误，缺少赋值号
        yyerror("missing assignment operator \":=\"", @2.last_line, @2.last_column+1);
        $$=new AST;
        $$->token="statement";
    }
    |FOR IDENTIFIER ASSIGN expression error expression DO statement{//语法错误，缺少TO
        yyerror("missing keyword \"to\"", @4.last_line, @4.last_column+1);
        $$=new AST;
        $$->token="statement";
    }
    | READ LPAREN variable_list RPAREN{//正常
        $$=new AST;
        $$->token="statement";
        $$->children.push_back($1);
        $$->children.push_back($2);
        $$->children.push_back($3);
        $$->children.push_back($4);
    }
    | READ error variable_list RPAREN{//语法错误，缺少左括号
        yyerror("missing left bracket", @1.last_line, @1.last_column+1);
        $$=new AST;
        $$->token="statement";
    }
    | READ LPAREN error{//语法错误，参数列表错误
        yyerror("fatal error in read statement",&@$);
        $$=new AST;
        $$->token="statement";
    }
    | READ LPAREN variable_list error{//语法错误，缺少右括号
        yyerror("missing right bracket", @3.last_line, @3.last_column+1);
        $$=new AST;
        $$->token="statement";
    }
    | WRITE LPAREN expression_list RPAREN{//正常
        $$=new AST;
        $$->token="statement";
        $$->children.push_back($1);
        $$->children.push_back($2);
        $$->children.push_back($3);
        $$->children.push_back($4);
    }
    | WRITE error expression_list RPAREN{//语法错误，缺少左括号
        yyerror("missing left bracket", @1.last_line, @1.last_column+1);
        $$=new AST;
        $$->token="statement";
    }
    | WRITE LPAREN error{//语法错误，参数列表错误
        yyerror("fatal error in write statement",&@$);
        $$=new AST;
        $$->token="statement";
    }
    | WRITE LPAREN expression_list error{//语法错误，缺少右括号
        yyerror("missing right bracket", @3.last_line, @3.last_column+1);
        $$=new AST;
        $$->token="statement";
    }
    ;

else_part:
    ELSE statement{ //正常
        $$=new AST;
        $$->token="else_part";
        $$->children.push_back($1);
        $$->children.push_back($2);
    }
    |%prec LOWER_THAN_ELSE{ //正常
        $$=new AST;
        $$->token="else_part";
    };

variable_list
    : variable{//正常
        $$=new AST;
        $$->token="variable_list";
        $$->children.push_back($1);
    }
    | variable_list COMMA variable{//正常
        $$=new AST;
        $$->token="variable_list";
        $$->children.push_back($1);
        $$->children.push_back($2);
        $$->children.push_back($3);
    }
    | variable_list error variable{//语法错误，缺少逗号
        yyerror("missing comma", @1.last_line, @1.last_column+1);
        $$=new AST;
        $$->token="variable_list";
    }
    ;

variable
    : IDENTIFIER id_varpart{//正常
        $$=new AST;
        $$->token="variable";
        $$->children.push_back($1);
        $$->children.push_back($2);

        // 语义分析：
        SymbolTableEntry* var = findSymbol($1);
        if (!var) {
            printf("Semantic error: Undefined variable %s\n", $1);
        }
    }
    ;

id_varpart
    : /* empty */{//正常
        $$=new AST;
        $$->token="id_varpart";
    }
    | LBRACKET expression RBRACKET{//正常
        $$=new AST;
        $$->token="id_varpart";
        $$->children.push_back($1);
        $$->children.push_back($2);
        $$->children.push_back($3);
    }
    | LBRACKET error {//语法错误，不完整的数组下标
        yyerror("incomplete array index", &@$);
        $$=new AST;
        $$->token="id_varpart";
    }
    | LBRACKET expression error{//语法错误，缺少右中括号
        yyerror("missing right bracket", @2.last_line, @2.last_column+1);
        $$=new AST;
        $$->token="id_varpart";
    }
    ;

procedure_call
    : IDENTIFIER {//正常
        $$=new AST;
        $$->token="procedure_call";
        $$->children.push_back($1);

        // 语义分析：
        SymbolTableEntry* func = findSymbol($1);
        if (!func || !isFunction(func)) {
            yyerror("Undefined function or identifier is not a function");
        } else if (func->paramCount != 0) {
            yyerror("Function expects parameters");
        }
      }
    | IDENTIFIER LPAREN expression_list RPAREN {//正常
        $$=new AST;
        $$->token="procedure_call";
        $$->children.push_back($1);
        $$->children.push_back($2);
        $$->children.push_back($3);
        $$->children.push_back($4);

        // 语义分析：
        SymbolTableEntry* func = findSymbol($1);
        if (!func || !isFunction(func)) {
            yyerror("Undefined function or identifier is not a function");
        } else {
            checkFunctionParameters(func, $3);
        }
      }
     |IDENTIFIER LPAREN expression_list error{//语法错误，缺少右括号
        yyerror("missing right bracket", @3.last_line, @3.last_column+1);
        $$=new AST;
        $$->token="procedure_call";
    }
    ;


expression_list
    : expression{//正常
        $$=new AST;
        $$->token="expression_list";
        $$->children.push_back($1);

        // 语义分析：
        $$ = createParamList();
        addParam($$, $1.type);
    }
    | expression_list COMMA expression{//正常
        $$=new AST;
        $$->token="expression_list";
        $$->children.push_back($1);
        $$->children.push_back($2);
        $$->children.push_back($3);

        // 语义分析：
        addParam($1, $3.type);
        $$ = $1;
    }
    | expression_list error expression{//语法错误，缺少逗号
        yyerror("missing comma", @1.last_line, @1.last_column+1);
        $$=new AST;
        $$->token="expression_list";
    }
    ;

expression
    : simple_expression{//正常
        $$=new AST;
        $$->token="expression";
        $$->children.push_back($1);
    }
    | simple_expression relop simple_expression {//正常
        $$=new AST;
        $$->token="expression";
        $$->children.push_back($1);
        $$->children.push_back($2);
        $$->children.push_back($3);

        // 语义分析：
        // 检查两个simple_expression的类型是否兼容
        if (!areTypesCompatible($1.type, $3.type))
            yyerror("Type mismatch in relational operation");
      }
    ;

relop
    : EQUAL{ $$=new AST
        $$->token="relop";
        $$->children.push_back($1);
    }
    | GREATER{ $$=new AST
        $$->token="relop";
        $$->children.push_back($1);
    }
    | LESS{ $$=new AST
        $$->token="relop";
        $$->children.push_back($1);
    }
    | LE{ $$=new AST
        $$->token="relop";
        $$->children.push_back($1);
    }
    | GE{ $$=new AST
        $$->token="relop";
        $$->children.push_back($1);
    }
    | LG{ $$=new AST
        $$->token="relop";
        $$->children.push_back($1);
    }
    ;

simple_expression
    : term{//正常
        $$=new AST;
        $$->token="simple_expression";
        $$->children.push_back($1);
    }
    | simple_expression addop term {//正常
        $$=new AST;
        $$->token="simple_expression";
        $$->children.push_back($1);
        $$->children.push_back($2);
        $$->children.push_back($3);

        // 语义分析：
        // 检查simple_expression和term的类型是否兼容
        if (!areTypesCompatible($1.type, $3.type)) {
            yyerror("Type mismatch in addition/subtraction operation");
        }
      }
    |simple_expression addop error term %prec PLUS{//语法错误，缺少操作数
        yyerror("missing operand", @2.last_line, @2.last_column+1);
        $$=new AST;
        $$->token="simple_expression";
    }
    ;

addop
    : PLUS{ $$=new AST
        $$->token="addop";
        $$->children.push_back($1);
    }
    | MINUS{ $$=new AST
        $$->token="addop";
        $$->children.push_back($1);
    }
    | OR{ $$=new AST
        $$->token="addop";
        $$->children.push_back($1);
    }
    ;

term
    : factor{//正常
        $$=new AST;
        $$->token="term";
        $$->children.push_back($1);
    }
    | term mulop factor{//正常
        $$=new AST;
        $$->token="term";
        $$->children.push_back($1);
        $$->children.push_back($2);
        $$->children.push_back($3);

        // 语义分析：
        // 检查term和factor的类型是否兼容
        if (!areTypesCompatible($1.type, $3.type)) {
            yyerror("Type mismatch in multiplication/division/modulus/and operation");
        }
      }
    | term mulop error factor %prec MUL{//语法错误，缺少mulop
        yyerror("missing multiplication/division/modulus/and operator", @1.last_line, @1.last_column+1);
        $$=new AST;
        $$->token="term";
    }
    ;

mulop
    : MUL{ $$=new AST
        $$->token="mulop";
        $$->children.push_back($1);
    }
    | DIV{ $$=new AST
        $$->token="mulop";
        $$->children.push_back($1);
    }
    | MOD{ $$=new AST
        $$->token="mulop";
        $$->children.push_back($1);
    }
    | AND{ $$=new AST
        $$->token="mulop";
        $$->children.push_back($1);
    }
    ;

factor
    : NUMBER{//正常
        $$=new AST;
        $$->token="factor";
        $$->children.push_back($1);

        // 语义分析：
        $$ = (YYSTYPE) {.type = INT_TYPE, .value.ival = $1};
      }
    | variable{//正常
        $$=new AST;
        $$->token="factor";
        $$->children.push_back($1);

        // 语义分析：
        SymbolTableEntry* var = findSymbol($1);
        if (!var) {
            yyerror("Undefined variable");
        }
      }
    | LPAREN expression RPAREN{//正常
        $$=new AST;
        $$->token="factor";
        $$->children.push_back($1);
        $$->children.push_back($2);
        $$->children.push_back($3);

        // 语义分析：
        $$ = $2;
      }
    | LPAREN expression error{//语法错误，缺少右括号
        yyerror("missing right bracket", @2.last_line, @2.last_column+1);
        $$=new AST;
        $$->token="factor";
    }
    | IDENTIFIER LPAREN expression_list RPAREN{//正常
        $$=new AST;
        $$->token="factor";
        $$->children.push_back($1);
        $$->children.push_back($2);
        $$->children.push_back($3);
        $$->children.push_back($4);

        // 语义分析：
        SymbolTableEntry* func = findSymbol($1);
        if (!func || !isFunction(func)) {
            yyerror("Undefined function or identifier is not a function");
        } else {
            checkFunctionParameters(func, $3);
        }
      }
    | IDENTIFIER LPAREN error{//语法错误，参数列表错误
        yyerror("fatal error in function call",&@$);
        $$=new AST;
        $$->token
    }
    | NOT factor{//正常
        $$=new AST;
        $$->token="factor";
        $$->children.push_back($1);
        $$->children.push_back($2);

        // 语义分析：
        if ($2.type != BOOLEAN_TYPE) {
            yyerror("Type mismatch in NOT operation");
        }
      }
    | MINUS factor %prec MINUS{//正常
        $$=new AST;
        $$->token="factor";
        $$->children.push_back($1);
        $$->children.push_back($2);

        // 语义分析：
        if ($2.type != INT_TYPE && $2.type != REAL_TYPE) {
            yyerror("Type mismatch in unary minus operation");
        }
      }
    ;

%%

void yyerror(const char *s){
	haveSemanticError = true;//错误标志，含有语法错误
	string errorInformation;//定义错误信息
	errorInformation += string(s);//添加错误信息
	errorInformation += ", location: " + to_string(yylineno-1) + "." + to_string(yycolumn-yyleng);//添加错误位置
	syntaxErrorInformation.push_back(errorInformation);//存放错误信息
}

void yyerror(const char *s, YYLTYPE *loc){//处理单个字符的错误
	haveSemanticError = true;
	string errorInformation;
	errorInformation = "syntax error, " + string(s) + ", location: " + to_string(loc->first_line) + "." + to_string(loc->first_column) + "-" + to_string(loc->last_line) + "." + to_string(loc->last_column);
	syntaxErrorInformation.push_back(errorInformation);
}

void yyerror(const char *s, int line, int col){//处理一行以内的错误
	haveSemanticError = true;
	string errorInformation;
	errorInformation = "syntax error, " + string(s) + ", location: " + to_string(line) + "." + to_string(col);
	syntaxErrorInformation.push_back(errorInformation);
}

void yyerror(const char *s, int startLine, int startCol, int endLine, int endCol){//处理涉及多行的错误
	haveSemanticError = true;
	string errorInformation;
	errorInformation = "syntax error, " + string(s) + ", location: " + to_string(startLine) + "." + to_string(startCol) + "-" + to_string(endLine) + "." + to_string(endCol);
	syntaxErrorInformation.push_back(errorInformation);
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