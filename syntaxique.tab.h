
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

/* Line 1676 of yacc.c  */
#line 47 "syntaxique.y"

    int    entier;
    float  reel;
    char  *chaine;
    struct {
        char type[20];
        char val[40];
    } noeud;



/* Line 1676 of yacc.c  */
#line 119 "syntaxique.tab.h"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif

extern YYSTYPE yylval;


