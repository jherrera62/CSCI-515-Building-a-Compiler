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

    // initialize array_index_expression to index_expr
Variable::Variable(const std::string& symbol_name, const Expression* index_expr)
    :array_index_expression(index_expr), symbol_name(symbol_name)
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

Variable::~Variable()
{
	delete array_index_expression;
}