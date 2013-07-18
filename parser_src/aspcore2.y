%{
//////////////////////////////////////////////////////////////////////////////
// AspCore2::getInstance().y

//////////////////////////////////////////////////////////////////////////////
/*
This file is part of the ASPCOMP2013 ASP-Core-2 validator (validator in the following)

    The validator is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    The validator is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with the validator.  If not, see <http://www.gnu.org/licenses/>.
*/

%}
%error-verbose
%union {
    char* string;
    Variable* variable;
    Term* term;
    Terms* terms;
    Atom* atom;
    Literal* literal;
    Literals* literals;
    Rule* rule;
}

%type <rule> rule
%type <literals> naf_literals conjunction body
%type <literal> naf_literal naf_literal_aggregate
%type <atom> atom classic_literal disjunction head
%type <term> term term_
%type <terms> terms
%type <variable> variable_term
%type <string> identifier

%token <string> SYMBOLIC_CONSTANT NUMBER VARIABLE STRING

%token ERROR NEWLINE   

%token DOT SEMICOLON COLON CONS QUERY_MARK

%token PLUS TIMES SLASH

%token ANON_VAR

%token PARAM_OPEN PARAM_CLOSE
%token SQUARE_OPEN SQUARE_CLOSE
%token CURLY_OPEN CURLY_CLOSE

%token EQUAL UNEQUAL LESS GREATER LESS_OR_EQ GREATER_OR_EQ

%token DASH COMMA NAF AT WCONS

%token VEL AGGR_COUNT AGGR_MAX AGGR_MIN AGGR_SUM

%left PLUS DASH
%left TIMES SLASH

%start program
%%

HEAD_SEPARATOR  : VEL;

program
    : 
    | rules
    | rules query
    | error { AspCore2::getInstance().onError("Generic error"); }
    ;

rules
    : rules rule { AspCore2::getInstance().addRule($2); }
    | rule { AspCore2::getInstance().addRule($1); }
    ;

rule
    : head DOT { $$ = AspCore2::getInstance().onRule($1); }
    | head CONS DOT { $$ = AspCore2::getInstance().onRule($1); }
    | head CONS body DOT { $$ = AspCore2::getInstance().onRule($1, $3); }
    | CONS body DOT /*constraint*/ { $$ = AspCore2::getInstance().onRule($2); }
    | WCONS body DOT weight_at_levels {}
    ;

head
    : disjunction { $$ = $1; }
    | choice_atom {}
    ;       

body
    : conjunction { $$ = $1; }
    ;

weight_at_levels : SQUARE_OPEN term SQUARE_CLOSE {}
         | SQUARE_OPEN term levels_and_terms SQUARE_CLOSE {}
                 ;

levels_and_terms : AT term {} 
                 | AT term COMMA terms {}
         | COMMA terms {} 
             ;
          
disjunction
    : classic_literal { $$ = $1; }
    | disjunction HEAD_SEPARATOR classic_literal { $$ = $3; }
    ;

conjunction
    : naf_literal_aggregate { $$ = AspCore2::getInstance().onNafLiterals($1); }
    | conjunction COMMA naf_literal_aggregate { $$ = AspCore2::getInstance().onNafLiterals($1, $3); }
    ;

choice_atom : term binop CURLY_OPEN choice_elements CURLY_CLOSE binop term {}
        | term binop CURLY_OPEN choice_elements CURLY_CLOSE {}    
        | CURLY_OPEN choice_elements CURLY_CLOSE {}    
        | CURLY_OPEN choice_elements CURLY_CLOSE binop term {}        
        ;

choice_elements : choice_elements SEMICOLON choice_element {}
        | choice_element {}
                ;

choice_element : atom {}
               | atom COLON naf_literals {}
               ;

naf_literals
    : naf_literal { $$ = AspCore2::getInstance().onNafLiterals($1); }
    | naf_literals COMMA naf_literal { $$ = AspCore2::getInstance().onNafLiterals($1, $3); }
    ;    
          
naf_literal
    : classic_literal { $$ = AspCore2::getInstance().onNafLiteral($1, true); }
    | NAF classic_literal { $$ = AspCore2::getInstance().onNafLiteral($2, false); }
    | builtin_atom {}
    ;

