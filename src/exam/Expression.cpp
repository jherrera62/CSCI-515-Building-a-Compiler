// File: Expression.cpp
#include "Expression.h"
#include "Constant.h"
#include "error.h"
#include<string>
#include <cmath>
#include<iostream>
#include<numbers>
using std::string;

Expression::~Expression(){delete evaluated_constant;}

// This wrapper ensures that Constant objects created by evaluate() are
// properly released when a subsequent call to evaluate() will otherwise
// overwrite the pointer.
const Constant* Expression::ret(const Constant* new_evald_constant) const
{
  delete evaluated_constant;
  return evaluated_constant=new_evald_constant;
}
/**********************************************/
/************* Other operators ****************/
/**********************************************/

const Constant* Plus::evaluate() const
{
	const Constant* lhs_constant=lhs->evaluate();
	const Constant* rhs_constant=rhs->evaluate();
	if(lhs->type()==GPL::STRING||rhs->type()==GPL::STRING)
	{
		return ret(new String_constant(lhs_constant->as_string()+rhs_constant->as_string()));

	}
	else if(lhs->type()==GPL::DOUBLE||rhs->type()==GPL::DOUBLE)
	{
		return ret(new Double_constant(lhs_constant->as_double()+rhs_constant->as_double()));
	}
	return ret(new Integer_constant(lhs_constant->as_int()+rhs_constant->as_int()));

}

GPL::Type Plus::type() const
{

	if(lhs->type()==GPL::STRING||rhs->type()==GPL::STRING)
	{
		return GPL::STRING;

	}
	if(lhs->type()==GPL::DOUBLE||rhs->type()==GPL::DOUBLE)
	{
		return GPL::DOUBLE;
	}
	return GPL::INT;
}

const Constant* Multiply::evaluate() const
{
	const Constant* lhs_constant=lhs->evaluate();
	const Constant* rhs_constant=rhs->evaluate();
	if(lhs->type()==GPL::DOUBLE||rhs->type()==GPL::DOUBLE)
	{
		return ret(new Double_constant(lhs_constant->as_double()*rhs_constant->as_double()));
	}
	return ret(new Integer_constant(lhs_constant->as_int()*rhs_constant->as_int()));
}

GPL::Type Multiply::type() const
{
	if(lhs->type()==GPL::DOUBLE||rhs->type()==GPL::DOUBLE)
	{
		return GPL::DOUBLE;
	}
	return GPL::INT;	
}
const Constant* Minus::evaluate() const
{
	const Constant* lhs_constant=lhs->evaluate();
	const Constant* rhs_constant=rhs->evaluate();
	if(lhs->type()==GPL::DOUBLE||rhs->type()==GPL::DOUBLE)
	{
		return ret(new Double_constant(lhs_constant->as_double()-rhs_constant->as_double()));
	}
	return ret(new Integer_constant(lhs_constant->as_int()-rhs_constant->as_int()));
}

GPL::Type Minus::type() const
{
	if(lhs->type()==GPL::DOUBLE||rhs->type()==GPL::DOUBLE)
	{
		return GPL::DOUBLE;
	}
	return GPL::INT;	
}
const Constant* Mod::evaluate() const
{
	const Constant* lhs_constant=lhs->evaluate();
	const Constant* rhs_constant=rhs->evaluate();
	if(!Error::runtime()&&rhs_constant->as_double()==0.0)
	{
		Error::error(Error::MOD_BY_ZERO_AT_PARSE_TIME);
		return ret(new Integer_constant(0));
	}

	return ret(new Integer_constant(lhs_constant->as_int()%rhs_constant->as_int()));
}

GPL::Type Mod::type() const
{
	return GPL::INT;	
}
const Constant* Divide::evaluate() const
{
	const Constant* lhs_constant=lhs->evaluate();
	const Constant* rhs_constant=rhs->evaluate();
	if (!Error::runtime() && rhs_constant->as_double() == 0.0)
  	{
  	  Error::error(Error::DIVIDE_BY_ZERO_AT_PARSE_TIME);
  	  return ret(new Integer_constant(0));
 	}
 	if (lhs->type() == GPL::DOUBLE || rhs->type() == GPL::DOUBLE)
 	{
 	  return ret(new Double_constant(lhs_constant->as_double() /rhs_constant->as_double()));
	}
 	return ret(new Integer_constant(lhs_constant->as_int() /rhs_constant->as_int()));}

