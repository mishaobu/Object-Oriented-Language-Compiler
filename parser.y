%{
    #include <stdio.h>
    #include <stdlib.h>
    #include <iostream>

    #include "ast.hpp"
    
    #define YYDEBUG 1
    #define YYINITDEPTH 10000

    int yylex(void);
    void yyerror(const char *);
    
    extern ASTNode* astRoot;
%}

%error-verbose

/* WRITEME: Copy your token and precedence speciers from Project 3 here */

%token INTEGER BOOLEAN DOT
%token WHILE_T
%token IF ELSE DO  
%token O_PAREN C_PAREN O_BRAC C_BRAC
%token PRINT RETURN TRUE FALSE NEW EXTENDS_T NUM ID SEMICOLON COMMA NONE ASSIGN ARROW
%token OR AND GREATER GREATER_EQUAL EQUALS PLUS MINUS MULT DIV NOT

%left OR AND
%left GREATER GREATER_EQUAL EQUALS 
%left PLUS MINUS
%left MULT DIV
%right NOT  

/* WRITEME: Specify types for all nonterminals and necessary terminals here */

%type <program_ptr> Start

%type <base_char_ptr> ID
%type <base_int> NUM
%type <class_list_ptr> class
%type <class_ptr> class1
%type <declaration_list_ptr> members declarations
%type <expression_list_ptr> arguments arguments1
%type <type_ptr> type
%type <identifier_ptr> extends

%type <methodcall_ptr> methodcall
%type <method_list_ptr> methods
%type <method_ptr> method
%type <returnstatement_ptr> return

%type <print_ptr> print
%type <dowhile_ptr> do_while
%type <while_ptr> while_loop
%type <ifelse_ptr> if_else
%type <assignment_ptr> assignment

%type <methodbody_ptr> body
%type <parameter_list_ptr> parameters parameters1

%type <statement_list_ptr> else statements block
%type <statement_ptr> statement
%type <identifier_list_ptr> id_list 
       

%type <expression_ptr> expression

%%

/* WRITEME: This rule is a placeholder. Replace it with your grammar
            rules from Project 3 */

Start : class    { $$ = new ProgramNode($1); astRoot = $$;} 
      ;

class : class1 class    { $$ = $2; $$->push_front($1); }
      | class1          { $$ = new std::list<ClassNode*>(); $$->push_front($1); }
      ; 
      

class1 : ID extends O_BRAC members methods C_BRAC { $$ = new ClassNode(new IdentifierNode($1), $2, $4, $5); }
      |  ID extends O_BRAC members C_BRAC { $$ = new ClassNode(new IdentifierNode($1), $2, $4, NULL); }
      |  ID extends O_BRAC methods C_BRAC { $$ = new ClassNode(new IdentifierNode($1), $2, NULL, $4); }
      |  ID extends O_BRAC C_BRAC { $$ = new ClassNode(new IdentifierNode($1), $2, NULL, NULL); }
      ;


members : members type ID SEMICOLON{   $$ = $1;
                                      std::list<IdentifierNode*>* t = new std::list<IdentifierNode*>(); 
                                      t->push_back(new IdentifierNode($3));
                                      $$->push_back(new DeclarationNode($2, t)) ;    }
          
      | type ID  SEMICOLON                 { $$ = new std::list<DeclarationNode*>(); 
                                    std::list<IdentifierNode*>* t = new std::list<IdentifierNode*>(); 
                                    t->push_back(new IdentifierNode($2));
                                    $$->push_back(new DeclarationNode($1, t));  } 
      ;


extends : EXTENDS_T ID { $$ = new IdentifierNode($2); } 
      | { $$ = NULL; } 
      ;



methods : method methods { $$ = $2; $$->push_front($1); } 
      | { $$ = new std::list<MethodNode*>(); } 
      ;

method : ID O_PAREN parameters C_PAREN ARROW type O_BRAC body C_BRAC
          { $$ = new MethodNode(new IdentifierNode($1), $3, $6, $8); } 
    ;


parameters : type ID parameters1 { $$ = $3; $$->push_front(new ParameterNode($1, new IdentifierNode($2))); }
    | { $$ = NULL; } 
    ;

parameters1 : COMMA type ID parameters1 
          { $$ = $4; $$->push_front(new ParameterNode($2, new IdentifierNode($3))); } 
    | { $$ = new std::list<ParameterNode*>(); }
    ;
    

body : declarations statements return { $$ = new MethodBodyNode($1, $2, $3); }
      | statements return {$$ = new MethodBodyNode(new std::list<DeclarationNode*>(), $1, $2); } 
      ;    


declarations : declarations type id_list { $$ = $1; $$->push_back(new DeclarationNode($2, $3)); }
    | type id_list { $$ = new std::list<DeclarationNode*>(); $$->push_back(new DeclarationNode($1, $2)); }
    ;
    

