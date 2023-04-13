/* A Bison parser, made by GNU Bison 3.5.1.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2020 Free Software Foundation,
   Inc.

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

/* Undocumented macros, especially those whose name start with YY_,
   are private implementation details.  Do not rely on them.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "3.5.1"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 1 "bison.y"

#include <iostream>
#include <stdio.h>
#include <string.h>
#include "../inc/asembler.hpp"
extern int yylex();
extern FILE *yyin;
 
void yyerror(const char *s);

#line 81 "bison.tab.c"

# ifndef YY_CAST
#  ifdef __cplusplus
#   define YY_CAST(Type, Val) static_cast<Type> (Val)
#   define YY_REINTERPRET_CAST(Type, Val) reinterpret_cast<Type> (Val)
#  else
#   define YY_CAST(Type, Val) ((Type) (Val))
#   define YY_REINTERPRET_CAST(Type, Val) ((Type) (Val))
#  endif
# endif
# ifndef YY_NULLPTR
#  if defined __cplusplus
#   if 201103L <= __cplusplus
#    define YY_NULLPTR nullptr
#   else
#    define YY_NULLPTR 0
#   endif
#  else
#   define YY_NULLPTR ((void*)0)
#  endif
# endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* Use api.header.include to #include this header
   instead of duplicating it here.  */
#ifndef YY_YY_BISON_TAB_H_INCLUDED
# define YY_YY_BISON_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    GLOBAL = 258,
    EXTERN = 259,
    ENDL = 260,
    SECTION = 261,
    WORD = 262,
    COLON = 263,
    SKIP = 264,
    END = 265,
    HALT = 266,
    INT = 267,
    IRET = 268,
    CALL = 269,
    PCREL = 270,
    VAL = 271,
    REGIND1 = 272,
    REGIND2 = 273,
    STAR = 274,
    RET = 275,
    JMP = 276,
    JEQ = 277,
    JNE = 278,
    JGT = 279,
    PUSH = 280,
    POP = 281,
    XCHG = 282,
    ADD = 283,
    SUB = 284,
    MUL = 285,
    DIV = 286,
    CMP = 287,
    NOT = 288,
    AND = 289,
    OR = 290,
    XOR = 291,
    TEST = 292,
    SHL = 293,
    SHR = 294,
    LDR = 295,
    STR = 296,
    SYMBOL = 297,
    NUM = 298,
    REG = 299,
    COMMA = 300,
    PLUS = 301
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 11 "bison.y"

  int number;
  char *string;

#line 185 "bison.tab.c"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_BISON_TAB_H_INCLUDED  */



#ifdef short
# undef short
#endif

/* On compilers that do not define __PTRDIFF_MAX__ etc., make sure
   <limits.h> and (if available) <stdint.h> are included
   so that the code can choose integer types of a good width.  */

#ifndef __PTRDIFF_MAX__
# include <limits.h> /* INFRINGES ON USER NAME SPACE */
# if defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stdint.h> /* INFRINGES ON USER NAME SPACE */
#  define YY_STDINT_H
# endif
#endif

/* Narrow types that promote to a signed type and that can represent a
   signed or unsigned integer of at least N bits.  In tables they can
   save space and decrease cache pressure.  Promoting to a signed type
   helps avoid bugs in integer arithmetic.  */

#ifdef __INT_LEAST8_MAX__
typedef __INT_LEAST8_TYPE__ yytype_int8;
#elif defined YY_STDINT_H
typedef int_least8_t yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef __INT_LEAST16_MAX__
typedef __INT_LEAST16_TYPE__ yytype_int16;
#elif defined YY_STDINT_H
typedef int_least16_t yytype_int16;
#else
typedef short yytype_int16;
#endif

#if defined __UINT_LEAST8_MAX__ && __UINT_LEAST8_MAX__ <= __INT_MAX__
typedef __UINT_LEAST8_TYPE__ yytype_uint8;
#elif (!defined __UINT_LEAST8_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST8_MAX <= INT_MAX)
typedef uint_least8_t yytype_uint8;
#elif !defined __UINT_LEAST8_MAX__ && UCHAR_MAX <= INT_MAX
typedef unsigned char yytype_uint8;
#else
typedef short yytype_uint8;
#endif

#if defined __UINT_LEAST16_MAX__ && __UINT_LEAST16_MAX__ <= __INT_MAX__
typedef __UINT_LEAST16_TYPE__ yytype_uint16;
#elif (!defined __UINT_LEAST16_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST16_MAX <= INT_MAX)
typedef uint_least16_t yytype_uint16;
#elif !defined __UINT_LEAST16_MAX__ && USHRT_MAX <= INT_MAX
typedef unsigned short yytype_uint16;
#else
typedef int yytype_uint16;
#endif

#ifndef YYPTRDIFF_T
# if defined __PTRDIFF_TYPE__ && defined __PTRDIFF_MAX__
#  define YYPTRDIFF_T __PTRDIFF_TYPE__
#  define YYPTRDIFF_MAXIMUM __PTRDIFF_MAX__
# elif defined PTRDIFF_MAX
#  ifndef ptrdiff_t
#   include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  endif
#  define YYPTRDIFF_T ptrdiff_t
#  define YYPTRDIFF_MAXIMUM PTRDIFF_MAX
# else
#  define YYPTRDIFF_T long
#  define YYPTRDIFF_MAXIMUM LONG_MAX
# endif
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned
# endif
#endif

#define YYSIZE_MAXIMUM                                  \
  YY_CAST (YYPTRDIFF_T,                                 \
           (YYPTRDIFF_MAXIMUM < YY_CAST (YYSIZE_T, -1)  \
            ? YYPTRDIFF_MAXIMUM                         \
            : YY_CAST (YYSIZE_T, -1)))

#define YYSIZEOF(X) YY_CAST (YYPTRDIFF_T, sizeof (X))

/* Stored state numbers (used for stacks). */
typedef yytype_int16 yy_state_t;

/* State numbers in computations.  */
typedef int yy_state_fast_t;

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif

