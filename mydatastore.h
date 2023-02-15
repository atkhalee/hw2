#ifndef MYDATASTORE_H
#define MYDATASTORE_H
#include <string>
#include <set>
#include <vector>
#include <map>
#include "product.h"
#include "user.h"
#include "datastore.h"
#include "util.h"
#include <deque>
#include <queue>

//core functinality of the program
//derived DatStore class
//need to store the values in a database
class MyDataStore : public DataStore
{
	public:
	MyDataStore();
	~MyDataStore();
	/**
		* Adds a product to the data store
		*/
		void addProduct(Product* p);
		//find all the keywords for the product --> then create a map for keywords associated with the products
	//create a new data structure that shoule be a map that goes between string and the keywords
		/**
		* Adds a user to the data store
		*/
		void addUser(User* u);
		//map --> adding user for 
		//3-4 lines of code
		//making pair between user and prodcuct
	
		/**
		* Performs a search of products whose keywords match the given "terms"
		*  type 0 = AND search (intersection of results for each term) while
		*  type 1 = OR search (union of results for each term)
		*/
		std::vector<Product*> search(std::vector<std::string>& terms, int type);

		/*
		* Reproduce the database file from the current Products and User values
		*/
		void dump(std::ostream& ofile);
		
		//should include features of the menu options as additional functions
		//addcart, viewcart, buycart
		void addCart(std::string username , Product* prod);
		//print products from user specific cart
		void viewCart(std::string username);
		
		void buyCart(std::string username);
	private:
		//std::vector<Product*> prod_;
		//use a map instead between the string the product
		//you do not need to iterate over all products, just terms 
		//map between keyword and products
		std::set<Product*> productSet;
		std::vector<std::string> userStorage;
		std::map<std::string, std::set<Product*>> keyToProd;
		std::map<std::string, User*> userMap;
		std::map<std::string , std::deque<Product*>> cart;
		
		//map<std::string , std::setMProduct*>> 
		//linking the keyword to product
		//map<std::string , std::string> keys;
		//map<std::string , <Product*>> name;
		//std::vector<User*> use_;
		//map between a user and their products
		//map<std::string, set<Product*>> produsePair;

};
#endif