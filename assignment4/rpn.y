//Juan Herrera
 /* Define your tokens here */
%token T_PLUS
%token T_MINUS
%token T_INT_CONSTANT
%token T_MULTIPLY
%token T_DIVIDE
%token T_ERROR
%token T_SIZE
%token T_PRINT

%{
  /* add all the necessary C++ header files and 
     variables required to manage a stack (hint: see orig_rpn.l
   */
  #include<stack>
  #include<string>
  #include<iostream>
  using std::cout;
  using std::cerr;
  using std::endl;
  using std::stoi;
  std::stack<int> rpnstack;
  bool stack_error(int expected);


  /* The prototype to yylex() is required since its source is
     in a separate file */
  int yylex();

  /* we must write this function. Generated code calls it */
  void yyerror(const char* err);
%}

%%
my_start_sym : /* empty */ 
      | my_start_sym misc_non_term_symbol
      ; /* semi-colon designates end of "production" */

misc_non_term_symbol: T_INT_CONSTANT {rpnstack.push($1);}
    | T_PLUS { if(stack_error(2)) break; int a=rpnstack.top(); rpnstack.pop(); int b=rpnstack.top(); rpnstack.pop(); rpnstack.push(a+b);}
    | T_MINUS { if(stack_error(2)) break; int a=rpnstack.top(); rpnstack.pop(); int b=rpnstack.top(); rpnstack.pop(); rpnstack.push(a-b);} /*etc for other tokens */
 /* semi-colon designates end of "production" */
    | T_MULTIPLY { if(stack_error(2)) break; int a=rpnstack.top(); rpnstack.pop(); int b=rpnstack.top(); rpnstack.pop(); rpnstack.push(a*b);}
	| T_DIVIDE { if(stack_error(2)) break; int a=rpnstack.top(); rpnstack.pop(); int b=rpnstack.top(); rpnstack.pop(); rpnstack.push(a/b);}
	| T_PRINT { if(stack_error(1)) break; cout << rpnstack.top() << endl; rpnstack.pop(); }
	| T_SIZE { cout << "stack=" << rpnstack.size() << endl; }
%%

int main(int argc, char** argv)
{
  yyparse();
}

bool stack_error(int expected)
{
  if(rpnstack.size() < expected)
  {
    cerr << "Stack size to small!\n";
    return 1;
  }
  return 0;
}

void yyerror(const char* err)
{
  cerr << err << endl;
}
