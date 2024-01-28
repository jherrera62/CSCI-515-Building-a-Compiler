#include<iostream>
#include <cstdlib>
#include "Statement.h"
#include "Constant.h"
#ifdef P5
#include "Locator.h"
#endif
#include "Variable.h"
#include "Window.h"
#include "Event_manager.h"
void Statement::append_statement(Statement* atend)
{
  Statement* current=this;
  while(current->next != nullptr)
    current=current->next;
  current->next=atend;
}
void Print::execute() const
{
  cout <<"print[" << line_number << "]: " <<
    argument->evaluate()->as_string() << '\n';
  if(next) 
  {
    next->execute();
  }
  return;
}
Print::~Print(){
  delete argument;
}
void Assign::execute() const
{
  if(lhs->type() == GPL::INT)
	{
		lhs->modify()->mutate(rhs->evaluate()->as_int());
	}
	else if(lhs->type() == GPL::DOUBLE)
	{
		lhs->modify()->mutate(rhs->evaluate()->as_double());
	}
	else if(lhs->type() == GPL::STRING)
	{
		lhs->modify()->mutate(rhs->evaluate()->as_string());
	}
  else if(lhs->type()==GPL::ANIMATION_BLOCK)
  {
    lhs->modify()->mutate(rhs->evaluate()->as_animation_block());
  }
  if(next)
  {
    next->execute();
  }
  return;
}
Assign::~Assign()
{
  delete rhs;
}
void If::execute() const
{
  if(expr_ptr->evaluate()->as_int())
  {
    if_clause_ptr->execute();
  }
  else
  {
    else_clause_ptr->execute();
  }
  if(next)
  {
    next->execute();
  }

  return;
}
If::~If()
{
  delete expr_ptr;
}
void For::execute() const
{
  for(initializer->execute(); expr_ptr->evaluate()->as_int(); inc_ptr->execute())
  {
    body_ptr->execute();
  }
  if(next)
  {
    next->execute();
  }
  return;
}
For::~For()
{
  delete expr_ptr;
}
void Exit::execute() const
{
  Event_manager::instance().execute_handlers(Window::TERMINATE);
  cout<<"gpl["<<line_number<<"]: exit("<<expr_ptr->evaluate()->as_string()<<")"<<endl;
  exit(expr_ptr->evaluate()->as_int());
  if(next)
  {
    next->execute();
  }
  return;
}
Exit::~Exit()
{
  delete expr_ptr;
}
//##
// NullStatement
//##
void NullStatement::execute() const
{
}
