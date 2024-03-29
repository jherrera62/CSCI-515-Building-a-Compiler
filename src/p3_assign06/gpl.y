// Mon Apr 27 16:03:16 PDT 2020
// bison syntax indicating C++ declarations required by both the parser and scanner
%code requires {
    #include <cassert>
    //#include "Scope_manager.h"
    #include "Constant.h"
    using namespace GPL;
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
  #include "Variable.h"
}

// bison syntax to indicate the beginning of a C/C++ code section
%{

extern int yylex();  // prototype of function generated by flex
extern int yyerror(const char *); // used to print errors
extern int line_count;            // current line in the input; from record.l

#include "error.h"      // class for printing errors (used by gpl)
#include <iostream>

// bison syntax indicating the end of a C/C++ code section
%} 


// turn on verbose (longer) error messages
%define parse.error verbose

%union {
 int                union_int;
 std::string*       union_string;  // MUST be a pointer to a string
 double             union_double;
 GPL::Type          union_gpl_type;
 const Expression*  union_expression_ptr;
 const Variable*    union_variable_ptr;
};
%{
	template<typename OP, GPL::Operator optype>
	const Expression* Bin_op_check(const Expression* one, const Expression* three, unsigned int valid_types)
	{ 
	bool lhs_valid=one->type() & valid_types;
	bool rhs_valid=three->type() & valid_types;
	if(lhs_valid && rhs_valid)
		return new OP(one, three); 
	if(!lhs_valid) { Error::error(Error::INVALID_LEFT_OPERAND_TYPE,  to_string(optype)); }
	if(!rhs_valid) { Error::error(Error::INVALID_RIGHT_OPERAND_TYPE, to_string(optype)); }
	delete one;
	delete three;
	return new Integer_constant(0);
	}
	template<typename OP, GPL::Operator optype>
	const Expression* Un_op_check(const Expression* one, unsigned int valid_types)
	{
		bool rhs_valid=one->type() & valid_types;
		if(rhs_valid)
		{
			return new OP(one);
		}
		if(!rhs_valid)
		{
			Error::error(Error::INVALID_RIGHT_OPERAND_TYPE, to_string(optype));
		}
		delete one;
		return new Integer_constant(0);
	}
%}
%destructor { delete $$; } <union_string>
// tokens declared here
// tokens declared here
 /* updated January 2019 
  * Copy the following token declarations into your .y file. */

 /* Tokens with angle braces < > after %token require a type. 
  * This is the type of the variable the scanner (flex) puts into the union.
  * Fill in the < > with the appropriate union variable
  *     for example
  *     %token <union_int> T_INT_CONSTANT       "int constant" 
  */

%token T_INT                 "int"
%token T_DOUBLE              "double"
%token T_STRING              "string"
%token T_TRIANGLE            "triangle"
%token T_PIXMAP              "pixmap"
%token T_CIRCLE              "circle"
%token T_RECTANGLE           "rectangle"
%token T_TEXTBOX             "textbox"

%token T_FORWARD             "forward"
%token T_INITIALIZATION      "initialization"
%token T_TERMINATION         "termination"
%token T_ON                  "on"
%token T_ANIMATION           "animation"
%token T_IF                  "if"
%token T_FOR                 "for"
%token T_ELSE                "else"
%token <union_string> T_EXIT            "exit"  /* value is line number */
%token <union_string> T_PRINT           "print"  /* value is line number */
%token T_TRUE                "true"
%token T_FALSE               "false"

%token T_SPACE               "space"
%token T_LEFTARROW           "leftarrow"
%token T_RIGHTARROW          "rightarrow"
%token T_UPARROW             "uparrow"
%token T_DOWNARROW           "downarrow"
%token T_LEFTMOUSE_DOWN      "leftmouse_down"
%token T_MIDDLEMOUSE_DOWN    "middlemouse_down"
%token T_RIGHTMOUSE_DOWN     "rightmouse_down"
%token T_LEFTMOUSE_UP        "leftmouse_up"
%token T_MIDDLEMOUSE_UP      "middlemouse_up"
%token T_RIGHTMOUSE_UP       "rightmouse_up"
%token T_MOUSE_MOVE          "mouse_move"
%token T_MOUSE_DRAG          "mouse_drag"
%token T_F1                  "f1"
%token T_AKEY                "akey"
%token T_SKEY                "skey"
%token T_DKEY                "dkey"
%token T_FKEY                "fkey"
%token T_HKEY                "hkey"
%token T_JKEY                "jkey"
%token T_KKEY                "kkey"
%token T_LKEY                "lkey"
%token T_WKEY                "wkey"
%token T_ZKEY                "zkey"

