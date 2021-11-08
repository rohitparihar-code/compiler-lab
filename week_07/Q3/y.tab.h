
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
     HEADER = 258,
     DIGIT = 259,
     ENTER = 260,
     HEADER1 = 261,
     MAIN = 262,
     OPENC = 263,
     CLOSEC = 264,
     INT = 265,
     FLOAT = 266,
     ID = 267,
     SPACE = 268,
     COMMA = 269,
     SEMICOLON = 270,
     OPENB = 271,
     CLOSEB = 272,
     EQUAL = 273,
     GT = 274,
     LT = 275,
     FOR = 276,
     WHILE = 277,
     PLUS = 278,
     MINUS = 279,
     MULTIPLY = 280,
     IF = 281,
     ERROR = 282,
     ELSE = 283
   };
#endif
/* Tokens.  */
#define HEADER 258
#define DIGIT 259
#define ENTER 260
#define HEADER1 261
#define MAIN 262
#define OPENC 263
#define CLOSEC 264
#define INT 265
#define FLOAT 266
#define ID 267
#define SPACE 268
#define COMMA 269
#define SEMICOLON 270
#define OPENB 271
#define CLOSEB 272
#define EQUAL 273
#define GT 274
#define LT 275
#define FOR 276
#define WHILE 277
#define PLUS 278
#define MINUS 279
#define MULTIPLY 280
#define IF 281
#define ERROR 282
#define ELSE 283




#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef int YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif

extern YYSTYPE yylval;