GPL::Type Divide::type() const
{
	if(lhs->type()==GPL::DOUBLE||rhs->type()==GPL::DOUBLE)
	{
		return GPL::DOUBLE;
	}
	return GPL::INT;	
}
const Constant* Or::evaluate() const
{
	const Constant* lhs_constant=lhs->evaluate();
	const Constant* rhs_constant=rhs->evaluate();
	if(lhs->type()==GPL::DOUBLE||rhs->type()==GPL::DOUBLE)
	{
		bool x=lhs_constant->as_double()||rhs_constant->as_double();
		return ret(new Integer_constant(x));
	}
	bool x=lhs_constant->as_int()||rhs_constant->as_int();
	return ret(new Integer_constant(x));}

GPL::Type Or::type() const
{
	return GPL::INT;	
}
const Constant* And::evaluate() const
{
	//std::cout<<"-----------------------"<<std::endl;
	const Constant* lhs_constant=lhs->evaluate();
	const Constant* rhs_constant=rhs->evaluate();

	if(lhs->type()==GPL::DOUBLE||rhs->type()==GPL::DOUBLE)
	{
		bool x=lhs_constant->as_double()&&rhs_constant->as_double();
		return ret(new Integer_constant(x));
	}
	bool x = lhs_constant->as_int()&&rhs_constant->as_int();
	return ret(new Integer_constant(x));

}

GPL::Type And::type() const
{
	return GPL::INT;	
}
const Constant* Less_equal::evaluate() const
{
	const Constant* lhs_constant=lhs->evaluate();
	const Constant* rhs_constant=rhs->evaluate();
	if(lhs->type()==GPL::STRING||rhs->type()==GPL::STRING)
	{
		return ret(new Integer_constant(lhs_constant->as_string()<=rhs_constant->as_string()));
	}
	else if(lhs->type()==GPL::DOUBLE||rhs->type()==GPL::DOUBLE)
	{
		return ret(new Integer_constant(lhs_constant->as_double()<=rhs_constant->as_double()));
	}
	return ret(new Integer_constant(lhs_constant->as_int()<=rhs_constant->as_int()));

}

GPL::Type Less_equal::type() const
{
	return GPL::INT;
}
const Constant* Greater_equal::evaluate() const
{
	const Constant* lhs_constant=lhs->evaluate();
	const Constant* rhs_constant=rhs->evaluate();
	if(lhs->type()==GPL::STRING||rhs->type()==GPL::STRING)
	{
		return ret(new Integer_constant(lhs_constant->as_string()>=rhs_constant->as_string()));
	}
	else if(lhs->type()==GPL::DOUBLE||rhs->type()==GPL::DOUBLE)
	{
		return ret(new Integer_constant(lhs_constant->as_double()>=rhs_constant->as_double()));
	}
	return ret(new Integer_constant(lhs_constant->as_int()>=rhs_constant->as_int()));

}

GPL::Type Greater_equal::type() const
{
	return GPL::INT;
}
const Constant* Less_than::evaluate() const
{
	const Constant* lhs_constant=lhs->evaluate();
	const Constant* rhs_constant=rhs->evaluate();
	if(lhs->type()==GPL::STRING||rhs->type()==GPL::STRING)
	{
		return ret(new Integer_constant(lhs_constant->as_string()<rhs_constant->as_string()));
	}
	else if(lhs->type()==GPL::DOUBLE||rhs->type()==GPL::DOUBLE)
	{
		return ret(new Integer_constant(lhs_constant->as_double()<rhs_constant->as_double()));
	}
	return ret(new Integer_constant(lhs_constant->as_int()<rhs_constant->as_int()));

}

GPL::Type Less_than::type() const
{
	return GPL::INT;
}
const Constant* Greater_than::evaluate() const
{
	const Constant* lhs_constant=lhs->evaluate();
	const Constant* rhs_constant=rhs->evaluate();
	if(lhs->type()==GPL::STRING||rhs->type()==GPL::STRING)
	{
		return ret(new Integer_constant(lhs_constant->as_string()>rhs_constant->as_string()));
	}
	else if(lhs->type()==GPL::DOUBLE||rhs->type()==GPL::DOUBLE)
	{
		return ret(new Integer_constant(lhs_constant->as_double()>rhs_constant->as_double()));
	}
	return ret(new Integer_constant(lhs_constant->as_int()>rhs_constant->as_int()));

}

