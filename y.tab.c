
/* A Bison parser, made by GNU Bison 2.4.1.  */

/* Skeleton implementation for Bison's Yacc-like parsers in C
   
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

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "2.4.1"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1

/* Using locations.  */
#define YYLSP_NEEDED 1



/* Copy the first part of user declarations.  */

/* Line 189 of yacc.c  */
#line 1 ".\\parser.y"

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



/* Line 189 of yacc.c  */
#line 175 "y.tab.c"

/* Enabling traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* Enabling the token table.  */
#ifndef YYTOKEN_TABLE
# define YYTOKEN_TABLE 0
#endif


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


/* Copy the second part of user declarations.  */


/* Line 264 of yacc.c  */
#line 336 "y.tab.c"

#ifdef short
# undef short
#endif

#ifdef YYTYPE_UINT8
typedef YYTYPE_UINT8 yytype_uint8;
#else
typedef unsigned char yytype_uint8;
#endif

#ifdef YYTYPE_INT8
typedef YYTYPE_INT8 yytype_int8;
#elif (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
typedef signed char yytype_int8;
#else
typedef short int yytype_int8;
#endif

#ifdef YYTYPE_UINT16
typedef YYTYPE_UINT16 yytype_uint16;
#else
typedef unsigned short int yytype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 yytype_int16;
#else
typedef short int yytype_int16;
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif ! defined YYSIZE_T && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned int
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

#ifndef YY_
# if YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(msgid) dgettext ("bison-runtime", msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(msgid) msgid
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(e) ((void) (e))
#else
# define YYUSE(e) /* empty */
#endif

/* Identity function, used to suppress warnings about constant conditions.  */
#ifndef lint
# define YYID(n) (n)
#else
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static int
YYID (int yyi)
#else
static int
YYID (yyi)
    int yyi;
#endif
{
  return yyi;
}
#endif

#if ! defined yyoverflow || YYERROR_VERBOSE

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#     ifndef _STDLIB_H
#      define _STDLIB_H 1
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's `empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (YYID (0))
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined _STDLIB_H \
       && ! ((defined YYMALLOC || defined malloc) \
	     && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef _STDLIB_H
#    define _STDLIB_H 1
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
	 || (defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL \
	     && defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss_alloc;
  YYSTYPE yyvs_alloc;
  YYLTYPE yyls_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE) + sizeof (YYLTYPE)) \
      + 2 * YYSTACK_GAP_MAXIMUM)

