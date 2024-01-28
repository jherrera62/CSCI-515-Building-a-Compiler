#include<iostream>
#include<string>
#include<memory>
#include<vector>
#include<unordered_map>
#include<map>
#include "Symbol.h"
#include "Symbol_table.h"
class Scope_manager{
	public:
		static Scope_manager& instance();
		void push_table();
		void pop_table();
		bool add_to_current_scope(std::shared_ptr<Symbol> sym);
		std::shared_ptr<Symbol> lookup(const std::string& name) const;
		bool defined_in_current_scope(const std::string& name);
		friend std::ostream& operator<<(std::ostream& os, const Scope_manager& sh);
		void erase(const std::string& name);
		
		//Scope_manager(const Scope_manager&) = delete;
		//Scope_manager& operator=(const Scope_manager&) = delete;
	private:
		std::vector<std::shared_ptr<Symbol_table>> tables;
		Scope_manager(){push_table();}
};