%token T_LPAREN              "("
%token T_RPAREN              ")"
%token T_LBRACE              "{"
%token T_RBRACE              "}"
%token T_LBRACKET            "["
%token T_RBRACKET            "]"
%token T_SEMIC               ";"
%token T_COMMA               ","
%token T_PERIOD              "."

%token T_ASSIGN              "="
%token T_PLUS_ASSIGN         "+="
%token T_MINUS_ASSIGN        "-="
%token T_PLUS_PLUS           "++"
%token T_MINUS_MINUS         "--"

%token T_SIN                 "sin"
%token T_COS                 "cos"
%token T_TAN                 "tan"
%token T_ASIN                "asin"
%token T_ACOS                "acos"
%token T_ATAN                "atan"
%token T_SQRT                "sqrt"
%token T_ABS                 "abs"
%token T_FLOOR               "floor"
%token T_RANDOM              "random"

%token T_TOUCHES             "touches"
%token T_NEAR                "near"

%token T_MULTIPLY            "*"
%token T_DIVIDE              "/"
%token T_PLUS                "+"
%token T_MINUS               "-"
%token T_MOD                 "%"

%token T_LESS                "<"
%token T_GREATER             ">"
%token T_LESS_EQUAL          "<="
%token T_GREATER_EQUAL       ">="
%token T_EQUAL               "=="
%token T_NOT_EQUAL           "!="
%token T_NOT                 "!"
%token T_AND                 "&&"
%token T_OR                  "||"

%token <union_int>    T_INT_CONSTANT    "int constant"
%token <union_double> T_DOUBLE_CONSTANT "double constant"
%token <union_string> T_STRING_CONSTANT "string constant"
%token <union_string> T_ID            	 "identifier"

 /* special token that does not match any production */
 /* used for characters that are not part of the language */
%token T_ERROR               "error"
%type <union_gpl_type> simple_type
%type <union_expression_ptr> primary_expression
%type <union_expression_ptr> expression
%type <union_expression_ptr> optional_initializer
%type <union_variable_ptr> variable
//precedence
%type <union_expression_ptr> near
%type <union_expression_ptr> minot
%type <union_expression_ptr> product
%type <union_expression_ptr> sum
%type <union_expression_ptr> comp
%type <union_expression_ptr> binand
%type <union_expression_ptr> binor
%type <union_expression_ptr> eq
%nonassoc IF_NO_ELSE
%nonassoc T_ELSE

%%
// updated October 2021

//---------------------------------------------------------------------
program:
    declaration_list block_list


//---------------------------------------------------------------------
declaration_list:
    declaration_list declaration
    | %empty


//---------------------------------------------------------------------
declaration:
    variable_declaration T_SEMIC
    | object_declaration T_SEMIC
    | forward_declaration T_SEMIC


