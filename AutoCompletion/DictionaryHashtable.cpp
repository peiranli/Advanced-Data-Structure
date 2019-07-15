/** Peiran Li; Ziang Jing
 * Date: 2/2/2017
 * PA2
 * This is a class that implements Dictionary hash table
 */

#include "util.h"
#include "DictionaryHashtable.h"

/* Create a new Dictionary that uses a Hashset back end */
DictionaryHashtable::DictionaryHashtable(){}

/* Insert a word into the dictionary. */
bool DictionaryHashtable::insert(std::string word){
    std::pair<std::unordered_set<std::string>::iterator, bool> mypair;  
    mypair = this->myset.insert(word);
    return mypair.second;
}

/* Return true if word is in the dictionary, and false otherwise */
bool DictionaryHashtable::find(std::string word) const{
    std::unordered_set<std::string>::const_iterator it;
    it = this->myset.find(word);
    if(it == this->myset.end())
        return false;
    return true;
}

/* Destructor */
DictionaryHashtable::~DictionaryHashtable(){}
