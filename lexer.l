%option yylineno
%pointer

%{
    #include <stdlib.h>
    #include <errno.h>
    #include <limits.h>
    #include "ast.hpp"
    #include "parser.hpp"
    void yyerror(const char *);
%}

/* WRITEME: Copy any definitions and start conditions from Project 3 here */

%x C_COMMENT

alpha [a-zA-Z]
digit [0-9]

%%

[ \t] ;
[ \n] ;

"->" return ARROW; 

"=" return ASSIGN;
"-" return MINUS;
"*" return MULT;
"/" return DIV;
"+" return PLUS;

">=" return GREATER_EQUAL;
">" return GREATER;

"." return DOT;
"," return COMMA;
";" return SEMICOLON;
"(" return O_PAREN;
")" return C_PAREN;
"{" return O_BRAC;
"}" return C_BRAC;

"not" return NOT;
"and" return AND;
"or" return OR;
"equals" return EQUALS;
"true" return TRUE;
"false" return FALSE;
"new" return NEW;
"print" return PRINT;
"return" return RETURN;
"integer" return INTEGER;
"boolean" return BOOLEAN;
"do" return DO;
"extends" return EXTENDS_T;
"if" return IF;
"else" return ELSE;
"while" { return WHILE_T; } 
"none" {return NONE; } 


{digit}+  { yylval.base_int = std::atoi(yytext); return NUM; } 
{alpha}({alpha}|{digit})* { yylval.base_char_ptr = strdup(yytext); return ID; }


"/*"            { BEGIN(C_COMMENT); }
<C_COMMENT>"*/" { BEGIN(INITIAL); }
<C_COMMENT>[ \t\n]   { }
<C_COMMENT><<EOF>> { yyerror("dangling comment");}
<C_COMMENT>.    { }



.          { yyerror("invalid character"); }


%%

int yywrap(void) {
  return 1;
}
