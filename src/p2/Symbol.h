#ifndef SYMBOL_H
#define SYMBOL_H
#include<iostream>
#include<string>
#include "types_and_ops.h"
//#include "Expression.h"
class Constant;
class Symbol
{
    private:
        union symbol_type{
			double* double_pointer;
			int* int_pointer;
			std::string* string_pointer;
			
			symbol_type(double* val) : double_pointer(val){}
			symbol_type(int* val) : int_pointer(val){}
			symbol_type(std::string* val) : string_pointer(val){}
		};
		std::string name;
		symbol_type value;
		int count;
		GPL::Type type;
    public:
        Symbol(const std::string& name, double* value); 
		Symbol(const std::string& name, double* value, int count);
		Symbol(const std::string& name, int* value); 
		Symbol(const std::string& name, int* value, int count);
		Symbol(const std::string& name, std::string* value); 
		Symbol(const std::string& name, std::string* value, int count);
        GPL::Type get_type() const {return type;};
		std::string get_name() const {return name;};
        virtual ~Symbol();
		friend std::ostream& operator<<(std::ostream& os, const Symbol& sym);
        Symbol(const Symbol&) = delete;
		Symbol& operator=(const Symbol&) = delete;
};
#endif