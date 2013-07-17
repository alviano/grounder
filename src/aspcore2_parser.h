/* A Bison parser, made by GNU Bison 2.7.12-4996.  */

/* Bison interface for Yacc-like parsers in C
   
      Copyright (C) 1984, 1989-1990, 2000-2013 Free Software Foundation, Inc.
   
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

#ifndef YY_YY_PARSER_SRC_ASPCORE2_PARSER_H_INCLUDED
# define YY_YY_PARSER_SRC_ASPCORE2_PARSER_H_INCLUDED
/* Enabling traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     SYMBOLIC_CONSTANT = 258,
     NUMBER = 259,
     VARIABLE = 260,
     STRING = 261,
     ERROR = 262,
     NEWLINE = 263,
     DOT = 264,
     SEMICOLON = 265,
     COLON = 266,
     CONS = 267,
     QUERY_MARK = 268,
     PLUS = 269,
     TIMES = 270,
     SLASH = 271,
     ANON_VAR = 272,
     PARAM_OPEN = 273,
     PARAM_CLOSE = 274,
     SQUARE_OPEN = 275,
     SQUARE_CLOSE = 276,
     CURLY_OPEN = 277,
     CURLY_CLOSE = 278,
     EQUAL = 279,
     UNEQUAL = 280,
     LESS = 281,
     GREATER = 282,
     LESS_OR_EQ = 283,
     GREATER_OR_EQ = 284,
     DASH = 285,
     COMMA = 286,
     NAF = 287,
     AT = 288,
     WCONS = 289,
     VEL = 290,
     AGGR_COUNT = 291,
     AGGR_MAX = 292,
     AGGR_MIN = 293,
     AGGR_SUM = 294
   };
#endif
/* Tokens.  */
#define SYMBOLIC_CONSTANT 258
#define NUMBER 259
#define VARIABLE 260
#define STRING 261
#define ERROR 262
#define NEWLINE 263
#define DOT 264
#define SEMICOLON 265
#define COLON 266
#define CONS 267
#define QUERY_MARK 268
#define PLUS 269
#define TIMES 270
#define SLASH 271
#define ANON_VAR 272
#define PARAM_OPEN 273
#define PARAM_CLOSE 274
#define SQUARE_OPEN 275
#define SQUARE_CLOSE 276
#define CURLY_OPEN 277
#define CURLY_CLOSE 278
#define EQUAL 279
#define UNEQUAL 280
#define LESS 281
#define GREATER 282
#define LESS_OR_EQ 283
#define GREATER_OR_EQ 284
#define DASH 285
#define COMMA 286
#define NAF 287
#define AT 288
#define WCONS 289
#define VEL 290
#define AGGR_COUNT 291
#define AGGR_MAX 292
#define AGGR_MIN 293
#define AGGR_SUM 294



#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
{
/* Line 2053 of yacc.c  */
#line 27 "../parser_src/aspcore2.y"

    char* string;
    Variable* variable;
    Term* term;
    Terms* terms;
    Atom* atom;
    Literal* literal;
    Literals* literals;
    Rule* rule;


/* Line 2053 of yacc.c  */
#line 147 "../parser_src/aspcore2_parser.h"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif

extern YYSTYPE yylval;

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

#endif /* !YY_YY_PARSER_SRC_ASPCORE2_PARSER_H_INCLUDED  */
