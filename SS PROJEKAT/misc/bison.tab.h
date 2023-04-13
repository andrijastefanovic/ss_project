/* A Bison parser, made by GNU Bison 3.5.1.  */

/* Bison interface for Yacc-like parsers in C

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

/* Undocumented macros, especially those whose name start with YY_,
   are private implementation details.  Do not rely on them.  */

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

#line 109 "bison.tab.h"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_BISON_TAB_H_INCLUDED  */
