#ifndef SYMBOL_H
#define SYMBOL_H
#include<iostream>
#include<string>
#include "types_and_ops.h"
using namespace std;
using namespace GPL;
//#include "Expression.h"
class Constant;
class Rectangle;
class Circle;
class Triangle;
class Pixmap;
class Textbox;
class Symbol
{
    private:
        union symbol_type{
			double* double_pointer;
			int* int_pointer;
			std::string* string_pointer;
			Rectangle* rectangle_pointer;
			Circle* circle_pointer;
			Triangle* triangle_pointer;
			Pixmap* pixmap_pointer;
			Textbox* textbox_pointer;
			symbol_type(double* val) : double_pointer(val){}
			symbol_type(int* val) : int_pointer(val){}
			symbol_type(std::string* val) : string_pointer(val){}
			symbol_type(Circle* val) : circle_pointer(val) {}
			symbol_type(Triangle* val) : triangle_pointer(val) {}
			symbol_type(Rectangle* val) : rectangle_pointer(val) {}
			symbol_type(Pixmap* val) : pixmap_pointer(val) {}
			symbol_type(Textbox* val) : textbox_pointer(val) {}
		};
		std::string name;
		symbol_type value;
		GPL::Type type;
		int count;
    public:
        Symbol(const std::string& name, double* value); 
		Symbol(const std::string& name, double* value, int count);
		Symbol(const std::string& name, int* value); 
		Symbol(const std::string& name, int* value, int count);
		Symbol(const std::string& name, std::string* value); 
		Symbol(const std::string& name, std::string* value, int count);
		Symbol(const std::string& name, Rectangle* value);
		Symbol(const std::string& name, Rectangle* value, int count);
		Symbol(const std::string& name, Circle* value);
		Symbol(const std::string& name, Circle* value, int count);
		Symbol(const std::string& name, Triangle* value);
		Symbol(const std::string& name, Triangle* value, int count);
		Symbol(const std::string& name, Pixmap* value);
		Symbol(const std::string& name, Pixmap* value, int count);
		Symbol(const std::string& name, Textbox* value);
		Symbol(const std::string& name, Textbox* value, int count);
		const Constant* as_constant() const;
		const Constant* as_constant(int index) const;
		const Constant* as_constant(int index, const std::string attribute_name) const;
   		const Constant* as_constant(const std::string attribute_name) const;

        GPL::Type get_type() const {return type;};
		std::string get_name() const {return name;};
		bool isArray() const {if(count==0){return false;} else{return true;}};
        virtual ~Symbol();
		friend std::ostream& operator<<(std::ostream& os, const Symbol& sym);
        Symbol(const Symbol&) = delete;
		Symbol& operator=(const Symbol&) = delete;
};
#endif