/* Copy COUNT objects from FROM to TO.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(To, From, Count) \
      __builtin_memcpy (To, From, (Count) * sizeof (*(From)))
#  else
#   define YYCOPY(To, From, Count)		\
      do					\
	{					\
	  YYSIZE_T yyi;				\
	  for (yyi = 0; yyi < (Count); yyi++)	\
	    (To)[yyi] = (From)[yyi];		\
	}					\
      while (YYID (0))
#  endif
# endif

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)				\
    do									\
      {									\
	YYSIZE_T yynewbytes;						\
	YYCOPY (&yyptr->Stack_alloc, Stack, yysize);			\
	Stack = &yyptr->Stack_alloc;					\
	yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
	yyptr += yynewbytes / sizeof (*yyptr);				\
      }									\
    while (YYID (0))

#endif

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  9
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   381

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  54
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  38
/* YYNRULES -- Number of rules.  */
#define YYNRULES  159
/* YYNRULES -- Number of states.  */
#define YYNSTATES  307

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   308

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint16 yyprhs[] =
{
       0,     0,     3,     8,    13,    18,    23,    28,    34,    40,
      46,    52,    58,    64,    70,    76,    79,    82,    87,    92,
      94,    98,    99,   103,   107,   111,   115,   121,   127,   133,
     139,   143,   147,   149,   152,   155,   157,   158,   162,   166,
     170,   174,   180,   184,   188,   194,   200,   206,   208,   215,
     222,   229,   236,   239,   243,   248,   250,   252,   254,   256,
     261,   268,   275,   281,   282,   286,   290,   294,   298,   302,
     308,   312,   318,   324,   330,   333,   334,   338,   342,   346,
     349,   351,   355,   359,   361,   363,   366,   369,   373,   377,
     381,   384,   388,   392,   394,   398,   402,   403,   407,   411,
     413,   415,   421,   427,   436,   445,   454,   463,   468,   473,
     477,   482,   487,   492,   496,   501,   504,   505,   507,   511,
     515,   518,   519,   523,   526,   530,   532,   537,   542,   544,
     548,   552,   554,   558,   560,   562,   564,   566,   568,   570,
     572,   576,   581,   583,   585,   587,   589,   593,   598,   600,
     602,   604,   606,   608,   610,   614,   618,   623,   627,   630
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int8 yyrhs[] =
{
      55,     0,    -1,    56,    38,    57,    48,    -1,    56,     1,
      57,    48,    -1,    56,    38,     1,    48,    -1,    56,    38,
      57,     1,    -1,     1,    38,    57,    48,    -1,     1,    56,
      38,    57,    48,    -1,     1,    56,     1,    57,    48,    -1,
       1,    56,    38,    57,     1,    -1,     1,    56,    38,     1,
      48,    -1,     3,    49,    42,    58,    43,    -1,     3,     1,
      42,    58,    43,    -1,     3,    49,    42,     1,    43,    -1,
       3,    49,    42,    58,     1,    -1,     3,    49,    -1,     3,
       1,    -1,     3,    49,    42,     1,    -1,    59,    62,    67,
      76,    -1,    49,    -1,    58,    39,    49,    -1,    -1,     4,
      60,    38,    -1,     4,     1,    38,    -1,     4,    60,     1,
      -1,    49,    33,    61,    -1,    60,    38,    49,    33,    61,
      -1,    60,    38,    49,    33,     1,    -1,    60,     1,    49,
      33,    61,    -1,    60,    38,    49,     1,    61,    -1,    49,
      33,     1,    -1,    49,     1,    61,    -1,    50,    -1,    24,
      50,    -1,    23,    50,    -1,    51,    -1,    -1,     5,    63,
      38,    -1,     5,     1,    38,    -1,     5,    63,     1,    -1,
      58,    40,    64,    -1,    63,    38,    58,    40,    64,    -1,
      58,     1,    64,    -1,    58,    40,     1,    -1,    63,     1,
      58,    40,    64,    -1,    63,    38,    58,     1,    64,    -1,
      63,    38,    58,    40,     1,    -1,    65,    -1,    14,    42,
      66,    43,    22,    65,    -1,    14,     1,    66,    43,    22,
      65,    -1,    14,    42,    66,    43,     1,    65,    -1,    14,
      42,    66,    43,    22,     1,    -1,    14,     1,    -1,    14,
      42,     1,    -1,    14,    42,    66,     1,    -1,    10,    -1,
      11,    -1,    12,    -1,    13,    -1,    50,    48,    48,    50,
      -1,    66,    39,    50,    48,    48,    50,    -1,    66,     1,
      50,    48,    48,    50,    -1,    66,    39,    50,     1,    50,
      -1,    -1,    67,    68,    38,    -1,    67,    68,     1,    -1,
      69,    38,    75,    -1,    69,     1,    75,    -1,     6,    49,
      70,    -1,     7,    49,    70,    40,    65,    -1,     6,     1,
      70,    -1,     7,     1,    70,    40,    65,    -1,     7,    49,
      70,     1,    65,    -1,     7,    49,    70,    40,     1,    -1,
       7,     1,    -1,    -1,    46,    71,    47,    -1,    46,     1,
      47,    -1,    46,    71,     1,    -1,    46,     1,    -1,    72,
      -1,    71,    38,    72,    -1,    71,     1,    72,    -1,    73,
      -1,    74,    -1,     5,    74,    -1,     5,     1,    -1,    58,
      40,    65,    -1,    58,     1,    65,    -1,    58,    40,     1,
      -1,    58,     1,    -1,    59,    62,    76,    -1,     8,    77,
       9,    -1,    78,    -1,    77,    38,    78,    -1,    77,     1,
      78,    -1,    -1,    81,    31,    85,    -1,     7,    31,    85,
      -1,    83,    -1,    76,    -1,    15,    85,    16,    78,    79,
      -1,    15,    85,     1,    78,    79,    -1,    17,    49,    31,
      85,    18,    85,    19,    78,    -1,    17,    49,    31,    85,
      18,    85,     1,    78,    -1,    17,    49,     1,    85,    18,
      85,    19,    78,    -1,    17,    49,    31,    85,     1,    85,
      19,    78,    -1,    20,    46,    80,    47,    -1,    20,     1,
      80,    47,    -1,    20,    46,     1,    -1,    20,    46,    80,
       1,    -1,    21,    46,    84,    47,    -1,    21,     1,    84,
      47,    -1,    21,    46,     1,    -1,    21,    46,    84,     1,
      -1,    53,    78,    -1,    -1,    81,    -1,    80,    39,    81,
      -1,    80,     1,    81,    -1,    49,    82,    -1,    -1,    42,
      85,    43,    -1,    42,     1,    -1,    42,    85,     1,    -1,
      49,    -1,    49,    46,    84,    47,    -1,    49,    46,    84,
       1,    -1,    85,    -1,    84,    39,    85,    -1,    84,     1,
      85,    -1,    87,    -1,    87,    86,    87,    -1,    33,    -1,
      32,    -1,    34,    -1,    35,    -1,    36,    -1,    37,    -1,
      89,    -1,    87,    88,    89,    -1,    87,    88,     1,    89,
      -1,    23,    -1,    24,    -1,    25,    -1,    91,    -1,    89,
      90,    91,    -1,    89,    90,     1,    91,    -1,    26,    -1,
      27,    -1,    28,    -1,    29,    -1,    50,    -1,    81,    -1,
      46,    85,    47,    -1,    46,    85,     1,    -1,    49,    46,
      84,    47,    -1,    49,    46,     1,    -1,    30,    91,    -1,
      24,    91,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   121,   121,   131,   136,   141,   146,   151,   156,   162,
     169,   178,   185,   190,   195,   200,   206,   211,   219,   230,
     238,   254,   258,   265,   270,   278,   294,   311,   316,   321,
     326,   331,   339,   347,   356,   365,   377,   381,   388,   393,
     401,   418,   437,   442,   447,   452,   457,   465,   473,   486,
     491,   496,   501,   506,   511,   519,   527,   535,   543,   554,
     562,   571,   576,   584,   588,   595,   603,   610,   618,   628,
     640,   645,   650,   655,   660,   669,   676,   686,   691,   696,
     704,   712,   722,   730,   738,   749,   758,   766,   780,   785,
     790,   798,   808,   818,   823,   830,   838,   842,   858,   873,
     878,   883,   891,   896,   907,   912,   917,   922,   930,   935,
     940,   945,   953,   958,   963,   971,   977,   983,   988,   995,
    1003,  1018,  1022,  1029,  1034,  1042,  1055,  1071,  1080,  1089,
    1100,  1108,  1113,  1128,  1132,  1136,  1140,  1144,  1148,  1155,
    1160,  1173,  1181,  1185,  1189,  1196,  1201,  1214,  1222,  1226,
    1230,  1234,  1241,  1249,  1260,  1270,  1275,  1291,  1296,  1307
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "PROGRAM", "CONST", "VAR", "PROCEDURE",
  "FUNCTION", "BEGIN", "END", "INTEGER", "REAL", "BOOLEAN", "CHAR",
  "ARRAY", "IF", "THEN", "FOR", "TO", "DO", "READ", "WRITE", "OF", "PLUS",
  "MINUS", "OR", "MUL", "DIV", "MOD", "AND", "NOT", "ASSIGN", "GREATER",
  "EQUAL", "LESS", "LE", "GE", "LG", "SEMICOLON", "COMMA", "COLON",
  "QMARK", "LBRACKET", "RBRACKET", "LBRACE", "RBRACE", "LPAREN", "RPAREN",
  "DOT", "IDENTIFIER", "NUMBER", "STRING", "LOWER_THAN_ELSE", "ELSE",
  "$accept", "program", "program_head", "program_body", "idlist",
  "const_declarations", "const_declaration", "const_value",
  "var_declarations", "var_declaration", "type", "basic_type", "period",
  "subprogram_declarations", "subprogram", "subprogram_head",
  "formal_parameter", "parameter_list", "parameter", "var_parameter",
  "value_parameter", "subprogram_body", "compound_statement",
  "statement_list", "statement", "else_part", "variable_list", "variable",
  "id_varpart", "procedure_call", "expression_list", "expression", "relop",
  "simple_expression", "addop", "term", "mulop", "factor", 0
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[YYLEX-NUM] -- Internal token number corresponding to
   token YYLEX-NUM.  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   300,   301,   302,   303,   304,
     305,   306,   307,   308
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    54,    55,    55,    55,    55,    55,    55,    55,    55,
      55,    56,    56,    56,    56,    56,    56,    56,    57,    58,
      58,    59,    59,    59,    59,    60,    60,    60,    60,    60,
      60,    60,    61,    61,    61,    61,    62,    62,    62,    62,
      63,    63,    63,    63,    63,    63,    63,    64,    64,    64,
      64,    64,    64,    64,    64,    65,    65,    65,    65,    66,
      66,    66,    66,    67,    67,    67,    68,    68,    69,    69,
      69,    69,    69,    69,    69,    70,    70,    70,    70,    70,
      71,    71,    71,    72,    72,    73,    73,    74,    74,    74,
      74,    75,    76,    77,    77,    77,    78,    78,    78,    78,
      78,    78,    78,    78,    78,    78,    78,    78,    78,    78,
      78,    78,    78,    78,    78,    79,    79,    80,    80,    80,
      81,    82,    82,    82,    82,    83,    83,    83,    84,    84,
      84,    85,    85,    86,    86,    86,    86,    86,    86,    87,
      87,    87,    88,    88,    88,    89,    89,    89,    90,    90,
      90,    90,    91,    91,    91,    91,    91,    91,    91,    91
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     4,     4,     4,     4,     4,     5,     5,     5,
       5,     5,     5,     5,     5,     2,     2,     4,     4,     1,
       3,     0,     3,     3,     3,     3,     5,     5,     5,     5,
       3,     3,     1,     2,     2,     1,     0,     3,     3,     3,
       3,     5,     3,     3,     5,     5,     5,     1,     6,     6,
       6,     6,     2,     3,     4,     1,     1,     1,     1,     4,
       6,     6,     5,     0,     3,     3,     3,     3,     3,     5,
       3,     5,     5,     5,     2,     0,     3,     3,     3,     2,
       1,     3,     3,     1,     1,     2,     2,     3,     3,     3,
       2,     3,     3,     1,     3,     3,     0,     3,     3,     1,
       1,     5,     5,     8,     8,     8,     8,     4,     4,     3,
       4,     4,     4,     3,     4,     2,     0,     1,     3,     3,
       2,     0,     3,     2,     3,     1,     4,     4,     1,     3,
       3,     1,     3,     1,     1,     1,     1,     1,     1,     1,
       3,     4,     1,     1,     1,     1,     3,     4,     1,     1,
       1,     1,     1,     1,     3,     3,     4,     3,     2,     2
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     0,     0,     0,     0,    21,     0,    16,    15,     1,
      21,     0,     0,     0,    36,    21,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     6,     0,    63,     0,     0,
       0,    19,     0,    17,     0,     3,     4,     5,     2,    23,
       0,     0,    24,    22,     0,     0,     0,     0,     8,    10,
       9,     7,     0,    12,    13,    14,    11,     0,     0,    32,
      35,    31,    30,    25,     0,     0,    38,     0,     0,    39,
      37,     0,     0,    96,     0,     0,    18,    20,    34,    33,
       0,     0,     0,    55,    56,    57,    58,     0,    42,    47,
      43,    40,     0,     0,    75,    75,    74,    75,     0,     0,
       0,     0,     0,   125,   100,     0,    93,     0,    99,    65,
      64,    21,    21,    28,    29,    27,    26,    52,     0,     0,
       0,     0,     0,    70,    68,     0,     0,     0,     0,     0,
       0,   121,   152,   153,     0,   131,   139,   145,     0,     0,
       0,     0,     0,     0,     0,   120,    96,    92,    96,     0,
      36,    67,    66,     0,     0,    53,     0,    44,    45,    46,
      41,    79,     0,     0,     0,    80,    83,    84,     0,     0,
       0,    98,   159,   158,     0,     0,    96,    96,   142,   143,
     144,   134,   133,   135,   136,   137,   138,     0,     0,   148,
     149,   150,   151,     0,     0,     0,   121,     0,   117,   109,
       0,     0,   128,   113,     0,   123,     0,     0,    95,    94,
      97,     0,     0,     0,     0,     0,    54,     0,    77,    86,
      85,    90,     0,    78,     0,    76,    71,    72,    73,    69,
     155,   154,   157,     0,   116,   116,   132,     0,   140,     0,
     146,     0,     0,     0,     0,   108,   110,   107,     0,     0,
     112,   114,   111,   124,   122,   127,   126,    91,     0,     0,
       0,     0,     0,     0,    88,    89,    87,    82,    81,   156,
      96,   102,   101,   141,   147,     0,     0,     0,   119,   118,
     130,   129,    59,     0,     0,     0,    49,    50,    51,    48,
     115,     0,     0,     0,     0,    62,     0,    96,    96,    96,
      96,    61,    60,   105,   106,   104,   103
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     3,     4,    13,   163,    14,    24,    61,    27,    46,
      88,    89,   154,    47,    74,    75,   123,   164,   165,   166,
     167,   151,   104,   105,   106,   271,   197,   133,   145,   108,
     201,   202,   187,   135,   188,   136,   193,   137
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -164
static const yytype_int16 yypact[] =
{
     233,   212,    32,    21,    47,    20,   191,   -11,   126,  -164,
      20,   313,    39,    35,   185,    20,   321,    74,    43,   199,
     204,    38,   195,   220,   201,  -164,    45,  -164,   216,   267,
     104,  -164,   -20,   202,   105,  -164,  -164,  -164,  -164,  -164,
     193,    12,   207,   217,   249,   115,   203,   292,  -164,  -164,
    -164,  -164,   274,  -164,  -164,  -164,  -164,   266,   297,  -164,
    -164,  -164,  -164,  -164,   291,   229,  -164,   320,   264,    74,
      74,    51,    81,   179,   210,   211,  -164,  -164,  -164,  -164,
     193,   193,    26,  -164,  -164,  -164,  -164,   134,  -164,  -164,
    -164,  -164,   100,   174,   302,   302,   -18,   302,   318,   208,
     301,    79,   121,   200,  -164,   197,  -164,   322,  -164,  -164,
    -164,    20,    20,  -164,  -164,  -164,  -164,   304,    14,   320,
     320,   278,    29,  -164,  -164,   311,   155,   208,   208,   208,
     208,   221,  -164,  -164,   239,   236,   276,  -164,   118,   303,
      92,   208,    41,    71,   208,  -164,   179,  -164,   179,   208,
     185,  -164,  -164,   307,   162,  -164,   164,  -164,  -164,  -164,
    -164,   309,    97,   183,     9,  -164,  -164,  -164,   325,   325,
     283,  -164,  -164,  -164,    52,    78,   179,   179,  -164,  -164,
    -164,  -164,  -164,  -164,  -164,  -164,  -164,   208,    83,  -164,
    -164,  -164,  -164,    88,   208,   208,   315,   125,  -164,  -164,
     135,   141,  -164,  -164,   142,  -164,    11,   144,  -164,  -164,
    -164,   350,   312,   314,   317,   337,   314,    19,  -164,  -164,
    -164,   325,   296,     6,     6,  -164,  -164,  -164,  -164,  -164,
    -164,  -164,  -164,   146,   308,   308,   316,   208,   276,   208,
    -164,   344,    25,   303,   303,  -164,   303,  -164,   208,   208,
    -164,   208,  -164,  -164,  -164,   208,  -164,  -164,   319,   323,
     114,   325,   325,   300,  -164,  -164,  -164,  -164,  -164,  -164,
     179,  -164,  -164,   276,  -164,   208,   208,   208,  -164,  -164,
    -164,  -164,  -164,   324,   326,   327,  -164,  -164,  -164,  -164,
    -164,   346,   347,   218,   328,  -164,   329,   179,   179,   179,
     179,  -164,  -164,  -164,  -164,  -164,  -164
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -164,  -164,   362,   270,   -12,   171,  -164,   128,   223,  -164,
     -60,  -152,   250,  -164,  -164,  -164,   247,  -164,   122,  -164,
     215,   258,   -45,  -164,  -139,   139,   240,   -73,  -164,  -164,
      76,   -98,  -164,   194,  -164,  -163,  -164,  -125
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -122
static const yytype_int16 yytable[] =
{
     107,   134,    76,   172,   173,    32,    34,   208,    91,   209,
     223,   162,   253,    62,    45,   155,   226,   227,   229,    52,
     262,     9,   -75,    53,    12,   238,   276,   115,   122,   171,
     161,    17,   174,     7,   162,    57,    58,   234,   235,    37,
      22,   263,   203,   277,    33,   206,    44,   224,    10,    57,
      58,   210,    94,   230,   254,    31,   225,    92,    93,   157,
     158,   160,    59,    60,   153,   128,   198,   198,   240,   264,
     266,   129,   205,   107,   273,   107,    59,    60,    31,   232,
     139,     8,    96,    25,   237,    11,    38,   130,    23,   239,
     131,   132,    31,   199,    31,   128,   241,   242,   219,   231,
      95,   129,   128,   107,   107,    50,    55,   128,   129,   286,
     287,   289,   128,   129,   274,   284,    67,   130,   129,   194,
     131,   132,   141,    31,   130,   140,   243,   131,   132,   130,
      97,   290,   131,   132,   130,   117,   246,   131,   132,    52,
     119,   196,   248,   251,    52,   255,    31,   248,    56,   195,
     280,   281,    51,   280,    52,    68,   169,   280,   303,   304,
     305,   306,   285,   213,   244,   216,   257,   142,    18,    63,
     278,   279,   245,   278,   244,   120,   118,   291,   292,   293,
     249,   249,   247,   249,   221,   249,    98,    73,   250,   252,
      26,   256,    15,   269,    99,   170,   100,   107,   146,   101,
     102,   214,    42,   214,    69,   215,   147,   217,   113,   114,
     116,   109,   111,    52,   121,     2,    57,    58,   204,   299,
     207,    40,    52,   222,   107,   107,   107,   107,   103,    16,
      81,  -121,   128,    39,     1,   148,     2,   300,   129,    43,
     176,    70,   143,    59,    60,    54,   144,    35,   110,   112,
       5,   233,    36,    41,   130,   177,    64,   131,   132,   178,
     179,   180,    82,   143,    48,    90,    65,   175,   181,   182,
     183,   184,   185,   186,    83,    84,    85,    86,    87,   159,
      19,    21,   150,   150,   228,    28,    30,    66,    83,    84,
      85,    86,    87,    83,    84,    85,    86,   265,    71,    72,
      73,   288,   189,   190,   191,   192,    83,    84,    85,    86,
      83,    84,    85,    86,    20,    49,    78,    12,   -21,   -21,
     -21,   -21,    29,    77,    80,    12,   -21,   -21,   -21,   -21,
      83,    84,    85,    86,    87,    83,    84,    85,    86,   178,
     179,   180,   124,   125,   126,   267,   268,    79,   122,   127,
     138,   168,   196,   149,   153,   212,   218,   143,    73,   261,
     258,   270,   275,     6,   259,   297,   298,   260,   156,   282,
     152,   283,   294,   211,   272,   296,   295,   220,   301,   302,
     200,   236
};

static const yytype_uint16 yycheck[] =
{
      73,    99,    47,   128,   129,    17,    18,   146,    68,   148,
       1,     5,     1,     1,    26,     1,   168,   169,   170,    39,
       1,     0,    40,    43,     4,   188,     1,     1,    46,   127,
       1,    42,   130,     1,     5,    23,    24,   176,   177,     1,
       1,    22,     1,    18,     1,   143,     1,    38,     1,    23,
      24,   149,     1,     1,    43,    49,    47,    69,    70,   119,
     120,   121,    50,    51,    50,    24,   139,   140,   193,   221,
     222,    30,     1,   146,   237,   148,    50,    51,    49,     1,
       1,    49,     1,    48,     1,    38,    48,    46,    49,     1,
      49,    50,    49,     1,    49,    24,   194,   195,     1,    47,
      49,    30,    24,   176,   177,     1,     1,    24,    30,   261,
     262,   263,    24,    30,   239,     1,     1,    46,    30,     1,
      49,    50,     1,    49,    46,    46,     1,    49,    50,    46,
      49,   270,    49,    50,    46,     1,     1,    49,    50,    39,
      40,    49,     1,     1,    39,     1,    49,     1,    43,    31,
     248,   249,    48,   251,    39,    40,     1,   255,   297,   298,
     299,   300,    48,     1,    39,     1,   211,    46,    42,    41,
     243,   244,    47,   246,    39,     1,    42,   275,   276,   277,
      39,    39,    47,    39,     1,    39,     7,     8,    47,    47,
       5,    47,     1,    47,    15,    40,    17,   270,     1,    20,
      21,    39,     1,    39,     1,    43,     9,    43,    80,    81,
      82,     1,     1,    39,    40,     3,    23,    24,   142,     1,
     144,     1,    39,    40,   297,   298,   299,   300,    49,    38,
       1,    31,    24,    38,     1,    38,     3,    19,    30,    38,
       1,    38,    42,    50,    51,    43,    46,    48,    38,    38,
      38,   175,    48,    33,    46,    16,    49,    49,    50,    23,
      24,    25,    33,    42,    48,     1,    49,    46,    32,    33,
      34,    35,    36,    37,    10,    11,    12,    13,    14,     1,
      10,    11,   111,   112,     1,    15,    16,    38,    10,    11,
      12,    13,    14,    10,    11,    12,    13,     1,     6,     7,
       8,     1,    26,    27,    28,    29,    10,    11,    12,    13,
      10,    11,    12,    13,     1,    48,    50,     4,     5,     6,
       7,     8,     1,    49,    33,     4,     5,     6,     7,     8,
      10,    11,    12,    13,    14,    10,    11,    12,    13,    23,
      24,    25,    95,    96,    97,   223,   224,    50,    46,    31,
      49,    40,    49,    31,    50,    48,    47,    42,     8,    22,
      48,    53,    18,     1,    50,    19,    19,    50,   118,    50,
     112,    48,    48,   150,   235,    48,    50,   162,    50,    50,
     140,   187
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     1,     3,    55,    56,    38,    56,     1,    49,     0,
       1,    38,     4,    57,    59,     1,    38,    42,    42,    57,
       1,    57,     1,    49,    60,    48,     5,    62,    57,     1,
      57,    49,    58,     1,    58,    48,    48,     1,    48,    38,
       1,    33,     1,    38,     1,    58,    63,    67,    48,    48,
       1,    48,    39,    43,    43,     1,    43,    23,    24,    50,
      51,    61,     1,    61,    49,    49,    38,     1,    40,     1,
      38,     6,     7,     8,    68,    69,    76,    49,    50,    50,
      33,     1,    33,    10,    11,    12,    13,    14,    64,    65,
       1,    64,    58,    58,     1,    49,     1,    49,     7,    15,
      17,    20,    21,    49,    76,    77,    78,    81,    83,     1,
      38,     1,    38,    61,    61,     1,    61,     1,    42,    40,
       1,    40,    46,    70,    70,    70,    70,    31,    24,    30,
      46,    49,    50,    81,    85,    87,    89,    91,    49,     1,
      46,     1,    46,    42,    46,    82,     1,     9,    38,    31,
      59,    75,    75,    50,    66,     1,    66,    64,    64,     1,
      64,     1,     5,    58,    71,    72,    73,    74,    40,     1,
      40,    85,    91,    91,    85,    46,     1,    16,    23,    24,
      25,    32,    33,    34,    35,    36,    37,    86,    88,    26,
      27,    28,    29,    90,     1,    31,    49,    80,    81,     1,
      80,    84,    85,     1,    84,     1,    85,    84,    78,    78,
      85,    62,    48,     1,    39,    43,     1,    43,    47,     1,
      74,     1,    40,     1,    38,    47,    65,    65,     1,    65,
       1,    47,     1,    84,    78,    78,    87,     1,    89,     1,
      91,    85,    85,     1,    39,    47,     1,    47,     1,    39,
      47,     1,    47,     1,    43,     1,    47,    76,    48,    50,
      50,    22,     1,    22,    65,     1,    65,    72,    72,    47,
      53,    79,    79,    89,    91,    18,     1,    18,    81,    81,
      85,    85,    50,    48,     1,    48,    65,    65,     1,    65,
      78,    85,    85,    85,    48,    50,    48,    19,    19,     1,
      19,    50,    50,    78,    78,    78,    78
};

#define yyerrok		(yyerrstatus = 0)
#define yyclearin	(yychar = YYEMPTY)
#define YYEMPTY		(-2)
#define YYEOF		0

#define YYACCEPT	goto yyacceptlab
#define YYABORT		goto yyabortlab
#define YYERROR		goto yyerrorlab


/* Like YYERROR except do call yyerror.  This remains here temporarily
   to ease the transition to the new meaning of YYERROR, for GCC.
   Once GCC version 2 has supplanted version 1, this can go.  */

#define YYFAIL		goto yyerrlab

#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)					\
do								\
  if (yychar == YYEMPTY && yylen == 1)				\
    {								\
      yychar = (Token);						\
      yylval = (Value);						\
      yytoken = YYTRANSLATE (yychar);				\
      YYPOPSTACK (1);						\
      goto yybackup;						\
    }								\
  else								\
    {								\
      yyerror (YY_("syntax error: cannot back up")); \
      YYERROR;							\
    }								\
while (YYID (0))


#define YYTERROR	1
#define YYERRCODE	256


/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#define YYRHSLOC(Rhs, K) ((Rhs)[K])
#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)				\
    do									\
      if (YYID (N))                                                    \
	{								\
	  (Current).first_line   = YYRHSLOC (Rhs, 1).first_line;	\
	  (Current).first_column = YYRHSLOC (Rhs, 1).first_column;	\
	  (Current).last_line    = YYRHSLOC (Rhs, N).last_line;		\
	  (Current).last_column  = YYRHSLOC (Rhs, N).last_column;	\
	}								\
      else								\
	{								\
	  (Current).first_line   = (Current).last_line   =		\
	    YYRHSLOC (Rhs, 0).last_line;				\
	  (Current).first_column = (Current).last_column =		\
	    YYRHSLOC (Rhs, 0).last_column;				\
	}								\
    while (YYID (0))
#endif


/* YY_LOCATION_PRINT -- Print the location on the stream.
   This macro was not mandated originally: define only if we know
   we won't break user code: when these are the locations we know.  */

#ifndef YY_LOCATION_PRINT
# if YYLTYPE_IS_TRIVIAL
#  define YY_LOCATION_PRINT(File, Loc)			\
     fprintf (File, "%d.%d-%d.%d",			\
	      (Loc).first_line, (Loc).first_column,	\
	      (Loc).last_line,  (Loc).last_column)
# else
#  define YY_LOCATION_PRINT(File, Loc) ((void) 0)
# endif
#endif


/* YYLEX -- calling `yylex' with the right arguments.  */

#ifdef YYLEX_PARAM
# define YYLEX yylex (YYLEX_PARAM)
#else
# define YYLEX yylex ()
#endif

/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)			\
do {						\
  if (yydebug)					\
    YYFPRINTF Args;				\
} while (YYID (0))

# define YY_SYMBOL_PRINT(Title, Type, Value, Location)			  \
do {									  \
  if (yydebug)								  \
    {									  \
      YYFPRINTF (stderr, "%s ", Title);					  \
      yy_symbol_print (stderr,						  \
		  Type, Value, Location); \
      YYFPRINTF (stderr, "\n");						  \
    }									  \
} while (YYID (0))


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp)
#else
static void
yy_symbol_value_print (yyoutput, yytype, yyvaluep, yylocationp)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
    YYLTYPE const * const yylocationp;
#endif
{
  if (!yyvaluep)
    return;
  YYUSE (yylocationp);
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# else
  YYUSE (yyoutput);
# endif
  switch (yytype)
    {
      default:
	break;
    }
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp)
#else
static void
yy_symbol_print (yyoutput, yytype, yyvaluep, yylocationp)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
    YYLTYPE const * const yylocationp;
#endif
{
  if (yytype < YYNTOKENS)
    YYFPRINTF (yyoutput, "token %s (", yytname[yytype]);
  else
    YYFPRINTF (yyoutput, "nterm %s (", yytname[yytype]);

  YY_LOCATION_PRINT (yyoutput, *yylocationp);
  YYFPRINTF (yyoutput, ": ");
  yy_symbol_value_print (yyoutput, yytype, yyvaluep, yylocationp);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
#else
static void
yy_stack_print (yybottom, yytop)
    yytype_int16 *yybottom;
    yytype_int16 *yytop;
#endif
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)				\
do {								\
  if (yydebug)							\
    yy_stack_print ((Bottom), (Top));				\
} while (YYID (0))


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_reduce_print (YYSTYPE *yyvsp, YYLTYPE *yylsp, int yyrule)
#else
static void
yy_reduce_print (yyvsp, yylsp, yyrule)
    YYSTYPE *yyvsp;
    YYLTYPE *yylsp;
    int yyrule;
#endif
{
  int yynrhs = yyr2[yyrule];
  int yyi;
  unsigned long int yylno = yyrline[yyrule];
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
	     yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr, yyrhs[yyprhs[yyrule] + yyi],
		       &(yyvsp[(yyi + 1) - (yynrhs)])
		       , &(yylsp[(yyi + 1) - (yynrhs)])		       );
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)		\
do {					\
  if (yydebug)				\
    yy_reduce_print (yyvsp, yylsp, Rule); \
} while (YYID (0))

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef	YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif



#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static YYSIZE_T
yystrlen (const char *yystr)
#else
static YYSIZE_T
yystrlen (yystr)
    const char *yystr;
#endif
{
  YYSIZE_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static char *
yystpcpy (char *yydest, const char *yysrc)
#else
static char *
yystpcpy (yydest, yysrc)
    char *yydest;
    const char *yysrc;
#endif
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

# ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYSIZE_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYSIZE_T yyn = 0;
      char const *yyp = yystr;

      for (;;)
	switch (*++yyp)
	  {
	  case '\'':
	  case ',':
	    goto do_not_strip_quotes;

	  case '\\':
	    if (*++yyp != '\\')
	      goto do_not_strip_quotes;
	    /* Fall through.  */
	  default:
	    if (yyres)
	      yyres[yyn] = *yyp;
	    yyn++;
	    break;

	  case '"':
	    if (yyres)
	      yyres[yyn] = '\0';
	    return yyn;
	  }
    do_not_strip_quotes: ;
    }

  if (! yyres)
    return yystrlen (yystr);

  return yystpcpy (yyres, yystr) - yyres;
}
# endif

/* Copy into YYRESULT an error message about the unexpected token
   YYCHAR while in state YYSTATE.  Return the number of bytes copied,
   including the terminating null byte.  If YYRESULT is null, do not
   copy anything; just return the number of bytes that would be
   copied.  As a special case, return 0 if an ordinary "syntax error"
   message will do.  Return YYSIZE_MAXIMUM if overflow occurs during
   size calculation.  */
static YYSIZE_T
yysyntax_error (char *yyresult, int yystate, int yychar)
{
  int yyn = yypact[yystate];

  if (! (YYPACT_NINF < yyn && yyn <= YYLAST))
    return 0;
  else
    {
      int yytype = YYTRANSLATE (yychar);
      YYSIZE_T yysize0 = yytnamerr (0, yytname[yytype]);
      YYSIZE_T yysize = yysize0;
      YYSIZE_T yysize1;
      int yysize_overflow = 0;
      enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
      char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
      int yyx;

# if 0
      /* This is so xgettext sees the translatable formats that are
	 constructed on the fly.  */
      YY_("syntax error, unexpected %s");
      YY_("syntax error, unexpected %s, expecting %s");
      YY_("syntax error, unexpected %s, expecting %s or %s");
      YY_("syntax error, unexpected %s, expecting %s or %s or %s");
      YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s");
# endif
      char *yyfmt;
      char const *yyf;
      static char const yyunexpected[] = "syntax error, unexpected %s";
      static char const yyexpecting[] = ", expecting %s";
      static char const yyor[] = " or %s";
      char yyformat[sizeof yyunexpected
		    + sizeof yyexpecting - 1
		    + ((YYERROR_VERBOSE_ARGS_MAXIMUM - 2)
		       * (sizeof yyor - 1))];
      char const *yyprefix = yyexpecting;

      /* Start YYX at -YYN if negative to avoid negative indexes in
	 YYCHECK.  */
      int yyxbegin = yyn < 0 ? -yyn : 0;

      /* Stay within bounds of both yycheck and yytname.  */
      int yychecklim = YYLAST - yyn + 1;
      int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
      int yycount = 1;

      yyarg[0] = yytname[yytype];
      yyfmt = yystpcpy (yyformat, yyunexpected);

      for (yyx = yyxbegin; yyx < yyxend; ++yyx)
	if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR)
	  {
	    if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
	      {
		yycount = 1;
		yysize = yysize0;
		yyformat[sizeof yyunexpected - 1] = '\0';
		break;
	      }
	    yyarg[yycount++] = yytname[yyx];
	    yysize1 = yysize + yytnamerr (0, yytname[yyx]);
	    yysize_overflow |= (yysize1 < yysize);
	    yysize = yysize1;
	    yyfmt = yystpcpy (yyfmt, yyprefix);
	    yyprefix = yyor;
	  }

      yyf = YY_(yyformat);
      yysize1 = yysize + yystrlen (yyf);
      yysize_overflow |= (yysize1 < yysize);
      yysize = yysize1;

      if (yysize_overflow)
	return YYSIZE_MAXIMUM;

      if (yyresult)
	{
	  /* Avoid sprintf, as that infringes on the user's name space.
	     Don't have undefined behavior even if the translation
	     produced a string with the wrong number of "%s"s.  */
	  char *yyp = yyresult;
	  int yyi = 0;
	  while ((*yyp = *yyf) != '\0')
	    {
	      if (*yyp == '%' && yyf[1] == 's' && yyi < yycount)
		{
		  yyp += yytnamerr (yyp, yyarg[yyi++]);
		  yyf += 2;
		}
	      else
		{
		  yyp++;
		  yyf++;
		}
	    }
	}
      return yysize;
    }
}
#endif /* YYERROR_VERBOSE */


/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep, YYLTYPE *yylocationp)
#else
static void
yydestruct (yymsg, yytype, yyvaluep, yylocationp)
    const char *yymsg;
    int yytype;
    YYSTYPE *yyvaluep;
    YYLTYPE *yylocationp;
#endif
{
  YYUSE (yyvaluep);
  YYUSE (yylocationp);

  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  switch (yytype)
    {

      default:
	break;
    }
}

/* Prevent warnings from -Wmissing-prototypes.  */
#ifdef YYPARSE_PARAM
#if defined __STDC__ || defined __cplusplus
int yyparse (void *YYPARSE_PARAM);
#else
int yyparse ();
#endif
#else /* ! YYPARSE_PARAM */
#if defined __STDC__ || defined __cplusplus
int yyparse (void);
#else
int yyparse ();
#endif
#endif /* ! YYPARSE_PARAM */


/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;

/* Location data for the lookahead symbol.  */
YYLTYPE yylloc;

/* Number of syntax errors so far.  */
int yynerrs;



/*-------------------------.
| yyparse or yypush_parse.  |
`-------------------------*/

#ifdef YYPARSE_PARAM
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void *YYPARSE_PARAM)
#else
int
yyparse (YYPARSE_PARAM)
    void *YYPARSE_PARAM;
#endif
#else /* ! YYPARSE_PARAM */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void)
#else
int
yyparse ()

