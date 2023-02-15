#ifndef UTIL_H
#define UTIL_H

#include <string>
#include <iostream>
#include <set>


/** Complete the setIntersection and setUnion functions below
 *  in this header file (since they are templates).
 *  Both functions should run in time O(n*log(n)) and not O(n^2)
 */
template <typename T>
std::set<T> setIntersection(std::set<T>& s1, std::set<T>& s2)
{
//the values that are shared between sets 1 and 2
//New set with all elements that appear in both set1 and set2
//iterate through s1 --> use find on set 2 --> if the value is found, then insert s1 value into new items set

std::set<T> andElements;
typename std::set<T>::iterator it;
for(it = s1.begin() ; it!= s1.end(); ++it){
	typename std::set<T>:: iterator it2 = s2.find(*it);	
	if(it2 !=s2.end()){
		andElements.insert(*it);
	}
}

return andElements;


}
template <typename T>
std::set<T> setUnion(std::set<T>& s1, std::set<T>& s2)
{

//all the values from set 1 and 2 
//New set with all elements that appear in either set1 and set2
std::set<T> orElements;
typename std::set<T>::iterator it;
//iteratre through s1 and push all of s1 values into the new set
for(it = s1.begin() ; it!= s1.end() ; ++it ){
	//dereferncing it and placing its value in orElements
	orElements.insert(*it);
	
}

//for s2, we will also iterate through the set
//will need to check if the particular it matches the s1 value
//for s2, instead of iterating, we can search orElements using find() --> 
//if the value is not present, then we insert
//typename std::set<T>:: iterator it2 = orElements.find()
typename std::set<T>::iterator it1;
for(it1 = s2.begin() ; it1!= s2.end(); ++it1 ){
	typename std::set<T>:: iterator it2 = orElements.find(*it1);
	//if element is not found, then we need to insert into orElements
	//the find returns an iterator to the key if found, otherwise returns a pointer to the end
	if(it2 == orElements.end()){
		orElements.insert(*it1);
	}
}

return orElements;

}

/***********************************************/
/* Prototypes of functions defined in util.cpp */
/***********************************************/

std::string convToLower(std::string src);

std::set<std::string> parseStringToWords(std::string line);

// Used from http://stackoverflow.com/questions/216823/whats-the-best-way-to-trim-stdstring
// Removes any leading whitespace
std::string &ltrim(std::string &s) ;

// Removes any trailing whitespace
std::string &rtrim(std::string &s) ;

// Removes leading and trailing whitespace
std::string &trim(std::string &s) ;
#endif
