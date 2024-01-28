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

#ifndef YY_YY_GPL_TAB_H_INCLUDED
# define YY_YY_GPL_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif
/* "%code requires" blocks.  */
#line 3 "gpl.y"

  #include <string>
  class Expression;
  class Variable;
  struct Parameter;
  class Statement;
  #ifndef P1
    #include "types_and_ops.h"  //include in all projects except the first
  #endif
  #ifdef GRAPHICS
    #include "Window.h"
  #endif

#line 62 "gpl.tab.h"

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    T_INT = 258,
    T_DOUBLE = 259,
    T_STRING = 260,
    T_TRIANGLE = 261,
    T_PIXMAP = 262,
    T_CIRCLE = 263,
    T_RECTANGLE = 264,
    T_TEXTBOX = 265,
    T_FORWARD = 266,
    T_INITIALIZATION = 267,
    T_TERMINATION = 268,
    T_ON = 269,
    T_ANIMATION = 270,
    T_IF = 271,
    T_FOR = 272,
    T_ELSE = 273,
    T_EXIT = 274,
    T_PRINT = 275,
    T_TRUE = 276,
    T_FALSE = 277,
    T_SPACE = 278,
    T_LEFTARROW = 279,
    T_RIGHTARROW = 280,
    T_UPARROW = 281,
    T_DOWNARROW = 282,
    T_LEFTMOUSE_DOWN = 283,
    T_MIDDLEMOUSE_DOWN = 284,
    T_RIGHTMOUSE_DOWN = 285,
    T_LEFTMOUSE_UP = 286,
    T_MIDDLEMOUSE_UP = 287,
    T_RIGHTMOUSE_UP = 288,
    T_MOUSE_MOVE = 289,
    T_MOUSE_DRAG = 290,
    T_F1 = 291,
    T_AKEY = 292,
    T_SKEY = 293,
    T_DKEY = 294,
    T_FKEY = 295,
    T_HKEY = 296,
    T_JKEY = 297,
    T_KKEY = 298,
    T_LKEY = 299,
    T_WKEY = 300,
    T_ZKEY = 301,
    T_LPAREN = 302,
    T_RPAREN = 303,
    T_LBRACE = 304,
    T_RBRACE = 305,
    T_LBRACKET = 306,
    T_RBRACKET = 307,
    T_SEMIC = 308,
    T_COMMA = 309,
    T_PERIOD = 310,
    T_ASSIGN = 311,
    T_PLUS_ASSIGN = 312,
    T_MINUS_ASSIGN = 313,
    T_PLUS_PLUS = 314,
    T_MINUS_MINUS = 315,
    T_SIN = 316,
    T_COS = 317,
    T_TAN = 318,
    T_ASIN = 319,
    T_ACOS = 320,
    T_ATAN = 321,
    T_SQRT = 322,
    T_ABS = 323,
    T_FLOOR = 324,
    T_RANDOM = 325,
    T_TOUCHES = 326,
    T_NEAR = 327,
    T_MULTIPLY = 328,
    T_DIVIDE = 329,
    T_PLUS = 330,
    T_MINUS = 331,
    T_MOD = 332,
    T_LESS = 333,
    T_GREATER = 334,
    T_LESS_EQUAL = 335,
    T_GREATER_EQUAL = 336,
    T_EQUAL = 337,
    T_NOT_EQUAL = 338,
    T_NOT = 339,
    T_AND = 340,
    T_OR = 341,
    T_INT_CONSTANT = 342,
    T_DOUBLE_CONSTANT = 343,
    T_STRING_CONSTANT = 344,
    T_ID = 345,
    T_ERROR = 346,
    UNARY_OPS = 347,
    IF_NO_ELSE = 348
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 34 "gpl.y"

 int            union_int;
 std::string*   union_string;  // MUST be a pointer to a string
 double         union_double;

#line 173 "gpl.tab.h"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_GPL_TAB_H_INCLUDED  */
