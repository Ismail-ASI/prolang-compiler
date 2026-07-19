
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
#line 2 "syntaxique.y"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ts.h"
#include "quad.h"
#include "optim.h"
#include "codegen.h"

extern int nb_ligne;
extern int tok_col;

char SauvType[20];
int  SauvVal = -1;
int  bz_quad = -1;
int  bz_quad_and = -1;
int  bz_or_true  = -1;

static int tc = 0;
static char tmp[20];

typedef struct {
    char type[20];
    char val[40];
} Noeud;

static Noeud* new_noeud(const char *type, const char *val)
{
    Noeud *n = malloc(sizeof(Noeud));
    strncpy(n->type, type ? type : "", 19);
    strncpy(n->val,  val  ? val  : "", 39);
    return n;
}

static char* new_tmp()
{
    static char buf[20];
    sprintf(buf, "T%d", tc++);
    return buf;
}

int yylex(void);
int yyerror(const char *msg);


/* Line 189 of yacc.c  */
#line 119 "syntaxique.tab.c"

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
     BEGINPROJECT = 258,
     MIV = 259,
     ENDPROJECT = 260,
     SETUP = 261,
     RUN = 262,
     DEFINE = 263,
     CONST = 264,
     INTEGER = 265,
     FLOAT = 266,
     IF = 267,
     THEN = 268,
     ELSE = 269,
     ENDIF = 270,
     LOOP = 271,
     WHILE = 272,
     ENDLOOP = 273,
     FOR = 274,
     IN = 275,
     TO = 276,
     ENDFOR = 277,
     MC_OUT = 278,
     AND = 279,
     OR = 280,
     NON = 281,
     MC_IN = 282,
     AFFECTATION = 283,
     INFEGAL = 284,
     SUPEGAL = 285,
     EGAL = 286,
     DIFF = 287,
     INF = 288,
     SUP = 289,
     EGALE_INIT = 290,
     PLUS = 291,
     MOINS = 292,
     MULT = 293,
     DIV = 294,
     PVIR = 295,
     DPTS = 296,
     BARRE = 297,
     PARG = 298,
     PARD = 299,
     CROG = 300,
     CROD = 301,
     ACCOG = 302,
     ACCOD = 303,
     VIRG = 304,
     IDF = 305,
     UINT = 306,
     SINT = 307,
     UFLOAT = 308,
     SFLOAT = 309,
     CHAINE = 310
   };
#endif



