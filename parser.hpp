/* A Bison parser, made by GNU Bison 3.5.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2019 Free Software Foundation,
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

#ifndef YY_YY_PARSER_HPP_INCLUDED
# define YY_YY_PARSER_HPP_INCLUDED
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
    INTEGER = 258,
    BOOLEAN = 259,
    DOT = 260,
    WHILE_T = 261,
    IF = 262,
    ELSE = 263,
    DO = 264,
    O_PAREN = 265,
    C_PAREN = 266,
    O_BRAC = 267,
    C_BRAC = 268,
    PRINT = 269,
    RETURN = 270,
    TRUE = 271,
    FALSE = 272,
    NEW = 273,
    EXTENDS_T = 274,
    NUM = 275,
    ID = 276,
    SEMICOLON = 277,
    COMMA = 278,
    NONE = 279,
    ASSIGN = 280,
    ARROW = 281,
    OR = 282,
    AND = 283,
    GREATER = 284,
    GREATER_EQUAL = 285,
    EQUALS = 286,
    PLUS = 287,
    MINUS = 288,
    MULT = 289,
    DIV = 290,
    NOT = 291
  };
#endif

/* Value type.  */


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_PARSER_HPP_INCLUDED  */
