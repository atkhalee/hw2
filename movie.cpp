#include <sstream>
#include <iomanip>
#include "movie.h"
#include "util.h"
using namespace std;

Movie::Movie(const std::string category, const std::string name, double price, int qty, std::string genre, std::string rating): 
	Product(category, name, price, qty), 
	genre_(genre), 
	rating_(rating)
{


}
Movie::~Movie()
{

}

std::set<std::string> Movie :: keywords() const
{
	//we need to parsestringtoWords(name)
	//need to check for the author or isbn numbers
	//author and name can be used interchangeably
	std::set<std::string> name = parseStringToWords(name_);
	std::set<std::string> genre = parseStringToWords(genre_);
	//std::set<std::string> rating = parseStringToWords(rating_);
	std::set<std::string> union__ = setUnion(name, genre);
	//std::set<std::string> union_ = setUnion(union__, rating);
	union__.insert(rating_);
	return union__;
}

std::string Movie::displayString() const
{
	//need to use stringstream
	//format is name, genre_, rating_, price, quantity
	std::string message = name_ + "\n" + "Genre: " + genre_ + " Rating: " + rating_ + "\n";
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

void Movie::dump(std::ostream& os) const
{
    os << category_ << "\n" << name_ << "\n" << price_ << "\n" << qty_ << "\n" << genre_ << "\n" << rating_ << endl;
}

std::string Movie::getGenre()const
{
	return genre_;
}

std::string Movie::getRating() const 
{
	return rating_;
}
