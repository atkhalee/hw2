#include <sstream>
#include <iomanip>
#include "book.h"
#include "util.h"
using namespace std;

Book::Book(const std::string category, const std::string name, double price, int qty, std::string author, std::string isbn): 
	Product(category, name, price, qty), 
	author_(author), 
	isbn_(isbn)
{


}

Book::~Book()
{

}

//1st function
std::set<std::string> Book :: keywords() const{
	//we need to parsestringtoWords(name)
	//need to check for the author or isbn numbers
	//author and name can be used interchangeably
	std::set<std::string> name = parseStringToWords(name_);
	std::set<std::string> author = parseStringToWords(author_);
	//std::set<std::string> isbn = parseStringToWords(isbn_);
	std::set<std::string> union__ = setUnion(name, author);
	//std::set<std::string> union_ = setUnion(union__, isbn);
	union__.insert(isbn_);
	return union__;
}
//2nd function
std::string Book::displayString() const{
	
	std::string message = name_ + "\n" + "Author: " + author_ + " ISBN: " + isbn_ + "\n";
	stringstream ss;
	ss << price_;
	std::string price = ss.str();
	stringstream ss1;
	ss1 << qty_;
	std::string qty = ss1.str();
	message += price + " " + qty + " left.";
	return message;
	//return name_ + "\nAuthor: " + author_ + "ISBN: " + isbn_ + "\n" + price + qty + "left.";
}
//3rd function
void Book::dump(std::ostream& os) const
{
    os << category_ << "\n" << name_ << "\n" << price_ << "\n" << qty_ << "\n" << isbn_ << "\n" << author_ << endl;
}

std::string Book::getAuthor()const
{
	return author_;
}

std::string Book::getISBN() const 
{
	return isbn_;
}