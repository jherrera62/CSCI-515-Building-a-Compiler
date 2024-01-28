#include<iostream>
#include<string>
#include<memory>
#include<unordered_map>
#include<map>
#include "Symbol.h"
#include "types_and_ops.h"
#include "Symbol_table.h"

using namespace std;
std::shared_ptr<Symbol> Symbol_table::lookup(const std::string& name) const
{
	auto result = symbols.find(name);
	if(result!=symbols.end())
	{
		return result->second;
	}
	else
	{
		return nullptr;	
	}
}
bool Symbol_table::insert(std::shared_ptr<Symbol> sym)
{
	if(lookup(sym->get_name())==nullptr)
	{
		symbols.insert({sym->get_name(), sym});
		return true;
	}
	else
	{
		return false;
	}
}
std::ostream& operator<<(std::ostream& os, const Symbol_table& symtab)
{
	map<std::string, std::shared_ptr<Symbol>> sym2;
	
	for(auto& elm: symtab.symbols)
	{
		sym2.insert({elm.first, elm.second});
	}
	for(auto& elm: sym2)
	{
		os<<*elm.second;
		/*if(elm.second->get_type()==1)
		{
			os<<"int"<<" "<<*elm.second<<endl;
		}
		if(elm.second->get_type()==2)
		{
			os<<"double"<<" "<<*elm.second<<endl;
		}
		if(elm.second->get_type()==4)
		{
			os<<"string"<<" "<<*elm.second<<endl;
		}*/
	}
	return os;
}
void Symbol_table::erase(const std::string& name)
{
	symbols.erase(name);
}
/*int main()
{
  Symbol_table symtab;

  double* double_oneofem=new double(3.141592);
  double* double_bunchofem=new double[4] {1.123, 2.234, 3.456, 7.899};
  string* string_oneofem=new string("hi there");
  string* string_bunchofem=new string[4]
    {"one", "two two", "three three three", "fo fo fo fo"};
  int* int_oneofem=new int(321);
  int* int_bunchofem=new int[4] {12, 34, 56, 78};

  symtab.insert(std::make_shared<Symbol>("alpha", string_oneofem));
  symtab.insert(std::make_shared<Symbol>("gamma", string_bunchofem, 4));
  symtab.insert(std::make_shared<Symbol>("beta", double_oneofem));
  symtab.insert(std::make_shared<Symbol>("delta", double_bunchofem, 4));
  symtab.insert(std::make_shared<Symbol>("zeta", int_oneofem));
  symtab.insert(std::make_shared<Symbol>("eta", int_bunchofem, 4));

  cout << symtab << endl;
  return 0;
}*/