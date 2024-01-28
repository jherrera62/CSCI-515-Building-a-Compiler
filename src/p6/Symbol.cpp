#include<iostream>
#include<string>
#include<cassert>
#include "types_and_ops.h"
#include "Symbol.h"
#include "Constant.h"
#include "Rectangle.h"
#include "Circle.h"
#include "Triangle.h"
#include "Pixmap.h"
#include "Textbox.h"
#include "Animation_code.h"
using namespace GPL;
using namespace std;
Symbol::Symbol(const string& name, double* value)
    :name(name), value(value), type(DOUBLE), count(0)
{

}
Symbol::Symbol(const string& name, double* value, int count)
    :name(name), value(value), type(DOUBLE), count(count)
{

}
Symbol::Symbol(const string& name, int* value)
    :name(name), value(value), type(INT), count(0)
{

}
Symbol::Symbol(const string& name, int* value, int count)
    :name(name), value(value), type(INT), count(count)
{

}
Symbol::Symbol(const string& name, string* value)
    :name(name), value(value), type(STRING), count(0)
{

}
Symbol::Symbol(const string& name, string* value, int count)
    :name(name), value(value), type(STRING), count(count)
{

}
Symbol::Symbol(const string& name, Rectangle* value)
    :name(name), value(value), type(RECTANGLE), count(0)
{

}
Symbol::Symbol(const string& name, Rectangle* value, int count)
    :name(name), value(value), type(RECTANGLE), count(count)
{

}
Symbol::Symbol(const string& name, Triangle* value)
    :name(name), value(value), type(TRIANGLE), count(0)
{

}
Symbol::Symbol(const string& name, Triangle* value, int count)
    :name(name), value(value), type(TRIANGLE), count(count)
{

}
Symbol::Symbol(const string& name, Circle* value)
    :name(name), value(value), type(CIRCLE), count(0)
{

}
Symbol::Symbol(const string& name, Circle* value, int count)
    :name(name), value(value), type(CIRCLE), count(count)
{

}
Symbol::Symbol(const string& name, Pixmap* value)
    :name(name), value(value), type(PIXMAP), count(0)
{

}
Symbol::Symbol(const string& name, Pixmap* value, int count)
    :name(name), value(value), type(PIXMAP), count(count)
{

}
Symbol::Symbol(const string& name, Textbox* value)
    :name(name), value(value), type(TEXTBOX), count(0)
{

}
Symbol::Symbol(const string& name, Textbox* value, int count)
    :name(name), value(value), type(TEXTBOX), count(count)
{

}
Symbol::Symbol(const string& name, Animation_code* value)
    :name(name), value(value), type(ANIMATION_CODE), count(0)
{

}
Symbol::Symbol(const std::string& name, GPL::Type type, Game_object* value)
    : name(name),value(value),type(type)
{}
Symbol::~Symbol()
{
	if(count == 0)
	{
		if(type==GPL::INT)
		{
			delete value.int_pointer;
		}
		else if(type==GPL::DOUBLE)
		{
			delete value.double_pointer;
		}
		else if(type==GPL::STRING)
		{
			delete value.string_pointer;
		}
		else if(type==GPL::ANIMATION_CODE)
		{
			delete value.animation_pointer;
		}
	}
	else
	{
		if(type==GPL::INT)
		{
			delete[] value.int_pointer;
			
		}
		else if(type==GPL::DOUBLE)
		{
			delete[] value.double_pointer;
		}
		else if(type==GPL::STRING)
		{
			delete[] value.string_pointer;
		}
	}
}
std::shared_ptr<Locator> Symbol::as_lvalue() const
{
  	if(type==GPL::INT)
	{
		return std::make_shared<Integer_locator>(*value.int_pointer);
	}
	else if(type==GPL::DOUBLE)
	{
		return std::make_shared<Double_locator>(*value.double_pointer);
	}
	else if(type==GPL::STRING)
	{
		return std::make_shared<String_locator>(*value.string_pointer);
	}
	else if (type==GPL::ANIMATION_CODE)
	{
		return std::make_shared<Animation_block_locator>(value.animation_pointer);
	}
	else
	{
		throw type;
		return nullptr;
	}
	return nullptr;
}
std::shared_ptr<Locator> Symbol::as_lvalue(int index) const
{
	if(index>=count||index<0)
		return nullptr;
 	if(type==GPL::INT)
	{
		return std::make_shared<Integer_locator>(value.int_pointer[index]);
	}
	else if(type==GPL::DOUBLE)
	{
		return std::make_shared<Double_locator>(value.double_pointer[index]);
	}
	else if(type==GPL::STRING)
	{
		return std::make_shared<String_locator>(value.string_pointer[index]);
	}
	else
	{
		throw type;
		return nullptr;
	}
}
std::shared_ptr<Locator> Symbol::as_lvalue(const std::string& attribute_name) const
{
 	if(type==GPL::RECTANGLE)
	{
		return std::make_shared<Game_attribute_locator>(value.rectangle_pointer, attribute_name);
	}
	else if(type==GPL::TRIANGLE)
	{
		return std::make_shared<Game_attribute_locator>(value.triangle_pointer, attribute_name);
	}
	else if(type==GPL::CIRCLE)
	{
		return std::make_shared<Game_attribute_locator>(value.circle_pointer, attribute_name);
	}
	else if(type==GPL::PIXMAP)
	{
		return std::make_shared<Game_attribute_locator>(value.pixmap_pointer, attribute_name);
	}
	else if(type==GPL::TEXTBOX)
	{
		return std::make_shared<Game_attribute_locator>(value.textbox_pointer, attribute_name);
	}
	else
	{
		throw type;
		return nullptr;
	}
}
std::shared_ptr<Locator> Symbol::as_lvalue(int index, const std::string& attribute_name) const
{
 	if(type==GPL::RECTANGLE)
	{
		return std::make_shared<Game_attribute_locator>(&value.rectangle_pointer[index], attribute_name);
	}
	else if(type==GPL::TRIANGLE)
	{
		return std::make_shared<Game_attribute_locator>(&value.triangle_pointer[index], attribute_name);
	}
	else if(type==GPL::CIRCLE)
	{
		return std::make_shared<Game_attribute_locator>(&value.circle_pointer[index], attribute_name);
	}
	else if(type==GPL::PIXMAP)
	{
		return std::make_shared<Game_attribute_locator>(&value.pixmap_pointer[index], attribute_name);
	}
	else if(type==GPL::TEXTBOX)
	{
		return std::make_shared<Game_attribute_locator>(&value.textbox_pointer[index], attribute_name);
	}
	else
	{
		throw type;
		return nullptr;
	}
}
const Constant* Symbol::as_constant() const
{
	if(type==GPL::INT)
	{
		return new Integer_constant(*value.int_pointer);
	}
	else if(type==GPL::DOUBLE)
	{
		return new Double_constant(*value.double_pointer);
	}
	else if(type==GPL::STRING)
	{
		return new String_constant(*value.string_pointer);
	}
	else if(type==GPL::RECTANGLE)
	{
		return new Game_object_constant(value.rectangle_pointer);
	}
	else if(type==GPL::TRIANGLE)
	{
		return new Game_object_constant(value.triangle_pointer);
	}
	else if(type==GPL::CIRCLE)
	{
		return new Game_object_constant(value.circle_pointer);
	}
	else if(type==GPL::PIXMAP)
	{
		return new Game_object_constant(value.pixmap_pointer);
	}
	else if(type==GPL::TEXTBOX)
	{
		return new Game_object_constant(value.textbox_pointer);
	}
	else if(type==GPL::ANIMATION_CODE)
	{
		return new Animation_block_constant(value.animation_pointer);

	}
	else
	{
		throw(type);
	}
}
const Constant* Symbol::as_constant(int index) const 
{
	if(index < 0 || index >= count){
		return nullptr;
	}
	if(type == GPL::INT)
	{
		return new Integer_constant(value.int_pointer[index]);
	}
	else if(type == GPL::DOUBLE)
	{
		return new Double_constant(value.double_pointer[index]);
	}
	else if(type == GPL::STRING)
	{
		return new String_constant(value.string_pointer[index]);
	}
	else
	{
		throw(type);
	}
}
const Constant* Symbol::as_constant(const std::string attribute_name) const
{
    switch(type)
    {
        case RECTANGLE:
            return new Game_attribute_constant(value.rectangle_pointer, attribute_name);
        case CIRCLE:
            return new Game_attribute_constant(value.circle_pointer, attribute_name);
        case TRIANGLE:
            return new Game_attribute_constant(value.triangle_pointer, attribute_name);
        case PIXMAP:
            return new Game_attribute_constant(value.pixmap_pointer, attribute_name);
        case TEXTBOX:
            return new Game_attribute_constant(value.textbox_pointer, attribute_name);
        default:
            throw type;
    }
    return nullptr;
}
const Constant* Symbol::as_constant(int index, const std::string attribute_name) const
{
    if(index < 0 || index >= count){
        return nullptr;
    }
    switch (type) {
        case RECTANGLE:
            return new Game_attribute_constant(&value.rectangle_pointer[index], attribute_name);
        case CIRCLE:
            return new Game_attribute_constant(&value.circle_pointer[index], attribute_name);
        case TRIANGLE:
            return new Game_attribute_constant(&value.triangle_pointer[index], attribute_name);
        case PIXMAP:
            return new Game_attribute_constant(&value.pixmap_pointer[index], attribute_name);
        case TEXTBOX:
            return new Game_attribute_constant(&value.textbox_pointer[index], attribute_name);
        default:
            throw type;
    }
}
std::ostream& operator<<(std::ostream& os, const Symbol& sym)
{
	if(sym.type == GPL::DOUBLE)
	{
		if(sym.count==0)
		{
			os<< "double "<<sym.name << " = " << *sym.value.double_pointer<<endl;
		}
		else
		{
			int i=0;
			for(i=0; i<sym.count;i++)
			{
				os <<"double "<< sym.name <<"["<<i<< "] = " << sym.value.double_pointer[i] <<endl;
			}
		}
    }
	if(sym.type == GPL::INT)
	{
		if(sym.count==0)
		{
			os<<"int "<< sym.name << " = " << *sym.value.int_pointer<<endl;
		}
		else
		{
			int i=0;
			for(i=0; i<sym.count;i++)
			{
				os<<"int "<< sym.name <<"["<<i<< "] = " << sym.value.int_pointer[i] <<endl;
			}
		}
    }
	if(sym.type == GPL::STRING)
	{
		if(sym.count==0)
		{
			os<< "string "<<sym.name << " = \"" << *sym.value.string_pointer<<"\""<<endl;
		}
		else
		{
			int i=0;
			for(i=0; i<sym.count;i++)
			{
				os<< "string "<<sym.name <<"["<<i<< "] = \"" << sym.value.string_pointer[i]<<"\"" <<endl;
			}
		}
    }
	if(sym.type == GPL::RECTANGLE)
	{
		if(sym.count==0)
		{
			os<< "rectangle "<<sym.name << *sym.value.rectangle_pointer<<endl;
		}
		else
		{
			int i=0;
			for(i=0; i<sym.count;i++)
			{
				os<< "rectangle "<<sym.name <<"["<<i<< "]" << sym.value.rectangle_pointer[i]<<endl;
			}
		}
	}
	if(sym.type == GPL::TRIANGLE)
	{
		if(sym.count==0)
		{
			os<< "triangle "<<sym.name << *sym.value.triangle_pointer<<endl;
		}
		else
		{
			int i=0;
			for(i=0; i<sym.count;i++)
			{
				os<< "triangle "<<sym.name <<"["<<i<< "]" << sym.value.triangle_pointer[i]<<endl;
			}
		}
	}
	if(sym.type == GPL::CIRCLE)
	{
		if(sym.count==0)
		{
			os<< "circle "<<sym.name << *sym.value.circle_pointer<<endl;
		}
		else
		{
			int i=0;
			for(i=0; i<sym.count;i++)
			{
				os<< "circle "<<sym.name <<"["<<i<< "]" << sym.value.circle_pointer[i] <<endl;
			}
		}
	}
	if(sym.type == GPL::PIXMAP)
	{
		if(sym.count==0)
		{
			os<< "pixmap "<<sym.name << *sym.value.pixmap_pointer<<endl;
		}
		else
		{
			int i=0;
			for(i=0; i<sym.count;i++)
			{
				os<< "pixmap "<<sym.name <<"["<<i<< "]" << sym.value.pixmap_pointer[i] <<endl;
			}
		}
	}
	if(sym.type == GPL::TEXTBOX)
	{
		if(sym.count==0)
		{
			os<< "textbox "<<sym.name << *sym.value.textbox_pointer<<endl;
		}
		else
		{
			int i=0;
			for(i=0; i<sym.count;i++)
			{
				os<< "textbox "<<sym.name <<"["<<i<< "]" << sym.value.textbox_pointer[i] <<endl;
			}
		}
	}
	if(sym.type==GPL::ANIMATION_CODE)
	{
		os << GPL::to_string(sym.type) << ' ' << sym.name<<endl;
	}
	
	return os;
}

/*int main()
{
	int debug=1;
	if(debug==0)
	{
		double* oneofem=new double(3.141592);
		double* bunchofem=new double[4] {1.123, 2.234, 3.456, 7.899};
		Symbol one("pi", oneofem);
		Symbol two("racetimes", bunchofem, 4);
		cout << two << endl;
		cout << one << endl;
	}
	if(debug==1)
	{
		cout<<"INT"<<endl;
		int* oneofem=new int(3);
		int* bunchofem=new int[4] {1, 2, 3, 7};
		Symbol one("pi", oneofem);
		Symbol two("racetimes", bunchofem, 4);
		cout << two << endl;
		cout << one << endl;
	}
	if(debug==2)
	{
		string* oneofem=new string("three");
		string* bunchofem=new string[4] {"one", "two", "three", "four"};
		Symbol one("pi", oneofem);
		Symbol two("racetimes", bunchofem, 4);
		cout << two << endl;
		cout << one << endl;
	}
	return 0;
}*/
