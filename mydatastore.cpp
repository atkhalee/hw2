#include <sstream>
#include <iostream>
#include <iomanip>
#include <map>
#include <set>
#include "mydatastore.h"
#include "util.h"
#include "user.h"
#include "product.h"
#include <deque>

using namespace std;
MyDataStore::MyDataStore()
{

}
MyDataStore::~MyDataStore()
{
	map<string, User*>::iterator it;
	for (it = userMap.begin(); it != userMap.end(); ++it)
	{
	//deallocating  second term, as it will then deallocate first term
		delete it->second;
	}
	set<Product*>::iterator it1;
	for (it1 = productSet.begin(); it1 != productSet.end(); ++it1) {
		delete *it1; 
	}

}

 /**
  * Adds a product to the data store
  */
	//find all the keywords for the product --> 
	//then create a map for keywords associated with the products
void MyDataStore::addProduct(Product* p)
{
	productSet.insert(p); 
	//products are unique, so storing in set so it can be saved in a large set of product data
	//need to check a list of keywords --> if keywords fall into place --> then add product with that keyword
	//create a set of key words
	std::set<std::string> keywords_ = p->keywords();
	//iterate through keywords 
	
	for(set<std::string>::iterator it = keywords_.begin() ; it!= keywords_.end(); ++it)
	{
		//should convert to lower as keywords are all in lowercase
		map<std::string, std::set<Product*>>::iterator it1 = keyToProd.find(convToLower(*it));
		//if we found the key
		//cout<< *it<<endl;
		if(it1 != keyToProd.end())
		{
				it1->second.insert(p);
		} 
		else
		{
			//if keyword is not present, then we need to make a pair
			//and add the pair to keyToProd map
			std::set<Product*> temp;
			temp.insert(p); //add prouct to the temp set --> will then be paired with the keyword
			keyToProd.insert(make_pair(convToLower(*it) , temp));	
		}
	}
}

void MyDataStore::addUser(User* u)
{
	//a containr for user --> better to store in map because set would only store unique values
	//map between user name and the user *u
	//user had name, balance, and type --> more convenient if we just use the name of the user as the key
	userMap.insert(make_pair(u->getName(), u));
	userStorage.push_back(u->getName());
	std::deque<Product*> newCart;
	cart.insert(make_pair(u->getName(),newCart));
	//adding username to the cart
}

/**
		* Performs a search of products whose keywords match the given "terms"
		*  type 0 = AND search (intersection of results for each term) while
		*  type 1 = OR search (union of results for each term)
		*/
std::vector<Product*> MyDataStore:: search(std::vector<std::string>& terms, int type)
{
	//use for loop to iterate and convert terms into convToLower
	std::vector<std::string> term;
	for(std::vector<std::string>::iterator it3 = terms.begin(); it3!= terms.end() ; ++it3)
	{
		term.push_back(convToLower(*it3));
	}
	if(type ==0)
	{
		//the problem might be in the AND
		std::vector<Product*> prods;
		//need to compare two string sets
		//comparing the first item of product to the next item in product --> then adding it to the vector
		std::set<Product*> prev; 
		for (unsigned int i = 0 ; i< term.size(); i++)
		{
			if(i == 0){
				prev =keyToProd[term[0]];
				//prev = setIntersection(prev, keyToProd[term[i]]);
			}else{	
				prev = setIntersection(prev, keyToProd[term[i]]);
			}
		}
		//push set into a vector
		for(std::set<Product*>::iterator it = prev.begin() ; it!= prev.end(); ++it)
		{
			prods.push_back(*it);	
		}
		return prods;
		
	}else if (type == 1)
	{
		std::vector<Product*> prods;
		std::set<Product*> prev; 
		
		for(unsigned int n =0 ; n< term.size(); n++)
		{
			//std::cout<<term[n-1] << " " << term[n] <<endl;
			prev = setUnion(prev, keyToProd[term[n]]);
		}
		for(std::set<Product*>::iterator it1 = prev.begin() ; it1!= prev.end(); ++it1)
		{
			prods.push_back(*it1);	
		}
		return prods;
	}else
	{
		//need to return  an empty vector of products
		std::vector<Product*> empty;
		return empty;
	}
}

