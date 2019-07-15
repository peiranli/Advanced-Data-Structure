/**
 *  CSE 100 PA3 C++ Autocomplete
 *  Authors: Jor-el Briones, Christine Alvarado
 */

#ifndef DICTIONARY_TRIE_H
#define DICTIONARY_TRIE_H

#include <iostream>
#include <vector>
#include <string>
#include <cstring>
#include <set>
#include <stack>
#include <utility>
/**
 *  The class for a dictionary ADT, implemented as a trie
 *  You may implement this class as either a mulit-way trie
 *  or a ternary search trie, but you must use one or the other.
 *
 */
class DictionaryTrie
{
public:
  
 /** This inner class is for TST node which contains 
 * left; right; mid; the string; whether the node is a word;
 * and a char data
 */
 class TSTNode{
  
  public:
      //node pointers
	  TSTNode* left;
	  TSTNode* right;
  	  TSTNode* mid;
    
      /*Constructor*/
	  TSTNode(char c);
	  
      /*Destructor*/
      ~TSTNode();
	  
      //member fields
      std::string text;
	  unsigned int freq;
      bool isWord;
      char c;



  };
  /* Create a new Dictionary that uses a Trie back end */
  DictionaryTrie();

  /* Insert a word with its frequency into the dictionary.
   * Return true if the word was inserted, and false if it
   * was not (i.e. it was already in the dictionary or it was
   * invalid (empty string) */
  bool insert(std::string word, unsigned int freq);

  /* Return true if word is in the dictionary, and false otherwise */
  bool find(std::string word) const;

  /* Return up to num_completions of the most frequent completions
   * of the prefix, such that the completions are words in the dictionary.
   * These completions should be listed from most frequent to least.
   * If there are fewer than num_completions legal completions, this
   * function returns a vector with as many completions as possible.
   * If no completions exist, then the function returns a vector of size 0.
   * The prefix itself might be included in the returned words if the prefix
   * is a word (and is among the num_completions most frequent completions
   * of the prefix)
   */
  std::vector<std::string>
  predictCompletions(std::string prefix, unsigned int num_completions);

  /* Destructor */
  ~DictionaryTrie();
  
  int getFreq(std::string word);
private:
  // Add your own data members and methods here
  DictionaryTrie::TSTNode* root;

  /* Helper that can return the pointer to given word*/
  static DictionaryTrie::TSTNode* findNode(TSTNode* curr, std::string word);

  /* Helper of insert which can recursively insert a word*/
  static DictionaryTrie::TSTNode* insertHelp(TSTNode* curr, std::string word, unsigned int i, unsigned int freq);

  /*Destructor helper*/
  static void deleteAll(TSTNode* curr); 

};

#endif // DICTIONARY_TRIE_H