//---------------------------------------------------------------------
variable_declaration:
    simple_type  T_ID  optional_initializer
    {
		Scope_manager& sm=Scope_manager::instance();
		if(sm.defined_in_current_scope(*$2))
		{
			Error::error(Error::PREVIOUSLY_DECLARED_VARIABLE,*$2);
			delete $2;
			break;
		}
        try
		{
			switch($1)
			{
				case GPL::INT:
				{
					int* ptr;
					if($3==nullptr)
					{
						ptr=new int(0);
					}
					else
					{
						ptr=new int($3->evaluate()->as_int());
					}
					sm.add_to_current_scope(std::make_shared<Symbol>(*$2,ptr));
					break;
				}
				case GPL::DOUBLE:
				{
					double* ptr;
					if($3==nullptr)
					{
						ptr=new double(0.0);
					}
					else
					{
						ptr=new double($3->evaluate()->as_double());
					}
					sm.add_to_current_scope(std::make_shared<Symbol>(*$2,ptr));
					break;
				}
				case GPL::STRING:
				{
					std::string* ptr;
					if($3==nullptr)
					{
						ptr=new std::string("");
					}
					else
					{
						ptr=new std::string($3->evaluate()->as_string());
					}
					sm.add_to_current_scope(std::make_shared<Symbol>(*$2,ptr));
					break;
				}
				default:
					assert(false);
				
			}
		}
        catch(GPL::Type actual_type)
		{
			Error::error(Error::INVALID_TYPE_FOR_INITIAL_VALUE, GPL::to_string(actual_type), *$2, GPL::to_string($1));
			switch($1)
			{
				case GPL::INT:
					sm.add_to_current_scope(std::make_shared<Symbol>(*$2, new int(0)));
					break;
				case GPL::DOUBLE:
					sm.add_to_current_scope(std::make_shared<Symbol>(*$2, new double(0.0)));
					break;
				case GPL::STRING:
					sm.add_to_current_scope(std::make_shared<Symbol>(*$2, new std::string("")));
					break;
				default:
					assert(false);
			}
		}
        delete $2; 
        delete $3;
	}
    | simple_type  T_ID T_LBRACKET expression T_RBRACKET
{

		//std::cout<<"-------------"<<std::endl;
		Scope_manager& sm=Scope_manager::instance();
		if($4->type()!=GPL::INT)
		{
			Error::error(Error::ARRAY_SIZE_MUST_BE_AN_INTEGER,GPL::to_string($4->type()),*$2);
            int size = 1; 
            int *data = new int[1]; 
            for(int i = 0; i < size; i++)
            {
                data[i] = 0; 
            }
            sm.add_to_current_scope(std::make_shared<Symbol> (*$2, data, size));
			delete $2;
            delete $4;
			break;
		}


        int temp = $4->evaluate()->as_int();
        if(temp < 1)
        {
            Error::error(Error::INVALID_ARRAY_SIZE,*$2, std::to_string(temp));
            int size = 1; 
            int *data = new int[1]; 
            for(int i = 0; i < size; i++)
            {
                data[i] = 0; 
            }

            if (sm.defined_in_current_scope(*$2)) 
            {
                Error::error(Error::PREVIOUSLY_DECLARED_VARIABLE,*$2);
                delete data;
                delete $2;
                delete $4;
                break; 
            }
            else
                sm.add_to_current_scope(std::make_shared<Symbol> (*$2, data, size));  
            //delete data;
            delete $2; 
            delete $4;
            break;
        }

		if(sm.defined_in_current_scope(*$2))
		{
			Error::error(Error::PREVIOUSLY_DECLARED_VARIABLE,*$2);
			delete $2;
            delete $4;
			break;
		}
		try
		{
			switch($1)
			{
				case GPL::INT:
				{
					int* ptr=new int[($4->evaluate()->as_int())];
					for(int i=0; i<$4->evaluate()->as_int(); i++)
					{
						ptr[i]=0;
					}
					sm.add_to_current_scope(std::make_shared<Symbol>(*$2, ptr, $4->evaluate()->as_int()));
					break;
				}
				case GPL::DOUBLE:
				{
					double* ptr=new double[($4->evaluate()->as_int())];
					for(int i=0; i<$4->evaluate()->as_int(); i++)
					{
						ptr[i]=0;
					}
					sm.add_to_current_scope(std::make_shared<Symbol>(*$2, ptr, $4->evaluate()->as_int()));
					
					break;
				}
				case GPL::STRING:
				{
					std::string* ptr=new std::string[($4->evaluate()->as_int())];
					for(int i=0; i<$4->evaluate()->as_int(); i++)
					{
						ptr[i]="";
					}
					sm.add_to_current_scope(std::make_shared<Symbol>(*$2, ptr, $4->evaluate()->as_int()));
					
					break;
				}
				default:
					assert(false);

			}
		}catch(GPL::Type actual_type)
		{
            Error::error(Error::INVALID_TYPE_FOR_INITIAL_VALUE, GPL::to_string(actual_type), *$2, GPL::to_string($1));
            switch(actual_type)
			{
				case GPL::INT:
                {
                    int size=1;
                    int* ptr= new int[1];
                    for(int i =0; i<size; i++)
                    {
                        ptr[i]=0;
                    }
					sm.add_to_current_scope(std::make_shared<Symbol>(*$2, ptr, size));
					break;
                }
				case GPL::DOUBLE:
                {
					int size=1;
                    int* ptr= new int[1];
                    for(int i =0; i<size; i++)
                    {
                        ptr[i]=0;
                    }
					sm.add_to_current_scope(std::make_shared<Symbol>(*$2, ptr, size));
					break;
                }
				case GPL::STRING:
                {
					int size=1;
                    int* ptr= new int[1];
                    for(int i =0; i<size; i++)
                    {
                        ptr[i]=0;
                    }
					sm.add_to_current_scope(std::make_shared<Symbol>(*$2, ptr, size));
					break;
                }
				default:
					assert(false);
			}
		}
		delete $2;
        delete $4;
	}


