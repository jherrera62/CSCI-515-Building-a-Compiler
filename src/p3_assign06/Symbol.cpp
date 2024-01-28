#include<iostream>
#include<string>
#include<cassert>
#include "types_and_ops.h"
#include "Symbol.h"
#include "Constant.h"


using namespace std;
Symbol::Symbol(const std::string& name, double* value)
	: name(name), value(value), count(0), type(GPL::DOUBLE) 
	{
		
	}
Symbol::Symbol(const std::string& name, double* value, int count)
	: name(name), value(value), count(count), type(GPL::DOUBLE) 
	{
		
	}
Symbol::Symbol(const std::string& name, int* value)
	: name(name), value(value), count(0), type(GPL::INT) 
	{
		
	}
Symbol::Symbol(const std::string& name, int* value, int count)
	: name(name), value(value), count(count), type(GPL::INT) 
	{
		
	}
Symbol::Symbol(const std::string& name, std::string* value)
	: name(name), value(value), count(0), type(GPL::STRING) 
	{
		
	}
Symbol::Symbol(const std::string& name, std::string* value, int count)
	: name(name), value(value), count(count), type(GPL::STRING) 
	{
		
	}
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