GPL::Type Greater_than::type() const
{
	return GPL::INT;
}
const Constant* Equal::evaluate() const
{
	const Constant* lhs_constant=lhs->evaluate();
	const Constant* rhs_constant=rhs->evaluate();
	if(lhs->type()==GPL::STRING||rhs->type()==GPL::STRING)
	{
		return ret(new Integer_constant(lhs_constant->as_string()==rhs_constant->as_string()));
	}
	else if(lhs->type()==GPL::DOUBLE||rhs->type()==GPL::DOUBLE)
	{
		return ret(new Integer_constant(lhs_constant->as_double()==rhs_constant->as_double()));
	}
	return ret(new Integer_constant(lhs_constant->as_int()==rhs_constant->as_int()));

}

GPL::Type Equal::type() const
{
	return GPL::INT;
}
const Constant* Not_equal::evaluate() const
{
	const Constant* lhs_constant=lhs->evaluate();
	const Constant* rhs_constant=rhs->evaluate();
	if(lhs->type()==GPL::STRING||rhs->type()==GPL::STRING)
	{
		return ret(new Integer_constant(lhs_constant->as_string()!=rhs_constant->as_string()));
	}
	else if(lhs->type()==GPL::DOUBLE||rhs->type()==GPL::DOUBLE)
	{
		return ret(new Integer_constant(lhs_constant->as_double()!=rhs_constant->as_double()));
	}
	return ret(new Integer_constant(lhs_constant->as_int()!=rhs_constant->as_int()));

}

GPL::Type Not_equal::type() const
{
	return GPL::INT;
}
const Constant* Tminus::evaluate() const
{
	const Constant* rhs_constant=rhs->evaluate();
	if(rhs->type()==GPL::DOUBLE)
	{
		return ret(new Double_constant(-rhs_constant->as_double()));
	}
	return ret(new Integer_constant(-rhs_constant->as_int()));
}

GPL::Type Tminus::type() const
{
	if(rhs->type()==GPL::DOUBLE)
	{
		return GPL::DOUBLE;
	}
	return GPL::INT;	
}
const Constant* Tnot::evaluate() const
{
	const Constant* rhs_constant=rhs->evaluate();
	if(rhs->type()==GPL::DOUBLE)
	{
		return ret(new Integer_constant(!rhs_constant->as_double()));
	}
	return ret(new Integer_constant(!rhs_constant->as_int()));
}

GPL::Type Tnot::type() const
{
	if(rhs->type()==GPL::DOUBLE)
	{
		return GPL::DOUBLE;
	}
	return GPL::INT;	
}

const Constant* Tsin::evaluate() const
{
	const Constant* rhs_constant=rhs->evaluate();
	if(rhs->type()==GPL::DOUBLE)
	{
		return ret(new Double_constant(sin((rhs_constant->as_double()*std::numbers::pi)/180)));
	}
	return ret(new Double_constant(sin((rhs_constant->as_int()*std::numbers::pi)/180)));
}

GPL::Type Tsin::type() const
{
	return GPL::DOUBLE;
}
const Constant* Tcos::evaluate() const
{
	const Constant* rhs_constant=rhs->evaluate();
	if(rhs->type()==GPL::DOUBLE)
	{
		return ret(new Double_constant(cos((rhs_constant->as_double()*std::numbers::pi)/180)));
	}
	return ret(new Double_constant(cos((rhs_constant->as_int()*std::numbers::pi)/180)));
}

GPL::Type Tcos::type() const
{
	return GPL::DOUBLE;	
}
const Constant* Ttan::evaluate() const
{
	const Constant* rhs_constant=rhs->evaluate();
	if(rhs->type()==GPL::DOUBLE)
	{
		return ret(new Double_constant(tan((rhs_constant->as_double()*std::numbers::pi)/180)));
	}
	return ret(new Double_constant(tan((rhs_constant->as_int()*std::numbers::pi)/180)));
}