void MyDataStore::dump(std::ostream& ofile)
{
	ofile<< "<products>"<<endl;
		//iterate and output the product details (category, name, price, etc.)
		//void dump(std::ostream& os) const;
		for(std::set<Product*>::iterator it = productSet.begin(); it!= productSet.end(); ++it)
		{
			(*it)->dump(ofile);
		}
	ofile<< "</products>"<<endl;
	ofile<< "<users>"<<endl;
		for(std::map<std::string, User*>::iterator it1 = userMap.begin(); it1!=userMap.end(); ++it1)
		{
			it1->second->dump(ofile);
		}
	ofile<< "</users>"<<endl;
}

//std::map<std::string , deque<Product*>> cart;
void MyDataStore::addCart(std::string username , Product* prod)
{
	//use a map iterator to add to cart
	//use find user first --> 
	for(std::map<std::string, std::deque<Product*>>::iterator it = cart.begin() ; it!=cart.end(); ++it)
	{
		//if username is found
		if(it->first==username)
		{
				it->second.push_back(prod);
		}
		// if(it == cart.end())
		// {
		// 	std::cout<<"Invalid request"<<endl;
		// }
		// else{
		// 	//if username is not found
		// 	std::cout<<"Invalid Request"<<endl;
		// }
	}
	// std::map<std::string , std::deque<Product*>>::iterator it1 = cart.find(username);
	// if(it1==cart.end()){
	// 	std::cout<<"Invalid Request"<<endl;
	// }
	//std::map<std::string, User*> userMap
	std::map<std::string, User*>::iterator it1 = userMap.find(username);
	if(it1->first !=username){
		std::cout<<"Invalid request"<<endl;
	}
}

void MyDataStore::viewCart(std::string username)
{
	int item_n = 1;
	std::map<std::string, std::deque<Product*>>::iterator it = cart.find(username);
	if(it!=cart.end()){ //found the user
		for(std::deque<Product*>::iterator it1 = it->second.begin() ; it1 != it->second.end(); ++it1)
			{
				
				std::cout<<"Item " <<item_n <<endl;
				item_n++;  
				std::cout<<(*it1)->displayString()<<endl;
			}
		}else{
			std::cout<<"Invalid username"<<endl;
		}
	
	// for(std::map<std::string,std::deque<Product*>>::iterator it = cart.begin(); it !=cart.end(); ++it)
	// {
	// 	if(it->first == username)
	// 	{
	// 		//need to print the products in cart (and all of their information)
	// 		for(std::deque<Product*>::iterator it1 = it->second.begin() ; it1 != it->second.end(); ++it1)
	// 		{
	// 			std::cout<<(*it1)->displayString()<<endl;
	// 		}
	// 	}else if(it == cart.end()){
	// 		std::cout<<"Invalid username"<<endl;
	// 	}
	// }
}

void MyDataStore::buyCart(std::string username)
{
	//first iteratre through user's cart
	//use find for map
	std::map<std::string , std::deque<Product*>>::iterator it = cart.find(username);
	if(it!=cart.end()) //found username
	{
		for(std::deque<Product*>::iterator it1 = it->second.begin() ; it1 != it->second.end(); ++it1)
		{
			std::map<std::string, User*>::iterator userIt = userMap.find(username);
			if((userIt->second->getBalance() >=(*it1)->getPrice()) && ((*it1)->getQty()>0))
			{
						//we want to purchase the item
						//remove item from cart
						//reduce qty by 1
						//reduce balance by getPrice()
					(*it1)->subtractQty(1);
						//need an integer to deduct balance by
						//double amt = (*it1)->getPrice();
					userIt->second->deductAmount((*it1)->getPrice());
					it->second.pop_front();
			}
		}
	}else if(it == cart.end()){
			std::cout <<"Invalid username" <<endl;
			return;
		}
	
	// std::map<std::string, std::deque<Product*>>::iterator it = cart.find(username);
	// if(it == cart.end()){
	// 	std::cout <<"Invalid username" <<endl;
	// }
	
}