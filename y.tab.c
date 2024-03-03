
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
#define YYLSP_NEEDED 0



/* Copy the first part of user declarations.  */

/* Line 189 of yacc.c  */
#line 1 ".\\parser.y"

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



/* Line 189 of yacc.c  */
#line 162 "y.tab.c"

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

/* Line 214 of yacc.c  */
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



/* Line 214 of yacc.c  */
#line 325 "y.tab.c"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif


/* Copy the second part of user declarations.  */


/* Line 264 of yacc.c  */
#line 337 "y.tab.c"

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
	 || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

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
#define YYFINAL  5
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   169

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  55
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  37
/* YYNRULES -- Number of rules.  */
#define YYNRULES  88
/* YYNRULES -- Number of states.  */
#define YYNSTATES  178

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   309

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
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint16 yyprhs[] =
{
       0,     0,     3,     8,    14,    17,    22,    24,    28,    29,
      33,    37,    43,    45,    48,    51,    53,    54,    58,    62,
      68,    70,    77,    79,    81,    83,    85,    90,    97,    98,
     102,   106,   110,   116,   117,   121,   123,   127,   129,   131,
     134,   138,   142,   146,   148,   152,   153,   157,   161,   163,
     165,   170,   177,   186,   191,   196,   198,   202,   205,   206,
     210,   212,   217,   219,   223,   225,   229,   231,   233,   235,
     237,   239,   241,   243,   247,   249,   251,   253,   255,   259,
     261,   263,   265,   267,   269,   271,   275,   280,   283
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int8 yyrhs[] =
{
      56,     0,    -1,    57,    38,    58,    48,    -1,     3,    51,
      42,    59,    43,    -1,     3,    51,    -1,    60,    63,    68,
      77,    -1,    51,    -1,    59,    39,    51,    -1,    -1,     4,
      61,    38,    -1,    51,    33,    62,    -1,    61,    38,    51,
      33,    62,    -1,    53,    -1,    24,    53,    -1,    23,    53,
      -1,    52,    -1,    -1,     5,    64,    38,    -1,    59,    40,
      65,    -1,    64,    38,    59,    40,    65,    -1,    66,    -1,
      14,    42,    67,    43,    22,    66,    -1,    10,    -1,    11,
      -1,    12,    -1,    13,    -1,    53,    48,    48,    53,    -1,
      67,    39,    53,    48,    48,    53,    -1,    -1,    68,    69,
      38,    -1,    70,    38,    76,    -1,     6,    51,    71,    -1,
       7,    51,    71,    40,    66,    -1,    -1,    46,    72,    47,
      -1,    73,    -1,    72,    38,    73,    -1,    74,    -1,    75,
      -1,     5,    75,    -1,    59,    40,    66,    -1,    60,    63,
      77,    -1,     8,    78,     9,    -1,    79,    -1,    78,    38,
      79,    -1,    -1,    81,    31,    85,    -1,     7,    31,    85,
      -1,    83,    -1,    77,    -1,    15,    85,    16,    79,    -1,
      15,    85,    16,    79,    50,    79,    -1,    17,    51,    31,
      85,    18,    85,    19,    79,    -1,    20,    46,    80,    47,
      -1,    21,    46,    84,    47,    -1,    81,    -1,    80,    39,
      81,    -1,    51,    82,    -1,    -1,    42,    85,    43,    -1,
      51,    -1,    51,    46,    84,    47,    -1,    85,    -1,    84,
      39,    85,    -1,    87,    -1,    87,    86,    87,    -1,    33,
      -1,    32,    -1,    34,    -1,    35,    -1,    36,    -1,    37,
      -1,    89,    -1,    87,    88,    89,    -1,    23,    -1,    24,
      -1,    25,    -1,    91,    -1,    89,    90,    91,    -1,    26,
      -1,    27,    -1,    28,    -1,    29,    -1,    53,    -1,    81,
      -1,    46,    85,    47,    -1,    51,    46,    84,    47,    -1,
      30,    91,    -1,    24,    91,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   128,   128,   132,   133,   137,   141,   144,   152,   154,
     158,   167,   178,   181,   184,   187,   193,   195,   199,   209,
     222,   223,   227,   228,   229,   230,   234,   235,   238,   240,
     244,   248,   251,   258,   259,   263,   264,   268,   269,   273,
     277,   287,   291,   295,   296,   299,   301,   310,   311,   312,
     313,   314,   315,   316,   317,   321,   322,   326,   329,   331,
     335,   343,   355,   359,   366,   367,   376,   377,   378,   379,
     380,   381,   385,   386,   395,   396,   397,   401,   402,   406,
     407,   408,   409,   413,   414,   420,   423,   431,   436
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
  "DOT", "LOWER_THAN_ELSE", "ELSE", "IDENTIFIER", "STRING", "NUMBER",
  "UMINUS", "$accept", "program", "program_head", "program_body", "idlist",
  "const_declarations", "const_declaration", "const_value",
  "var_declarations", "var_declaration", "type", "basic_type", "period",
  "subprogram_declarations", "subprogram", "subprogram_head",
  "formal_parameter", "parameter_list", "parameter", "var_parameter",
  "value_parameter", "subprogram_body", "compound_statement",
  "statement_list", "statement", "variable_list", "variable", "id_varpart",
  "procedure_call", "expression_list", "expression", "relop",
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
     305,   306,   307,   308,   309
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    55,    56,    57,    57,    58,    59,    59,    60,    60,
      61,    61,    62,    62,    62,    62,    63,    63,    64,    64,
      65,    65,    66,    66,    66,    66,    67,    67,    68,    68,
      69,    70,    70,    71,    71,    72,    72,    73,    73,    74,
      75,    76,    77,    78,    78,    79,    79,    79,    79,    79,
      79,    79,    79,    79,    79,    80,    80,    81,    82,    82,
      83,    83,    84,    84,    85,    85,    86,    86,    86,    86,
      86,    86,    87,    87,    88,    88,    88,    89,    89,    90,
      90,    90,    90,    91,    91,    91,    91,    91,    91
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     4,     5,     2,     4,     1,     3,     0,     3,
       3,     5,     1,     2,     2,     1,     0,     3,     3,     5,
       1,     6,     1,     1,     1,     1,     4,     6,     0,     3,
       3,     3,     5,     0,     3,     1,     3,     1,     1,     2,
       3,     3,     3,     1,     3,     0,     3,     3,     1,     1,
       4,     6,     8,     4,     4,     1,     3,     2,     0,     3,
       1,     4,     1,     3,     1,     3,     1,     1,     1,     1,
       1,     1,     1,     3,     1,     1,     1,     1,     3,     1,
       1,     1,     1,     1,     1,     3,     4,     2,     2
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     0,     0,     0,     4,     1,     8,     0,     0,     0,
      16,     6,     0,     0,     0,     2,     0,    28,     0,     3,
       0,     9,     0,     0,     0,     7,     0,     0,    15,    12,
      10,     0,     0,    17,     0,     0,    45,     0,     0,     5,
      14,    13,     0,    22,    23,    24,    25,     0,    18,    20,
       0,    33,    33,     0,     0,     0,     0,     0,    60,    49,
       0,    43,     0,    48,    29,     8,    11,     0,     0,     0,
      31,     0,     0,     0,     0,     0,    58,    83,    84,     0,
      64,    72,    77,     0,     0,     0,     0,     0,    57,    42,
      45,     0,    16,    30,     0,     0,    19,     0,     0,     0,
      35,    37,    38,     0,    47,    88,    87,     0,     0,    45,
      74,    75,    76,    67,    66,    68,    69,    70,    71,     0,
       0,    79,    80,    81,    82,     0,     0,    58,     0,    55,
       0,    62,     0,     0,    44,    46,     0,     0,     0,     0,
      39,     0,     0,    34,    32,    85,     0,    50,    65,    73,
      78,     0,     0,    53,     0,    54,    59,    61,    41,     0,
       0,     0,    40,    36,    86,    45,     0,    56,    63,    26,
       0,    21,    51,     0,     0,    45,    27,    52
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     2,     3,     9,    98,    10,    14,    30,    17,    23,
      48,    49,    95,    24,    37,    38,    70,    99,   100,   101,
     102,    93,    59,    60,    61,   128,    78,    88,    63,   130,
     131,   119,    80,   120,    81,   125,    82
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -100
static const yytype_int16 yypact[] =
{
      30,   -35,    49,     9,    21,  -100,    65,    15,    56,    60,
     104,  -100,     7,    77,    73,  -100,    15,  -100,    61,  -100,
     -15,    67,   -26,    81,    69,  -100,    70,    71,  -100,  -100,
    -100,    82,    79,    15,    74,    75,     4,    83,    84,  -100,
    -100,  -100,   -15,  -100,  -100,  -100,  -100,    78,  -100,  -100,
      64,    85,    85,    86,     5,    76,    87,    89,    -1,  -100,
       6,  -100,    97,  -100,  -100,    65,  -100,    90,    79,     2,
    -100,    92,     5,     5,     5,     5,    19,  -100,  -100,   114,
      47,    68,  -100,   103,    91,     5,     5,     5,  -100,  -100,
       4,     5,   104,  -100,    93,    25,  -100,    15,    66,   -20,
    -100,  -100,  -100,    88,  -100,  -100,  -100,    98,     5,     4,
    -100,  -100,  -100,  -100,  -100,  -100,  -100,  -100,  -100,     5,
       5,  -100,  -100,  -100,  -100,     5,     5,    94,   -11,  -100,
      -7,  -100,    95,    13,  -100,  -100,   129,    96,    99,   118,
    -100,    88,     2,  -100,  -100,  -100,    20,   100,    62,    68,
    -100,   128,    91,  -100,     5,  -100,  -100,  -100,  -100,   101,
     105,    88,  -100,  -100,  -100,     4,     5,  -100,  -100,  -100,
     107,  -100,  -100,   130,   106,     4,  -100,  -100
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
    -100,  -100,  -100,  -100,    10,   102,  -100,   109,    55,  -100,
      80,   -99,  -100,  -100,  -100,  -100,   108,  -100,    14,  -100,
      72,  -100,   -23,  -100,   -87,  -100,   -36,  -100,  -100,   -77,
     -52,  -100,    38,  -100,    41,  -100,   -68
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -59
static const yytype_int16 yytable[] =
{
      62,    39,    79,   134,   144,   105,   106,    97,    26,    27,
     133,    53,    36,    18,    32,    89,     4,    12,   142,    54,
     104,    55,   147,   107,    56,    57,    22,   143,   152,    73,
     -58,   146,   154,     1,   132,    74,   153,    28,    29,   135,
     155,    86,   162,    50,    90,    87,    18,     6,   129,     5,
      19,    75,   154,    11,    62,    58,    76,   150,    77,   154,
     157,    86,   171,     7,   138,   108,    11,   164,   139,     8,
     110,   111,   112,    62,   151,    34,    35,    36,   172,   113,
     114,   115,   116,   117,   118,   110,   111,   112,   177,    43,
      44,    45,    46,    47,   121,   122,   123,   124,    43,    44,
      45,    46,   168,    18,    68,    18,   141,    13,    15,    16,
      20,    21,    25,   158,   173,    42,   167,    72,    31,    33,
      67,    64,    65,    40,    41,    51,    52,    83,    91,    62,
     109,    69,   103,    84,   126,    85,    86,    36,   156,    62,
     161,   137,   127,    94,   159,   145,   166,   136,    96,   175,
     165,    66,   160,   170,   169,   174,   163,   148,     0,   176,
      71,   149,     0,     0,     0,     0,     0,    92,     0,   140
};

static const yytype_int16 yycheck[] =
{
      36,    24,    54,    90,   103,    73,    74,     5,    23,    24,
      87,     7,     8,    39,    40,     9,    51,     7,    38,    15,
      72,    17,   109,    75,    20,    21,    16,    47,    39,    24,
      31,   108,    39,     3,    86,    30,    47,    52,    53,    91,
      47,    42,   141,    33,    38,    46,    39,    38,    84,     0,
      43,    46,    39,    51,    90,    51,    51,   125,    53,    39,
      47,    42,   161,    42,    39,    46,    51,    47,    43,     4,
      23,    24,    25,   109,   126,     6,     7,     8,   165,    32,
      33,    34,    35,    36,    37,    23,    24,    25,   175,    10,
      11,    12,    13,    14,    26,    27,    28,    29,    10,    11,
      12,    13,   154,    39,    40,    39,    40,    51,    48,     5,
      33,    38,    51,   136,   166,    33,   152,    31,    51,    38,
      42,    38,    38,    53,    53,    51,    51,    51,    31,   165,
      16,    46,    40,    46,    31,    46,    42,     8,    43,   175,
      22,    48,    51,    53,    48,    47,    18,    92,    68,    19,
      50,    42,    53,    48,    53,    48,   142,   119,    -1,    53,
      52,   120,    -1,    -1,    -1,    -1,    -1,    65,    -1,    97
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     3,    56,    57,    51,     0,    38,    42,     4,    58,
      60,    51,    59,    51,    61,    48,     5,    63,    39,    43,
      33,    38,    59,    64,    68,    51,    23,    24,    52,    53,
      62,    51,    40,    38,     6,     7,     8,    69,    70,    77,
      53,    53,    33,    10,    11,    12,    13,    14,    65,    66,
      59,    51,    51,     7,    15,    17,    20,    21,    51,    77,
      78,    79,    81,    83,    38,    38,    62,    42,    40,    46,
      71,    71,    31,    24,    30,    46,    51,    53,    81,    85,
      87,    89,    91,    51,    46,    46,    42,    46,    82,     9,
      38,    31,    60,    76,    53,    67,    65,     5,    59,    72,
      73,    74,    75,    40,    85,    91,    91,    85,    46,    16,
      23,    24,    25,    32,    33,    34,    35,    36,    37,    86,
      88,    26,    27,    28,    29,    90,    31,    51,    80,    81,
      84,    85,    85,    84,    79,    85,    63,    48,    39,    43,
      75,    40,    38,    47,    66,    47,    84,    79,    87,    89,
      91,    85,    39,    47,    39,    47,    43,    47,    77,    48,
      53,    22,    66,    73,    47,    50,    18,    81,    85,    53,
      48,    66,    79,    85,    48,    19,    53,    79
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
		  Type, Value); \
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
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_value_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  if (!yyvaluep)
    return;
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
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  if (yytype < YYNTOKENS)
    YYFPRINTF (yyoutput, "token %s (", yytname[yytype]);
  else
    YYFPRINTF (yyoutput, "nterm %s (", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep);
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
yy_reduce_print (YYSTYPE *yyvsp, int yyrule)
#else
static void
yy_reduce_print (yyvsp, yyrule)
    YYSTYPE *yyvsp;
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
		       		       );
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)		\
do {					\
  if (yydebug)				\
    yy_reduce_print (yyvsp, Rule); \
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
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
#else
static void
yydestruct (yymsg, yytype, yyvaluep)
    const char *yymsg;
    int yytype;
    YYSTYPE *yyvaluep;
#endif
{
  YYUSE (yyvaluep);

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

    YYSIZE_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yytoken = 0;
  yyss = yyssa;
  yyvs = yyvsa;
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

	/* Each stack pointer address is followed by the size of the
	   data in use in that stack, in bytes.  This used to be a
	   conditional around just the two extra args, but that might
	   be undefined if yyoverflow is a macro.  */
	yyoverflow (YY_("memory exhausted"),
		    &yyss1, yysize * sizeof (*yyssp),
		    &yyvs1, yysize * sizeof (*yyvsp),
		    &yystacksize);

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
#  undef YYSTACK_RELOCATE
	if (yyss1 != yyssa)
	  YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

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


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 6:

/* Line 1455 of yacc.c  */
#line 141 ".\\parser.y"
    {
          (yyval.symEntry) = createSymbol((yyvsp[(1) - (1)].sval), SOME_TYPE, NULL); // 假设 createSymbol 返回 SymbolTableEntry* 类型
      }
    break;

  case 7:

/* Line 1455 of yacc.c  */
#line 144 ".\\parser.y"
    {
          SymbolTableEntry* entry = createSymbol((yyvsp[(3) - (3)].sval), SOME_TYPE, NULL);
          entry->next = (yyvsp[(1) - (3)].symEntry); // 假设 $1 是之前 idlist 的返回值，即 SymbolTableEntry* 类型
          (yyval.symEntry) = entry;
      }
    break;

  case 10:

/* Line 1455 of yacc.c  */
#line 158 ".\\parser.y"
    {
          if (findSymbol((yyvsp[(1) - (3)].sval))) {
              yyerror("Identifier already declared");
          } else {
              // 根据const_value的类型来决定是哪种DataType
              DataType type = (yyvsp[(3) - (3)].constVal).type; // 假设const_value已经确定了类型
              addSymbol((yyvsp[(1) - (3)].sval), type, 0, NULL);
          }
    }
    break;

  case 11:

/* Line 1455 of yacc.c  */
#line 167 ".\\parser.y"
    {
        SymbolTableEntry* found = findSymbol((yyvsp[(3) - (5)].sval));
        if (found) {
            yyerror("Duplicate identifier");
        } else {
            addSymbol((yyvsp[(3) - (5)].sval), (yyvsp[(5) - (5)].constVal).type, 0, NULL);
        }
      }
    break;

  case 12:

/* Line 1455 of yacc.c  */
#line 178 ".\\parser.y"
    {
          (yyval.constVal) = (YYSTYPE) {.type = INT_TYPE, .value.ival = (yyvsp[(1) - (1)].ival)};
      }
    break;

  case 13:

/* Line 1455 of yacc.c  */
#line 181 ".\\parser.y"
    {
          (yyval.constVal) = (YYSTYPE) {.type = INT_TYPE, .value.ival = -(yyvsp[(2) - (2)].ival)};
      }
    break;

  case 14:

/* Line 1455 of yacc.c  */
#line 184 ".\\parser.y"
    {
          (yyval.constVal) = (YYSTYPE) {.type = INT_TYPE, .value.ival = (yyvsp[(2) - (2)].ival)};
      }
    break;

  case 15:

/* Line 1455 of yacc.c  */
#line 187 ".\\parser.y"
    {
          (yyval.constVal) = (YYSTYPE) {.type = STRING_TYPE, .value.sval = strdup((yyvsp[(1) - (1)].sval))};
      }
    break;

  case 18:

/* Line 1455 of yacc.c  */
#line 199 ".\\parser.y"
    {
        /* 对于每个变量名，检查是否已经定义 */
       for (int i = 0; i < (yyvsp[(1) - (3)].symEntry).count; ++i) {
           if (findSymbol((yyvsp[(1) - (3)].symEntry).names[i])) {
               printf("Semantic error: variable %s is already defined\n", (yyvsp[(1) - (3)].symEntry).names[i]);
           } else {
               createSymbol((yyvsp[(1) - (3)].symEntry).names[i], (yyvsp[(3) - (3)].type));  /* 创建符号 */
           }
       }
    }
    break;

  case 19:

/* Line 1455 of yacc.c  */
#line 209 ".\\parser.y"
    {
        /* 同上 */
        for (int i = 0; i < (yyvsp[(3) - (5)].symEntry).count; ++i) {
            if (findSymbol((yyvsp[(3) - (5)].symEntry).names[i])) {
                printf("Semantic error: variable %s is already defined\n", (yyvsp[(3) - (5)].symEntry).names[i]);
            } else {
                createSymbol((yyvsp[(3) - (5)].symEntry).names[i], (yyvsp[(5) - (5)].type));  /* 同上 */
            }
        }
    }
    break;

  case 20:

/* Line 1455 of yacc.c  */
#line 222 ".\\parser.y"
    { (yyval.type) = (yyvsp[(1) - (1)].type); }
    break;

  case 21:

/* Line 1455 of yacc.c  */
#line 223 ".\\parser.y"
    { (yyval.type) = ARRAY_TYPE; }
    break;

  case 22:

/* Line 1455 of yacc.c  */
#line 227 ".\\parser.y"
    { (yyval.type) = INT_TYPE; }
    break;

  case 23:

/* Line 1455 of yacc.c  */
#line 228 ".\\parser.y"
    { (yyval.type) = REAL_TYPE; }
    break;

  case 24:

/* Line 1455 of yacc.c  */
#line 229 ".\\parser.y"
    { (yyval.type) = BOOLEAN_TYPE; }
    break;

  case 25:

/* Line 1455 of yacc.c  */
#line 230 ".\\parser.y"
    { (yyval.type) = CHAR_TYPE; }
    break;

  case 31:

/* Line 1455 of yacc.c  */
#line 248 ".\\parser.y"
    {
        addSymbol((yyvsp[(2) - (3)].sval), PROCEDURE_TYPE, (yyvsp[(3) - (3)].param).paramList);
    }
    break;

  case 32:

/* Line 1455 of yacc.c  */
#line 251 ".\\parser.y"
    {
        addSymbol((yyvsp[(2) - (5)].sval), (yyvsp[(5) - (5)].type), (yyvsp[(3) - (5)].param).paramList);
    }
    break;

  case 33:

/* Line 1455 of yacc.c  */
#line 258 ".\\parser.y"
    { (yyval.param) = createParamList(); }
    break;

  case 34:

/* Line 1455 of yacc.c  */
#line 259 ".\\parser.y"
    { (yyval.param) = (yyvsp[(2) - (3)].param); }
    break;

  case 35:

/* Line 1455 of yacc.c  */
#line 263 ".\\parser.y"
    { (yyval.param) = createParamList(); addParam((yyval.param), (yyvsp[(1) - (1)].param).type); }
    break;

  case 36:

/* Line 1455 of yacc.c  */
#line 264 ".\\parser.y"
    { addParam((yyvsp[(1) - (3)].param), (yyvsp[(3) - (3)].param).type); (yyval.param) = (yyvsp[(1) - (3)].param); }
    break;

  case 39:

/* Line 1455 of yacc.c  */
#line 273 ".\\parser.y"
    { (yyval.param) = (yyvsp[(2) - (2)].param); (yyval.param)->isVar = TRUE; }
    break;

  case 40:

/* Line 1455 of yacc.c  */
#line 277 ".\\parser.y"
    {
        // 对于每个idlist中的标识符，设置其类型
        for (int i = 0; i < (yyvsp[(1) - (3)].symEntry).count; ++i) {
            setParamType((yyvsp[(1) - (3)].symEntry).names[i], (yyvsp[(3) - (3)].type));
        }
        (yyval.param) = (yyvsp[(3) - (3)].type); // 假设这里$3是从basic_type传递来的类型
    }
    break;

  case 46:

/* Line 1455 of yacc.c  */
#line 301 ".\\parser.y"
    {
        /* 检查变量是否已经定义，检查类型是否匹配 */
        SymbolTableEntry* var = findSymbol((yyvsp[(1) - (3)].sval));
        if (!var) {
            printf("Semantic error: Undefined variable %s\n", (yyvsp[(1) - (3)].sval));
        } else if (var->type != (yyvsp[(3) - (3)].ival).type) {
            printf("Semantic error: Type mismatch in assignment to %s\n", (yyvsp[(1) - (3)].sval));
        }
    }
    break;

  case 60:

/* Line 1455 of yacc.c  */
#line 335 ".\\parser.y"
    {
        SymbolTableEntry* func = findSymbol((yyvsp[(1) - (1)].sval));
        if (!func || !isFunction(func)) {
            yyerror("Undefined function or identifier is not a function");
        } else if (func->paramCount != 0) {
            yyerror("Function expects parameters");
        }
      }
    break;

  case 61:

/* Line 1455 of yacc.c  */
#line 343 ".\\parser.y"
    {
        SymbolTableEntry* func = findSymbol((yyvsp[(1) - (4)].sval));
        if (!func || !isFunction(func)) {
            yyerror("Undefined function or identifier is not a function");
        } else {
            checkFunctionParameters(func, (yyvsp[(3) - (4)].paramList));
        }
      }
    break;

  case 62:

/* Line 1455 of yacc.c  */
#line 355 ".\\parser.y"
    {
        (yyval.paramList) = createParamList();
        addParam((yyval.paramList), (yyvsp[(1) - (1)].ival).type);
    }
    break;

  case 63:

/* Line 1455 of yacc.c  */
#line 359 ".\\parser.y"
    {
        addParam((yyvsp[(1) - (3)].paramList), (yyvsp[(3) - (3)].ival).type);
        (yyval.paramList) = (yyvsp[(1) - (3)].paramList);
    }
    break;

  case 65:

/* Line 1455 of yacc.c  */
#line 367 ".\\parser.y"
    {
        // 检查两个simple_expression的类型是否兼容
        if (!areTypesCompatible((yyvsp[(1) - (3)].ival).type, (yyvsp[(3) - (3)].ival).type)) {
            yyerror("Type mismatch in relational operation");
        }
      }
    break;

  case 73:

/* Line 1455 of yacc.c  */
#line 386 ".\\parser.y"
    {
        // 检查simple_expression和term的类型是否兼容
        if (!areTypesCompatible((yyvsp[(1) - (3)].ival).type, (yyvsp[(3) - (3)].ival).type)) {
            yyerror("Type mismatch in addition/subtraction operation");
        }
      }
    break;

  case 84:

/* Line 1455 of yacc.c  */
#line 414 ".\\parser.y"
    {
        SymbolTableEntry* var = findSymbol((yyvsp[(1) - (1)].sval));
        if (!var) {
            yyerror("Undefined variable");
        }
      }
    break;

  case 85:

/* Line 1455 of yacc.c  */
#line 420 ".\\parser.y"
    {
        (yyval.ival) = (yyvsp[(2) - (3)].ival);
      }
    break;

  case 86:

/* Line 1455 of yacc.c  */
#line 423 ".\\parser.y"
    {
        SymbolTableEntry* func = findSymbol((yyvsp[(1) - (4)].sval));
        if (!func || !isFunction(func)) {
            yyerror("Undefined function or identifier is not a function");
        } else {
            checkFunctionParameters(func, (yyvsp[(3) - (4)].paramList));
        }
      }
    break;

  case 87:

/* Line 1455 of yacc.c  */
#line 431 ".\\parser.y"
    {
        if ((yyvsp[(2) - (2)].ival).type != BOOLEAN_TYPE) {
            yyerror("Type mismatch in NOT operation");
        }
      }
    break;

  case 88:

/* Line 1455 of yacc.c  */
#line 436 ".\\parser.y"
    {
        if ((yyvsp[(2) - (2)].ival).type != INT_TYPE && (yyvsp[(2) - (2)].ival).type != REAL_TYPE) {
            yyerror("Type mismatch in unary minus operation");
        }
      }
    break;



/* Line 1455 of yacc.c  */
#line 2056 "y.tab.c"
      default: break;
    }
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;

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
		      yytoken, &yylval);
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


      yydestruct ("Error: popping",
		  yystos[yystate], yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  *++yyvsp = yylval;


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
		 yytoken, &yylval);
  /* Do not reclaim the symbols of the rule which action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
		  yystos[*yyssp], yyvsp);
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
#line 443 ".\\parser.y"


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
