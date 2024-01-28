#ifndef STATEMENT_H
#define STATEMENT_H

class Expression;
class Variable;
class Statement {
  public:
    void append_statement(Statement* atend);
    Statement() {}
    virtual void execute() const=0;
    virtual ~Statement() {delete next;}
  protected:
    Statement* next{nullptr};
};
class Print : public Statement {
  public:
    Print(int line_number, const Expression* argument) : line_number(line_number), argument(argument){}
    virtual void execute() const;
    virtual ~Print();
  private:
    int line_number;
    const Expression* argument;
};
//##
// NullStatement
//##
class NullStatement : public Statement {
  public:
    NullStatement(){}
    virtual void execute() const;
};
class Assign : public Statement {
  public:
    Assign(const Variable* lhs, const Expression* rhs) : lhs(lhs), rhs(rhs){}
    virtual void execute() const;
    virtual ~Assign();
  private:
    const Variable* lhs;
    const Expression* rhs;
};
class If : public Statement
{
  public:
    If(const Expression* expr_ptr, Statement* if_clause_ptr, Statement* else_clause_ptr) 
    : expr_ptr(expr_ptr), if_clause_ptr(if_clause_ptr), else_clause_ptr(else_clause_ptr){}
    virtual void execute() const;
    virtual ~If();
  private:
    const Expression* expr_ptr;
    Statement* if_clause_ptr;
    Statement* else_clause_ptr;
};
class For : public Statement
{
  public:
    For(Statement* initializer, const Expression* expr_ptr, Statement* inc_ptr, Statement* body_ptr)
    : initializer(initializer), expr_ptr(expr_ptr), inc_ptr(inc_ptr), body_ptr(body_ptr) {}
    virtual void execute() const;
    virtual ~For();
  private:
    Statement* initializer;
    const Expression* expr_ptr;
    Statement* inc_ptr;
    Statement* body_ptr;
};
class Repeat : public Statement
{
  public:
    Repeat(const Expression* expr_ptr, Statement* body_ptr)
    : expr_ptr(expr_ptr), body_ptr(body_ptr) {}
    virtual void execute() const;
    virtual ~Repeat();

  private:
    const Expression* expr_ptr;
    Statement* body_ptr;
};
class Exit : public Statement
{
  public:
    Exit(int line_number, const Expression* expr_ptr)
    : line_number(line_number), expr_ptr(expr_ptr){}
    virtual void execute() const;
    virtual ~Exit();
  private:
    int line_number;
    const Expression* expr_ptr;
};


#endif
