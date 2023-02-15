#ifndef CLOTHING_H
#define CLOTHING_H
#include <iostream>
#include <string>
#include <set>
#include <vector>
#include <algorithm>
#include "product.h"

class Clothing : public Product{
	public:
		Clothing(const std::string category, const std::string name, double price, int qty, std::string size, std::string brand);
		~Clothing();
		std::set<std::string> keywords() const;
		std::string displayString() const;
		void dump(std::ostream& os) const;

		/**
     * Accessors and mutators
     */
		std::string getSize() const;
		std::string getBrand() const;
	private: //not sure if it should be private or protected?
		std::string size_;
		std::string brand_;
};
#endif
