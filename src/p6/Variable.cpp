#include <iostream>
#include "Expression.h"
#include "Error.h"
#include "Symbol.h"
#include "Variable.h"
#include "Constant.h"
//#include "Scope_manager.h"
Variable::Variable(const std::string& symbol_name)
    :array_index_expression(nullptr), symbol_name(symbol_name)
	{
		
	}

Variable::Variable(const std::string& symbol_name, const Expression* index_expr)
    :array_index_expression(index_expr), symbol_name(symbol_name)
	{
		
	}
Member_variable::Member_variable(const std::string& s_name, const std::string& attribute_name)
  : Variable(s_name), attribute_name(attribute_name)
    {

    }
Member_variable::Member_variable(const std::string& s_name, const std::string& attribute_name,const Expression* index_expr)
  : Variable(s_name, index_expr), attribute_name(attribute_name)
    {

    }

const Constant* Variable::evaluate() const
{
    if(symbol_name.empty())
	{
        return ret(new Integer_constant(0));
    }
    if(symbol()->isArray()==false)
	{
        return ret(symbol()->as_constant());
    }
    const Constant *ptr = array_index_expression->evaluate();
    if (ret(symbol()->as_constant(ptr->as_int())) == nullptr)
    {
        Error::error(Error::ARRAY_INDEX_OUT_OF_BOUNDS, symbol_name, std::to_string(array_index_expression->evaluate()->as_int()));
        return ret(symbol()->as_constant());
    }
    return ret(symbol()->as_constant(ptr->as_int()));
}

GPL::Type Variable::type() const
{
    if(symbol_name != "")
	{
        return symbol()->get_type();
    }
    else
	{
        return GPL::INT;
    }
}

GPL::Type Member_variable::type() const
{
    const Constant* val=nullptr;
    if(array_index_expression==nullptr)
    {
        val=symbol()->as_constant(attribute_name);
    }
    else
    {
        val=symbol()->as_constant(0, attribute_name);
    }
    GPL::Type type=val->type();
    delete val;
    return type;
}
const Constant* Member_variable::evaluate() const
{
    if(array_index_expression==nullptr)
    {
        return ret(symbol()->as_constant(attribute_name));
    }
    int i=0;
    i=array_index_expression->evaluate()->as_int();
    // const Constant* value;
    if(symbol()->as_constant(i, attribute_name)==nullptr)
    {
        Error::error(Error::ARRAY_INDEX_OUT_OF_BOUNDS, symbol()->get_name(), std::to_string(i));
        return symbol()->as_constant(0, attribute_name);
    }
    return symbol()->as_constant(i, attribute_name);
}
const std::shared_ptr<Locator> Variable::modify() const
{
    if(array_index_expression==nullptr)
    {
        return symbol()->as_lvalue();
    }
    else
    {
        std::shared_ptr<Locator> value = symbol()->as_lvalue(array_index_expression->evaluate()->as_int());
        if(value==nullptr)
        {
            Error::error(Error::ARRAY_INDEX_OUT_OF_BOUNDS, symbol_name, std::to_string(array_index_expression->evaluate()->as_int()));
            value = symbol()->as_lvalue(0);
        }
        return value;
    }
}
const std::shared_ptr<Locator> Member_variable::modify() const
{
    if(array_index_expression==nullptr)
    {
        return symbol()->as_lvalue(attribute_name);
    }
    else
    {
        std::shared_ptr<Locator> value = symbol()->as_lvalue(array_index_expression->evaluate()->as_int(), attribute_name);
        if(value==nullptr)
        {
            Error::error(Error::ARRAY_INDEX_OUT_OF_BOUNDS, symbol()->get_name(), std::to_string(array_index_expression->evaluate()->as_int()));
            value=symbol()->as_lvalue(0,attribute_name);
        }
        return value;
    }
}
Variable::~Variable()
{
	delete array_index_expression;
}