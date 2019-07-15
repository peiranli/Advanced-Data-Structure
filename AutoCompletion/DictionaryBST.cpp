/** Peiran Li; Ziang Jing
 * Date: 2/2/2017
 * PA2
 * This is a class that implements the DictionaryBST
 */

#include "util.h"
#include "DictionaryBST.h"

/* Create a new Dictionary that uses a BST back end */
DictionaryBST::DictionaryBST() {}

/* Insert a word into the dictionary. */
bool DictionaryBST::insert(std::string word) {
    std::pair<std::set<std::string>::iterator, bool> ret;
    ret = this->myset.insert(word); 
    return ret.second;
}

/* Return true if word is in the dictionary, and false otherwise */
bool DictionaryBST::find(std::string word) const {
    std::set<std::string>::iterator it;
    it = this->myset.find(word); 
    if(it == this->myset.end())
       return false;
    return true;
}

/* Destructor */
DictionaryBST::~DictionaryBST(){}