#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
{

/* Line 214 of yacc.c  */
#line 47 "syntaxique.y"

    int    entier;
    float  reel;
    char  *chaine;
    struct {
        char type[20];
        char val[40];
    } noeud;



/* Line 214 of yacc.c  */
#line 222 "syntaxique.tab.c"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif


/* Copy the second part of user declarations.  */


/* Line 264 of yacc.c  */
#line 234 "syntaxique.tab.c"

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
#define YYFINAL  4
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   212

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  56
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  36
/* YYNRULES -- Number of rules.  */
#define YYNRULES  78
/* YYNRULES -- Number of states.  */
#define YYNSTATES  185

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   310

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
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint16 yyprhs[] =
{
       0,     0,     3,    17,    18,    21,    23,    25,    31,    39,
      49,    57,    59,    63,    65,    67,    75,    77,    79,    81,
      83,    84,    87,    89,    91,    93,    95,    97,    99,   104,
     105,   114,   115,   116,   134,   135,   136,   137,   151,   152,
     165,   167,   169,   171,   173,   175,   177,   183,   189,   191,
     195,   197,   199,   201,   205,   206,   211,   212,   217,   222,
     226,   230,   234,   238,   242,   246,   248,   252,   256,   258,
     262,   266,   268,   270,   272,   274,   276,   277,   283
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int8 yyrhs[] =
{
      57,     0,    -1,     3,     4,    40,     6,    41,    58,     7,
      41,    47,    65,    48,     5,    40,    -1,    -1,    58,    59,
      -1,    60,    -1,    63,    -1,     8,    50,    41,    62,    40,
      -1,     8,    50,    41,    62,    35,    88,    40,    -1,     8,
      50,    41,    45,    62,    40,    64,    46,    40,    -1,     8,
      50,    42,    61,    41,    62,    40,    -1,    50,    -1,    61,
      42,    50,    -1,    10,    -1,    11,    -1,     9,    50,    41,
      62,    35,    64,    40,    -1,    51,    -1,    52,    -1,    53,
      -1,    54,    -1,    -1,    65,    66,    -1,    67,    -1,    69,
      -1,    72,    -1,    76,    -1,    80,    -1,    81,    -1,    50,
      28,    88,    40,    -1,    -1,    50,    45,    88,    68,    46,
      28,    88,    40,    -1,    -1,    -1,    12,    43,    84,    44,
      13,    41,    47,    70,    65,    48,    71,    14,    47,    65,
      48,    15,    40,    -1,    -1,    -1,    -1,    16,    17,    73,
      43,    84,    44,    74,    75,    47,    65,    48,    18,    40,
      -1,    -1,    19,    50,    20,    78,    21,    79,    77,    47,
      65,    48,    22,    40,    -1,    51,    -1,    52,    -1,    50,
      -1,    51,    -1,    52,    -1,    50,    -1,    27,    43,    50,
      44,    40,    -1,    23,    43,    82,    44,    40,    -1,    83,
      -1,    82,    49,    83,    -1,    55,    -1,    50,    -1,    87,
      -1,    43,    84,    44,    -1,    -1,    84,    24,    85,    84,
      -1,    -1,    84,    25,    86,    84,    -1,    26,    43,    84,
      44,    -1,    88,    33,    88,    -1,    88,    34,    88,    -1,
      88,    29,    88,    -1,    88,    30,    88,    -1,    88,    31,
      88,    -1,    88,    32,    88,    -1,    89,    -1,    88,    36,
      89,    -1,    88,    37,    89,    -1,    90,    -1,    89,    38,
      90,    -1,    89,    39,    90,    -1,    50,    -1,    51,    -1,
      52,    -1,    53,    -1,    54,    -1,    -1,    50,    45,    88,
      91,    46,    -1,    43,    88,    44,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,    75,    75,    78,    80,    84,    85,    89,   105,   124,
     152,   197,   199,   208,   209,   213,   232,   233,   234,   235,
     238,   240,   244,   245,   246,   247,   248,   249,   253,   269,
     269,   298,   310,   297,   330,   334,   343,   329,   364,   363,
     403,   408,   416,   432,   437,   445,   461,   472,   476,   477,
     481,   483,   494,   495,   497,   496,   513,   512,   533,   552,
     553,   554,   555,   556,   557,   561,   563,   575,   590,   592,
     604,   622,   635,   641,   647,   652,   657,   657,   685
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "BEGINPROJECT", "MIV", "ENDPROJECT",
  "SETUP", "RUN", "DEFINE", "CONST", "INTEGER", "FLOAT", "IF", "THEN",
  "ELSE", "ENDIF", "LOOP", "WHILE", "ENDLOOP", "FOR", "IN", "TO", "ENDFOR",
  "MC_OUT", "AND", "OR", "NON", "MC_IN", "AFFECTATION", "INFEGAL",
  "SUPEGAL", "EGAL", "DIFF", "INF", "SUP", "EGALE_INIT", "PLUS", "MOINS",
  "MULT", "DIV", "PVIR", "DPTS", "BARRE", "PARG", "PARD", "CROG", "CROD",
  "ACCOG", "ACCOD", "VIRG", "IDF", "UINT", "SINT", "UFLOAT", "SFLOAT",
  "CHAINE", "$accept", "programme", "partie_decl", "decl", "decl_var",
  "liste_idfs", "type", "decl_const", "cst", "liste_instrs", "instr",
  "instr_affectation", "@1", "instr_condition", "@2", "@3",
  "instr_loop_while", "@4", "@5", "@6", "instr_for", "@7", "val_init",
  "val_limit", "instr_input", "instr_out", "liste_out_args", "out_arg",
  "condition", "@8", "$@9", "expr_comp", "expr", "terme", "facteur", "@10", 0
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
     305,   306,   307,   308,   309,   310
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    56,    57,    58,    58,    59,    59,    60,    60,    60,
      60,    61,    61,    62,    62,    63,    64,    64,    64,    64,
      65,    65,    66,    66,    66,    66,    66,    66,    67,    68,
      67,    70,    71,    69,    73,    74,    75,    72,    77,    76,
      78,    78,    78,    79,    79,    79,    80,    81,    82,    82,
      83,    83,    84,    84,    85,    84,    86,    84,    84,    87,
      87,    87,    87,    87,    87,    88,    88,    88,    89,    89,
      89,    90,    90,    90,    90,    90,    91,    90,    90
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,    13,     0,     2,     1,     1,     5,     7,     9,
       7,     1,     3,     1,     1,     7,     1,     1,     1,     1,
       0,     2,     1,     1,     1,     1,     1,     1,     4,     0,
       8,     0,     0,    17,     0,     0,     0,    13,     0,    12,
       1,     1,     1,     1,     1,     1,     5,     5,     1,     3,
       1,     1,     1,     3,     0,     4,     0,     4,     4,     3,
       3,     3,     3,     3,     3,     1,     3,     3,     1,     3,
       3,     1,     1,     1,     1,     1,     0,     5,     3
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     0,     0,     0,     1,     0,     0,     3,     0,     0,
       0,     0,     4,     5,     6,     0,     0,     0,    20,     0,
       0,     0,     0,    13,    14,     0,     0,    11,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    21,    22,    23,
      24,    25,    26,    27,     0,     0,     7,     0,     0,     0,
       0,    34,     0,     0,     0,     0,     0,     0,     0,     0,
      71,    72,    73,    74,    75,     0,    65,    68,     0,    12,
      16,    17,    18,    19,     0,     0,     0,     0,    52,     0,
       0,     0,    51,    50,     0,    48,     0,     2,     0,    29,
       0,     0,     0,     0,     0,     8,     0,     0,    10,    15,
       0,     0,     0,    54,    56,     0,     0,     0,     0,     0,
       0,     0,     0,    42,    40,    41,     0,     0,     0,     0,
      28,     0,     0,    78,    76,    66,    67,    69,    70,     0,
      53,     0,     0,     0,    61,    62,    63,    64,    59,    60,
       0,     0,    47,    49,    46,     0,     9,     0,    58,    55,
      57,     0,    35,    45,    43,    44,    38,     0,    77,    31,
      36,     0,     0,    20,     0,    20,    30,     0,    20,     0,
      32,     0,     0,     0,     0,     0,     0,     0,    39,    20,
      37,     0,     0,     0,    33
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     2,     8,    12,    13,    28,    26,    14,    74,    22,
      37,    38,   121,    39,   163,   173,    40,    80,   160,   164,
      41,   161,   116,   156,    42,    43,    84,    85,    77,   131,
     132,    78,    79,    66,    67,   147
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -76
static const yytype_int16 yypact[] =
{
       7,     4,    16,   -12,   -76,    28,     2,   -76,   152,    19,
      -5,    -2,   -76,   -76,   -76,    20,    60,    29,   -76,    10,
      24,   118,   -10,   -76,   -76,   118,   -17,   -76,   109,    41,
      37,    68,    32,    44,    46,    94,    -1,   -76,   -76,   -76,
     -76,   -76,   -76,   -76,    69,    82,   -76,   118,    55,   104,
      43,   -76,   102,   -14,    93,   122,    82,    82,   104,    82,
     132,   -76,   -76,   -76,   -76,    71,   131,   -76,   138,   -76,
     -76,   -76,   -76,   -76,   139,   137,    43,   -20,   -76,   108,
     140,   113,   -76,   -76,     5,   -76,   141,   -76,    90,   135,
     107,   110,    82,    82,    82,   -76,    82,    82,   -76,   -76,
      43,     8,    87,   -76,   -76,   168,    82,    82,    82,    82,
      82,    82,    43,   -76,   -76,   -76,   161,   144,   -14,   146,
     -76,   142,   147,   -76,   135,   131,   131,   -76,   -76,    34,
     -76,    43,    43,   148,   135,   135,   135,   135,   135,   135,
      66,   116,   -76,   -76,   -76,   162,   -76,   145,   -76,   -76,
     169,   149,   -76,   -76,   -76,   -76,   -76,    82,   -76,   -76,
     -76,   150,   112,   -76,   151,   -76,   -76,     3,   -76,    23,
     -76,    56,   170,   180,   177,   159,   153,   163,   -76,   -76,
     -76,    65,   186,   164,   -76
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
     -76,   -76,   -76,   -76,   -76,   -76,   -18,   -76,   154,   -65,
     -76,   -76,   -76,   -76,   -76,   -76,   -76,   -76,   -76,   -76,
     -76,   -76,   -76,   -76,   -76,   -76,   -76,    84,   -75,   -76,
     -76,   -76,   -45,    80,    79,   -76
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -1
static const yytype_uint8 yytable[] =
{
      65,   101,    30,    29,   103,   104,    31,    44,     3,    32,
       1,    88,    89,    33,    91,    30,     4,    34,    45,    31,
      23,    24,    32,    46,   105,   129,    33,    56,     5,    68,
      34,   102,   103,   104,     6,    30,    82,   140,    35,    31,
      36,    83,    32,     7,    57,    16,    33,   124,    17,   117,
      34,   170,   130,    36,   118,    25,   149,   150,   103,   104,
      15,   134,   135,   136,   137,   138,   139,    18,    30,    75,
      21,   172,    31,    36,    27,    32,    49,    30,   148,    33,
      50,    31,    52,    34,    32,    51,    76,    53,    33,    54,
     103,   104,    34,    60,    61,    62,    63,    64,   167,    55,
     169,    19,    20,   171,   174,    69,    36,    93,    94,    58,
     152,    95,   162,   182,   181,    36,   106,   107,   108,   109,
     110,   111,    81,    93,    94,    59,    93,    94,    23,    24,
     120,   123,    60,    61,    62,    63,    64,   106,   107,   108,
     109,   110,   111,    86,    93,    94,    93,    94,    93,    94,
      47,    48,   166,   122,   123,    70,    71,    72,    73,     9,
      10,    11,    87,   113,   114,   115,   153,   154,   155,    96,
      97,    93,    94,   125,   126,   127,   128,    92,    98,    99,
     100,   133,   141,   112,   142,   119,   144,   146,   145,   151,
     157,   158,   175,   103,   176,   177,   159,   165,   168,   178,
     179,   183,   143,   180,   184,     0,     0,     0,     0,     0,
       0,     0,    90
};

static const yytype_int16 yycheck[] =
{
      45,    76,    12,    21,    24,    25,    16,    25,     4,    19,
       3,    56,    57,    23,    59,    12,     0,    27,    35,    16,
      10,    11,    19,    40,    44,   100,    23,    28,    40,    47,
      27,    76,    24,    25,     6,    12,    50,   112,    48,    16,
      50,    55,    19,    41,    45,    50,    23,    92,    50,    44,
      27,    48,    44,    50,    49,    45,   131,   132,    24,    25,
      41,   106,   107,   108,   109,   110,   111,    47,    12,    26,
      41,    48,    16,    50,    50,    19,    35,    12,    44,    23,
      43,    16,    50,    27,    19,    17,    43,    43,    23,    43,
      24,    25,    27,    50,    51,    52,    53,    54,   163,     5,
     165,    41,    42,   168,    48,    50,    50,    36,    37,    40,
      44,    40,   157,    48,   179,    50,    29,    30,    31,    32,
      33,    34,    20,    36,    37,    43,    36,    37,    10,    11,
      40,    44,    50,    51,    52,    53,    54,    29,    30,    31,
      32,    33,    34,    50,    36,    37,    36,    37,    36,    37,
      41,    42,    40,    46,    44,    51,    52,    53,    54,     7,
       8,     9,    40,    50,    51,    52,    50,    51,    52,    38,
      39,    36,    37,    93,    94,    96,    97,    45,    40,    40,
      43,    13,    21,    43,    40,    44,    40,    40,    46,    41,
      28,    46,    22,    24,    14,    18,    47,    47,    47,    40,
      47,    15,   118,    40,    40,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    58
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     3,    57,     4,     0,    40,     6,    41,    58,     7,
       8,     9,    59,    60,    63,    41,    50,    50,    47,    41,
      42,    41,    65,    10,    11,    45,    62,    50,    61,    62,
      12,    16,    19,    23,    27,    48,    50,    66,    67,    69,
      72,    76,    80,    81,    62,    35,    40,    41,    42,    35,
      43,    17,    50,    43,    43,     5,    28,    45,    40,    43,
      50,    51,    52,    53,    54,    88,    89,    90,    62,    50,
      51,    52,    53,    54,    64,    26,    43,    84,    87,    88,
      73,    20,    50,    55,    82,    83,    50,    40,    88,    88,
      64,    88,    45,    36,    37,    40,    38,    39,    40,    40,
      43,    84,    88,    24,    25,    44,    29,    30,    31,    32,
      33,    34,    43,    50,    51,    52,    78,    44,    49,    44,
      40,    68,    46,    44,    88,    89,    89,    90,    90,    84,
      44,    85,    86,    13,    88,    88,    88,    88,    88,    88,
      84,    21,    40,    83,    40,    46,    40,    91,    44,    84,
      84,    41,    44,    50,    51,    52,    79,    28,    46,    47,
      74,    77,    88,    70,    75,    47,    40,    65,    47,    65,
      48,    65,    48,    71,    48,    22,    14,    18,    40,    47,
      40,    65,    48,    15,    40
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
        case 7:

/* Line 1455 of yacc.c  */
#line 90 "syntaxique.y"
    {
            int pos = chercher((yyvsp[(2) - (5)].chaine));
            if (pos == -1)
                printf("Erreur semantique, ligne %d, colonne %d, identificateur %s non trouve dans TS\n",
                       nb_ligne, tok_col, (yyvsp[(2) - (5)].chaine));
            else if (TS[pos].type[0] != '\0')
                printf("Erreur semantique, ligne %d, colonne %d, double declaration de %s\n",
                       nb_ligne, tok_col, (yyvsp[(2) - (5)].chaine));
            else
            {
                strcpy(TS[pos].type, SauvType);
                quadr(":", SauvType, "vide", (yyvsp[(2) - (5)].chaine));
            }
        ;}
    break;

  case 8:

/* Line 1455 of yacc.c  */
#line 106 "syntaxique.y"
    {
            int pos = chercher((yyvsp[(2) - (7)].chaine));
            if (pos == -1)
                printf("Erreur semantique, ligne %d, colonne %d, identificateur %s non trouve dans TS\n",
                       nb_ligne, tok_col, (yyvsp[(2) - (7)].chaine));
            else if (TS[pos].type[0] != '\0')
                printf("Erreur semantique, ligne %d, colonne %d, double declaration de %s\n",
                       nb_ligne, tok_col, (yyvsp[(2) - (7)].chaine));
            else
            {
                strcpy(TS[pos].type, SauvType);
                if ((yyvsp[(6) - (7)].noeud).type[0] != '\0' && strcmp(SauvType, (yyvsp[(6) - (7)].noeud).type) != 0)
                    printf("Erreur semantique, ligne %d, colonne %d, incompatibilite de type : %s attend %s mais recoit %s\n",
                           nb_ligne, tok_col, (yyvsp[(2) - (7)].chaine), SauvType, (yyvsp[(6) - (7)].noeud).type);
                quadr(":", SauvType, (yyvsp[(6) - (7)].noeud).val, (yyvsp[(2) - (7)].chaine));
            }
        ;}
    break;

  case 9:

/* Line 1455 of yacc.c  */
#line 125 "syntaxique.y"
    {
            int pos = chercher((yyvsp[(2) - (9)].chaine));
            if (pos == -1)
                printf("Erreur semantique, ligne %d, colonne %d, identificateur %s non trouve dans TS\n",
                       nb_ligne, tok_col, (yyvsp[(2) - (9)].chaine));
            else if (TS[pos].type[0] != '\0')
                printf("Erreur semantique, ligne %d, colonne %d, double declaration de %s\n",
                       nb_ligne, tok_col, (yyvsp[(2) - (9)].chaine));
            else
            {
                strcpy(TS[pos].type, SauvType);
                strcpy(TS[pos].code, "TABLEAU");
                int taille = atoi((yyvsp[(7) - (9)].noeud).val);
                if (taille > 0)
                {
                    sprintf(TS[pos].val, "%d", taille);
                    char upper[20];
                    sprintf(upper, "%d", taille - 1);
                    quadr("BOUNDS", "0", upper, "vide");
                    quadr("ADEC", (yyvsp[(2) - (9)].chaine), "vide", "vide");
                }
                else
                    printf("Erreur semantique, ligne %d, colonne %d, taille de tableau invalide pour %s\n",
                           nb_ligne, tok_col, (yyvsp[(2) - (9)].chaine));
            }
        ;}
    break;

  case 10:

/* Line 1455 of yacc.c  */
#line 153 "syntaxique.y"
    {
            /* liste_idfs contains identifiers AFTER the first BARRE, $2 is the first one */
            /* emit ":" quad for each identifier in liste_idfs (all except $2: no init) */
            char *liste = strdup((yyvsp[(4) - (7)].chaine));
            char *tok = strtok(liste, "|");
            while (tok != NULL)
            {
                int p = chercher(tok);
                if (p == -1)
                    printf("Erreur semantique, ligne %d, colonne %d, identificateur %s non trouve dans TS\n",
                           nb_ligne, tok_col, tok);
                else if (TS[p].type[0] != '\0')
                    printf("Erreur semantique, ligne %d, colonne %d, double declaration de %s\n",
                           nb_ligne, tok_col, tok);
                else
                {
                    strcpy(TS[p].type, SauvType);
                    quadr(":", SauvType, "vide", tok);
                }
                tok = strtok(NULL, "|");
            }
            free(liste);
            /* $2 is the first identifier declared (define $2 | liste_idfs : type) - no init */
            int pos = chercher((yyvsp[(2) - (7)].chaine));
            if (pos == -1)
                printf("Erreur semantique, ligne %d, colonne %d, identificateur %s non trouve dans TS\n",
                       nb_ligne, tok_col, (yyvsp[(2) - (7)].chaine));
            else if (TS[pos].type[0] != '\0')
                printf("Erreur semantique, ligne %d, colonne %d, double declaration de %s\n",
                       nb_ligne, tok_col, (yyvsp[(2) - (7)].chaine));
            else
            {
                strcpy(TS[pos].type, SauvType);
                quadr(":", SauvType, "vide", (yyvsp[(2) - (7)].chaine));
            }
        ;}
    break;

  case 11:

/* Line 1455 of yacc.c  */
#line 198 "syntaxique.y"
    { (yyval.chaine) = strdup((yyvsp[(1) - (1)].chaine)); ;}
    break;

  case 12:

/* Line 1455 of yacc.c  */
#line 200 "syntaxique.y"
    {
            char *buf = malloc(strlen((yyvsp[(1) - (3)].chaine)) + 1 + strlen((yyvsp[(3) - (3)].chaine)) + 1);
            sprintf(buf, "%s|%s", (yyvsp[(1) - (3)].chaine), (yyvsp[(3) - (3)].chaine));
            (yyval.chaine) = buf;
        ;}
    break;

  case 13:

/* Line 1455 of yacc.c  */
#line 208 "syntaxique.y"
    { strcpy(SauvType, "integer"); ;}
    break;

  case 14:

/* Line 1455 of yacc.c  */
#line 209 "syntaxique.y"
    { strcpy(SauvType, "float");   ;}
    break;

  case 15:

/* Line 1455 of yacc.c  */
#line 214 "syntaxique.y"
    {
            int pos = chercher((yyvsp[(2) - (7)].chaine));
            if (pos == -1)
                printf("Erreur semantique, ligne %d, colonne %d, identificateur %s non trouve dans TS\n",
                       nb_ligne, tok_col, (yyvsp[(2) - (7)].chaine));
            else if (TS[pos].type[0] != '\0')
                printf("Erreur semantique, ligne %d, colonne %d, double declaration de %s\n",
                       nb_ligne, tok_col, (yyvsp[(2) - (7)].chaine));
            else
            {
                strcpy(TS[pos].type, SauvType);
                strcpy(TS[pos].code, "CONST");
                quadr(":", SauvType, (yyvsp[(6) - (7)].noeud).val, (yyvsp[(2) - (7)].chaine));
            }
        ;}
    break;

  case 16:

/* Line 1455 of yacc.c  */
#line 232 "syntaxique.y"
    { SauvVal = (yyvsp[(1) - (1)].entier); strcpy((yyval.noeud).type,"integer"); sprintf((yyval.noeud).val,"%d",(yyvsp[(1) - (1)].entier)); ;}
    break;

  case 17:

/* Line 1455 of yacc.c  */
#line 233 "syntaxique.y"
    { SauvVal = (yyvsp[(1) - (1)].entier); strcpy((yyval.noeud).type,"integer"); sprintf((yyval.noeud).val,"%d",(yyvsp[(1) - (1)].entier)); ;}
    break;

  case 18:

/* Line 1455 of yacc.c  */
#line 234 "syntaxique.y"
    { strcpy((yyval.noeud).type,"float");   sprintf((yyval.noeud).val,"%g",(yyvsp[(1) - (1)].reel)); ;}
    break;

  case 19:

/* Line 1455 of yacc.c  */
#line 235 "syntaxique.y"
    { strcpy((yyval.noeud).type,"float");   sprintf((yyval.noeud).val,"%g",(yyvsp[(1) - (1)].reel)); ;}
    break;

  case 28:

/* Line 1455 of yacc.c  */
#line 254 "syntaxique.y"
    {
            int pos = chercher((yyvsp[(1) - (4)].chaine));
            if (pos == -1 || TS[pos].type[0] == '\0')
                printf("Erreur semantique, ligne %d, colonne %d, identificateur %s non declare\n",
                       nb_ligne, tok_col, (yyvsp[(1) - (4)].chaine));
            else if (strcmp(TS[pos].code, "CONST") == 0)
                printf("Erreur semantique, ligne %d, colonne %d, modification d'une constante %s\n",
                       nb_ligne, tok_col, (yyvsp[(1) - (4)].chaine));
            else if ((yyvsp[(3) - (4)].noeud).type[0] != '\0' && strcmp(TS[pos].type, (yyvsp[(3) - (4)].noeud).type) != 0
                     && !(strcmp(TS[pos].type, "float") == 0 && strcmp((yyvsp[(3) - (4)].noeud).type, "integer") == 0))
                printf("Erreur semantique, ligne %d, colonne %d, incompatibilite de type : %s est %s mais recoit %s\n",
                       nb_ligne, tok_col, (yyvsp[(1) - (4)].chaine), TS[pos].type, (yyvsp[(3) - (4)].noeud).type);
            quadr("<--", (yyvsp[(3) - (4)].noeud).val, "vide", (yyvsp[(1) - (4)].chaine));
        ;}
    break;

  case 29:

/* Line 1455 of yacc.c  */
#line 269 "syntaxique.y"
    { (yyval.entier) = SauvVal; ;}
    break;

  case 30:

/* Line 1455 of yacc.c  */
#line 270 "syntaxique.y"
    {
            int pos = chercher((yyvsp[(1) - (8)].chaine));
            int idx_sauve = (yyvsp[(4) - (8)].entier);
            if (pos == -1 || TS[pos].type[0] == '\0')
                printf("Erreur semantique, ligne %d, colonne %d, identificateur %s non declare\n",
                       nb_ligne, tok_col, (yyvsp[(1) - (8)].chaine));
            else if (strcmp(TS[pos].code, "CONST") == 0)
                printf("Erreur semantique, ligne %d, colonne %d, modification d'une constante %s\n",
                       nb_ligne, tok_col, (yyvsp[(1) - (8)].chaine));
            else if (strcmp(TS[pos].code, "TABLEAU") == 0 && TS[pos].val[0] != '\0')
            {
                int taille = atoi(TS[pos].val);
                if (idx_sauve < 0 || idx_sauve >= taille)
                    printf("Erreur semantique, ligne %d, colonne %d, index hors limites pour %s\n",
                           nb_ligne, tok_col, (yyvsp[(1) - (8)].chaine));
            }
            if ((yyvsp[(7) - (8)].noeud).type[0] != '\0' && TS[pos].type[0] != '\0' && strcmp(TS[pos].type, (yyvsp[(7) - (8)].noeud).type) != 0
                && !(strcmp(TS[pos].type, "float") == 0 && strcmp((yyvsp[(7) - (8)].noeud).type, "integer") == 0))
                printf("Erreur semantique, ligne %d, colonne %d, incompatibilite de type : %s est %s mais reçoit %s\n",
                       nb_ligne, tok_col, (yyvsp[(1) - (8)].chaine), TS[pos].type, (yyvsp[(7) - (8)].noeud).type);
            char dest[60];
            sprintf(dest, "%s[%s]", (yyvsp[(1) - (8)].chaine), (yyvsp[(3) - (8)].noeud).val);
            quadr("<--", (yyvsp[(7) - (8)].noeud).val, "vide", dest);
        ;}
    break;

  case 31:

/* Line 1455 of yacc.c  */
#line 298 "syntaxique.y"
    {
            /* Patch OR true-branch BR toward then-body entry */
            if (bz_or_true >= 0)
            {
                sprintf(tmp, "%d", qc);
                updateQuad(bz_or_true, 1, tmp);
                bz_or_true = -1;
            }
            /* Save bz_quad & bz_quad_and NOW before the then-body overwrites them */
            (yyval.entier) = bz_quad;
        ;}
    break;

  case 32:

/* Line 1455 of yacc.c  */
#line 310 "syntaxique.y"
    {
            int saved_bz     = (yyvsp[(8) - (10)].entier);
            int saved_bz_and = bz_quad_and;
            int br_quad = qc;
            quadr("BR", "vide", "vide", "vide");
            /* Patch condition false-branch(es) → else entry */
            sprintf(tmp, "%d", qc);
            updateQuad(saved_bz, 1, tmp);
            if (saved_bz_and >= 0) { updateQuad(saved_bz_and, 1, tmp); bz_quad_and = -1; }
            (yyval.entier) = br_quad;
        ;}
    break;

  case 33:

/* Line 1455 of yacc.c  */
#line 322 "syntaxique.y"
    {
            sprintf(tmp, "%d", qc);
            updateQuad((yyvsp[(11) - (17)].entier), 1, tmp);
        ;}
    break;

  case 34:

/* Line 1455 of yacc.c  */
#line 330 "syntaxique.y"
    {
            (yyval.entier) = qc;   /* slot 3: debut */
        ;}
    break;

  case 35:

/* Line 1455 of yacc.c  */
#line 334 "syntaxique.y"
    {
            if (bz_or_true >= 0)
            {
                char buf[20]; sprintf(buf, "%d", qc);
                updateQuad(bz_or_true, 1, buf);
                bz_or_true = -1;
            }
            (yyval.entier) = bz_quad;     /* slot 7: bz_quad after condition */
        ;}
    break;

  case 36:

/* Line 1455 of yacc.c  */
#line 343 "syntaxique.y"
    {
            (yyval.entier) = bz_quad_and; /* slot 8: bz_quad_and after condition */
        ;}
    break;

  case 37:

/* Line 1455 of yacc.c  */
#line 347 "syntaxique.y"
    {
            int debut        = (yyvsp[(3) - (13)].entier);
            int saved_bz     = (yyvsp[(7) - (13)].entier);
            int saved_bz_and = (yyvsp[(8) - (13)].entier);
            int br_quad = qc;
            quadr("BR", "vide", "vide", "vide");
            char buf[20];
            sprintf(buf, "%d", debut);
            updateQuad(br_quad, 1, buf);
            sprintf(buf, "%d", qc);
            updateQuad(saved_bz, 1, buf);
            if (saved_bz_and >= 0) { updateQuad(saved_bz_and, 1, buf); bz_quad_and = -1; }
        ;}
    break;

  case 38:

/* Line 1455 of yacc.c  */
#line 364 "syntaxique.y"
    {
            int pos = chercher((yyvsp[(2) - (6)].chaine));
            if (pos == -1 || TS[pos].type[0] == '\0')
                printf("Erreur semantique, ligne %d, colonne %d, identificateur %s non declare\n",
                       nb_ligne, tok_col, (yyvsp[(2) - (6)].chaine));
            else if (strcmp(TS[pos].type, "integer") != 0)
                printf("Erreur semantique, ligne %d, colonne %d, incompatibilite de type : compteur de boucle %s doit etre integer\n",
                       nb_ligne, tok_col, (yyvsp[(2) - (6)].chaine));
            if ((yyvsp[(4) - (6)].noeud).val[0] != '\0' && (yyvsp[(6) - (6)].noeud).val[0] != '\0')
            {
                char *end1, *end2;
                long v_init  = strtol((yyvsp[(4) - (6)].noeud).val, &end1, 10);
                long v_limit = strtol((yyvsp[(6) - (6)].noeud).val, &end2, 10);
                if (*end1 == '\0' && *end2 == '\0' && v_limit <= v_init)
                    printf("Erreur semantique, ligne %d, colonne %d, valeur de fin (%ld) doit etre superieure a valeur de depart (%ld)\n",
                           nb_ligne, tok_col, v_limit, v_init);
            }
            quadr("=", (yyvsp[(4) - (6)].noeud).val, "vide", (yyvsp[(2) - (6)].chaine));
            int saved_bz_for = qc;
            bz_quad = qc;
            quadr("BG", "vide", (yyvsp[(2) - (6)].chaine), (yyvsp[(6) - (6)].noeud).val);
            (yyval.entier) = saved_bz_for;
        ;}
    break;

  case 39:

/* Line 1455 of yacc.c  */
#line 388 "syntaxique.y"
    {
            int test_quad = (yyvsp[(7) - (12)].entier);
            char *t = new_tmp();
            quadr("+", (yyvsp[(2) - (12)].chaine), "1", t);
            quadr("=", t, "vide", (yyvsp[(2) - (12)].chaine));
            int br_quad = qc;
            quadr("BR", "vide", "vide", "vide");
            sprintf(tmp, "%d", test_quad);
            updateQuad(br_quad, 1, tmp);
            sprintf(tmp, "%d", qc);
            updateQuad(test_quad, 1, tmp);
        ;}
    break;

  case 40:

/* Line 1455 of yacc.c  */
#line 404 "syntaxique.y"
    {
            strcpy((yyval.noeud).type, "integer");
            sprintf((yyval.noeud).val, "%d", (yyvsp[(1) - (1)].entier));
        ;}
    break;

  case 41:

/* Line 1455 of yacc.c  */
#line 409 "syntaxique.y"
    {
            strcpy((yyval.noeud).type, "integer");
            sprintf((yyval.noeud).val, "%d", (yyvsp[(1) - (1)].entier));
            if ((yyvsp[(1) - (1)].entier) < 0)
                printf("Erreur semantique, ligne %d, colonne %d, valeur de depart negative (%d) dans for\n",
                       nb_ligne, tok_col, (yyvsp[(1) - (1)].entier));
        ;}
    break;

  case 42:

/* Line 1455 of yacc.c  */
#line 417 "syntaxique.y"
    {
            int pos = chercher((yyvsp[(1) - (1)].chaine));
            if (pos == -1 || TS[pos].type[0] == '\0')
            {
                printf("Erreur semantique, ligne %d, colonne %d, identificateur %s non declare\n",
                       nb_ligne, tok_col, (yyvsp[(1) - (1)].chaine));
                strcpy((yyval.noeud).type, "");
            }
            else
                strcpy((yyval.noeud).type, TS[pos].type);
            strcpy((yyval.noeud).val, (yyvsp[(1) - (1)].chaine));
        ;}
    break;

  case 43:

/* Line 1455 of yacc.c  */
#line 433 "syntaxique.y"
    {
            strcpy((yyval.noeud).type, "integer");
            sprintf((yyval.noeud).val, "%d", (yyvsp[(1) - (1)].entier));
        ;}
    break;

  case 44:

/* Line 1455 of yacc.c  */
#line 438 "syntaxique.y"
    {
            strcpy((yyval.noeud).type, "integer");
            sprintf((yyval.noeud).val, "%d", (yyvsp[(1) - (1)].entier));
            if ((yyvsp[(1) - (1)].entier) < 0)
                printf("Erreur semantique, ligne %d, colonne %d, valeur de fin negative (%d) dans for\n",
                       nb_ligne, tok_col, (yyvsp[(1) - (1)].entier));
        ;}
    break;

  case 45:

/* Line 1455 of yacc.c  */
#line 446 "syntaxique.y"
    {
            int pos = chercher((yyvsp[(1) - (1)].chaine));
            if (pos == -1 || TS[pos].type[0] == '\0')
            {
                printf("Erreur semantique, ligne %d, colonne %d, identificateur %s non declare\n",
                       nb_ligne, tok_col, (yyvsp[(1) - (1)].chaine));
                strcpy((yyval.noeud).type, "");
            }
            else
                strcpy((yyval.noeud).type, TS[pos].type);
            strcpy((yyval.noeud).val, (yyvsp[(1) - (1)].chaine));
        ;}
    break;

  case 46:

/* Line 1455 of yacc.c  */
#line 462 "syntaxique.y"
    {
            int pos = chercher((yyvsp[(3) - (5)].chaine));
            if (pos == -1 || TS[pos].type[0] == '\0')
                printf("Erreur semantique, ligne %d, colonne %d, identificateur %s non declare\n",
                       nb_ligne, tok_col, (yyvsp[(3) - (5)].chaine));
            quadr("IN", "vide", "vide", (yyvsp[(3) - (5)].chaine));
        ;}
    break;

  case 50:

/* Line 1455 of yacc.c  */
#line 482 "syntaxique.y"
    { quadr("OUT", (yyvsp[(1) - (1)].chaine), "vide", "vide"); ;}
    break;

  case 51:

/* Line 1455 of yacc.c  */
#line 484 "syntaxique.y"
    {
            int pos = chercher((yyvsp[(1) - (1)].chaine));
            if (pos == -1 || TS[pos].type[0] == '\0')
                printf("Erreur semantique, ligne %d, colonne %d, identificateur %s non declare\n",
                       nb_ligne, tok_col, (yyvsp[(1) - (1)].chaine));
            quadr("OUT", (yyvsp[(1) - (1)].chaine), "vide", "vide");
        ;}
    break;

  case 54:

/* Line 1455 of yacc.c  */
#line 497 "syntaxique.y"
    {
            /* A faux → bz_quad de A saute au else (laissé non patché, sera patché par instr_condition).
               A vrai → tombe dans B. On sauvegarde bz_quad de A pour que instr_condition le patche. */
            (yyval.entier) = bz_quad;
        ;}
    break;

  case 55:

/* Line 1455 of yacc.c  */
#line 503 "syntaxique.y"
    {
            /* bz_quad final = quad de B (si B faux → else).
               Le quad de A (sauvé dans $3) sera aussi patché vers else par instr_condition
               via la variable globale bz_quad qu'on met à jour ici avec le dernier. */
            /* On garde bz_quad = quad de B (déjà mis à jour par expr_comp de B).
               Le quad de A reste non patché avec "vide" ; instr_condition doit patcher les deux.
               Pour rester sur le même format, on stocke le quad de A dans un second global. */
            bz_quad_and = (yyvsp[(3) - (4)].entier);
        ;}
    break;

  case 56:

/* Line 1455 of yacc.c  */
#line 513 "syntaxique.y"
    {
            /* A vrai → BR inconditionnel vers then-body.
               On émet le BR EN PREMIER pour que l'entrée de B soit APRÈS lui. */
            if (bz_or_true >= 0)
            {
                /* Chaîner un bz_or_true précédent vers ce BR */
                char buf[20]; sprintf(buf, "%d", qc);
                updateQuad(bz_or_true, 1, buf);
            }
            bz_or_true = qc;
            quadr("BR", "vide", "vide", "vide");
            /* A faux → évalue B. Patche bz_quad ET bz_quad_and vers entrée de B (= qc, après le BR). */
            sprintf(tmp, "%d", qc);
            updateQuad(bz_quad, 1, tmp);
            if (bz_quad_and >= 0) { updateQuad(bz_quad_and, 1, tmp); bz_quad_and = -1; }
        ;}
    break;

  case 57:

/* Line 1455 of yacc.c  */
#line 530 "syntaxique.y"
    {
            /* bz_quad final = quad de B (si B faux → else). Mis à jour par expr_comp de B. */
        ;}
    break;

  case 58:

/* Line 1455 of yacc.c  */
#line 534 "syntaxique.y"
    {
            /* C vrai → bz_quad de C saute → else  (NON faux)
               C faux → tombe → BR → then-body            (NON vrai) */
            int br_then = qc;
            quadr("BR", "vide", "vide", "vide");
            /* Si un bz_or_true existait déjà (mis par un OR parent), on le chaîne
               vers br_then pour ne pas le perdre. */
            if (bz_or_true >= 0)
            {
                char buf[20];
                sprintf(buf, "%d", br_then);
                updateQuad(bz_or_true, 1, buf);
            }
            bz_or_true = br_then;
        ;}
    break;

  case 59:

/* Line 1455 of yacc.c  */
#line 552 "syntaxique.y"
    { bz_quad = qc; quadr("BGE", "vide", (yyvsp[(1) - (3)].noeud).val, (yyvsp[(3) - (3)].noeud).val); ;}
    break;

  case 60:

/* Line 1455 of yacc.c  */
#line 553 "syntaxique.y"
    { bz_quad = qc; quadr("BLE", "vide", (yyvsp[(1) - (3)].noeud).val, (yyvsp[(3) - (3)].noeud).val); ;}
    break;

  case 61:

/* Line 1455 of yacc.c  */
#line 554 "syntaxique.y"
    { bz_quad = qc; quadr("BG",  "vide", (yyvsp[(1) - (3)].noeud).val, (yyvsp[(3) - (3)].noeud).val); ;}
    break;

  case 62:

/* Line 1455 of yacc.c  */
#line 555 "syntaxique.y"
    { bz_quad = qc; quadr("BL",  "vide", (yyvsp[(1) - (3)].noeud).val, (yyvsp[(3) - (3)].noeud).val); ;}
    break;

  case 63:

/* Line 1455 of yacc.c  */
#line 556 "syntaxique.y"
    { bz_quad = qc; quadr("BNE", "vide", (yyvsp[(1) - (3)].noeud).val, (yyvsp[(3) - (3)].noeud).val); ;}
    break;

  case 64:

/* Line 1455 of yacc.c  */
#line 557 "syntaxique.y"
    { bz_quad = qc; quadr("BE",  "vide", (yyvsp[(1) - (3)].noeud).val, (yyvsp[(3) - (3)].noeud).val); ;}
    break;

  case 65:

/* Line 1455 of yacc.c  */
#line 562 "syntaxique.y"
    { (yyval.noeud) = (yyvsp[(1) - (1)].noeud); ;}
    break;

  case 66:

/* Line 1455 of yacc.c  */
#line 564 "syntaxique.y"
    {
            if ((yyvsp[(1) - (3)].noeud).type[0] == '\0' || (yyvsp[(3) - (3)].noeud).type[0] == '\0')
                strcpy((yyval.noeud).type, "");
            else if (strcmp((yyvsp[(1) - (3)].noeud).type, (yyvsp[(3) - (3)].noeud).type) == 0)
                strcpy((yyval.noeud).type, (yyvsp[(1) - (3)].noeud).type);
            else
                strcpy((yyval.noeud).type, "float");
            char *t = new_tmp();
            strcpy((yyval.noeud).val, t);
            quadr("+", (yyvsp[(1) - (3)].noeud).val, (yyvsp[(3) - (3)].noeud).val, t);
        ;}
    break;

  case 67:

/* Line 1455 of yacc.c  */
#line 576 "syntaxique.y"
    {
            if ((yyvsp[(1) - (3)].noeud).type[0] == '\0' || (yyvsp[(3) - (3)].noeud).type[0] == '\0')
                strcpy((yyval.noeud).type, "");
            else if (strcmp((yyvsp[(1) - (3)].noeud).type, (yyvsp[(3) - (3)].noeud).type) == 0)
                strcpy((yyval.noeud).type, (yyvsp[(1) - (3)].noeud).type);
            else
                strcpy((yyval.noeud).type, "float");
            char *t = new_tmp();
            strcpy((yyval.noeud).val, t);
            quadr("-", (yyvsp[(1) - (3)].noeud).val, (yyvsp[(3) - (3)].noeud).val, t);
        ;}
    break;

  case 68:

/* Line 1455 of yacc.c  */
#line 591 "syntaxique.y"
    { (yyval.noeud) = (yyvsp[(1) - (1)].noeud); ;}
    break;

  case 69:

/* Line 1455 of yacc.c  */
#line 593 "syntaxique.y"
    {
            if ((yyvsp[(1) - (3)].noeud).type[0] == '\0' || (yyvsp[(3) - (3)].noeud).type[0] == '\0')
                strcpy((yyval.noeud).type, "");
            else if (strcmp((yyvsp[(1) - (3)].noeud).type, (yyvsp[(3) - (3)].noeud).type) == 0)
                strcpy((yyval.noeud).type, (yyvsp[(1) - (3)].noeud).type);
            else
                strcpy((yyval.noeud).type, "float");
            char *t = new_tmp();
            strcpy((yyval.noeud).val, t);
            quadr("*", (yyvsp[(1) - (3)].noeud).val, (yyvsp[(3) - (3)].noeud).val, t);
        ;}
    break;

  case 70:

/* Line 1455 of yacc.c  */
#line 605 "syntaxique.y"
    {
            if (SauvVal == 0)
                printf("Erreur semantique, ligne %d, colonne %d, division par zero\n",
                       nb_ligne, tok_col);
            if ((yyvsp[(1) - (3)].noeud).type[0] == '\0' || (yyvsp[(3) - (3)].noeud).type[0] == '\0')
                strcpy((yyval.noeud).type, "");
            else if (strcmp((yyvsp[(1) - (3)].noeud).type, (yyvsp[(3) - (3)].noeud).type) == 0)
                strcpy((yyval.noeud).type, (yyvsp[(1) - (3)].noeud).type);
            else
                strcpy((yyval.noeud).type, "float");
            char *t = new_tmp();
            strcpy((yyval.noeud).val, t);
            quadr("/", (yyvsp[(1) - (3)].noeud).val, (yyvsp[(3) - (3)].noeud).val, t);
        ;}
    break;

  case 71:

/* Line 1455 of yacc.c  */
#line 623 "syntaxique.y"
    {
            int pos = chercher((yyvsp[(1) - (1)].chaine));
            if (pos == -1 || TS[pos].type[0] == '\0')
            {
                printf("Erreur semantique, ligne %d, colonne %d, identificateur %s non declare\n",
                       nb_ligne, tok_col, (yyvsp[(1) - (1)].chaine));
                strcpy((yyval.noeud).type, "");
            }
            else
                strcpy((yyval.noeud).type, TS[pos].type);
            strcpy((yyval.noeud).val, (yyvsp[(1) - (1)].chaine));
        ;}
    break;

  case 72:

/* Line 1455 of yacc.c  */
#line 636 "syntaxique.y"
    {
            SauvVal = (yyvsp[(1) - (1)].entier);
            strcpy((yyval.noeud).type, "integer");
            sprintf((yyval.noeud).val, "%d", (yyvsp[(1) - (1)].entier));
        ;}
    break;

  case 73:

/* Line 1455 of yacc.c  */
#line 642 "syntaxique.y"
    {
            SauvVal = (yyvsp[(1) - (1)].entier);
            strcpy((yyval.noeud).type, "integer");
            sprintf((yyval.noeud).val, "%d", (yyvsp[(1) - (1)].entier));
        ;}
    break;

  case 74:

/* Line 1455 of yacc.c  */
#line 648 "syntaxique.y"
    {
            strcpy((yyval.noeud).type, "float");
            sprintf((yyval.noeud).val, "%g", (yyvsp[(1) - (1)].reel));
        ;}
    break;

  case 75:

/* Line 1455 of yacc.c  */
#line 653 "syntaxique.y"
    {
            strcpy((yyval.noeud).type, "float");
            sprintf((yyval.noeud).val, "%g", (yyvsp[(1) - (1)].reel));
        ;}
    break;

  case 76:

/* Line 1455 of yacc.c  */
#line 657 "syntaxique.y"
    { (yyval.entier) = SauvVal; ;}
    break;

  case 77:

/* Line 1455 of yacc.c  */
#line 658 "syntaxique.y"
    {
            int pos = chercher((yyvsp[(1) - (5)].chaine));
            if (pos == -1 || TS[pos].type[0] == '\0')
            {
                printf("Erreur semantique, ligne %d, colonne %d, identificateur %s non declare\n",
                       nb_ligne, tok_col, (yyvsp[(1) - (5)].chaine));
                strcpy((yyval.noeud).type, "");
                strcpy((yyval.noeud).val, "vide");
            }
            else
            {
                if (strcmp(TS[pos].code, "TABLEAU") == 0 && TS[pos].val[0] != '\0')
                {
                    int taille = atoi(TS[pos].val);
                    int idx_sauve = (yyvsp[(4) - (5)].entier);
                    if (idx_sauve < 0 || idx_sauve >= taille)
                        printf("Erreur semantique, ligne %d, colonne %d, index hors limites pour %s\n",
                               nb_ligne, tok_col, (yyvsp[(1) - (5)].chaine));
                }
                char *t = new_tmp();
                strcpy((yyval.noeud).type, TS[pos].type);
                strcpy((yyval.noeud).val, t);
                char operande[60];
                sprintf(operande, "%s[%s]", (yyvsp[(1) - (5)].chaine), (yyvsp[(3) - (5)].noeud).val);
                quadr("<--", operande, "vide", t);
            }
        ;}
    break;

  case 78:

/* Line 1455 of yacc.c  */
#line 685 "syntaxique.y"
    { (yyval.noeud) = (yyvsp[(2) - (3)].noeud); ;}
    break;



/* Line 1455 of yacc.c  */
#line 2416 "syntaxique.tab.c"
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
#line 688 "syntaxique.y"


int yyerror(const char *msg)
{
    printf("Erreur syntaxique, ligne %d, colonne %d : %s\n", nb_ligne, tok_col, msg);
    return 1;
}

int main(int argc, char *argv[])
{
    extern FILE *yyin;

    initialization();

    if (argc > 1)
    {
        FILE *f = fopen(argv[1], "r");
        if (!f) { perror(argv[1]); return 1; }
        yyin = f;
    }

    yyparse();

    afficher();
    printf("\n****** Code intermédiaire AVANT optimisation ******\n");
    afficher_qdr();
 
    optimiser_quadruplets();

    printf("\n****** Code intermédiaire APRÈS optimisation ******\n");
    afficher_qdr();
    generer_code_8086("output.asm");
    return 0;
}