//---------------------------------------------------------------------
simple_type:
    T_INT      {$$=GPL::INT;}
    | T_DOUBLE {$$=GPL::DOUBLE;}
    | T_STRING {$$=GPL::STRING;}


//---------------------------------------------------------------------
optional_initializer:
    T_ASSIGN expression { $$=$2; }
    | %empty {$$=nullptr;}


//---------------------------------------------------------------------
object_declaration:
    object_type T_ID parameter_list_or_empty {$2; /*CHANGE*/}
    | object_type T_ID T_LBRACKET expression T_RBRACKET {$2; /*CHANGE*/}


//---------------------------------------------------------------------
object_type:
    T_TRIANGLE
    | T_PIXMAP
    | T_CIRCLE
    | T_RECTANGLE
    | T_TEXTBOX


//---------------------------------------------------------------------
parameter_list_or_empty :
    T_LPAREN parameter_list T_RPAREN
    | T_LPAREN T_RPAREN
    | %empty


//---------------------------------------------------------------------
parameter_list :
    parameter_list T_COMMA parameter
    | parameter


//---------------------------------------------------------------------
parameter:
    T_ID T_ASSIGN expression


//---------------------------------------------------------------------
block_list:
    block_list block
    | %empty


//---------------------------------------------------------------------
block:
    initialization_block
    | termination_block
    | animation_block
    | on_block


//---------------------------------------------------------------------
initialization_block:
    T_INITIALIZATION statement_block


//---------------------------------------------------------------------
termination_block:
    T_TERMINATION statement_block


//---------------------------------------------------------------------
forward_declaration:
    T_FORWARD T_ANIMATION T_ID T_LPAREN animation_parameter T_RPAREN  {$3; /*CHANGE*/}


//---------------------------------------------------------------------
animation_parameter:
    object_type T_ID {$2; /*CHANGE*/}
    | object_type


//---------------------------------------------------------------------
animation_block:
    animation_declaration statement_block


//---------------------------------------------------------------------
animation_declaration:
    T_ANIMATION T_ID T_LPAREN object_type T_ID T_RPAREN {$5,$2; /*CHANGE*/}


//---------------------------------------------------------------------
on_block:
    T_ON keystroke statement_block


//---------------------------------------------------------------------
keystroke:
    T_SPACE
    | T_UPARROW
    | T_DOWNARROW
    | T_LEFTARROW
    | T_RIGHTARROW
    | T_LEFTMOUSE_DOWN
    | T_MIDDLEMOUSE_DOWN
    | T_RIGHTMOUSE_DOWN
    | T_LEFTMOUSE_UP
    | T_MIDDLEMOUSE_UP
    | T_RIGHTMOUSE_UP
    | T_MOUSE_MOVE
    | T_MOUSE_DRAG
    | T_AKEY
    | T_SKEY
    | T_DKEY
    | T_FKEY
    | T_HKEY
    | T_JKEY
    | T_KKEY
    | T_LKEY
    | T_WKEY
    | T_ZKEY
    | T_F1


