
/* A Bison parser, made by GNU Bison 2.4.1.  */

/* Skeleton interface for Bison's Yacc-like parsers in C
   
      Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002, 2003, 2004, 2005, 2006
   Free Software Foundation, Inc.
   
   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.
   
   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.
   
   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.
   
   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */


/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     PROGRAM = 258,
     CONST = 259,
     VAR = 260,
     PROCEDURE = 261,
     FUNCTION = 262,
     BEGIN = 263,
     END = 264,
     INTEGER = 265,
     REAL = 266,
     BOOLEAN = 267,
     CHAR = 268,
     ARRAY = 269,
     IF = 270,
     THEN = 271,
     FOR = 272,
     TO = 273,
     DO = 274,
     READ = 275,
     WRITE = 276,
     OF = 277,
     PLUS = 278,
     MINUS = 279,
     OR = 280,
     MUL = 281,
     DIV = 282,
     MOD = 283,
     AND = 284,
     NOT = 285,
     ASSIGN = 286,
     GREATER = 287,
     EQUAL = 288,
     LESS = 289,
     LE = 290,
     GE = 291,
     LG = 292,
     SEMICOLON = 293,
     COMMA = 294,
     COLON = 295,
     QMARK = 296,
     LBRACKET = 297,
     RBRACKET = 298,
     LBRACE = 299,
     RBRACE = 300,
     LPAREN = 301,
     RPAREN = 302,
     DOT = 303,
     LOWER_THAN_ELSE = 304,
     ELSE = 305,
     IDENTIFIER = 306,
     STRING = 307,
     NUMBER = 308,
     UMINUS = 309
   };
#endif
/* Tokens.  */
#define PROGRAM 258
#define CONST 259
#define VAR 260
#define PROCEDURE 261
#define FUNCTION 262
#define BEGIN 263
#define END 264
#define INTEGER 265
#define REAL 266
#define BOOLEAN 267
#define CHAR 268
#define ARRAY 269
#define IF 270
#define THEN 271
#define FOR 272
#define TO 273
#define DO 274
#define READ 275
#define WRITE 276
#define OF 277
#define PLUS 278
#define MINUS 279
#define OR 280
#define MUL 281
#define DIV 282
#define MOD 283
#define AND 284
#define NOT 285
#define ASSIGN 286
#define GREATER 287
#define EQUAL 288
#define LESS 289
#define LE 290
#define GE 291
#define LG 292
#define SEMICOLON 293
#define COMMA 294
#define COLON 295
#define QMARK 296
#define LBRACKET 297
#define RBRACKET 298
#define LBRACE 299
#define RBRACE 300
#define LPAREN 301
#define RPAREN 302
#define DOT 303
#define LOWER_THAN_ELSE 304
#define ELSE 305
#define IDENTIFIER 306
#define STRING 307
#define NUMBER 308
#define UMINUS 309




#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
{

/* Line 1676 of yacc.c  */
#line 89 ".\\parser.y"

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



/* Line 1676 of yacc.c  */
#line 179 "y.tab.h"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif

extern YYSTYPE yylval;