#ifndef YY_ATTRIBUTE_PURE
# if defined __GNUC__ && 2 < __GNUC__ + (96 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_PURE __attribute__ ((__pure__))
# else
#  define YY_ATTRIBUTE_PURE
# endif
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# if defined __GNUC__ && 2 < __GNUC__ + (7 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_UNUSED __attribute__ ((__unused__))
# else
#  define YY_ATTRIBUTE_UNUSED
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

#if defined __GNUC__ && ! defined __ICC && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                            \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# define YY_IGNORE_MAYBE_UNINITIALIZED_END      \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif

#if defined __cplusplus && defined __GNUC__ && ! defined __ICC && 6 <= __GNUC__
# define YY_IGNORE_USELESS_CAST_BEGIN                          \
    _Pragma ("GCC diagnostic push")                            \
    _Pragma ("GCC diagnostic ignored \"-Wuseless-cast\"")
# define YY_IGNORE_USELESS_CAST_END            \
    _Pragma ("GCC diagnostic pop")
#endif
#ifndef YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_END
#endif


#define YY_ASSERT(E) ((void) (0 && (E)))

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
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
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
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
             && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
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
  yy_state_t yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (YYSIZEOF (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (YYSIZEOF (yy_state_t) + YYSIZEOF (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYPTRDIFF_T yynewbytes;                                         \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * YYSIZEOF (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / YYSIZEOF (*yyptr);                        \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, YY_CAST (YYSIZE_T, (Count)) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYPTRDIFF_T yyi;                      \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  89
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   329

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  47
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  7
/* YYNRULES -- Number of rules.  */
#define YYNRULES  99
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  284

#define YYUNDEFTOK  2
#define YYMAXUTOK   301


/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                                \
  (0 <= (YYX) && (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex.  */
static const yytype_int8 yytranslate[] =
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
      45,    46
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,    25,    25,    27,    27,    29,    29,    29,    29,    31,
      35,    39,    43,    47,    51,    55,    58,    61,    65,    68,
      72,    76,    80,    84,    88,    92,    96,   100,   104,   107,
     111,   115,   119,   123,   127,   131,   135,   139,   143,   147,
     151,   155,   159,   163,   167,   171,   175,   179,   183,   187,
     191,   195,   199,   203,   207,   211,   215,   219,   223,   227,
     231,   235,   239,   243,   247,   251,   255,   259,   263,   267,
     271,   275,   279,   283,   287,   291,   295,   299,   303,   307,
     311,   315,   319,   323,   327,   331,   335,   339,   343,   347,
     351,   355,   359,   363,   367,   371,   376,   379,   383,   383
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "GLOBAL", "EXTERN", "ENDL", "SECTION",
  "WORD", "COLON", "SKIP", "END", "HALT", "INT", "IRET", "CALL", "PCREL",
  "VAL", "REGIND1", "REGIND2", "STAR", "RET", "JMP", "JEQ", "JNE", "JGT",
  "PUSH", "POP", "XCHG", "ADD", "SUB", "MUL", "DIV", "CMP", "NOT", "AND",
  "OR", "XOR", "TEST", "SHL", "SHR", "LDR", "STR", "SYMBOL", "NUM", "REG",
  "COMMA", "PLUS", "$accept", "bison", "lines", "line", "directive",
  "label", "SYMBOLLIST", YY_NULLPTR
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_int16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   300,   301
};
# endif

#define YYPACT_NINF (-38)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
      23,    26,    26,   -38,    29,   -37,    35,   -38,    77,    66,
     108,    97,   120,    99,   102,   104,   107,    71,    76,    85,
      86,    90,   119,   121,   122,   123,   127,   128,   135,   136,
     137,   138,   139,   140,   145,   154,    23,   -38,   -38,    63,
     -38,    -5,    -4,   159,   180,    -3,   181,   -38,   182,   -38,
      89,   115,   183,   184,   -38,   148,   118,   186,   187,   151,
     126,   189,   190,   155,   131,   191,   193,   157,   134,   195,
     196,   197,   198,   160,   161,   162,   163,   164,   165,   199,
     166,   167,   168,   169,   170,   171,   172,   173,   214,   -38,
     -38,   -38,   -38,   178,   -38,   -38,   -38,   -38,   -38,   -38,
     216,   179,   217,   219,   220,   -38,   -38,   221,   185,   222,
     223,   225,   -38,   -38,   226,   188,   228,   229,   230,   -38,
     -38,   231,   194,   232,   234,   235,   -38,   -38,   236,   200,
     237,   238,   240,   -38,   -38,   -38,   -38,   202,   203,   204,
     205,   206,   207,   -38,   208,   209,   210,   211,   212,   213,
      64,    94,   -38,   -38,   -38,   -15,   -38,   -38,   -38,   -38,
      -8,   -38,   -38,   -38,   -38,    -7,   -38,   -38,   -38,   -38,
      87,   -38,   -38,   -38,   -38,   106,   -38,   -38,   -38,   253,
     254,   255,   256,   257,   258,   259,   260,   261,   262,   263,
     264,   233,   -34,   227,   265,   267,   268,   239,   241,   269,
     271,   272,   273,   -30,   274,   -28,   275,   -26,   277,   -24,
     278,   -22,   -38,   -38,   -38,   -38,   -38,   -38,   -38,   -38,
     -38,   -38,   -38,   -38,   279,   281,   282,   109,   -38,   -38,
     -38,   283,   110,   -38,   -38,   -38,   -38,   276,   280,   -38,
     284,   285,   -38,   286,   287,   -38,   288,   289,   -38,   290,
     291,   -38,   -38,   -38,   292,   -20,   -38,   294,   -18,   -38,
     295,   -38,   296,   -38,   305,   -38,   306,   -38,   307,   -38,
     297,   298,   -38,   299,   300,   -38,   -38,   -38,   -38,   -38,
     -38,   -38,   -38,   -38
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       0,     0,     0,     8,     0,     0,     0,    15,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     2,     4,     7,     5,
      98,     0,     0,     0,     0,     0,     0,    16,     0,    18,
       0,     0,     0,     0,    28,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    96,     1,
       3,     6,     9,     0,    10,    11,    13,    12,    14,    17,
       0,     0,     0,     0,     0,    20,    19,     0,     0,     0,
       0,     0,    30,    29,     0,     0,     0,     0,     0,    39,
      38,     0,     0,     0,     0,     0,    48,    47,     0,     0,
       0,     0,     0,    57,    56,    65,    66,     0,     0,     0,
       0,     0,     0,    73,     0,     0,     0,     0,     0,     0,
       0,     0,    97,    99,    21,     0,    23,    22,    24,    31,
       0,    33,    32,    34,    40,     0,    42,    41,    43,    49,
       0,    51,    50,    52,    58,     0,    60,    59,    61,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    67,    68,    69,    70,    71,    72,    74,    75,
      76,    77,    78,    79,     0,     0,     0,     0,    83,    82,
      85,     0,     0,    90,    89,    92,    25,     0,     0,    35,
       0,     0,    44,     0,     0,    53,     0,     0,    62,     0,
       0,    84,    81,    80,     0,     0,    91,     0,     0,    27,
       0,    37,     0,    46,     0,    55,     0,    64,     0,    86,
       0,     0,    93,     0,     0,    26,    36,    45,    54,    63,
      88,    87,    95,    94
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
     -38,   -38,   -38,   293,   250,   -38,     2
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
      -1,    35,    36,    37,    38,    39,    41
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      92,    94,    97,   202,    42,    40,    44,    45,   225,   226,
     204,   206,   237,   238,   240,   241,   243,   244,   246,   247,
     249,   250,   270,   271,   273,   274,     1,     2,     3,     4,
       5,   203,     6,     7,     8,     9,    10,    11,   205,   207,
      93,    93,    93,    12,    13,    14,    15,    16,    17,    18,
      19,    20,    21,    22,    23,    24,    25,    26,    27,    28,
      29,    30,    31,    32,    33,    34,     1,     2,    40,     4,
       5,    43,     6,     7,     8,     9,    10,    11,    46,   191,
     192,   193,    47,    12,    13,    14,    15,    16,    17,    18,
      19,    20,    21,    22,    23,    24,    25,    26,    27,    28,
      29,    30,    31,    32,    33,   208,   194,   195,   196,   197,
      48,   198,    50,    49,    55,    71,    51,    59,    56,    63,
      72,    60,    67,    64,   210,    54,    68,   254,   257,    73,
      74,   100,   101,   209,    75,   108,   199,   200,   201,    52,
      53,    57,    58,   115,    61,    62,    65,    66,   122,    69,
      70,   129,   211,    88,    89,   255,   258,   102,   103,   104,
     109,   110,   111,    76,    95,    77,    78,    79,   116,   117,
     118,    80,    81,   123,   124,   125,   130,   131,   132,    82,
      83,    84,    85,    86,    87,    96,    98,    99,   105,   106,
     107,   112,   113,   114,   119,   120,   126,   121,   127,   128,
     133,   134,   135,   136,   143,   137,   138,   139,   140,   141,
     142,   144,   145,   146,   147,   148,   149,   150,   151,   152,
     153,   154,   156,   155,   157,   158,   159,   161,   162,   160,
     163,   164,   165,   166,   167,   168,   169,   171,   170,   172,
     173,   174,   176,   177,   175,   178,   179,   180,   181,   182,
     183,   184,   185,   186,   187,   188,   189,   190,   212,   213,
     214,   215,   216,   217,   218,   219,   220,   221,   222,   223,
     228,   227,   229,   230,   233,   224,   234,   235,   236,   239,
     242,   231,   245,   248,   251,   232,   252,   253,   256,    91,
       0,     0,     0,     0,   259,     0,     0,   269,   260,   272,
     275,   276,   261,   262,   263,   264,   265,   266,   267,   268,
     277,   278,   279,     0,     0,   280,   281,   282,   283,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    90
};

static const yytype_int8 yycheck[] =
{
       5,     5,     5,    18,     2,    42,    43,     5,    42,    43,
      18,    18,    42,    43,    42,    43,    42,    43,    42,    43,
      42,    43,    42,    43,    42,    43,     3,     4,     5,     6,
       7,    46,     9,    10,    11,    12,    13,    14,    46,    46,
      45,    45,    45,    20,    21,    22,    23,    24,    25,    26,
      27,    28,    29,    30,    31,    32,    33,    34,    35,    36,
      37,    38,    39,    40,    41,    42,     3,     4,    42,     6,
       7,    42,     9,    10,    11,    12,    13,    14,    43,    15,
      16,    17,     5,    20,    21,    22,    23,    24,    25,    26,
      27,    28,    29,    30,    31,    32,    33,    34,    35,    36,
      37,    38,    39,    40,    41,    18,    42,    43,    44,    15,
      44,    17,    15,     5,    15,    44,    19,    15,    19,    15,
      44,    19,    15,    19,    18,     5,    19,    18,    18,    44,
      44,    42,    17,    46,    44,    17,    42,    43,    44,    42,
      43,    42,    43,    17,    42,    43,    42,    43,    17,    42,
      43,    17,    46,     8,     0,    46,    46,    42,    43,    44,
      42,    43,    44,    44,     5,    44,    44,    44,    42,    43,
      44,    44,    44,    42,    43,    44,    42,    43,    44,    44,
      44,    44,    44,    44,    44,     5,     5,     5,     5,     5,
      42,     5,     5,    42,     5,     5,     5,    42,     5,    42,
       5,     5,     5,     5,     5,    45,    45,    45,    45,    45,
      45,    45,    45,    45,    45,    45,    45,    45,    45,     5,
      42,     5,     5,    44,     5,     5,     5,     5,     5,    44,
       5,     5,    44,     5,     5,     5,     5,     5,    44,     5,
       5,     5,     5,     5,    44,     5,    44,    44,    44,    44,
      44,    44,    44,    44,    44,    44,    44,    44,     5,     5,
       5,     5,     5,     5,     5,     5,     5,     5,     5,     5,
       5,    44,     5,     5,     5,    42,     5,     5,     5,     5,
       5,    42,     5,     5,     5,    44,     5,     5,     5,    39,
      -1,    -1,    -1,    -1,    18,    -1,    -1,     5,    18,     5,
       5,     5,    18,    18,    18,    18,    18,    18,    18,    18,
       5,     5,     5,    -1,    -1,    18,    18,    18,    18,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    36
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,     3,     4,     5,     6,     7,     9,    10,    11,    12,
      13,    14,    20,    21,    22,    23,    24,    25,    26,    27,
      28,    29,    30,    31,    32,    33,    34,    35,    36,    37,
      38,    39,    40,    41,    42,    48,    49,    50,    51,    52,
      42,    53,    53,    42,    43,    53,    43,     5,    44,     5,
      15,    19,    42,    43,     5,    15,    19,    42,    43,    15,
      19,    42,    43,    15,    19,    42,    43,    15,    19,    42,
      43,    44,    44,    44,    44,    44,    44,    44,    44,    44,
      44,    44,    44,    44,    44,    44,    44,    44,     8,     0,
      50,    51,     5,    45,     5,     5,     5,     5,     5,     5,
      42,    17,    42,    43,    44,     5,     5,    42,    17,    42,
      43,    44,     5,     5,    42,    17,    42,    43,    44,     5,
       5,    42,    17,    42,    43,    44,     5,     5,    42,    17,
      42,    43,    44,     5,     5,     5,     5,    45,    45,    45,
      45,    45,    45,     5,    45,    45,    45,    45,    45,    45,
      45,    45,     5,    42,     5,    44,     5,     5,     5,     5,
      44,     5,     5,     5,     5,    44,     5,     5,     5,     5,
      44,     5,     5,     5,     5,    44,     5,     5,     5,    44,
      44,    44,    44,    44,    44,    44,    44,    44,    44,    44,
      44,    15,    16,    17,    42,    43,    44,    15,    17,    42,
      43,    44,    18,    46,    18,    46,    18,    46,    18,    46,
      18,    46,     5,     5,     5,     5,     5,     5,     5,     5,
       5,     5,     5,     5,    42,    42,    43,    44,     5,     5,
       5,    42,    44,     5,     5,     5,     5,    42,    43,     5,
      42,    43,     5,    42,    43,     5,    42,    43,     5,    42,
      43,     5,     5,     5,    18,    46,     5,    18,    46,    18,
      18,    18,    18,    18,    18,    18,    18,    18,    18,     5,
      42,    43,     5,    42,    43,     5,     5,     5,     5,     5,
      18,    18,    18,    18
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_int8 yyr1[] =
{
       0,    47,    48,    49,    49,    50,    50,    50,    50,    51,
      51,    51,    51,    51,    51,    51,    51,    51,    51,    51,
      51,    51,    51,    51,    51,    51,    51,    51,    51,    51,
      51,    51,    51,    51,    51,    51,    51,    51,    51,    51,
      51,    51,    51,    51,    51,    51,    51,    51,    51,    51,
      51,    51,    51,    51,    51,    51,    51,    51,    51,    51,
      51,    51,    51,    51,    51,    51,    51,    51,    51,    51,
      51,    51,    51,    51,    51,    51,    51,    51,    51,    51,
      51,    51,    51,    51,    51,    51,    51,    51,    51,    51,
      51,    51,    51,    51,    51,    51,    52,    52,    53,    53
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     1,     2,     1,     1,     2,     1,     1,     3,
       3,     3,     3,     3,     3,     1,     2,     3,     2,     3,
       3,     4,     4,     4,     4,     6,     8,     7,     2,     3,
       3,     4,     4,     4,     4,     6,     8,     7,     3,     3,
       4,     4,     4,     4,     6,     8,     7,     3,     3,     4,
       4,     4,     4,     6,     8,     7,     3,     3,     4,     4,
       4,     4,     6,     8,     7,     3,     3,     5,     5,     5,
       5,     5,     5,     3,     5,     5,     5,     5,     5,     5,
       6,     6,     5,     5,     6,     5,     7,     8,     8,     5,
       5,     6,     5,     7,     8,     8,     2,     3,     1,     3
};


#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)
#define YYEMPTY         (-2)
#define YYEOF           0

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                    \
  do                                                              \
    if (yychar == YYEMPTY)                                        \
      {                                                           \
        yychar = (Token);                                         \
        yylval = (Value);                                         \
        YYPOPSTACK (yylen);                                       \
        yystate = *yyssp;                                         \
        goto yybackup;                                            \
      }                                                           \
    else                                                          \
      {                                                           \
        yyerror (YY_("syntax error: cannot back up")); \
        YYERROR;                                                  \
      }                                                           \
  while (0)

/* Error token number */
#define YYTERROR        1
#define YYERRCODE       256



/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)

/* This macro is provided for backward compatibility. */
#ifndef YY_LOCATION_PRINT
# define YY_LOCATION_PRINT(File, Loc) ((void) 0)
#endif


# define YY_SYMBOL_PRINT(Title, Type, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Type, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo, int yytype, YYSTYPE const * const yyvaluep)
{
  FILE *yyoutput = yyo;
  YYUSE (yyoutput);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyo, yytoknum[yytype], *yyvaluep);
# endif
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yytype);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo, int yytype, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyo, "%s %s (",
             yytype < YYNTOKENS ? "token" : "nterm", yytname[yytype]);

  yy_symbol_value_print (yyo, yytype, yyvaluep);
  YYFPRINTF (yyo, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yy_state_t *yybottom, yy_state_t *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp, int yyrule)
{
  int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %d):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       yystos[+yyssp[yyi + 1 - yynrhs]],
                       &yyvsp[(yyi + 1) - (yynrhs)]
                                              );
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule); \
} while (0)

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
#ifndef YYINITDEPTH
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
#   define yystrlen(S) (YY_CAST (YYPTRDIFF_T, strlen (S)))
#  else
/* Return the length of YYSTR.  */
static YYPTRDIFF_T
yystrlen (const char *yystr)
{
  YYPTRDIFF_T yylen;
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
static char *
yystpcpy (char *yydest, const char *yysrc)
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
static YYPTRDIFF_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYPTRDIFF_T yyn = 0;
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
            else
              goto append;

          append:
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

  if (yyres)
    return yystpcpy (yyres, yystr) - yyres;
  else
    return yystrlen (yystr);
}
# endif

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return 1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return 2 if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYPTRDIFF_T *yymsg_alloc, char **yymsg,
                yy_state_t *yyssp, int yytoken)
{
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat: reported tokens (one for the "unexpected",
     one per "expected"). */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Actual size of YYARG. */
  int yycount = 0;
  /* Cumulated lengths of YYARG.  */
  YYPTRDIFF_T yysize = 0;

  /* There are many possibilities here to consider:
     - If this state is a consistent state with a default action, then
       the only way this function was invoked is if the default action
       is an error action.  In that case, don't check for expected
       tokens because there are none.
     - The only way there can be no lookahead present (in yychar) is if
       this state is a consistent state with a default action.  Thus,
       detecting the absence of a lookahead is sufficient to determine
       that there is no unexpected or expected token to report.  In that
       case, just report a simple "syntax error".
     - Don't assume there isn't a lookahead just because this state is a
       consistent state with a default action.  There might have been a
       previous inconsistent state, consistent state with a non-default
       action, or user semantic action that manipulated yychar.
     - Of course, the expected token list depends on states to have
       correct lookahead information, and it depends on the parser not
       to perform extra reductions after fetching a lookahead from the
       scanner and before detecting a syntax error.  Thus, state merging
       (from LALR or IELR) and default reductions corrupt the expected
       token list.  However, the list is correct for canonical LR with
       one exception: it will still contain any token that will not be
       accepted due to an error action in a later state.
  */
  if (yytoken != YYEMPTY)
    {
      int yyn = yypact[+*yyssp];
      YYPTRDIFF_T yysize0 = yytnamerr (YY_NULLPTR, yytname[yytoken]);
      yysize = yysize0;
      yyarg[yycount++] = yytname[yytoken];
      if (!yypact_value_is_default (yyn))
        {
          /* Start YYX at -YYN if negative to avoid negative indexes in
             YYCHECK.  In other words, skip the first -YYN actions for
             this state because they are default actions.  */
          int yyxbegin = yyn < 0 ? -yyn : 0;
          /* Stay within bounds of both yycheck and yytname.  */
          int yychecklim = YYLAST - yyn + 1;
          int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
          int yyx;

          for (yyx = yyxbegin; yyx < yyxend; ++yyx)
            if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR
                && !yytable_value_is_error (yytable[yyx + yyn]))
              {
                if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
                  {
                    yycount = 1;
                    yysize = yysize0;
                    break;
                  }
                yyarg[yycount++] = yytname[yyx];
                {
                  YYPTRDIFF_T yysize1
                    = yysize + yytnamerr (YY_NULLPTR, yytname[yyx]);
                  if (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM)
                    yysize = yysize1;
                  else
                    return 2;
                }
              }
        }
    }

  switch (yycount)
    {
# define YYCASE_(N, S)                      \
      case N:                               \
        yyformat = S;                       \
      break
    default: /* Avoid compiler warnings. */
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
# undef YYCASE_
    }

  {
    /* Don't count the "%s"s in the final size, but reserve room for
       the terminator.  */
    YYPTRDIFF_T yysize1 = yysize + (yystrlen (yyformat) - 2 * yycount) + 1;
    if (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM)
      yysize = yysize1;
    else
      return 2;
  }

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return 1;
    }

  /* Avoid sprintf, as that infringes on the user's name space.
     Don't have undefined behavior even if the translation
     produced a string with the wrong number of "%s"s.  */
  {
    char *yyp = *yymsg;
    int yyi = 0;
    while ((*yyp = *yyformat) != '\0')
      if (*yyp == '%' && yyformat[1] == 's' && yyi < yycount)
        {
          yyp += yytnamerr (yyp, yyarg[yyi++]);
          yyformat += 2;
        }
      else
        {
          ++yyp;
          ++yyformat;
        }
  }
  return 0;
}
#endif /* YYERROR_VERBOSE */