//---------------------------------------------------------------------
statement_or_block_of_statements:
    statement_block
    | statement


//---------------------------------------------------------------------
statement_block:
    T_LBRACE statement_list T_RBRACE
    | T_LBRACE T_RBRACE



//---------------------------------------------------------------------
statement_list:
    statement_list statement
    | statement


//---------------------------------------------------------------------
statement:
    if_statement
    | for_statement
    | assign_statement T_SEMIC
    | print_statement T_SEMIC
    | exit_statement T_SEMIC


//---------------------------------------------------------------------
if_statement:
    T_IF T_LPAREN expression T_RPAREN statement_or_block_of_statements %prec IF_NO_ELSE
    | T_IF T_LPAREN expression T_RPAREN statement_or_block_of_statements T_ELSE statement_or_block_of_statements


//---------------------------------------------------------------------
for_statement:
    T_FOR T_LPAREN assign_statement_or_empty T_SEMIC expression T_SEMIC assign_statement_or_empty T_RPAREN statement_or_block_of_statements


//---------------------------------------------------------------------
print_statement:
    T_PRINT T_LPAREN expression T_RPAREN


//---------------------------------------------------------------------
exit_statement:
    T_EXIT T_LPAREN expression T_RPAREN


//---------------------------------------------------------------------
assign_statement_or_empty:
    assign_statement
    | %empty


//---------------------------------------------------------------------
assign_statement:
    variable T_ASSIGN expression
    | variable T_PLUS_ASSIGN expression
    | variable T_MINUS_ASSIGN expression
    | variable T_PLUS_PLUS
    | variable T_MINUS_MINUS


//---------------------------------------------------------------------
variable:
    T_ID {
        Scope_manager& sm=Scope_manager::instance();
        if(sm.lookup(*$1)==nullptr)
        {
            Error::error(Error::UNDECLARED_VARIABLE, *$1);
            $$=new Variable("");
            delete $1;
            break;
        }
        if(sm.lookup(*$1)->isArray()){
            Error::error(Error::VARIABLE_IS_AN_ARRAY, *$1);
            $$=new Variable("");
            delete $1;
            break;
        }
        $$=new Variable(*$1);
        delete $1;
    }
    | T_ID T_LBRACKET expression T_RBRACKET {
        Scope_manager& sm=Scope_manager::instance();
        if(sm.lookup(*$1)==nullptr)
        {
            Error::error(Error::UNDECLARED_VARIABLE, *$1+"[]");
            $$=new Variable("");
            delete $1;
            delete $3;
            break;
        }
        if(!sm.lookup(*$1)->isArray())
        {
            Error::error(Error::VARIABLE_NOT_AN_ARRAY, *$1);
            $$=new Variable("");
            delete $1;
            delete $3;
            break;
        }
        if($3->type()!=GPL::INT)
        {
            Error::error(Error::ARRAY_INDEX_MUST_BE_AN_INTEGER,*$1,GPL::to_string($3->type()));
            $$ = new Variable("");
            delete $1;
            delete $3;
            break;
        }
        $$ = new Variable(*$1, $3);
        delete $1;
        //delete $3;
    }
        | T_ID T_PERIOD T_ID {$1; $3; /* CHANGE */}
    | T_ID T_LBRACKET expression T_RBRACKET T_PERIOD T_ID {$1; $6; /* CHANGE */}


//---------------------------------------------------------------------