#endif
#endif
{


    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       `yyss': related to states.
       `yyvs': related to semantic values.
       `yyls': related to locations.

       Refer to the stacks thru separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yytype_int16 yyssa[YYINITDEPTH];
    yytype_int16 *yyss;
    yytype_int16 *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    /* The location stack.  */
    YYLTYPE yylsa[YYINITDEPTH];
    YYLTYPE *yyls;
    YYLTYPE *yylsp;

    /* The locations where the error started and ended.  */
    YYLTYPE yyerror_range[2];

    YYSIZE_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;
  YYLTYPE yyloc;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N), yylsp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yytoken = 0;
  yyss = yyssa;
  yyvs = yyvsa;
  yyls = yylsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */

  /* Initialize stack pointers.
     Waste one element of value and location stack
     so that they stay on the same level as the state stack.
     The wasted elements are never initialized.  */
  yyssp = yyss;
  yyvsp = yyvs;
  yylsp = yyls;

#if YYLTYPE_IS_TRIVIAL
  /* Initialize the default location before parsing starts.  */
  yylloc.first_line   = yylloc.last_line   = 1;
  yylloc.first_column = yylloc.last_column = 1;
#endif

  goto yysetstate;

/*------------------------------------------------------------.
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
	/* Give user a chance to reallocate the stack.  Use copies of
	   these so that the &'s don't force the real ones into
	   memory.  */
	YYSTYPE *yyvs1 = yyvs;
	yytype_int16 *yyss1 = yyss;
	YYLTYPE *yyls1 = yyls;

	/* Each stack pointer address is followed by the size of the
	   data in use in that stack, in bytes.  This used to be a
	   conditional around just the two extra args, but that might
	   be undefined if yyoverflow is a macro.  */
	yyoverflow (YY_("memory exhausted"),
		    &yyss1, yysize * sizeof (*yyssp),
		    &yyvs1, yysize * sizeof (*yyvsp),
		    &yyls1, yysize * sizeof (*yylsp),
		    &yystacksize);

	yyls = yyls1;
	yyss = yyss1;
	yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyexhaustedlab;
# else
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
	goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
	yystacksize = YYMAXDEPTH;

      {
	yytype_int16 *yyss1 = yyss;
	union yyalloc *yyptr =
	  (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
	if (! yyptr)
	  goto yyexhaustedlab;
	YYSTACK_RELOCATE (yyss_alloc, yyss);
	YYSTACK_RELOCATE (yyvs_alloc, yyvs);
	YYSTACK_RELOCATE (yyls_alloc, yyls);
#  undef YYSTACK_RELOCATE
	if (yyss1 != yyssa)
	  YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;
      yylsp = yyls + yysize - 1;

      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
		  (unsigned long int) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
	YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;

/*-----------.
| yybackup.  |
`-----------*/
yybackup:

  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yyn == YYPACT_NINF)
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = YYLEX;
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yyn == 0 || yyn == YYTABLE_NINF)
	goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);

  /* Discard the shifted token.  */
  yychar = YYEMPTY;

  yystate = yyn;
  *++yyvsp = yylval;
  *++yylsp = yylloc;
  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- Do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     `$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];

  /* Default location.  */
  YYLLOC_DEFAULT (yyloc, (yylsp - yylen), yylen);
  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 2:

/* Line 1455 of yacc.c  */
#line 121 ".\\parser.y"
    {//正常语法，建立语法树
        ParseTree = (yyval) = new AST;//建立根节点
        (yyval)->token = "program";
        (yyval)->children.push_back((yyvsp[(1) - (4)]));//将program_head的语法树节点作为根节点的子节点
        (yyval)->children.push_back((yyvsp[(2) - (4)]));
        (yyval)->children.push_back((yyvsp[(3) - (4)]));//将program_body的语法树节点作为根节点的子节点
        (yyval)->children.push_back((yyvsp[(4) - (4)]));
        if(yylex())//如果还有其他语法树节点
            yyerror("extra tokens at the end of the program",(yylsp[(4) - (4)]).last_line, (yylsp[(4) - (4)]).last_column+1);
    }
    break;

  case 3:

/* Line 1455 of yacc.c  */
#line 131 ".\\parser.y"
    {//语法错误，缺少分号
        yyerror("missing semicolon", (yylsp[(2) - (4)]).last_line, (yylsp[(2) - (4)]).last_column+1);
        ParseTree=(yyval)=new AST;
        (yyval)->token = "program";
    }
    break;

  case 4:

/* Line 1455 of yacc.c  */
#line 136 ".\\parser.y"
    {//语法错误，缺少program_body
        yyerror("fatal error in program boady");
        ParseTree=(yyval)=new AST;
        (yyval)->token = "program";
    }
    break;

  case 5:

/* Line 1455 of yacc.c  */
#line 141 ".\\parser.y"
    {//语法错误，缺少点号
        yyerror("missing dot", (yylsp[(4) - (4)]).last_line, (yylsp[(4) - (4)]).last_column+1);
        ParseTree=(yyval)=new AST;
        (yyval)->token = "program";
    }
    break;

  case 6:

/* Line 1455 of yacc.c  */
#line 146 ".\\parser.y"
    {//语法错误，缺少program_head
        yyerror("fatal error in program head, maybe missing keyword \"program\"", (yylsp[(1) - (4)]).first_line, (yylsp[(1) - (4)]).first_column, (yylsp[(1) - (4)]).last_line, (yylsp[(1) - (4)]).last_column);
        ParseTree=(yyval)=new AST;
        (yyval)->token = "program";
    }
    break;

  case 7:

/* Line 1455 of yacc.c  */
#line 151 ".\\parser.y"
    {//语法错误，program_head前面有多余的字符
        yyerror("extra tokens before program head",(yyloc).first_line, (yyloc).first_column, (yylsp[(2) - (5)]).first_line, (yylsp[(2) - (5)]).first_column-1);
        ParseTree=(yyval)=new AST;
        (yyval)->token = "program";
    }
    break;

  case 8:

/* Line 1455 of yacc.c  */
#line 156 ".\\parser.y"
    { //program_head前包含非法记号、缺失分号
        yyerror("invalid token before program head, maybe missing keyword \"program\"", (yyloc).first_line, (yyloc).first_column, (yylsp[(2) - (5)]).first_line, (yylsp[(2) - (5)]).first_column-1);
        yerror("missing semicolon", (yylsp[(2) - (5)]).last_line, (yylsp[(2) - (5)]).last_column+1);
        ParseTree=(yyval)=new AST
        (yyval)->token="program";
    }
    break;

  case 9:

/* Line 1455 of yacc.c  */
#line 162 ".\\parser.y"
    { //program_head前包含非法记号、缺失点号
        yyerror("invalid token before program head, maybe missing keyword \"program\"", (yyloc).first_line, (yyloc).first_column, (yylsp[(2) - (5)]).first_line, (yylsp[(2) - (5)]).first_column-1);
        yyerror("missing dot", (yylsp[(4) - (5)]).last_line, (yylsp[(4) - (5)]).last_column+1);
        ParseTree=(yyval)=new Type;
        (yyval)->token = "program";

    }
    break;

  case 10:

/* Line 1455 of yacc.c  */
#line 169 ".\\parser.y"
    { //ERROR program_head前包含非法记号、program_body缺失
        yyerror("invalid token before program head, maybe missing keyword \"program\"", (yyloc).first_line, (yyloc).first_column, (yylsp[(2) - (5)]).first_line, (yylsp[(2) - (5)]).first_column-1);
        yyerror("fatal error in program body", (yylsp[(3) - (5)]).last_line, (yylsp[(3) - (5)]).last_column+1, (yylsp[(5) - (5)]).first_line, (yylsp[(5) - (5)]).first_column-1);
        ParseTree=(yyval)=new AST;
        (yyval)->token = "program";
    }
    break;

  case 11:

/* Line 1455 of yacc.c  */
#line 178 ".\\parser.y"
    {//正常
         (yyval)=new AST;
         (yyval)->token = "program_head";
         (yyval)->children.push_back((yyvsp[(1) - (5)])); (yyval)->children.push_back((yyvsp[(2) - (5)]));
         (yyval)->children.push_back((yyvsp[(3) - (5)])); (yyval)->children.push_back((yyvsp[(4) - (5)]));
         (yyval)->children.push_back((yyvsp[(5) - (5)]));
     }
    break;

  case 12:

/* Line 1455 of yacc.c  */
#line 185 ".\\parser.y"
    {//语法错误，缺少标识符
         yyerror("missing program name", (yylsp[(1) - (5)]).last_line, (yylsp[(1) - (5)]).last_column+1);
         (yyval)=new AST;
         (yyval)->token = "program_head";
     }
    break;

  case 13:

/* Line 1455 of yacc.c  */
#line 190 ".\\parser.y"
    {//语法错误，idlist识别失败
         yyerror("program identifier list missing or imcomplete", (yylsp[(4) - (5)]).first_line, (yylsp[(4) - (5)]).first_column, (yylsp[(4) - (5)]).last_line, (yylsp[(4) - (5)]).last_column);
         (yyval)=new AST;
         (yyval)->token = "program_head";
     }
    break;

  case 14:

/* Line 1455 of yacc.c  */
#line 195 ".\\parser.y"
    {//语法错误，缺少右中括号
         yyerror("missing right bracket", (yylsp[(4) - (5)]).last_line, (yylsp[(4) - (5)]).last_column+1);
         (yyval)=new AST;
         (yyval)->token = "program_head";
     }
    break;

  case 15:

/* Line 1455 of yacc.c  */
#line 200 ".\\parser.y"
    {//正常
        (yyval)=new AST;
        (yyval)->token="program_head";
        (yyval)->children.push_back((yyvsp[(1) - (2)]));
        (yyval)->children.push_back((yyvsp[(2) - (2)]));
    }
    break;

  case 16:

/* Line 1455 of yacc.c  */
#line 206 ".\\parser.y"
    {//语法错误，缺少标识符
        yyerror("missing program name",  (yylsp[(1) - (2)]).first_line, (yylsp[(1) - (2)]).first_column, (yylsp[(1) - (2)]).last_line, (yylsp[(1) - (2)]).last_column);
        (yyval)=new AST;
        (yyval)->token="program_head";
    }
    break;

  case 17:

/* Line 1455 of yacc.c  */
#line 211 ".\\parser.y"
    {//语法错误，缺少idlist
        yyerror("program identifier list missing or imcomplete",(yylsp[(1) - (4)]).first_line, (yylsp[(1) - (4)]).first_column, (yylsp[(2) - (4)]).last_line, (yylsp[(2) - (4)]).last_column);
        (yyval)=new AST;
        (yyval)->token="program_head";
    }
    break;

  case 18:

/* Line 1455 of yacc.c  */
#line 219 ".\\parser.y"
    {//正常
        (yyval)=new AST;
        (yyval)->token="program_body";
        (yyval)->children.push_back((yyvsp[(1) - (4)]));
        (yyval)->children.push_back((yyvsp[(2) - (4)]));
        (yyval)->children.push_back((yyvsp[(3) - (4)]));
        (yyval)->children.push_back((yyvsp[(4) - (4)]));
    }
    break;

  case 19:

/* Line 1455 of yacc.c  */
#line 230 ".\\parser.y"
    {//正常
        (yyval)=new AST;
        (yyval)->token="idlist";
        (yyval)->children.push_back((yyvsp[(1) - (1)]));

        //语义分析：
        (yyval) = createSymbol((yyvsp[(1) - (1)]), SOME_TYPE, NULL); // 假设 createSymbol 返回 SymbolTableEntry* 类型
      }
    break;

  case 20:

/* Line 1455 of yacc.c  */
#line 238 ".\\parser.y"
    {//正常
        (yyval)=new AST;
        (yyval)->token="idlist";
        (yyval)->children.push_back((yyvsp[(1) - (3)]));
        (yyval)->children.push_back((yyvsp[(2) - (3)]));
        (yyval)->children.push_back((yyvsp[(3) - (3)]));

        //语义分析：
        SymbolTableEntry* entry = createSymbol((yyvsp[(3) - (3)]), SOME_TYPE, NULL);
        entry->next = (yyvsp[(1) - (3)]); // 假设 $1 是之前 idlist 的返回值，即 SymbolTableEntry* 类型
        (yyval) = entry;
      }
    break;

  case 21:

/* Line 1455 of yacc.c  */
#line 254 ".\\parser.y"
    {//正常
        (yyval)=new AST;
        (yyval)->token="const_declarations";
    }
    break;

  case 22:

/* Line 1455 of yacc.c  */
#line 258 ".\\parser.y"
    {//正常
        (yyval)=new AST;
        (yyval)->token="const_declarations";
        (yyval)->children.push_back((yyvsp[(1) - (3)]));
        (yyval)->children.push_back((yyvsp[(2) - (3)]));
        (yyval)->children.push_back((yyvsp[(3) - (3)]));
    }
    break;

  case 23:

/* Line 1455 of yacc.c  */
#line 265 ".\\parser.y"
    {//语法错误，缺少const_declaration
        yyerror("fatal error in const declarations", (yylsp[(2) - (3)]).first_line, (yylsp[(2) - (3)]).first_column, (yylsp[(2) - (3)]).last_line, (yylsp[(2) - (3)]).last_column);
        (yyval)=new AST
        (yyval)->token="const_declarations";
    }
    break;

  case 24:

/* Line 1455 of yacc.c  */
#line 270 ".\\parser.y"
    {//语法错误，缺少分号
        yyerror("missing a semicolon here", (yylsp[(2) - (3)]).first_line, (yylsp[(2) - (3)]).first_column, (yylsp[(2) - (3)]).last_line, (yylsp[(2) - (3)]).last_column);
        (yyval)=new AST;
        (yyval)->token="const_declarations";
    }
    break;

  case 25:

/* Line 1455 of yacc.c  */
#line 278 ".\\parser.y"
    {//正常
            (yyval)=new AST;
            (yyval)->token="const_declaration";
            (yyval)->children.push_back((yyvsp[(1) - (3)]));
            (yyval)->children.push_back((yyvsp[(2) - (3)]));
            (yyval)->children.push_back((yyvsp[(3) - (3)]));

          //语义分析：
          if (findSymbol((yyvsp[(1) - (3)]))) {
              yyerror("Identifier already declared");
          } else {
              // 根据const_value的类型来决定是哪种DataType
              DataType type = (yyvsp[(3) - (3)]).type; // 假设const_value已经确定了类型
              addSymbol((yyvsp[(1) - (3)]), type, 0, NULL);
          }
    }
    break;

  case 26:

/* Line 1455 of yacc.c  */
#line 294 ".\\parser.y"
    {//正常
        (yyval)=new AST;
        (yyval)->token="const_declaration";
        (yyval)->children.push_back((yyvsp[(1) - (5)]));
        (yyval)->children.push_back((yyvsp[(2) - (5)]));
        (yyval)->children.push_back((yyvsp[(3) - (5)]));
        (yyval)->children.push_back((yyvsp[(4) - (5)]));
        (yyval)->children.push_back((yyvsp[(5) - (5)]));

        //语义分析：
        SymbolTableEntry* found = findSymbol((yyvsp[(3) - (5)]));
        if (found) {
            yyerror("Duplicate identifier");
        } else {
            addSymbol((yyvsp[(3) - (5)]), (yyvsp[(5) - (5)]).type, 0, NULL);
        }
      }
    break;

  case 27:

/* Line 1455 of yacc.c  */
#line 311 ".\\parser.y"
    {//语法错误，缺少const_value
        yyerror("constant definition missing initial r-value", (yylsp[(4) - (5)]).first_line, (yylsp[(4) - (5)]).first_column, (yylsp[(4) - (5)]).last_line, (yylsp[(4) - (5)]).last_column);
        (yyval)=new AST;
        (yyval)->token="const_declaration";
    }
    break;

  case 28:

/* Line 1455 of yacc.c  */
#line 316 ".\\parser.y"
    {//语法错误，缺少分号
        yyerror("missing a semicolon", (yylsp[(1) - (5)]).first_line, (yylsp[(1) - (5)]).first_column, (yylsp[(1) - (5)]).last_line, (yylsp[(1) - (5)]).last_column+1);
        (yyval)=new AST;
        (yyval)->token="const_declaration";
    }
    break;

  case 29:

/* Line 1455 of yacc.c  */
#line 321 ".\\parser.y"
    {//语法错误，缺少等号
        yyerror("missing equal sign",(yylsp[(3) - (5)]).first_line, (yylsp[(3) - (5)]).first_column, (yylsp[(3) - (5)]).last_line, (yylsp[(3) - (5)]).last_column);
        (yyval)=new AST;
        (yyval)->token="const_declaration";
    }
    break;

  case 30:

/* Line 1455 of yacc.c  */
#line 326 ".\\parser.y"
    {//语法错误，缺少const_value
        yyerror("constant definition missing initial r-value", (yylsp[(3) - (3)]).first_line, (yylsp[(3) - (3)]).first_column, (yylsp[(3) - (3)]).last_line, (yylsp[(3) - (3)]).last_column);
        (yyval)=new AST
        (yyval)->token="const_declaration";
    }
    break;

  case 31:

/* Line 1455 of yacc.c  */
#line 331 ".\\parser.y"
    {//语法错误，缺少等号
        yyerror("missing equal sign", (yylsp[(2) - (3)]).first_line, (yylsp[(2) - (3)]).first_column, (yylsp[(2) - (3)]).last_line, (yylsp[(2) - (3)]).last_column);
        (yyval)=new AST;
        (yyval)->token="const_declaration";
    }
    break;

  case 32:

/* Line 1455 of yacc.c  */
#line 339 ".\\parser.y"
    {//正常
        (yyval)=new AST;
        (yyval)->token="const_value";
        (yyval)->children.push_back((yyvsp[(1) - (1)]));

        //语义分析：
        (yyval) = (YYSTYPE) {.type = INT_TYPE, .value.ival = (yyvsp[(1) - (1)])};
      }
    break;

  case 33:

/* Line 1455 of yacc.c  */
#line 347 ".\\parser.y"
    {//正常
        (yyval)=new AST;
        (yyval)->token="const_value";
        (yyval)->children.push_back((yyvsp[(1) - (2)]));
        (yyval)->children.push_back((yyvsp[(2) - (2)]));

        //语义分析：
        (yyval) = (YYSTYPE) {.type = INT_TYPE, .value.ival = -(yyvsp[(2) - (2)])};
      }
    break;

  case 34:

/* Line 1455 of yacc.c  */
#line 356 ".\\parser.y"
    {//正常
        (yyval)=new AST;
        (yyval)->token="const_value";
        (yyval)->children.push_back((yyvsp[(1) - (2)]));
        (yyval)->children.push_back((yyvsp[(2) - (2)]));

        //语义分析：
        (yyval) = (YYSTYPE) {.type = INT_TYPE, .value.ival = (yyvsp[(2) - (2)])};
      }
    break;

  case 35:

/* Line 1455 of yacc.c  */
#line 365 ".\\parser.y"
    {//正常,字符串处理不一定正确，词法分析做todo
        (yyval)=new AST;
        (yyval)->token="const_value";
        (yyval)->children.push_back((yyvsp[(1) - (1)]));

        //语义分析：
        (yyval) = (YYSTYPE) {.type = STRING_TYPE, .value.sval = strdup((yyvsp[(1) - (1)]))};
      }
    break;

  case 36:

/* Line 1455 of yacc.c  */
#line 377 ".\\parser.y"
    {//正常
        (yyval)=new AST;
        (yyval)->token="var_declarations";
    }
    break;

  case 37:

/* Line 1455 of yacc.c  */
#line 381 ".\\parser.y"
    {//正常
        (yyval)=new AST;
        (yyval)->token="var_declarations";
        (yyval)->children.push_back((yyvsp[(1) - (3)]));
        (yyval)->children.push_back((yyvsp[(2) - (3)]));
        (yyval)->children.push_back((yyvsp[(3) - (3)]));
    }
    break;

  case 38:

/* Line 1455 of yacc.c  */
#line 388 ".\\parser.y"
    {//语法错误，缺少var_declaration
        yyerror("fatal error in var declarations", (yylsp[(1) - (3)]).first_line, (yylsp[(1) - (3)]).first_column, (yylsp[(1) - (3)]).last_line, (yylsp[(1) - (3)]).last_column);
        (yyval)=new AST;
        (yyval)->token="var_declarations";
    }
    break;

  case 39:

/* Line 1455 of yacc.c  */
#line 393 ".\\parser.y"
    {//语法错误，缺少分号
        yyerror("missing a semicolon",(yylsp[(2) - (3)]).last_line, (yylsp[(2) - (3)]).last_column+1);
        (yyval)=new AST
        (yyval)->token="var_declarations";
    }
    break;

  case 40:

/* Line 1455 of yacc.c  */
#line 401 ".\\parser.y"
    {//正常
        (yyval)=new AST;
        (yyval)->token="var_declaration";
        (yyval)->children.push_back((yyvsp[(1) - (3)]));
        (yyval)->children.push_back((yyvsp[(2) - (3)]));
        (yyval)->children.push_back((yyvsp[(3) - (3)]));

        //语义分析：
        /* 对于每个变量名，检查是否已经定义 */
       for (int i = 0; i < (yyvsp[(1) - (3)]).count; ++i) {
           if (findSymbol((yyvsp[(1) - (3)]).names[i])) {
               printf("Semantic error: variable %s is already defined\n", (yyvsp[(1) - (3)]).names[i]);
           } else {
               createSymbol((yyvsp[(1) - (3)]).names[i], (yyvsp[(3) - (3)]));  /* 创建符号 */
           }
       }
    }
    break;

  case 41:

/* Line 1455 of yacc.c  */
#line 418 ".\\parser.y"
    {//正常
        (yyval)=new AST;
        (yyval)->token="var_declaration";
        (yyval)->children.push_back((yyvsp[(1) - (5)]));
        (yyval)->children.push_back((yyvsp[(2) - (5)]));
        (yyval)->children.push_back((yyvsp[(3) - (5)]));
        (yyval)->children.push_back((yyvsp[(4) - (5)]));
        (yyval)->children.push_back((yyvsp[(5) - (5)]));

        //语义分析：
        /* 同上 */
        for (int i = 0; i < (yyvsp[(3) - (5)]).count; ++i) {
            if (findSymbol((yyvsp[(3) - (5)]).names[i])) {
                printf("Semantic error: variable %s is already defined\n", (yyvsp[(3) - (5)]).names[i]);
            } else {
                createSymbol((yyvsp[(3) - (5)]).names[i], (yyvsp[(5) - (5)]));  /* 同上 */
            }
        }
    }
    break;

  case 42:

/* Line 1455 of yacc.c  */
#line 437 ".\\parser.y"
    {//语法错误，缺少冒号
        yyerror("missing colon", (yylsp[(1) - (3)]).last_line, (yylsp[(1) - (3)]).last_column+1);
        (yyval)=new AST
        (yyval)->token="var_declaration";
    }
    break;

  case 43:

/* Line 1455 of yacc.c  */
#line 442 ".\\parser.y"
    {//语法错误，缺少type
        yyerror("missing type", (yylsp[(3) - (3)]).last_line, (yylsp[(3) - (3)]).last_column+1);
        (yyval)=new AST;
        (yyval)->token="var_declaration";
    }
    break;

  case 44:

/* Line 1455 of yacc.c  */
#line 447 ".\\parser.y"
    {//语法错误，缺少分号
        yyerror("missing a semicolon", (yylsp[(1) - (5)]).last_line, (yylsp[(1) - (5)]).last_column+1);
        (yyval)=new AST;
        (yyval)->token="var_declaration";
    }
    break;

  case 45:

/* Line 1455 of yacc.c  */
#line 452 ".\\parser.y"
    {//语法错误，缺少冒号
        yyerror("missing colon", (yylsp[(3) - (5)]).last_line, (yylsp[(3) - (5)]).last_column+1);
        (yyval)=new AST;
        (yyval)->token="var_declaration";
    }
    break;

  case 46:

/* Line 1455 of yacc.c  */
#line 457 ".\\parser.y"
    {//语法错误，缺少type
        yyerror("missing type", (yylsp[(4) - (5)]).last_line, (yylsp[(4) - (5)]).last_column+1);
        (yyval)=new AST;
        (yyval)->token="var_declaration";
    }
    break;

  case 47:

/* Line 1455 of yacc.c  */
#line 465 ".\\parser.y"
    { // 正常
        (yyval)=new AST;
        (yyval)->token="type";
        (yyval)->children.push_back((yyvsp[(1) - (1)]));

        // 语义分析：
        (yyval) = (yyvsp[(1) - (1)]);
     }
    break;

  case 48:

/* Line 1455 of yacc.c  */
#line 473 ".\\parser.y"
    { // 正常
        (yyval)=new AST;
        (yyval)->token="type";
        (yyval)->children.push_back((yyvsp[(1) - (6)]));
        (yyval)->children.push_back((yyvsp[(2) - (6)]));
        (yyval)->children.push_back((yyvsp[(3) - (6)]));
        (yyval)->children.push_back((yyvsp[(4) - (6)]));
        (yyval)->children.push_back((yyvsp[(5) - (6)]));
        (yyval)->children.push_back((yyvsp[(6) - (6)]));

        // 语义分析：
        (yyval) = ARRAY_TYPE;
     }
    break;

  case 49:

/* Line 1455 of yacc.c  */
#line 486 ".\\parser.y"
    { // 语法错误，缺少左中括号
        yyerror("missing left bracket", (yylsp[(1) - (6)]).last_line, (yylsp[(1) - (6)]).last_column+1);
        (yyval)=new AST;
        (yyval)->token="type";
     }
    break;

  case 50:

/* Line 1455 of yacc.c  */
#line 491 ".\\parser.y"
    { // 语法错误，缺少OF
        yyerror("missing keyword \"OF\"", (yylsp[(4) - (6)]).last_line, (yylsp[(4) - (6)]).last_column+1, (yylsp[(6) - (6)]).first_line, (yylsp[(6) - (6)]).first_column-1);
        (yyval)=new AST;
        (yyval)->token="type";
     }
    break;

  case 51:

/* Line 1455 of yacc.c  */
#line 496 ".\\parser.y"
    {//语法错误，缺少basic_type
        yyerror("missing base type keyword", (yylsp[(5) - (6)]).last_line, (yylsp[(5) - (6)]).last_column+1);
        (yyval)=new AST;
        (yyval)->token="type";
    }
    break;

  case 52:

/* Line 1455 of yacc.c  */
#line 501 ".\\parser.y"
    {//语法错误，不完整的ARRAY
        yyerror("incomplete array type", &(yyloc));
        (yyval)=new AST
        (yyval)->token="type";
    }
    break;

  case 53:

/* Line 1455 of yacc.c  */
#line 506 ".\\parser.y"
    {//语法错误，不完整的ARRAY
        yyerror("incomplete array type", &(yyloc));
        (yyval)=new AST
        (yyval)->token="type";
    }
    break;

  case 54:

/* Line 1455 of yacc.c  */
#line 511 ".\\parser.y"
    {//语法错误，不完整的ARRAY
        yyerror("incomplete array type", &(yyloc));
        (yyval)=new AST
        (yyval)->token="type";
    }
    break;

  case 55:

/* Line 1455 of yacc.c  */
#line 519 ".\\parser.y"
    { // 正常
        (yyval)=new AST;
        (yyval)->token="basic_type";
        (yyval)->children.push_back((yyvsp[(1) - (1)]));

        // 语义分析：
        (yyval) = INT_TYPE;
    }
    break;

  case 56:

/* Line 1455 of yacc.c  */
#line 527 ".\\parser.y"
    { // 正常
        (yyval)=new AST;
        (yyval)->token="basic_type";
        (yyval)->children.push_back((yyvsp[(1) - (1)]));

        // 语义分析：
        (yyval) = REAL_TYPE;
    }
    break;

  case 57:

/* Line 1455 of yacc.c  */
#line 535 ".\\parser.y"
    { // 正常
        (yyval)=new AST;
        (yyval)->token="basic_type";
        (yyval)->children.push_back((yyvsp[(1) - (1)]));

        // 语义分析：
        (yyval) = BOOLEAN_TYPE;
    }
    break;

  case 58:

/* Line 1455 of yacc.c  */
#line 543 ".\\parser.y"
    { // 正常
        (yyval)=new AST;
        (yyval)->token="basic_type";
        (yyval)->children.push_back((yyvsp[(1) - (1)]));

        // 语义分析：
        (yyval) = CHAR_TYPE;
    }
    break;

  case 59:

/* Line 1455 of yacc.c  */
#line 554 ".\\parser.y"
    {//正常
        (yyval)=new AST;
        (yyval)->token="period";
        (yyval)->children.push_back((yyvsp[(1) - (4)]));
        (yyval)->children.push_back((yyvsp[(2) - (4)]));
        (yyval)->children.push_back((yyvsp[(3) - (4)]));
        (yyval)->children.push_back((yyvsp[(4) - (4)]));
    }
    break;

  case 60:

/* Line 1455 of yacc.c  */
#line 562 ".\\parser.y"
    {//正常
        (yyval)=new AST;
        (yyval)->token="period";
        (yyval)->children.push_back((yyvsp[(1) - (6)]));
        (yyval)->children.push_back((yyvsp[(2) - (6)]));
        (yyval)->children.push_back((yyvsp[(3) - (6)]));
        (yyval)->children.push_back((yyvsp[(4) - (6)]));
        (yyval)->children.push_back((yyvsp[(5) - (6)]));
    }
    break;

  case 61:

/* Line 1455 of yacc.c  */
#line 571 ".\\parser.y"
    {//语法错误，缺少逗号
        yyerror("missing comma", (yylsp[(1) - (6)]).last_line, (yylsp[(1) - (6)]).last_column+1);
        (yyval)=new AST;
        (yyval)->token="period";
    }
    break;

  case 62:

/* Line 1455 of yacc.c  */
#line 576 ".\\parser.y"
    {//语法错误，缺少点号
        yyerror("missing dot..", (yylsp[(3) - (5)]).last_line, (yylsp[(3) - (5)]).last_column+1);
        (yyval)=new AST;
        (yyval)->token="period";
    }
    break;

  case 63:

/* Line 1455 of yacc.c  */
#line 584 ".\\parser.y"
    {//正常
        (yyval)=new AST;
        (yyval)->token="subprogram_declarations";
    }
    break;

  case 64:

/* Line 1455 of yacc.c  */
#line 588 ".\\parser.y"
    {//正常
        (yyval)=new AST;
        (yyval)->token="subprogram_declarations";
        (yyval)->children.push_back((yyvsp[(1) - (3)]));
        (yyval)->children.push_back((yyvsp[(2) - (3)]));
        (yyval)->children.push_back((yyvsp[(3) - (3)]));
    }
    break;

  case 65:

/* Line 1455 of yacc.c  */
#line 595 ".\\parser.y"
    {//语法错误，缺少分号
        yyerror("missing a semicolon", (yylsp[(2) - (3)]).last_line, (yylsp[(2) - (3)]).last_column+1);
        (yyval)=new AST;
        (yyval)->token="subprogram_declarations";
    }
    break;

  case 66:

/* Line 1455 of yacc.c  */
#line 603 ".\\parser.y"
    {//正常
        (yyval)=new AST;
        (yyval)->token="subprogram";
        (yyval)->children.push_back((yyvsp[(1) - (3)]));
        (yyval)->children.push_back((yyvsp[(2) - (3)]));
        (yyval)->children.push_back((yyvsp[(3) - (3)]));
    }
    break;

  case 67:

/* Line 1455 of yacc.c  */
#line 610 ".\\parser.y"
    {//语法错误，缺少分号
        yyerror("missing semicolon", (yylsp[(1) - (3)]).last_line, (yylsp[(1) - (3)]).last_column+1);
        (yyval)=new AST;
        (yyval)->token="subprogram";
    }
    break;

  case 68:

/* Line 1455 of yacc.c  */
#line 618 ".\\parser.y"
    {//正常
        (yyval)=new AST;
        (yyval)->token="subprogram_head";
        (yyval)->children.push_back((yyvsp[(1) - (3)]));
        (yyval)->children.push_back((yyvsp[(2) - (3)]));
        (yyval)->children.push_back((yyvsp[(3) - (3)]));

        //语义分析：
        addSymbol((yyvsp[(2) - (3)]), PROCEDURE_TYPE, (yyvsp[(3) - (3)]).paramList);
    }
    break;

  case 69:

/* Line 1455 of yacc.c  */
#line 628 ".\\parser.y"
    {//正常
        (yyval)=new AST;
        (yyval)->token="subprogram_head";
        (yyval)->children.push_back((yyvsp[(1) - (5)]));
        (yyval)->children.push_back((yyvsp[(2) - (5)]));
        (yyval)->children.push_back((yyvsp[(3) - (5)]));
        (yyval)->children.push_back((yyvsp[(4) - (5)]));
        (yyval)->children.push_back((yyvsp[(5) - (5)]));

        //语义分析：
        addSymbol((yyvsp[(2) - (5)]), (yyvsp[(5) - (5)]), (yyvsp[(3) - (5)]).paramList);
    }
    break;

  case 70:

/* Line 1455 of yacc.c  */
#line 640 ".\\parser.y"
    {//语法错误，缺少标识符
        yyerror("missing procedure name", (yylsp[(1) - (3)]).last_line, (yylsp[(1) - (3)]).last_column+1);
        (yyval)=new AST;
        (yyval)->token="subprogram_head";
    }
    break;

  case 71:

/* Line 1455 of yacc.c  */
#line 645 ".\\parser.y"
    {//语法错误，函数名缺失
        yyerror("missing function name", (yylsp[(1) - (5)]).last_line, (yylsp[(1) - (5)]).last_column+1);
        (yyval)=new AST;
        (yyval)->token="subprogram_head";
    }
    break;

  case 72:

/* Line 1455 of yacc.c  */
#line 650 ".\\parser.y"
    {//语法错误，缺少冒号
        yyerror("missing colon", (yylsp[(3) - (5)]).last_line, (yylsp[(3) - (5)]).last_column+1);
        (yyval)=new AST
        (yyval)->token="subprogram_head";
    }
    break;

  case 73:

/* Line 1455 of yacc.c  */
#line 655 ".\\parser.y"
    {//语法错误，缺少basic_type
        yyerror("missing base type keyword", (yylsp[(4) - (5)]).last_line, (yylsp[(4) - (5)]).last_column+1);
        (yyval)=new AST
        (yyval)->token="subprogram_head";
    }
    break;

  case 74:

/* Line 1455 of yacc.c  */
#line 660 ".\\parser.y"
    {//语法错误，函数头不完整
        yyerror("incomplete function head", &(yyloc));
        (yyval)=new AST
        (yyval)->token="subprogram_head";
    }
    break;

  case 75:

/* Line 1455 of yacc.c  */
#line 669 ".\\parser.y"
    {//正常
        (yyval)=new AST;
        (yyval)->token="formal_parameter";

        // 语义分析：
        (yyval) = createParamList();
     }
    break;

  case 76:

/* Line 1455 of yacc.c  */
#line 676 ".\\parser.y"
    {//正常
        (yyval)=new AST;
        (yyval)->token="formal_parameter";
        (yyval)->children.push_back((yyvsp[(1) - (3)]));
        (yyval)->children.push_back((yyvsp[(2) - (3)]));
        (yyval)->children.push_back((yyvsp[(3) - (3)]));

        // 语义分析：
        (yyval) = (yyvsp[(2) - (3)]);
     }
    break;

  case 77:

/* Line 1455 of yacc.c  */
#line 686 ".\\parser.y"
    {//语法错误，缺少parameter_list
        yyerror("incomplete formal parameter list", &(yyloc));
        (yyval)=new AST;
        (yyval)->token="formal_parameter";
    }
    break;

  case 78:

/* Line 1455 of yacc.c  */
#line 691 ".\\parser.y"
    {//语法错误，缺少右括号
        yyerror("missing right bracket", (yylsp[(2) - (3)]).last_line, (yylsp[(2) - (3)]).last_column+1);
        (yyval)=new AST;
        (yyval)->token="formal_parameter";
    }
    break;

  case 79:

/* Line 1455 of yacc.c  */
#line 696 ".\\parser.y"
    {//语法错误，缺少parameter_list
        yyerror("incomplete formal parameter list", &(yyloc));
        (yyval)=new AST;
        (yyval)->token="formal_parameter";
    }
    break;

  case 80:

/* Line 1455 of yacc.c  */
#line 704 ".\\parser.y"
    {//正常
        (yyval)=new AST;
        (yyval)->token="parameter_list";
        (yyval)->children.push_back((yyvsp[(1) - (1)]));

        // 语义分析：
        (yyval) = createParamList(); addParam((yyval), (yyvsp[(1) - (1)]).type);
        }
    break;

  case 81:

/* Line 1455 of yacc.c  */
#line 712 ".\\parser.y"
    {//正常
        (yyval)=new AST;
        (yyval)->token="parameter_list";
        (yyval)->children.push_back((yyvsp[(1) - (3)]));
        (yyval)->children.push_back((yyvsp[(2) - (3)]));
        (yyval)->children.push_back((yyvsp[(3) - (3)]));

        // 语义分析：
        addParam((yyvsp[(1) - (3)]), (yyvsp[(3) - (3)]).type); (yyval) = (yyvsp[(1) - (3)]);
        }
    break;

  case 82:

/* Line 1455 of yacc.c  */
#line 722 ".\\parser.y"
    {//语法错误，缺少分号
        yyerror("missing semicolon", (yylsp[(1) - (3)]).last_line, (yylsp[(1) - (3)]).last_column+1);
        (yyval)=new AST;
        (yyval)->token="parameter_list";
    }
    break;

  case 83:

/* Line 1455 of yacc.c  */
#line 730 ".\\parser.y"
    {//正常
        (yyval)=new AST;
        (yyval)->token="parameter";
        (yyval)->children.push_back((yyvsp[(1) - (1)]));

        // 语义分析：
        (yyval) = (yyvsp[(1) - (1)]);
    }
    break;

  case 84:

/* Line 1455 of yacc.c  */
#line 738 ".\\parser.y"
    {//正常
        (yyval)=new AST;
        (yyval)->token="parameter";
        (yyval)->children.push_back((yyvsp[(1) - (1)]));

        // 语义分析：
        (yyval) = (yyvsp[(1) - (1)]);
    }
    break;

  case 85:

/* Line 1455 of yacc.c  */
#line 749 ".\\parser.y"
    {//正常
        (yyval)=new AST;
        (yyval)->token="var_parameter";
        (yyval)->children.push_back((yyvsp[(1) - (2)]));
        (yyval)->children.push_back((yyvsp[(2) - (2)]));

        // 语义分析：
        (yyval) = (yyvsp[(2) - (2)]); (yyval)->isVar = TRUE;
    }
    break;

  case 86:

/* Line 1455 of yacc.c  */
#line 758 ".\\parser.y"
    {//语法错误，缺少value_parameter
        yyerror("incomplete refereced parameter list", &(yyloc));
        (yyval)=new AST
        (yyval)->token="var_parameter";
    }
    break;

  case 87:

/* Line 1455 of yacc.c  */
#line 766 ".\\parser.y"
    {//正常
        (yyval)=new AST;
        (yyval)->token="value_parameter";
        (yyval)->children.push_back((yyvsp[(1) - (3)]));
        (yyval)->children.push_back((yyvsp[(2) - (3)]));
        (yyval)->children.push_back((yyvsp[(3) - (3)]));

        // 语义分析：
        // 对于每个idlist中的标识符，设置其类型
        for (int i = 0; i < (yyvsp[(1) - (3)]).count; ++i) {
            setParamType((yyvsp[(1) - (3)]).names[i], (yyvsp[(3) - (3)]));
        }
        (yyval) = (yyvsp[(3) - (3)]); // 假设这里$3是从basic_type传递来的类型
    }
    break;

  case 88:

/* Line 1455 of yacc.c  */
#line 780 ".\\parser.y"
    {//语法错误，缺少冒号
        yyerror("missing colon", (yylsp[(1) - (3)]).last_line, (yylsp[(1) - (3)]).last_column+1);
        (yyval)=new AST
        (yyval)->token="value_parameter";
    }
    break;

  case 89:

/* Line 1455 of yacc.c  */
#line 785 ".\\parser.y"
    {//语法错误，缺少basic_type
        yyerror("missing base type keyword", (yylsp[(2) - (3)]).last_line, (yylsp[(2) - (3)]).last_column+1);
        (yyval)=new AST
        (yyval)->token="value_parameter";
    }
    break;

  case 90:

/* Line 1455 of yacc.c  */
#line 790 ".\\parser.y"
    {//语法错误，缺少basic_type
        yyerror("missing base type keyword", (yylsp[(1) - (2)]).last_line, (yylsp[(1) - (2)]).last_column+1);
        (yyval)=new AST
        (yyval)->token="value_parameter";
    }
    break;

  case 91:

/* Line 1455 of yacc.c  */
#line 798 ".\\parser.y"
    {//正常
        (yyval)=new AST;
        (yyval)->token="subprogram_body";
        (yyval)->children.push_back((yyvsp[(1) - (3)]));
        (yyval)->children.push_back((yyvsp[(2) - (3)]));
        (yyval)->children.push_back((yyvsp[(3) - (3)]));
    }
    break;

  case 92:

/* Line 1455 of yacc.c  */
#line 808 ".\\parser.y"
    {//正常
        (yyval)=new AST;
        (yyval)->token="compound_statement";
        (yyval)->children.push_back((yyvsp[(1) - (3)]));
        (yyval)->children.push_back((yyvsp[(2) - (3)]));
        (yyval)->children.push_back((yyvsp[(3) - (3)]));
    }
    break;

  case 93:

/* Line 1455 of yacc.c  */
#line 818 ".\\parser.y"
    {//正常
        (yyval)=new AST;
        (yyval)->token="statement_list";
        (yyval)->children.push_back((yyvsp[(1) - (1)]));
    }
    break;

  case 94:

/* Line 1455 of yacc.c  */
#line 823 ".\\parser.y"
    {//正常
        (yyval)=new AST;
        (yyval)->token="statement_list";
        (yyval)->children.push_back((yyvsp[(1) - (3)]));
        (yyval)->children.push_back((yyvsp[(2) - (3)]));
        (yyval)->children.push_back((yyvsp[(3) - (3)]));
    }
    break;

  case 95:

/* Line 1455 of yacc.c  */
#line 830 ".\\parser.y"
    {//语法错误，缺少分号
        yyerror("missing semicolon", (yylsp[(1) - (3)]).last_line, (yylsp[(1) - (3)]).last_column+1);
        (yyval)=new AST;
        (yyval)->token="statement_list";
    }
    break;

  case 96:

/* Line 1455 of yacc.c  */
#line 838 ".\\parser.y"
    {//正常
        (yyval)=new AST;
        (yyval)->token="statement";
    }
    break;

  case 97:

/* Line 1455 of yacc.c  */
#line 842 ".\\parser.y"
    {//正常
        (yyval)=new AST;
        (yyval)->token="statement";
        (yyval)->children.push_back((yyvsp[(1) - (3)]));
        (yyval)->children.push_back((yyvsp[(2) - (3)]));
        (yyval)->children.push_back((yyvsp[(3) - (3)]));

        // 语义分析：
        /* 检查变量是否已经定义，检查类型是否匹配 */
        SymbolTableEntry* var = findSymbol((yyvsp[(1) - (3)]));
        if (!var) {
            printf("Semantic error: Undefined variable %s\n", (yyvsp[(1) - (3)]));
        } else if (var->type != (yyvsp[(3) - (3)]).type) {
            printf("Semantic error: Type mismatch in assignment to %s\n", (yyvsp[(1) - (3)]));
        }
    }
    break;

  case 98:

/* Line 1455 of yacc.c  */
#line 858 ".\\parser.y"
    {//正常
        (yyval)=new AST;
        (yyval)->token="statement";
        (yyval)->children.push_back((yyvsp[(1) - (3)]));
        (yyval)->children.push_back((yyvsp[(2) - (3)]));
        (yyval)->children.push_back((yyvsp[(3) - (3)]));

        // 语义分析：
        SymbolTableEntry* func = findSymbol((yyvsp[(1) - (3)]));
        if (!func || !isFunction(func)) {
            printf("Semantic error: Undefined function or identifier is not a function\n");
        } else if (func->paramCount != 0) {
            printf("Semantic error: Function expects parameters\n");
        }
    }
    break;

  case 99:

/* Line 1455 of yacc.c  */
#line 873 ".\\parser.y"
    {//正常
        (yyval)=new AST;
        (yyval)->token="statement";
        (yyval)->children.push_back((yyvsp[(1) - (1)]));
    }
    break;

  case 100:

/* Line 1455 of yacc.c  */
#line 878 ".\\parser.y"
    {//正常
        (yyval)=new AST;
        (yyval)->token="statement";
        (yyval)->children.push_back((yyvsp[(1) - (1)]));
    }
    break;

  case 101:

/* Line 1455 of yacc.c  */
#line 883 ".\\parser.y"
    {//正常
        (yyval)=new AST;
        (yyval)->token="statement";
        (yyval)->children.push_back((yyvsp[(1) - (5)]));
        (yyval)->children.push_back((yyvsp[(2) - (5)]));
        (yyval)->children.push_back((yyvsp[(3) - (5)]));
        (yyval)->children.push_back((yyvsp[(4) - (5)]));
    }
    break;

  case 102:

/* Line 1455 of yacc.c  */
#line 891 ".\\parser.y"
    {//语法错误，缺少THEN
        yyerror("missing keyword \"then\"", (yylsp[(1) - (5)]).last_line, (yylsp[(1) - (5)]).last_column+1);
        (yyval)=new AST;
        (yyval)->token="statement";
    }
    break;

  case 103:

/* Line 1455 of yacc.c  */
#line 896 ".\\parser.y"
    {//正常
        (yyval)=new AST;
        (yyval)->token="statement";
        (yyval)->children.push_back((yyvsp[(1) - (8)]));
        (yyval)->children.push_back((yyvsp[(2) - (8)]));
        (yyval)->children.push_back((yyvsp[(3) - (8)]));
        (yyval)->children.push_back((yyvsp[(4) - (8)]));
        (yyval)->children.push_back((yyvsp[(5) - (8)]));
        (yyval)->children.push_back((yyvsp[(6) - (8)]));
        (yyval)->children.push_back((yyvsp[(7) - (8)]));
    }
    break;

  case 104:

/* Line 1455 of yacc.c  */
#line 907 ".\\parser.y"
    {//语法错误，缺少DO
        yyerror("missing keyword \"do\"", (yylsp[(6) - (8)]).last_line, (yylsp[(6) - (8)]).last_column+1);
        (yyval)=new AST;
        (yyval)->token="statement";
    }
    break;

  case 105:

/* Line 1455 of yacc.c  */
#line 912 ".\\parser.y"
    {//语法错误，缺少赋值号
        yyerror("missing assignment operator \":=\"", (yylsp[(2) - (8)]).last_line, (yylsp[(2) - (8)]).last_column+1);
        (yyval)=new AST;
        (yyval)->token="statement";
    }
    break;

  case 106:

/* Line 1455 of yacc.c  */
#line 917 ".\\parser.y"
    {//语法错误，缺少TO
        yyerror("missing keyword \"to\"", (yylsp[(4) - (8)]).last_line, (yylsp[(4) - (8)]).last_column+1);
        (yyval)=new AST;
        (yyval)->token="statement";
    }
    break;

  case 107:

/* Line 1455 of yacc.c  */
#line 922 ".\\parser.y"
    {//正常
        (yyval)=new AST;
        (yyval)->token="statement";
        (yyval)->children.push_back((yyvsp[(1) - (4)]));
        (yyval)->children.push_back((yyvsp[(2) - (4)]));
        (yyval)->children.push_back((yyvsp[(3) - (4)]));
        (yyval)->children.push_back((yyvsp[(4) - (4)]));
    }
    break;

  case 108:

/* Line 1455 of yacc.c  */
#line 930 ".\\parser.y"
    {//语法错误，缺少左括号
        yyerror("missing left bracket", (yylsp[(1) - (4)]).last_line, (yylsp[(1) - (4)]).last_column+1);
        (yyval)=new AST;
        (yyval)->token="statement";
    }
    break;

  case 109:

/* Line 1455 of yacc.c  */
#line 935 ".\\parser.y"
    {//语法错误，参数列表错误
        yyerror("fatal error in read statement",&(yyloc));
        (yyval)=new AST;
        (yyval)->token="statement";
    }
    break;

  case 110:

/* Line 1455 of yacc.c  */
#line 940 ".\\parser.y"
    {//语法错误，缺少右括号
        yyerror("missing right bracket", (yylsp[(3) - (4)]).last_line, (yylsp[(3) - (4)]).last_column+1);
        (yyval)=new AST;
        (yyval)->token="statement";
    }
    break;

  case 111:

/* Line 1455 of yacc.c  */
#line 945 ".\\parser.y"
    {//正常
        (yyval)=new AST;
        (yyval)->token="statement";
        (yyval)->children.push_back((yyvsp[(1) - (4)]));
        (yyval)->children.push_back((yyvsp[(2) - (4)]));
        (yyval)->children.push_back((yyvsp[(3) - (4)]));
        (yyval)->children.push_back((yyvsp[(4) - (4)]));
    }
    break;

  case 112:

/* Line 1455 of yacc.c  */
#line 953 ".\\parser.y"
    {//语法错误，缺少左括号
        yyerror("missing left bracket", (yylsp[(1) - (4)]).last_line, (yylsp[(1) - (4)]).last_column+1);
        (yyval)=new AST;
        (yyval)->token="statement";
    }
    break;

  case 113:

/* Line 1455 of yacc.c  */
#line 958 ".\\parser.y"
    {//语法错误，参数列表错误
        yyerror("fatal error in write statement",&(yyloc));
        (yyval)=new AST;
        (yyval)->token="statement";
    }
    break;

  case 114:

/* Line 1455 of yacc.c  */
#line 963 ".\\parser.y"
    {//语法错误，缺少右括号
        yyerror("missing right bracket", (yylsp[(3) - (4)]).last_line, (yylsp[(3) - (4)]).last_column+1);
        (yyval)=new AST;
        (yyval)->token="statement";
    }
    break;

  case 115:

/* Line 1455 of yacc.c  */
#line 971 ".\\parser.y"
    { //正常
        (yyval)=new AST;
        (yyval)->token="else_part";
        (yyval)->children.push_back((yyvsp[(1) - (2)]));
        (yyval)->children.push_back((yyvsp[(2) - (2)]));
    }
    break;

  case 116:

/* Line 1455 of yacc.c  */
#line 977 ".\\parser.y"
    { //正常
        (yyval)=new AST;
        (yyval)->token="else_part";
    }
    break;

  case 117:

/* Line 1455 of yacc.c  */
#line 983 ".\\parser.y"
    {//正常
        (yyval)=new AST;
        (yyval)->token="variable_list";
        (yyval)->children.push_back((yyvsp[(1) - (1)]));
    }
    break;

  case 118:

/* Line 1455 of yacc.c  */
#line 988 ".\\parser.y"
    {//正常
        (yyval)=new AST;
        (yyval)->token="variable_list";
        (yyval)->children.push_back((yyvsp[(1) - (3)]));
        (yyval)->children.push_back((yyvsp[(2) - (3)]));
        (yyval)->children.push_back((yyvsp[(3) - (3)]));
    }
    break;

  case 119:

/* Line 1455 of yacc.c  */
#line 995 ".\\parser.y"
    {//语法错误，缺少逗号
        yyerror("missing comma", (yylsp[(1) - (3)]).last_line, (yylsp[(1) - (3)]).last_column+1);
        (yyval)=new AST;
        (yyval)->token="variable_list";
    }
    break;

  case 120:

/* Line 1455 of yacc.c  */
#line 1003 ".\\parser.y"
    {//正常
        (yyval)=new AST;
        (yyval)->token="variable";
        (yyval)->children.push_back((yyvsp[(1) - (2)]));
        (yyval)->children.push_back((yyvsp[(2) - (2)]));

        // 语义分析：
        SymbolTableEntry* var = findSymbol((yyvsp[(1) - (2)]));
        if (!var) {
            printf("Semantic error: Undefined variable %s\n", (yyvsp[(1) - (2)]));
        }
    }
    break;

  case 121:

/* Line 1455 of yacc.c  */
#line 1018 ".\\parser.y"
    {//正常
        (yyval)=new AST;
        (yyval)->token="id_varpart";
    }
    break;

  case 122:

/* Line 1455 of yacc.c  */
#line 1022 ".\\parser.y"
    {//正常
        (yyval)=new AST;
        (yyval)->token="id_varpart";
        (yyval)->children.push_back((yyvsp[(1) - (3)]));
        (yyval)->children.push_back((yyvsp[(2) - (3)]));
        (yyval)->children.push_back((yyvsp[(3) - (3)]));
    }
    break;

  case 123:

/* Line 1455 of yacc.c  */
#line 1029 ".\\parser.y"
    {//语法错误，不完整的数组下标
        yyerror("incomplete array index", &(yyloc));
        (yyval)=new AST;
        (yyval)->token="id_varpart";
    }
    break;

  case 124:

/* Line 1455 of yacc.c  */
#line 1034 ".\\parser.y"
    {//语法错误，缺少右中括号
        yyerror("missing right bracket", (yylsp[(2) - (3)]).last_line, (yylsp[(2) - (3)]).last_column+1);
        (yyval)=new AST;
        (yyval)->token="id_varpart";
    }
    break;

  case 125:

/* Line 1455 of yacc.c  */
#line 1042 ".\\parser.y"
    {//正常
        (yyval)=new AST;
        (yyval)->token="procedure_call";
        (yyval)->children.push_back((yyvsp[(1) - (1)]));

        // 语义分析：
        SymbolTableEntry* func = findSymbol((yyvsp[(1) - (1)]));
        if (!func || !isFunction(func)) {
            yyerror("Undefined function or identifier is not a function");
        } else if (func->paramCount != 0) {
            yyerror("Function expects parameters");
        }
      }
    break;

  case 126:

/* Line 1455 of yacc.c  */
#line 1055 ".\\parser.y"
    {//正常
        (yyval)=new AST;
        (yyval)->token="procedure_call";
        (yyval)->children.push_back((yyvsp[(1) - (4)]));
        (yyval)->children.push_back((yyvsp[(2) - (4)]));
        (yyval)->children.push_back((yyvsp[(3) - (4)]));
        (yyval)->children.push_back((yyvsp[(4) - (4)]));

        // 语义分析：
        SymbolTableEntry* func = findSymbol((yyvsp[(1) - (4)]));
        if (!func || !isFunction(func)) {
            yyerror("Undefined function or identifier is not a function");
        } else {
            checkFunctionParameters(func, (yyvsp[(3) - (4)]));
        }
      }
    break;

  case 127:

/* Line 1455 of yacc.c  */
#line 1071 ".\\parser.y"
    {//语法错误，缺少右括号
        yyerror("missing right bracket", (yylsp[(3) - (4)]).last_line, (yylsp[(3) - (4)]).last_column+1);
        (yyval)=new AST;
        (yyval)->token="procedure_call";
    }
    break;

  case 128:

/* Line 1455 of yacc.c  */
#line 1080 ".\\parser.y"
    {//正常
        (yyval)=new AST;
        (yyval)->token="expression_list";
        (yyval)->children.push_back((yyvsp[(1) - (1)]));

        // 语义分析：
        (yyval) = createParamList();
        addParam((yyval), (yyvsp[(1) - (1)]).type);
    }
    break;

  case 129:

/* Line 1455 of yacc.c  */
#line 1089 ".\\parser.y"
    {//正常
        (yyval)=new AST;
        (yyval)->token="expression_list";
        (yyval)->children.push_back((yyvsp[(1) - (3)]));
        (yyval)->children.push_back((yyvsp[(2) - (3)]));
        (yyval)->children.push_back((yyvsp[(3) - (3)]));

        // 语义分析：
        addParam((yyvsp[(1) - (3)]), (yyvsp[(3) - (3)]).type);
        (yyval) = (yyvsp[(1) - (3)]);
    }
    break;

  case 130:

/* Line 1455 of yacc.c  */
#line 1100 ".\\parser.y"
    {//语法错误，缺少逗号
        yyerror("missing comma", (yylsp[(1) - (3)]).last_line, (yylsp[(1) - (3)]).last_column+1);
        (yyval)=new AST;
        (yyval)->token="expression_list";
    }
    break;

  case 131:

/* Line 1455 of yacc.c  */
#line 1108 ".\\parser.y"
    {//正常
        (yyval)=new AST;
        (yyval)->token="expression";
        (yyval)->children.push_back((yyvsp[(1) - (1)]));
    }
    break;

  case 132:

/* Line 1455 of yacc.c  */
#line 1113 ".\\parser.y"
    {//正常
        (yyval)=new AST;
        (yyval)->token="expression";
        (yyval)->children.push_back((yyvsp[(1) - (3)]));
        (yyval)->children.push_back((yyvsp[(2) - (3)]));
        (yyval)->children.push_back((yyvsp[(3) - (3)]));

        // 语义分析：
        // 检查两个simple_expression的类型是否兼容
        if (!areTypesCompatible((yyvsp[(1) - (3)]).type, (yyvsp[(3) - (3)]).type))
            yyerror("Type mismatch in relational operation");
      }
    break;

  case 133:

/* Line 1455 of yacc.c  */
#line 1128 ".\\parser.y"
    { (yyval)=new AST
        (yyval)->token="relop";
        (yyval)->children.push_back((yyvsp[(1) - (1)]));
    }
    break;

  case 134:

/* Line 1455 of yacc.c  */
#line 1132 ".\\parser.y"
    { (yyval)=new AST
        (yyval)->token="relop";
        (yyval)->children.push_back((yyvsp[(1) - (1)]));
    }
    break;

  case 135:

/* Line 1455 of yacc.c  */
#line 1136 ".\\parser.y"
    { (yyval)=new AST
        (yyval)->token="relop";
        (yyval)->children.push_back((yyvsp[(1) - (1)]));
    }
    break;

  case 136:

/* Line 1455 of yacc.c  */
#line 1140 ".\\parser.y"
    { (yyval)=new AST
        (yyval)->token="relop";
        (yyval)->children.push_back((yyvsp[(1) - (1)]));
    }
    break;

  case 137:

/* Line 1455 of yacc.c  */
#line 1144 ".\\parser.y"
    { (yyval)=new AST
        (yyval)->token="relop";
        (yyval)->children.push_back((yyvsp[(1) - (1)]));
    }
    break;

  case 138:

/* Line 1455 of yacc.c  */
#line 1148 ".\\parser.y"
    { (yyval)=new AST
        (yyval)->token="relop";
        (yyval)->children.push_back((yyvsp[(1) - (1)]));
    }
    break;

  case 139:

/* Line 1455 of yacc.c  */
#line 1155 ".\\parser.y"
    {//正常
        (yyval)=new AST;
        (yyval)->token="simple_expression";
        (yyval)->children.push_back((yyvsp[(1) - (1)]));
    }
    break;

  case 140:

/* Line 1455 of yacc.c  */
#line 1160 ".\\parser.y"
    {//正常
        (yyval)=new AST;
        (yyval)->token="simple_expression";
        (yyval)->children.push_back((yyvsp[(1) - (3)]));
        (yyval)->children.push_back((yyvsp[(2) - (3)]));
        (yyval)->children.push_back((yyvsp[(3) - (3)]));

        // 语义分析：
        // 检查simple_expression和term的类型是否兼容
        if (!areTypesCompatible((yyvsp[(1) - (3)]).type, (yyvsp[(3) - (3)]).type)) {
            yyerror("Type mismatch in addition/subtraction operation");
        }
      }
    break;

  case 141:

/* Line 1455 of yacc.c  */
#line 1173 ".\\parser.y"
    {//语法错误，缺少操作数
        yyerror("missing operand", (yylsp[(2) - (4)]).last_line, (yylsp[(2) - (4)]).last_column+1);
        (yyval)=new AST;
        (yyval)->token="simple_expression";
    }
    break;

  case 142:

/* Line 1455 of yacc.c  */
#line 1181 ".\\parser.y"
    { (yyval)=new AST
        (yyval)->token="addop";
        (yyval)->children.push_back((yyvsp[(1) - (1)]));
    }
    break;

  case 143:

/* Line 1455 of yacc.c  */
#line 1185 ".\\parser.y"
    { (yyval)=new AST
        (yyval)->token="addop";
        (yyval)->children.push_back((yyvsp[(1) - (1)]));
    }
    break;

  case 144:

/* Line 1455 of yacc.c  */
#line 1189 ".\\parser.y"
    { (yyval)=new AST
        (yyval)->token="addop";
        (yyval)->children.push_back((yyvsp[(1) - (1)]));
    }
    break;

  case 145:

/* Line 1455 of yacc.c  */
#line 1196 ".\\parser.y"
    {//正常
        (yyval)=new AST;
        (yyval)->token="term";
        (yyval)->children.push_back((yyvsp[(1) - (1)]));
    }
    break;

  case 146:

/* Line 1455 of yacc.c  */
#line 1201 ".\\parser.y"
    {//正常
        (yyval)=new AST;
        (yyval)->token="term";
        (yyval)->children.push_back((yyvsp[(1) - (3)]));
        (yyval)->children.push_back((yyvsp[(2) - (3)]));
        (yyval)->children.push_back((yyvsp[(3) - (3)]));

        // 语义分析：
        // 检查term和factor的类型是否兼容
        if (!areTypesCompatible((yyvsp[(1) - (3)]).type, (yyvsp[(3) - (3)]).type)) {
            yyerror("Type mismatch in multiplication/division/modulus/and operation");
        }
      }
    break;

  case 147:

/* Line 1455 of yacc.c  */
#line 1214 ".\\parser.y"
    {//语法错误，缺少mulop
        yyerror("missing multiplication/division/modulus/and operator", (yylsp[(1) - (4)]).last_line, (yylsp[(1) - (4)]).last_column+1);
        (yyval)=new AST;
        (yyval)->token="term";
    }
    break;

  case 148:

/* Line 1455 of yacc.c  */
#line 1222 ".\\parser.y"
    { (yyval)=new AST
        (yyval)->token="mulop";
        (yyval)->children.push_back((yyvsp[(1) - (1)]));
    }
    break;

  case 149:

/* Line 1455 of yacc.c  */
#line 1226 ".\\parser.y"
    { (yyval)=new AST
        (yyval)->token="mulop";
        (yyval)->children.push_back((yyvsp[(1) - (1)]));
    }
    break;

  case 150:

/* Line 1455 of yacc.c  */
#line 1230 ".\\parser.y"
    { (yyval)=new AST
        (yyval)->token="mulop";
        (yyval)->children.push_back((yyvsp[(1) - (1)]));
    }
    break;

  case 151:

/* Line 1455 of yacc.c  */
#line 1234 ".\\parser.y"
    { (yyval)=new AST
        (yyval)->token="mulop";
        (yyval)->children.push_back((yyvsp[(1) - (1)]));
    }
    break;

  case 152:

/* Line 1455 of yacc.c  */
#line 1241 ".\\parser.y"
    {//正常
        (yyval)=new AST;
        (yyval)->token="factor";
        (yyval)->children.push_back((yyvsp[(1) - (1)]));

        // 语义分析：
        (yyval) = (YYSTYPE) {.type = INT_TYPE, .value.ival = (yyvsp[(1) - (1)])};
      }
    break;

  case 153:

/* Line 1455 of yacc.c  */
#line 1249 ".\\parser.y"
    {//正常
        (yyval)=new AST;
        (yyval)->token="factor";
        (yyval)->children.push_back((yyvsp[(1) - (1)]));

        // 语义分析：
        SymbolTableEntry* var = findSymbol((yyvsp[(1) - (1)]));
        if (!var) {
            yyerror("Undefined variable");
        }
      }
    break;

  case 154:

/* Line 1455 of yacc.c  */
#line 1260 ".\\parser.y"
    {//正常
        (yyval)=new AST;
        (yyval)->token="factor";
        (yyval)->children.push_back((yyvsp[(1) - (3)]));
        (yyval)->children.push_back((yyvsp[(2) - (3)]));
        (yyval)->children.push_back((yyvsp[(3) - (3)]));

        // 语义分析：
        (yyval) = (yyvsp[(2) - (3)]);
      }
    break;

  case 155:

/* Line 1455 of yacc.c  */
#line 1270 ".\\parser.y"
    {//语法错误，缺少右括号
        yyerror("missing right bracket", (yylsp[(2) - (3)]).last_line, (yylsp[(2) - (3)]).last_column+1);
        (yyval)=new AST;
        (yyval)->token="factor";
    }
    break;

  case 156:

/* Line 1455 of yacc.c  */
#line 1275 ".\\parser.y"
    {//正常
        (yyval)=new AST;
        (yyval)->token="factor";
        (yyval)->children.push_back((yyvsp[(1) - (4)]));
        (yyval)->children.push_back((yyvsp[(2) - (4)]));
        (yyval)->children.push_back((yyvsp[(3) - (4)]));
        (yyval)->children.push_back((yyvsp[(4) - (4)]));

        // 语义分析：
        SymbolTableEntry* func = findSymbol((yyvsp[(1) - (4)]));
        if (!func || !isFunction(func)) {
            yyerror("Undefined function or identifier is not a function");
        } else {
            checkFunctionParameters(func, (yyvsp[(3) - (4)]));
        }
      }
    break;

  case 157:

/* Line 1455 of yacc.c  */
#line 1291 ".\\parser.y"
    {//语法错误，参数列表错误
        yyerror("fatal error in function call",&(yyloc));
        (yyval)=new AST;
        (yyval)->token
    }
    break;

  case 158:

/* Line 1455 of yacc.c  */
#line 1296 ".\\parser.y"
    {//正常
        (yyval)=new AST;
        (yyval)->token="factor";
        (yyval)->children.push_back((yyvsp[(1) - (2)]));
        (yyval)->children.push_back((yyvsp[(2) - (2)]));

        // 语义分析：
        if ((yyvsp[(2) - (2)]).type != BOOLEAN_TYPE) {
            yyerror("Type mismatch in NOT operation");
        }
      }
    break;

  case 159:

/* Line 1455 of yacc.c  */
#line 1307 ".\\parser.y"
    {//正常
        (yyval)=new AST;
        (yyval)->token="factor";
        (yyval)->children.push_back((yyvsp[(1) - (2)]));
        (yyval)->children.push_back((yyvsp[(2) - (2)]));

        // 语义分析：
        if ((yyvsp[(2) - (2)]).type != INT_TYPE && (yyvsp[(2) - (2)]).type != REAL_TYPE) {
            yyerror("Type mismatch in unary minus operation");
        }
      }
    break;



/* Line 1455 of yacc.c  */
#line 3903 "y.tab.c"
      default: break;
    }
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;
  *++yylsp = yyloc;

  /* Now `shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*------------------------------------.
