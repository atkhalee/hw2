#ifndef BOOK_H
#define BOOK_H
#include <iostream>
#include <string>
#include <set>
#include <vector>
#include <algorithm>
#include "product.h"

class Book : public Product{
	public:
		Book(const std::string category, const std::string name, double price, int qty, std::string author, std::string isbn);
		~Book();
		//keywords require the displayStringtoWords function
		std::set<std::string> keywords() const;
		std::string displayString() const;
		void dump(std::ostream& os) const;
		/**
     * Accessors and mutators
     */
		std::string getAuthor() const;
		std::string getISBN() const;
	private: //not sure if it should be private or protected?
		std::string author_;
		std::string isbn_;
};
#endif