/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
{
  YYUSE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yytype);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}




/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Number of syntax errors so far.  */
int yynerrs;


/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
    yy_state_fast_t yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       'yyss': related to states.
       'yyvs': related to semantic values.

       Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yy_state_t yyssa[YYINITDEPTH];
    yy_state_t *yyss;
    yy_state_t *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    YYPTRDIFF_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken = 0;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYPTRDIFF_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yyssp = yyss = yyssa;
  yyvsp = yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */
  goto yysetstate;


/*------------------------------------------------------------.
| yynewstate -- push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;


/*--------------------------------------------------------------------.
| yysetstate -- set current state (the top of the stack) to yystate.  |
`--------------------------------------------------------------------*/
yysetstate:
  YYDPRINTF ((stderr, "Entering state %d\n", yystate));
  YY_ASSERT (0 <= yystate && yystate < YYNSTATES);
  YY_IGNORE_USELESS_CAST_BEGIN
  *yyssp = YY_CAST (yy_state_t, yystate);
  YY_IGNORE_USELESS_CAST_END

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    goto yyexhaustedlab;
#else
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYPTRDIFF_T yysize = yyssp - yyss + 1;

# if defined yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        yy_state_t *yyss1 = yyss;
        YYSTYPE *yyvs1 = yyvs;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * YYSIZEOF (*yyssp),
                    &yyvs1, yysize * YYSIZEOF (*yyvsp),
                    &yystacksize);
        yyss = yyss1;
        yyvs = yyvs1;
      }