| yyerrlab -- here on detecting error |
`------------------------------------*/
yyerrlab:
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
      {
	YYSIZE_T yysize = yysyntax_error (0, yystate, yychar);
	if (yymsg_alloc < yysize && yymsg_alloc < YYSTACK_ALLOC_MAXIMUM)
	  {
	    YYSIZE_T yyalloc = 2 * yysize;
	    if (! (yysize <= yyalloc && yyalloc <= YYSTACK_ALLOC_MAXIMUM))
	      yyalloc = YYSTACK_ALLOC_MAXIMUM;
	    if (yymsg != yymsgbuf)
	      YYSTACK_FREE (yymsg);
	    yymsg = (char *) YYSTACK_ALLOC (yyalloc);
	    if (yymsg)
	      yymsg_alloc = yyalloc;
	    else
	      {
		yymsg = yymsgbuf;
		yymsg_alloc = sizeof yymsgbuf;
	      }
	  }

	if (0 < yysize && yysize <= yymsg_alloc)
	  {
	    (void) yysyntax_error (yymsg, yystate, yychar);
	    yyerror (yymsg);
	  }
	else
	  {
	    yyerror (YY_("syntax error"));
	    if (yysize != 0)
	      goto yyexhaustedlab;
	  }
      }
#endif
    }

  yyerror_range[0] = yylloc;

  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
	 error, discard it.  */

      if (yychar <= YYEOF)
	{
	  /* Return failure if at end of input.  */
	  if (yychar == YYEOF)
	    YYABORT;
	}
      else
	{
	  yydestruct ("Error: discarding",
		      yytoken, &yylval, &yylloc);
	  yychar = YYEMPTY;
	}
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:

  /* Pacify compilers like GCC when the user code never invokes
     YYERROR and the label yyerrorlab therefore never appears in user
     code.  */
  if (/*CONSTCOND*/ 0)
     goto yyerrorlab;

  yyerror_range[0] = yylsp[1-yylen];
  /* Do not reclaim the symbols of the rule which action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;	/* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (yyn != YYPACT_NINF)
	{
	  yyn += YYTERROR;
	  if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
	    {
	      yyn = yytable[yyn];
	      if (0 < yyn)
		break;
	    }
	}

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
	YYABORT;

      yyerror_range[0] = *yylsp;
      yydestruct ("Error: popping",
		  yystos[yystate], yyvsp, yylsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  *++yyvsp = yylval;

  yyerror_range[1] = yylloc;
  /* Using YYLLOC is tempting, but would change the location of
     the lookahead.  YYLOC is available though.  */
  YYLLOC_DEFAULT (yyloc, (yyerror_range - 1), 2);
  *++yylsp = yyloc;

  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;

/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;

#if !defined(yyoverflow) || YYERROR_VERBOSE
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEMPTY)
     yydestruct ("Cleanup: discarding lookahead",
		 yytoken, &yylval, &yylloc);
  /* Do not reclaim the symbols of the rule which action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
		  yystos[*yyssp], yyvsp, yylsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  /* Make sure YYID is used.  */
  return YYID (yyresult);
}



/* Line 1675 of yacc.c  */
#line 1320 ".\\parser.y"


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
