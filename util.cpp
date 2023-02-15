#include <iostream>
#include <sstream>
#include <cctype>
#include <algorithm>
#include "util.h"
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
using namespace std;
std::string convToLower(std::string src)
{
    std::transform(src.begin(), src.end(), src.begin(), ::tolower);
    return src;
}
//create a cpp file to test this code
/** Complete the code to convert a string containing a rawWord
    to a set of words based on the criteria given in the assignment **/
std::set<std::string> parseStringToWords(string rawWords)
{
	std::set<std::string>keyword;		
	std::string lower = convToLower(rawWords);
	//std::cout<<lower<<endl;
	//stringstream ss (lower); //split by whitespace
	//std::string temp;
	//std::string spacing;

			for(unsigned int i =0; i<lower.length(); i++){
			//ispunct return 0. if not punctuation character
			//returns nonzero if punctuation character
				if(ispunct(lower[i]) != 0){
					lower[i] = ' ';
				}
			}
			stringstream ss (lower);
			std::string temp;
	while(ss>>temp){
		if(temp.length() >= 2){
			keyword.insert(temp);
		}
	}	

	return keyword;
}

/**************************************************
 * COMPLETED - You may use the following functions
 **************************************************/

// Used from http://stackoverflow.com/questions/216823/whats-the-best-way-to-trim-stdstring
// trim from start
std::string &ltrim(std::string &s) {
    s.erase(s.begin(), 
	    std::find_if(s.begin(), 
			 s.end(), 
			 std::not1(std::ptr_fun<int, int>(std::isspace))));
    return s;
}

// trim from end
std::string &rtrim(std::string &s) {
    s.erase(
	    std::find_if(s.rbegin(), 
			 s.rend(), 
			 std::not1(std::ptr_fun<int, int>(std::isspace))).base(), 
	    s.end());
    return s;
}

// trim from both ends
std::string &trim(std::string &s) {
    return ltrim(rtrim(s));
}
