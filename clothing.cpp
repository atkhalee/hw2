#include <sstream>
#include <iomanip>
#include "clothing.h"
#include "util.h"
using namespace std;

Clothing::Clothing(const std::string category, const std::string name, double price, int qty, std::string size, std::string brand): 
	Product(category, name, price, qty), 
	size_(size), 
	brand_(brand)
{


}
Clothing::~Clothing()
{

}

std::set<std::string> Clothing :: keywords() const
{
	//we need to parsestringtoWords(name)
	//need to check for the author or isbn numbers
	//author and name can be used interchangeably
	std::set<std::string> name = parseStringToWords(name_);
	std::set<std::string> size = parseStringToWords(size_);
	std::set<std::string> brand = parseStringToWords(brand_);
	std::set<std::string> union__ = setUnion(name, size);
	std::set<std::string> union_ = setUnion(union__, brand);
	//union__.insert(brand);
	return union_;
}

std::string Clothing::displayString() const
{
	//need to use stringstream
	//format is name, size, brand, price, quantity
	std::string message = name_ + "\n" + "Size: " + size_ + " Brand: " + brand_ + "\n";
	//price and quantity are int and double (not strings) can converting using stringstream or to_string

	stringstream ss;
	ss << price_;
	std::string price = ss.str();
	stringstream ss1;
	ss1 << qty_;
	std::string qty = ss1.str();
	message += price + " " + qty + " left.";
	return message;
	
}

void Clothing::dump(std::ostream& os) const
{
    os << category_ << "\n" << name_ << "\n" << price_ << "\n" << qty_ << "\n" << size_ << "\n" << brand_ << endl;
}

std::string Clothing::getSize()const
{
	return size_;
}

std::string Clothing::getBrand() const 
{
	return brand_;
}
