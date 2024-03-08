
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
     IDENTIFIER = 304,
     NUMBER = 305,
     STRING = 306,
     LOWER_THAN_ELSE = 307,
     ELSE = 308
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
#define IDENTIFIER 304
#define NUMBER 305
#define STRING 306
#define LOWER_THAN_ELSE 307
#define ELSE 308




#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef int YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif

extern YYSTYPE yylval;

#if ! defined YYLTYPE && ! defined YYLTYPE_IS_DECLARED
typedef struct YYLTYPE
{
  int first_line;
  int first_column;
  int last_line;
  int last_column;
} YYLTYPE;
# define yyltype YYLTYPE /* obsolescent; will be withdrawn */
# define YYLTYPE_IS_DECLARED 1
# define YYLTYPE_IS_TRIVIAL 1
#endif

extern YYLTYPE yylloc;

