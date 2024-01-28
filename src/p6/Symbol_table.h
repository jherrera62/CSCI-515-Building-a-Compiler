#ifndef SYMBOL_TABLE_H
#define SYMBOL_TABLE_H
#include<iostream>
#include<string>
#include<memory>
#include<unordered_map>
#include "Symbol.h"
#include "types_and_ops.h"
class Symbol;
class Symbol_table {
	public:
		Symbol_table(){}
		std::shared_ptr<Symbol> lookup(const std::string& name) const;
		bool insert(std::shared_ptr<Symbol> sym);
		friend std::ostream& operator<<(std::ostream& os, const Symbol_table& symtab);
		
		//prevent compiler from generating these functions
		Symbol_table(const Symbol_table&) = delete;
		Symbol_table& operator=(const Symbol_table&) = delete;
		void erase(const std::string& name);

	private:
		std::unordered_map<std::string, std::shared_ptr<Symbol>> symbols;
};

#endif