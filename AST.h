// AST.h
#ifndef AST_H
#define AST_H
#define YYERROR_VERBOSE
#define YYDEBUG 1
#define LEXDEBUG


#include <iostream>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <vector>

extern int yydebug;
using namespace std;

class AST{
public:
    std::string str; // 终结符号的具体属性
    std::string token; // 终结符号或非终结符号本身的名称
    int lineNumber; // 终结符号的行号
    std::vector<AST*> children; // 对应产生式下面的节点

    AST() {}
    AST(std::string typ, std::string name, int ln): str(typ), token(name), lineNumber(ln) {}
    AST(std::string name, std::vector<AST*> cdn): token(name), children(cdn) {}
};
#define YYSTYPE AST*

#endif // AST_H