id_list : ID COMMA id_list { $$ = $3; $$->push_front(new IdentifierNode($1)); }
      | ID SEMICOLON { $$ = new std::list<IdentifierNode*>(); $$->push_front(new IdentifierNode($1)); } 
      ;

    
return : RETURN expression SEMICOLON { $$ = new ReturnStatementNode($2); } 
    | %empty { $$ = NULL; };
    ;

statements : statement statements { $$ = $2; $$->push_front($1); }
    | %empty {$$ = new std::list<StatementNode*>(); }
    ;
    
statement : assignment { $$ = $1; } 
		| methodcall SEMICOLON { $$ = new CallNode($1); }
		| if_else { $$ = $1; }
		| while_loop { $$ = $1; }
		| do_while { $$ = $1; }
		| print { $$ = $1; }
    ;
    
   
  
assignment : ID ASSIGN expression SEMICOLON { $$ = new AssignmentNode(new IdentifierNode($1), NULL, $3); }
    |  ID DOT ID ASSIGN expression SEMICOLON { $$ = new AssignmentNode(new IdentifierNode($1), new IdentifierNode($3), $5); }
    ;
    
    
if_else : IF expression O_BRAC block C_BRAC else { $$ = new IfElseNode($2, $4, $6); }
    ; 
    
else : ELSE O_BRAC block C_BRAC { $$ = $3; }
    | { $$ = NULL; } 
    ;

while_loop : WHILE_T expression O_BRAC block C_BRAC  { $$ = new WhileNode($2, $4); }
    ;
    
do_while : DO O_BRAC block C_BRAC WHILE_T O_PAREN expression C_PAREN SEMICOLON
        { $$ = new DoWhileNode($3, $7); }
    ;

print : PRINT expression SEMICOLON { $$ = new PrintNode($2); }
    ;

block : statement statements { $$ = $2; $$->push_front($1); } 
    ;
    
expression : expression PLUS expression { $$ = new PlusNode($1, $3); };
    |	expression MINUS expression { $$ = new MinusNode($1, $3); } 
    |	expression MULT expression { $$ = new TimesNode($1, $3); } 
    |	expression DIV expression { $$ = new DivideNode($1, $3); } 
    |	expression GREATER expression { $$ = new GreaterNode($1, $3); } 
    |	expression GREATER_EQUAL expression{ $$ = new GreaterEqualNode($1, $3); } 
    |	expression EQUALS expression { $$ = new EqualNode($1, $3); } 
    |	expression AND expression { $$ = new AndNode($1, $3); }
    |	expression OR expression { $$ = new OrNode($1, $3); }
    |	NOT expression  %prec NOT { $$ = new NotNode($2); }
    |	MINUS expression  %prec NOT  { $$ = new NegationNode($2); }
    |	ID { $$ = new VariableNode(new IdentifierNode($1)); } 
    |	ID DOT ID   { $$ = new MemberAccessNode(new IdentifierNode($1), new IdentifierNode($3)); }
    |	methodcall{ $$ = $1; } 
    |	O_PAREN expression C_PAREN { $$ = $2; }
    |	NUM { $$ = new IntegerLiteralNode(new IntegerNode($1)); } 
    |	TRUE { $$ = new BooleanLiteralNode(new IntegerNode(1)); } /* note not $1 */
    |	FALSE { $$ = new BooleanLiteralNode(new IntegerNode(0)); }
    |	NEW ID { $$ = new NewNode(new IdentifierNode($2), NULL); }
    |	NEW ID O_PAREN arguments C_PAREN { $$ = new NewNode(new IdentifierNode($2), $4); } 
    ;
    
methodcall : ID O_PAREN arguments C_PAREN { $$ = new MethodCallNode(new IdentifierNode($1), NULL, $3); }
    | ID DOT ID O_PAREN arguments C_PAREN  { $$ = new MethodCallNode(new IdentifierNode($1), new IdentifierNode($3), $5); } 
    ;
    
arguments : arguments1 { $$ = $1; }
    | { $$ = NULL; } 
    ;

arguments1 : arguments1 COMMA expression { $$ = $1; $$->push_back($3); }
    | expression { $$ = new std::list<ExpressionNode*>(); $$->push_back($1); } 
    ;
    
type : INTEGER { $$ = new IntegerTypeNode(); }
    | BOOLEAN { $$ = new BooleanTypeNode(); }
    | ID { $$ = new ObjectTypeNode(new IdentifierNode($1)); }
    | NONE { $$ = new NoneNode(); } 
    ;


%%

extern int yylineno;

void yyerror(const char *s) {
  fprintf(stderr, "%s at line %d\n", s, yylineno);
  exit(0);
}