naf_literal_aggregate
    : naf_literal { $$ = $1; }
    | aggregate_atom {}
    | NAF aggregate_atom {}
    ;      

classic_literal
    : atom { $$ = $1; }
    | DASH atom { $$ = $2; }
    ;  

atom
    : identifier { $$ = AspCore2::getInstance().onAtom($1); }
    | identifier PARAM_OPEN terms PARAM_CLOSE { $$ = AspCore2::getInstance().onAtom($1, $3); }
    | identifier PARAM_OPEN PARAM_CLOSE { $$ = AspCore2::getInstance().onAtom($1); }
    ;              
         
terms
    : term { $$ = AspCore2::getInstance().onTerms($1); }
    | terms COMMA term { $$ = AspCore2::getInstance().onTerms($1, $3); }
    ;

basic_terms : basic_term {}
         | basic_terms COMMA basic_term    {}
         ;



builtin_atom    : term binop term {}
                ;

compareop : EQUAL         {} 
          | UNEQUAL       {}
          ;       
         
binop    : compareop     {} 
         | leftwardop        {}
         | rightwardop       {}
         ;       
         
arithop   : PLUS     {} 
          | DASH    {}
          | TIMES    {}
          | SLASH      {}
          ;      

term_ 
    : identifier { $$ = AspCore2::getInstance().onTerm($1); }
    | NUMBER { $$ = AspCore2::getInstance().onTerm($1); }
    | ANON_VAR { $$ = AspCore2::getInstance().onTerm("_"); }
    | identifier PARAM_OPEN terms PARAM_CLOSE { $$ = AspCore2::getInstance().onTerm($1, $3); }
    | PARAM_OPEN term PARAM_CLOSE { $$ = $2; }
    | DASH term { $$ = AspCore2::getInstance().onTermDash($2); }
    ;

term
    : term_ { $$ = $1; }
    | term arithop term_ { $$ = AspCore2::getInstance().onTerm($1, $3); }
    ;        

basic_term : ground_term {}
       | variable_term {}
       ;

ground_term 
    : SYMBOLIC_CONSTANT 
    | STRING
    | NUMBER
    | DASH NUMBER
    ;

variable_term 
    : VARIABLE { $$ = AspCore2::getInstance().onVariableTerm($1); }
    | ANON_VAR { $$ = AspCore2::getInstance().onVariableTerm(); }
    ;
         
identifier
    : SYMBOLIC_CONSTANT { $$ = $1; }
    | STRING { $$ = $1; }
    | VARIABLE { $$ = $1; }
    ;
                
query     : atom QUERY_MARK {}
          ; 

compare_aggregate : term compareop aggregate {}
                  | aggregate compareop term {}            
                  ;

leftward_left_aggregate  : term leftwardop aggregate {}
                         ;
left_aggregate : leftward_left_aggregate
               | rightward_left_aggregate {}
               ;

rightward_left_aggregate  : term rightwardop aggregate {}
                          ;
                          
right_aggregate : aggregate leftwardop term {}
                |  aggregate rightwardop term {}
                ;

aggregate_atom   : left_aggregate {}
            | right_aggregate {}
            | compare_aggregate {}
            | leftward_left_aggregate leftwardop term {}
            | rightward_left_aggregate rightwardop term {}
            ;   

leftwardop : LESS {}
       | LESS_OR_EQ {}
       ;    

rightwardop : GREATER {}
        | GREATER_OR_EQ {}
        ;           
            
aggregate  : aggregate_function CURLY_OPEN aggregate_elements CURLY_CLOSE {}
                ;

aggregate_elements : aggregate_elements SEMICOLON aggregate_element {}
           | aggregate_element {}
           ;
        
            
aggregate_element    : basic_terms COLON naf_literals {}
                    ;

aggregate_function  : AGGR_COUNT {}
                    | AGGR_MAX {}
                    | AGGR_MIN {}
                    | AGGR_SUM {}
                    ;   


%%

// Local Variables:
// mode: c++
// End:
