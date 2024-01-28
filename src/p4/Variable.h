#ifndef VARIABLE_H
#define VARIABLE_H
#include <iostream>
//#include "Expression.h"
#include "Symbol.h"
#include "types_and_ops.h"
#include "error.h"
#include "Scope_manager.h"
#include <string>
#include <memory>
#include <cassert>
class Constant;
class Variable : public Expression {
  public:
    // initialize unused array_index_expression to nullptr
    Variable(const std::string& symbol_name);

    // initialize array_index_expression to index_expr
    Variable(const std::string& symbol_name, const Expression* index_expr);

    virtual const Constant* evaluate() const;
    virtual GPL::Type type() const;
    virtual ~Variable();

    Variable(const Variable&) = delete;
    Variable& operator=(const Variable&) = delete;
  protected: //allow derived class access

    const Expression* array_index_expression;
    std::string symbol_name;

    //The symbol() function eases access to the symbol
    //use it within Variable's member functions
    std::shared_ptr<Symbol> symbol()
    { return Scope_manager::instance().lookup(symbol_name); }
    std::shared_ptr<Symbol> symbol() const
    { return Scope_manager::instance().lookup(symbol_name); }
};
class Member_variable : public Variable {
  public:
    Member_variable(const std::string& s_name, const std::string& attribute_name);
    Member_variable(const std::string& s_name,const std::string& attribute_name, const Expression* array_index_expression);
    virtual const Constant* evaluate() const override;
    virtual GPL::Type type() const override;
  
  private:
    std::string s_name;
    std::string attribute_name;
};
#endif