# else /* defined YYSTACK_RELOCATE */
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          goto yyexhaustedlab;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
# undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YY_IGNORE_USELESS_CAST_BEGIN
      YYDPRINTF ((stderr, "Stack size increased to %ld\n",
                  YY_CAST (long, yystacksize)));
      YY_IGNORE_USELESS_CAST_END

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }
#endif /* !defined yyoverflow && !defined YYSTACK_RELOCATE */

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
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = yylex ();
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
      if (yytable_value_is_error (yyn))
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
  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  /* Discard the shifted token.  */
  yychar = YYEMPTY;
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
| yyreduce -- do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     '$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
  case 9:
#line 31 "bison.y"
                      {
  
  Asembler::global((yyvsp[-1].string));
}
#line 1539 "bison.tab.c"
    break;

  case 10:
#line 35 "bison.y"
                      {
  
  Asembler::externSymbols((yyvsp[-1].string));
}
#line 1548 "bison.tab.c"
    break;

  case 11:
#line 39 "bison.y"
                   {
  
  Asembler::section((yyvsp[-1].string));
}
#line 1557 "bison.tab.c"
    break;

  case 12:
#line 43 "bison.y"
                    {
  
  Asembler::wordSymbolList((yyvsp[-1].string));
}
#line 1566 "bison.tab.c"
    break;

  case 13:
