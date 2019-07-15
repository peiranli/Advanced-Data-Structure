/** Peiran Li; Ziang Jing
 * PA2
 * Date: 2/2/2017
 * This is a class that implements Dictionary using TST
 */

#include "util.h"
#include "DictionaryTrie.h"


/* TSTNode constructor */
DictionaryTrie::TSTNode::TSTNode(char c){
  this->c = c;
  this->left = this->mid = this->right = nullptr;
  this->freq = 0;  
  this->isWord = false;
  this->text = "";	
}

/* TSTNode distructor*/
DictionaryTrie::TSTNode::~TSTNode() {}

/* Create a new Dictionary that uses a Trie back end */
DictionaryTrie::DictionaryTrie(){
  root = nullptr;
}

/* Insert a word with its frequency into the dictionary.
 * Return true if the word was inserted, and false if it
 * was not (i.e. it was already in the dictionary or it was
 * invalid (empty string) */
bool DictionaryTrie::insert(std::string word, unsigned int freq)
{
  DictionaryTrie::TSTNode* curr;
  //if it is an empty string
  if(word.size() == 0)
  	return false;

  //if the word exists in present Trie
  if(find(word)){
    curr = findNode(root,word);
	curr->freq = freq;
	return false;
  }
  
  //call insertHelp to recursively insert
  root = insertHelp(root, word, 0, freq);
  
  return true;
  
  
}


/* Get the frequency of given node*/
int DictionaryTrie::getFreq(std::string word){
  DictionaryTrie::TSTNode* curr = findNode(root,word);
  if(curr == nullptr)
	return -1;
  return (unsigned)curr->freq;
}

/* Take four parameters that recursively insert nodes of word*/
DictionaryTrie::TSTNode* DictionaryTrie::insertHelp(DictionaryTrie::TSTNode* curr, std::string word,unsigned int i, unsigned int freq){
	//if current node is null, simply create a new one
    if(curr == nullptr){
		curr = new DictionaryTrie::TSTNode(word[i]);
        curr->text = word.substr(0,i+1);
	}
    //if character is less than current node
    //recursively insert to the left
	if(curr->c > word[i]){
		curr->left = insertHelp((curr->left), word, i, freq);
	}
    //recursively insert to right
	else if(curr->c < word[i]){
		curr->right = insertHelp((curr->right), word, i, freq);
	}
    //if the word exists, simply set to wordNode
    //recusively insert to mid 
	else{
		if(i == word.size()-1){
			curr->isWord = true;
			curr->freq = freq;
  			curr->text = word.substr(0,i+1);
        }
		else{
			curr->mid = insertHelp((curr->mid), word, i+1, freq);
			curr->text = word.substr(0,i+1);
		}
	}
    //return the current node
	return curr;
    			
}

/* Find the word node and return a pointer*/
DictionaryTrie::TSTNode* DictionaryTrie::findNode(DictionaryTrie::TSTNode* curr, std::string word){
	unsigned int i;
    DictionaryTrie::TSTNode* parent;
	for(i=0; i<word.size(); ){
        //if it does not reach the last char
        //simply return null
		if(curr == nullptr)
			return nullptr;
        //keep finding left
		if(word[i] < curr->c){
			parent = curr;
			curr = curr->left;
		}
        //keep finding right
		else if(word[i] > curr->c){
			parent = curr;
			curr = curr->right;
		}
        //advance and check for next char		
		else{
			parent = curr;
			curr = curr->mid;
			i++;
		}
	}
	return parent;

}
/* Return true if word is in the dictionary, and false otherwise */
bool DictionaryTrie::find(std::string word) const
{
  if(!root)
	return false;
  DictionaryTrie::TSTNode* curr = root;
  DictionaryTrie::TSTNode* parent;
  unsigned int i = 0;
  //basically same as findNode but different return type
  while(i < word.size()){
    if(curr == nullptr){
        return false;
    }
    parent = curr;
    if(word[i] < curr->c){
        curr = curr->left;
    }
    else if(word[i] > curr->c){
        curr= curr->right;
    }
    else{
        curr = curr->mid;
        i++;
    }
  } 
  return parent->isWord;
}

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
std::vector<std::string> DictionaryTrie::predictCompletions(std::string prefix, unsigned int num_completions)
{
  std::vector<std::string> words;
  //if prefix is empty or does not exist, return empty vector
  if(prefix.size() == 0 || (findNode(root,prefix) == nullptr)){
     std::cout << "Invalid input, please retry with correct input" << std::endl;
	 return words;
  }
  //find the node with the prefix in it
  DictionaryTrie::TSTNode* curr = findNode(root, prefix);
  std::stack<DictionaryTrie::TSTNode*> temp;
  std::set<std::pair<unsigned int, std::string>> wordSet;
  //push a first word
  if(curr->isWord) 
     wordSet.insert(std::pair<unsigned int , std::string>(curr->freq, curr->text));
  temp.push(curr->mid);
  // Depth first search to add all word node
  while(temp.size() != 0){
     DictionaryTrie::TSTNode* tmpNode = temp.top();
     temp.pop();
     if(tmpNode->isWord){
		wordSet.insert(std::pair<unsigned int, std::string>(tmpNode->freq, tmpNode->text));
     }
     if(tmpNode->mid)
		temp.push(tmpNode->mid);
     if(tmpNode->left)
		temp.push(tmpNode->left);
     if(tmpNode->right)
		temp.push(tmpNode->right);
  }
   
  unsigned int i;	
  //create set that store pairs in which contains the frequency and word
  std::set<std::pair<unsigned int, std::string>>::reverse_iterator it;
  it = wordSet.rbegin();
  //output the highest frequent words
  for(i=0; i<num_completions; i++){
     words.push_back((*it).second);	 
     it++;
  }
  return words;
}

/* Destructor */
DictionaryTrie::~DictionaryTrie(){
  deleteAll(root);
}

/* Destructor helper  recursively delete all the nodes*/
void DictionaryTrie::deleteAll(DictionaryTrie::TSTNode* curr){
  if(curr->left)
	deleteAll(curr->left);
  if(curr->right)
	deleteAll(curr->right);
  if(curr->mid)
	deleteAll(curr->mid);
  delete curr;
}


