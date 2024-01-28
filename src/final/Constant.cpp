#include "Constant.h"

GPL::Type  Constant::type() const 
{ return intrinsic_type; }

const Constant* Constant::evaluate() const
{ return this; }

int Game_attribute_constant::as_int() const
{
    if( type() == GPL::INT)
    {
        int var;
        gop->read_attribute(attribute_name, var);
        return var;
    }
    else
    {
        throw type();
    }
}
double Game_attribute_constant::as_double() const
{
    if(type()==GPL::INT)
    {
        int var;
        gop->read_attribute(attribute_name, var);
        return var;
    }
    else if(type()==GPL::DOUBLE)
    {
        double var;
        gop->read_attribute(attribute_name, var);
        return var;
    }
    else
    {
        throw type();
    }
}
std::string Game_attribute_constant::as_string() const
{
    if(type()==GPL::INT)
    {
        int var;
        gop->read_attribute(attribute_name, var);
        return std::to_string(var);
    }
    else if(type()==GPL::DOUBLE)
    { 
        double var;
        gop->read_attribute(attribute_name, var);
        return std::to_string(var);
    }
    else if(type()==GPL::STRING)
    {
        std::string var;
        gop->read_attribute(attribute_name, var);
        return var;
    }
    else
    {
        throw type();  
    }
}