#line 47 "bison.y"
             {
  
  Asembler::wordNumber((yyvsp[-1].number));
}
#line 1575 "bison.tab.c"
    break;

  case 14:
#line 51 "bison.y"
             {
  
  Asembler::skip((yyvsp[-1].number));
}
#line 1584 "bison.tab.c"
    break;

  case 15:
#line 55 "bison.y"
   {
  Asembler::end();
}
#line 1592 "bison.tab.c"
    break;

  case 16:
#line 58 "bison.y"
         {
  Asembler::halt();
}
#line 1600 "bison.tab.c"
    break;

  case 17:
#line 61 "bison.y"
            {
  
  Asembler::interrupt((yyvsp[-1].number));
}
#line 1609 "bison.tab.c"
    break;

  case 18:
#line 65 "bison.y"
         {
  Asembler::iret();
}
#line 1617 "bison.tab.c"
    break;

  case 19:
#line 68 "bison.y"
             {
  
  Asembler::callNum((yyvsp[-1].number));
}
#line 1626 "bison.tab.c"
    break;

  case 20:
#line 72 "bison.y"
                {
  
  Asembler::callSymbol((yyvsp[-1].string));
}
#line 1635 "bison.tab.c"
    break;

  case 21:
#line 76 "bison.y"
                      {
  
  Asembler::callPcrelSymbol((yyvsp[-1].string));
}
#line 1644 "bison.tab.c"
    break;

  case 22:
#line 80 "bison.y"
                  {
  
  Asembler::callMemNum((yyvsp[-1].number));
}
#line 1653 "bison.tab.c"
    break;

  case 23:
#line 84 "bison.y"
                     {
  
  Asembler::callMemSymbol((yyvsp[-1].string));
}
#line 1662 "bison.tab.c"
    break;

  case 24:
#line 88 "bison.y"
                  {
  
  Asembler::callReg((yyvsp[-1].number));
}
#line 1671 "bison.tab.c"
    break;

  case 25:
#line 92 "bison.y"
                                  {
  
  Asembler::callMemReg((yyvsp[-2].number));
}
#line 1680 "bison.tab.c"
    break;

  case 26:
#line 96 "bison.y"
                                           {
  
  Asembler::callMemRegNum((yyvsp[-4].number),(yyvsp[-2].number));
}
#line 1689 "bison.tab.c"
    break;

  case 27:
#line 100 "bison.y"
                                         {
  
  Asembler::callMemRegSymbol((yyvsp[-3].number),(yyvsp[-1].string));
}
#line 1698 "bison.tab.c"
    break;

  case 28:
#line 104 "bison.y"
        {
  Asembler::ret();
}
#line 1706 "bison.tab.c"
    break;

  case 29:
#line 107 "bison.y"
            {
  
  Asembler::jmpNum((yyvsp[-1].number));
}
#line 1715 "bison.tab.c"
    break;

  case 30:
#line 111 "bison.y"
               {
  
  Asembler::jmpSymbol((yyvsp[-1].string));
}
#line 1724 "bison.tab.c"
    break;

  case 31:
#line 115 "bison.y"
                     {
  
  Asembler::jmpPcrelSymbol((yyvsp[-1].string));
}
#line 1733 "bison.tab.c"
    break;

  case 32:
#line 119 "bison.y"
                 {
  
  Asembler::jmpMemNum((yyvsp[-1].number));
}
#line 1742 "bison.tab.c"
    break;

  case 33:
#line 123 "bison.y"
                    {
  
  Asembler::jmpMemSymbol((yyvsp[-1].string));
}
#line 1751 "bison.tab.c"
    break;

  case 34:
#line 127 "bison.y"
                 {
  
  Asembler::jmpReg((yyvsp[-1].number));
}
#line 1760 "bison.tab.c"
    break;

  case 35:
#line 131 "bison.y"
                                 {
  
  Asembler::jmpMemReg((yyvsp[-2].number));
}
#line 1769 "bison.tab.c"
    break;

  case 36:
#line 135 "bison.y"
                                          {
  
  Asembler::jmpMemRegNum((yyvsp[-4].number),(yyvsp[-2].number));
}
#line 1778 "bison.tab.c"
    break;

  case 37:
#line 139 "bison.y"
                                        {
  
  Asembler::jmpMemRegSymbol((yyvsp[-3].number),(yyvsp[-1].string));
}
#line 1787 "bison.tab.c"
    break;

  case 38:
#line 143 "bison.y"
            {
  
  Asembler::jeqNum((yyvsp[-1].number));
}
#line 1796 "bison.tab.c"
    break;

  case 39:
#line 147 "bison.y"
               {
  
  Asembler::jeqSymbol((yyvsp[-1].string));
}
#line 1805 "bison.tab.c"
    break;

  case 40:
#line 151 "bison.y"
                     {
  
  Asembler::jeqPcrelSymbol((yyvsp[-1].string));
}
#line 1814 "bison.tab.c"
    break;

  case 41:
#line 155 "bison.y"
                 {
  
  Asembler::jeqMemNum((yyvsp[-1].number));
}
#line 1823 "bison.tab.c"
    break;

  case 42:
#line 159 "bison.y"
                    {
  
  Asembler::jeqMemSymbol((yyvsp[-1].string));
}
#line 1832 "bison.tab.c"
    break;

  case 43:
#line 163 "bison.y"
                 {
  
  Asembler::jeqReg((yyvsp[-1].number));
}
#line 1841 "bison.tab.c"
    break;

  case 44:
#line 167 "bison.y"
                                 {
  
  Asembler::jeqMemReg((yyvsp[-2].number));
}
#line 1850 "bison.tab.c"
    break;

  case 45:
#line 171 "bison.y"
                                          {
  
  Asembler::jeqMemRegNum((yyvsp[-4].number),(yyvsp[-2].number));
}
#line 1859 "bison.tab.c"
    break;

  case 46:
#line 175 "bison.y"
                                        {
  
  Asembler::jeqMemRegSymbol((yyvsp[-3].number),(yyvsp[-1].string));
}
#line 1868 "bison.tab.c"
    break;

  case 47:
#line 179 "bison.y"
            {
  
  Asembler::jneNum((yyvsp[-1].number));
}
#line 1877 "bison.tab.c"
    break;

  case 48:
#line 183 "bison.y"
               {
  
  Asembler::jneSymbol((yyvsp[-1].string));
}
#line 1886 "bison.tab.c"
    break;

  case 49:
#line 187 "bison.y"
                     {
  
  Asembler::jnePcrelSymbol((yyvsp[-1].string));
}
#line 1895 "bison.tab.c"
    break;

  case 50:
#line 191 "bison.y"
                 {
  
  Asembler::jneMemNum((yyvsp[-1].number));
}
#line 1904 "bison.tab.c"
    break;

  case 51:
#line 195 "bison.y"
                    {
  
  Asembler::jneMemSymbol((yyvsp[-1].string));
}
#line 1913 "bison.tab.c"
    break;

  case 52:
#line 199 "bison.y"
                 {
  
  Asembler::jneReg((yyvsp[-1].number));
}
#line 1922 "bison.tab.c"
    break;

  case 53:
#line 203 "bison.y"
                                 {
  
  Asembler::jneMemReg((yyvsp[-2].number));
}
#line 1931 "bison.tab.c"
    break;

  case 54:
#line 207 "bison.y"
                                          {
  
  Asembler::jneMemRegNum((yyvsp[-4].number),(yyvsp[-2].number));
}
#line 1940 "bison.tab.c"
    break;

  case 55:
#line 211 "bison.y"
                                        {
  
  Asembler::jneMemRegSymbol((yyvsp[-3].number),(yyvsp[-1].string));
}
#line 1949 "bison.tab.c"
    break;

  case 56:
#line 215 "bison.y"
            {
  
  Asembler::jgtNum((yyvsp[-1].number));
}
#line 1958 "bison.tab.c"
    break;

  case 57:
#line 219 "bison.y"
               {
  
  Asembler::jgtSymbol((yyvsp[-1].string));
}
#line 1967 "bison.tab.c"
    break;

  case 58:
#line 223 "bison.y"
                     {
  
  Asembler::jgtPcrelSymbol((yyvsp[-1].string));
}
#line 1976 "bison.tab.c"
    break;

  case 59:
#line 227 "bison.y"
                 {
  
  Asembler::jgtMemNum((yyvsp[-1].number));
}
#line 1985 "bison.tab.c"
    break;

  case 60:
#line 231 "bison.y"
                    {
  
  Asembler::jgtMemSymbol((yyvsp[-1].string));
}
#line 1994 "bison.tab.c"
    break;

  case 61:
#line 235 "bison.y"
                 {
  
  Asembler::jgtReg((yyvsp[-1].number));
}
#line 2003 "bison.tab.c"
    break;

  case 62:
#line 239 "bison.y"
                                 {
  
  Asembler::jgtMemReg((yyvsp[-2].number));
}
#line 2012 "bison.tab.c"
    break;

  case 63:
#line 243 "bison.y"
                                          {
  
  Asembler::jgtMemRegNum((yyvsp[-4].number),(yyvsp[-2].number));
}
#line 2021 "bison.tab.c"
    break;

  case 64:
#line 247 "bison.y"
                                        {
  
  Asembler::jgtMemRegSymbol((yyvsp[-3].number),(yyvsp[-1].string));
}
#line 2030 "bison.tab.c"
    break;

  case 65:
#line 251 "bison.y"
             {
  
  Asembler::push((yyvsp[-1].number));
}
#line 2039 "bison.tab.c"
    break;

  case 66:
#line 255 "bison.y"
            {
  
  Asembler::pop((yyvsp[-1].number));
}
#line 2048 "bison.tab.c"
    break;

  case 67:
#line 259 "bison.y"
                       {
  
  Asembler::xchg((yyvsp[-3].number),(yyvsp[-1].number));
}
#line 2057 "bison.tab.c"
    break;

  case 68:
#line 263 "bison.y"
                      {
  
  Asembler::add((yyvsp[-3].number),(yyvsp[-1].number));
}
#line 2066 "bison.tab.c"
    break;

  case 69:
#line 267 "bison.y"
                      {
  
  Asembler::sub((yyvsp[-3].number),(yyvsp[-1].number));
}
#line 2075 "bison.tab.c"
    break;

  case 70:
#line 271 "bison.y"
                      {
  
  Asembler::mul((yyvsp[-3].number),(yyvsp[-1].number));
}
#line 2084 "bison.tab.c"
    break;

  case 71:
#line 275 "bison.y"
                      {
  
  Asembler::div((yyvsp[-3].number),(yyvsp[-1].number));
}
#line 2093 "bison.tab.c"
    break;

  case 72:
#line 279 "bison.y"
                      {
  
  Asembler::cmp((yyvsp[-3].number),(yyvsp[-1].number));
}
#line 2102 "bison.tab.c"
    break;

  case 73:
#line 283 "bison.y"
            {
  
  Asembler::notReg((yyvsp[-1].number));
}
#line 2111 "bison.tab.c"
    break;

  case 74:
#line 287 "bison.y"
                      { 
  
  Asembler::andReg((yyvsp[-3].number),(yyvsp[-1].number));
}
#line 2120 "bison.tab.c"
    break;

  case 75:
#line 291 "bison.y"
                     {
  
  Asembler::orReg((yyvsp[-3].number),(yyvsp[-1].number));
}
#line 2129 "bison.tab.c"
    break;

  case 76:
#line 295 "bison.y"
                      {
  
  Asembler::xorReg((yyvsp[-3].number),(yyvsp[-1].number));
}
#line 2138 "bison.tab.c"
    break;

  case 77:
#line 299 "bison.y"
                       {
  
  Asembler::test((yyvsp[-3].number),(yyvsp[-1].number));
}
#line 2147 "bison.tab.c"
    break;

  case 78:
#line 303 "bison.y"
                      {
  
  Asembler::shl((yyvsp[-3].number),(yyvsp[-1].number));
}
#line 2156 "bison.tab.c"
    break;

  case 79:
#line 307 "bison.y"
                      {
  
  Asembler::shr((yyvsp[-3].number),(yyvsp[-1].number));
}
#line 2165 "bison.tab.c"
    break;

  case 80:
#line 311 "bison.y"
                          {
  
  Asembler::ldrValNum((yyvsp[-4].number),(yyvsp[-1].number));
}
#line 2174 "bison.tab.c"
    break;

  case 81:
#line 315 "bison.y"
                             {
  
  Asembler::ldrValSymbol((yyvsp[-4].number),(yyvsp[-1].string));
}
#line 2183 "bison.tab.c"
    break;

  case 82:
#line 319 "bison.y"
                      {
  
  Asembler::ldrMemNum((yyvsp[-3].number),(yyvsp[-1].number));
}
#line 2192 "bison.tab.c"
    break;

  case 83:
#line 323 "bison.y"
                         {
  
  Asembler::ldrMemSymbol((yyvsp[-3].number),(yyvsp[-1].string));
}
#line 2201 "bison.tab.c"
    break;

  case 84:
#line 327 "bison.y"
                               {
  
  Asembler::ldrPcrelSymbol((yyvsp[-4].number),(yyvsp[-1].string));
}
#line 2210 "bison.tab.c"
    break;

  case 85:
#line 331 "bison.y"
                      {
  
  Asembler::ldrReg((yyvsp[-3].number),(yyvsp[-1].number));
}
#line 2219 "bison.tab.c"
    break;

  case 86:
#line 335 "bison.y"
                                      {
  
  Asembler::ldrMemReg((yyvsp[-5].number),(yyvsp[-2].number));
}
#line 2228 "bison.tab.c"
    break;

  case 87:
#line 339 "bison.y"
                                          {
  
  Asembler::ldrMemRegNum((yyvsp[-6].number),(yyvsp[-3].number),(yyvsp[-1].number));
}
#line 2237 "bison.tab.c"
    break;

  case 88:
#line 343 "bison.y"
                                             {
  
  Asembler::ldrMemRegSymbol((yyvsp[-6].number),(yyvsp[-3].number),(yyvsp[-1].string));
}
#line 2246 "bison.tab.c"
    break;

  case 89:
#line 347 "bison.y"
                      {
  
  Asembler::strMemNum((yyvsp[-3].number),(yyvsp[-1].number));
}
#line 2255 "bison.tab.c"
    break;

  case 90:
#line 351 "bison.y"
                         {
  
  Asembler::strMemSymbol((yyvsp[-3].number),(yyvsp[-1].string));
}
#line 2264 "bison.tab.c"
    break;

  case 91:
#line 355 "bison.y"
                               {
  
  Asembler::strPcrelSymbol((yyvsp[-4].number),(yyvsp[-1].string));
}
#line 2273 "bison.tab.c"
    break;

  case 92:
#line 359 "bison.y"
                      {
  
  Asembler::strReg((yyvsp[-3].number),(yyvsp[-1].number));
}
#line 2282 "bison.tab.c"
    break;

  case 93:
#line 363 "bison.y"
                                      {
  
  Asembler::strMemReg((yyvsp[-5].number),(yyvsp[-2].number));
}
#line 2291 "bison.tab.c"
    break;

  case 94:
#line 367 "bison.y"
                                          {
  
  Asembler::strMemRegNum((yyvsp[-6].number),(yyvsp[-3].number),(yyvsp[-1].number));
}
#line 2300 "bison.tab.c"
    break;

  case 95:
#line 371 "bison.y"
                                             {
  
  Asembler::strMemRegSymbol((yyvsp[-6].number),(yyvsp[-3].number),(yyvsp[-1].string));
}
#line 2309 "bison.tab.c"
    break;

  case 96:
#line 376 "bison.y"
             {
Asembler::label((yyvsp[-1].string));
}
#line 2317 "bison.tab.c"
    break;

  case 97:
#line 379 "bison.y"
                 {
Asembler::label((yyvsp[-2].string));
}
#line 2325 "bison.tab.c"
    break;

  case 98:
#line 383 "bison.y"
      {(yyval.string)=(yyvsp[0].string);}
#line 2331 "bison.tab.c"
    break;

  case 99:
#line 383 "bison.y"
                                       {strcpy((yyval.string),(yyvsp[-2].string));strcat((yyval.string),(yyvsp[-1].string));strcat((yyval.string),(yyvsp[0].string));}
#line 2337 "bison.tab.c"
    break;


#line 2341 "bison.tab.c"

      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */
  {
    const int yylhs = yyr1[yyn] - YYNTOKENS;
    const int yyi = yypgoto[yylhs] + *yyssp;
    yystate = (0 <= yyi && yyi <= YYLAST && yycheck[yyi] == *yyssp
               ? yytable[yyi]
               : yydefgoto[yylhs]);
  }

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYEMPTY : YYTRANSLATE (yychar);

  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
# define YYSYNTAX_ERROR yysyntax_error (&yymsg_alloc, &yymsg, \
                                        yyssp, yytoken)
      {
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        yysyntax_error_status = YYSYNTAX_ERROR;
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == 1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = YY_CAST (char *, YYSTACK_ALLOC (YY_CAST (YYSIZE_T, yymsg_alloc)));
            if (!yymsg)
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = 2;
              }
            else
              {
                yysyntax_error_status = YYSYNTAX_ERROR;
                yymsgp = yymsg;
              }
          }
        yyerror (yymsgp);
        if (yysyntax_error_status == 2)
          goto yyexhaustedlab;
      }
# undef YYSYNTAX_ERROR
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
  /* Pacify compilers when the user code never invokes YYERROR and the
     label yyerrorlab therefore never appears in user code.  */
  if (0)
    YYERROR;

  /* Do not reclaim the symbols of the rule whose action triggered
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
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
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

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


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


#if !defined yyoverflow || YYERROR_VERBOSE
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif


/*-----------------------------------------------------.
| yyreturn -- parsing is finished, return the result.  |
`-----------------------------------------------------*/
yyreturn:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  yystos[+*yyssp], yyvsp);
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
  return yyresult;
}
#line 384 "bison.y"

void yyerror(const char *s){
  std::cout<<"ERROR"<<std::endl;
  exit(-1);
}
