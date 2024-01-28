#include<iostream>
#include<string>
#include<memory>
#include<vector>
#include<unordered_map>
#include<map>
#include "Symbol.h"
#include "types_and_ops.h"
#include "Symbol_table.h"
#include "Scope_manager.h"
using namespace std;

/*class Scope_manager{
	public:
		static Scope_manager& instance();
		void push_table();
		void pop_table();
		bool add_to_current_scope(std::shared_ptr<Symbol> sym);
		std::shared_ptr<Symbol> lookup(const std::string& name);
		bool defined_in_current_scope(const std::string& name);
		friend std::ostream& operator<<(std::ostream& os, const Scope_manager& sh);
		
		//Scope_manager(const Scope_manager&) = delete;
		//Scope_manager& operator=(const Scope_manager&) = delete;
	private:
		std::vector<std::shared_ptr<Symbol_table>> tables;
		//Scope_manager(){push_table();}
		Scope_manager() {std::shared_ptr<Symbol_table> newt(new Symbol_table);tables.push_back(newt);}
};*/
std::shared_ptr<Symbol> Scope_manager::lookup(const std::string& name) const
{
	for(int i=tables.size()-1; i>=0; i--)
	{
		if(tables[i]->lookup(name)!=nullptr)
		{
			return tables[i]->lookup(name);
		}
	}
	return nullptr;
}
bool Scope_manager::defined_in_current_scope(const std::string& name)
{
	if(tables.back()->lookup(name)==nullptr)
	{
		return false;
	}
	else
	{
		return true;
	}
}
bool Scope_manager::add_to_current_scope(std::shared_ptr<Symbol> sym)
{
	return tables.back()->insert(sym);
}

void Scope_manager::push_table()
{
	std::shared_ptr<Symbol_table> symt(new Symbol_table);
	tables.push_back(symt);
	
}
void Scope_manager::pop_table()
{
	if (tables.size() == 1)
	{
        throw std::underflow_error("Can't pop global symbol table");
    }
    else
	{
        tables.pop_back();
    }
}
Scope_manager& Scope_manager::instance()
{
	static Scope_manager the_instance;
	return the_instance;
}
std::ostream& operator<<(std::ostream& os, const Scope_manager& sh)
{
	for(int i = sh.tables.size() - 1; i >= 0; i--)
	{
		os << *sh.tables[i];//<<endl;
	}
	return os;
}

/*int main()
{
 // Symbol_table symtab;
	Scope_manager& symtab = Scope_manager::instance();

  double* double_oneofem=new double(3.141592);
  double* double_bunchofem=new double[4] {1.123, 2.234, 3.456, 7.899};
  string* string_oneofem=new string("hi there");
  string* string_bunchofem=new string[4]
    {"one", "two two", "three three three", "fo fo fo fo"};
  int* int_oneofem=new int(321);
  int* int_bunchofem=new int[4] {12, 34, 56, 78};

  symtab.add_to_current_scope(std::make_shared<Symbol>("alpha", string_oneofem));
  symtab.add_to_current_scope(std::make_shared<Symbol>("gamma", string_bunchofem, 4));
  symtab.add_to_current_scope(std::make_shared<Symbol>("beta", double_oneofem));
  symtab.add_to_current_scope(std::make_shared<Symbol>("delta", double_bunchofem, 4));
  symtab.add_to_current_scope(std::make_shared<Symbol>("zeta", int_oneofem));
  symtab.add_to_current_scope(std::make_shared<Symbol>("eta", int_bunchofem, 4));

  cout << symtab << endl;
  return 0;
}*/