expression: binor{ $$=$1; }

    binor: binand
    | binor T_OR binand             {$$=Bin_op_check<Or, OR>($1, $3, GPL::INT|GPL::DOUBLE);}
    binand: eq
    | binand T_AND eq            {$$=Bin_op_check<And, AND>($1, $3, GPL::INT|GPL::DOUBLE);}

	eq: comp
    | eq T_EQUAL comp          {$$=Bin_op_check<Equal, EQUAL>($1, $3, INT|DOUBLE|STRING);}
    | eq T_NOT_EQUAL comp      {$$=Bin_op_check<Not_equal, NOT_EQUAL>($1, $3, INT|DOUBLE|STRING);}

	comp: sum
    | comp T_LESS_EQUAL sum     {$$=Bin_op_check<Less_equal, LESS_EQUAL>($1, $3, INT|DOUBLE|STRING);}
    | comp T_GREATER_EQUAL  sum {$$=Bin_op_check<Greater_equal, GREATER_EQUAL>($1, $3, INT|DOUBLE|STRING);}
    | comp T_LESS sum           {$$=Bin_op_check<Less_than, LESS_THAN>($1, $3, INT|DOUBLE|STRING);}
    | comp T_GREATER  sum 	     {$$=Bin_op_check<Greater_than, GREATER_THAN>($1, $3, INT|DOUBLE|STRING);}

	sum: product
    | sum T_PLUS product           {$$=Bin_op_check<Plus, PLUS>($1, $3, INT|DOUBLE|STRING);}
    | sum T_MINUS product          {$$=Bin_op_check<Minus, MINUS>($1, $3, GPL::INT|GPL::DOUBLE);}

	product: minot
    | product T_MULTIPLY minot       {$$=Bin_op_check<Multiply, MULTIPLY>($1, $3, GPL::INT|GPL::DOUBLE);}
    | product T_DIVIDE minot         {$$=Bin_op_check<Divide, DIVIDE>($1, $3, GPL::INT|GPL::DOUBLE);}
    | product T_MOD minot            {$$=Bin_op_check<Mod, MOD>($1, $3, GPL::INT);}

	minot: near
    | T_MINUS  minot                    {$$=Un_op_check<Tminus, UNARY_MINUS>($2, GPL::INT|GPL::DOUBLE);}
    | T_NOT  minot                      {$$=Un_op_check<Tnot, NOT>($2, GPL::INT|GPL::DOUBLE);}
	
	near: primary_expression
    | near T_NEAR primary_expression          {$$=nullptr; /*CHANGE*/}
    | near T_TOUCHES primary_expression        {$$=nullptr; /*CHANGE*/}

    primary_expression:
    T_SIN T_LPAREN expression T_RPAREN     {$$=Un_op_check<Tsin, SIN>($3, GPL::INT|GPL::DOUBLE);}
    | T_COS T_LPAREN expression T_RPAREN     {$$=Un_op_check<Tcos, COS>($3, GPL::INT|GPL::DOUBLE);}
    | T_TAN T_LPAREN expression T_RPAREN     {$$=Un_op_check<Ttan, TAN>($3, GPL::INT|GPL::DOUBLE);}
    | T_ASIN T_LPAREN expression T_RPAREN    {$$=Un_op_check<Tasin, ASIN>($3, GPL::INT|GPL::DOUBLE);}
    | T_ACOS T_LPAREN expression T_RPAREN    {$$=Un_op_check<Tacos, ACOS>($3, GPL::INT|GPL::DOUBLE);}
    | T_ATAN T_LPAREN expression T_RPAREN    {$$=Un_op_check<Tatan, ATAN>($3, GPL::INT|GPL::DOUBLE);}
    | T_SQRT T_LPAREN expression T_RPAREN    {$$=Un_op_check<Tsqrt, SQRT>($3, GPL::INT|GPL::DOUBLE);}
    | T_ABS T_LPAREN expression T_RPAREN     {$$=Un_op_check<Tabs, ABS>($3, GPL::INT|GPL::DOUBLE);}
    | T_FLOOR T_LPAREN expression T_RPAREN   {$$=Un_op_check<Tfloor, FLOOR>($3, GPL::INT|GPL::DOUBLE);}
    | T_RANDOM T_LPAREN expression T_RPAREN  {$$=Un_op_check<Trandom, RANDOM>($3, GPL::INT|GPL::DOUBLE);}


//---------------------------------------------------------------------
primary_expression:
    T_LPAREN  expression T_RPAREN {$$= $2;}
    | variable{$$=$1;}
    | T_INT_CONSTANT   {$$ = new Integer_constant($1);}
    | T_TRUE{$$=new const Integer_constant(1);}
    | T_FALSE{$$=new const Integer_constant(0);}
    | T_DOUBLE_CONSTANT{$$=new Double_constant($1);}
    | T_STRING_CONSTANT{$$= new String_constant(*$1); delete $1;}


%%