GPL::Type Ttan::type() const
{
	return GPL::DOUBLE;
}
const Constant* Tasin::evaluate() const
{
	const Constant* rhs_constant=rhs->evaluate();
	if(rhs->type()==GPL::DOUBLE)
	{
		return ret(new Double_constant(asin(rhs_constant->as_double())*180/std::numbers::pi));
	}
	return ret(new Double_constant(asin(rhs_constant->as_double())*180/std::numbers::pi));
}

GPL::Type Tasin::type() const
{
	return GPL::DOUBLE;	
}
const Constant* Tacos::evaluate() const
{
	const Constant* rhs_constant=rhs->evaluate();
	if(rhs->type()==GPL::DOUBLE)
	{
		return ret(new Double_constant(acos(rhs_constant->as_double())*180/std::numbers::pi));
	}
	return ret(new Double_constant(acos(rhs_constant->as_double())*180/std::numbers::pi));
}

GPL::Type Tacos::type() const
{
	return GPL::DOUBLE;	
}
const Constant* Tatan::evaluate() const
{
	const Constant* rhs_constant=rhs->evaluate();
	if(rhs->type()==GPL::DOUBLE)
	{
		return ret(new Double_constant(atan(rhs_constant->as_double())*180/std::numbers::pi));
	}
	return ret(new Double_constant(atan(rhs_constant->as_double())*180/std::numbers::pi));
}

GPL::Type Tatan::type() const
{
	return GPL::DOUBLE;	
}
const Constant* Tsqrt::evaluate() const
{
	const Constant* rhs_constant=rhs->evaluate();
	if(rhs->type()==GPL::DOUBLE)
	{
		return ret(new Double_constant(sqrt(rhs_constant->as_double())));
	}
	return ret(new Double_constant(sqrt(rhs_constant->as_int())));
}

GPL::Type Tsqrt::type() const
{
	return GPL::DOUBLE;	
}
const Constant* Tabs::evaluate() const
{
	const Constant* rhs_constant=rhs->evaluate();
	if(rhs->type()==GPL::DOUBLE)
	{
		return ret(new Double_constant(std::fabs(rhs_constant->as_double())));
	}
	return ret(new Integer_constant(abs(rhs_constant->as_int())));
}

GPL::Type Tabs::type() const
{
	if(rhs->type()==GPL::DOUBLE)
	{
		return GPL::DOUBLE;
	}
	return GPL::INT;	
}
const Constant* Tfloor::evaluate() const
{
	const Constant* rhs_constant=rhs->evaluate();
	if(rhs->type()==GPL::DOUBLE)
	{
		return ret(new Integer_constant(floor(rhs_constant->as_double())));
	}
	return ret(new Integer_constant(floor(rhs_constant->as_int())));
}

GPL::Type Tfloor::type() const
{
	return GPL::INT;	
}
const Constant* Trandom::evaluate() const
{
	const Constant* rhs_constant=rhs->evaluate();
	if(rhs->type()==GPL::DOUBLE)
	{
		if(rhs_constant->as_double()>=1.0)
		{
			int x=floor(rhs_constant->as_double());
			return ret(new Integer_constant(rand()%x));
		}
		else
		{	Error::error(Error::INVALID_ARGUMENT_FOR_RANDOM,  std::to_string(rhs_constant->as_double()));
			return ret(new Integer_constant(rand()%2));
		}
	}
	//if (rhs->type()==GPL::INT)
	{
		if(rhs_constant->as_int()>=1)
		{
			return ret(new Integer_constant(rand()%(rhs_constant->as_int())));
		}
		else
		{	Error::error(Error::INVALID_ARGUMENT_FOR_RANDOM,  std::to_string(rhs_constant->as_int())); 
			return ret(new Integer_constant(rand()%2));
		}
	}
	//std::cout<<"/////////////////////////////////////////////////////////////"<<std::endl;
}

GPL::Type Trandom::type() const
{
	return GPL::INT;	
}
const Constant* Ternary::evaluate() const
{
	const Constant* lhs_constant=lhs->evaluate();
	const Constant* mhs_constant=mhs->evaluate();
	const Constant* rhs_constant=rhs->evaluate();
	if(lhs_constant->as_int())
	{
		return ret(new Integer_constant(mhs_constant->as_int()));
	}
	return ret(new Integer_constant(lhs_constant->as_int()? mhs_constant->as_int():rhs_constant->as_int()));

}

GPL::Type Ternary::type() const
{
	return GPL::INT;
}