/** Peiran Li; Ziang Jing
 * PA2
 * Date: 2/2/2017
 * This is a file that contains test cases
 */




#include<iostream>
#include<fstream>
#include<string>
#include<algorithm>
#include<set>
#include<cstdlib>
#include "util.h"
#include "DictionaryTrie.h"
#include "DictionaryBST.h"
#include "DictionaryHashtable.h"
#define LETTERS 26
using namespace std;


int main(int argc, char** argv)
{

  //Initialize words
  vector<std::string> words;
  vector<string>::iterator wit;
  vector<string>::iterator wen;
  //initialize nonwords
  set<string> nope;
  set<string>::iterator nit;
  set<string>::iterator nen;

  //Initialize data structures
  DictionaryBST d_bst;
  DictionaryHashtable d_ht;
  DictionaryTrie dt;
  int t_bst, t_ht, tt;

  words.push_back("harry");
  words.push_back("sriram");
  words.push_back("cse");
  words.push_back("crucio");
  words.push_back("autocomplete");
  
  
  cout << "Inserting into Dictionaries..." << endl;

  wit = words.begin();
  wen = words.end();
  for(; wit != wen; ++wit)
    {
      cout << "Inserting: \"" << *wit << "\"... ";
      t_bst = d_bst.insert(*wit);
      t_ht = d_ht.insert(*wit);
      tt = dt.insert(*wit, 1);
      //cout << t_bst << " " << t_ht << " "<< tt << "... ";
      if(!t_bst)
	{
	  cout << "failed for DictionaryBST... ";
	}
      if(!t_ht)
	{
	  cout << "failed for DictionaryHashset... ";
	}
      if(!tt)
	{
	  cout << "failed for DictionaryTrie... ";
	}
      if(t_bst && t_ht && tt)
	{
	  cout << "PASSED! :D ";
	}
      cout << endl;
    }

  cout << endl << "Re-inserting elements that were just inserted into Dictionaries..." << endl;

  wit = words.begin();
  wen = words.end();
  for(; wit != wen; ++wit)
    {
      cout << "Inserting: \"" << *wit << "\"... ";
      t_bst = d_bst.insert(*wit);
      t_ht = d_ht.insert(*wit);
      tt = dt.insert(*wit, 0);
      if(t_bst)
        {
          cout << "failed for DictionaryBST... ";
        }
      if(t_ht)
        {
          cout << "failed for DictionaryHashset... ";
        }
      if(tt)
        {
          cout << "failed for DictionaryTrie... ";
        }
      if(!t_bst && !t_ht && !tt)
        {
          cout << "PASSED! :D ";
        }
      cout << endl;
    }

  cout << endl;
   
  //test insert
  dt.insert("ritardo",250);
  dt.insert("ahahah", 76476);
  dt.insert("ritardoDai",68123);
  dt.insert("nihao",4678);
  //test find
  bool findWord = dt.find("ahahah");
  if (findWord!=true) cout << "Incorrect find"<< endl;
  else cout<<"find ahahah correct"<< endl;
  findWord = dt.find("ritardo");
  if (findWord!=true) cout << "Incorrect find"<< endl;
  else cout<< "find ritardo correct"<<endl;
  //test freq
  int freq = dt.getFreq("harry");
  if(freq != 0)
	cout << "Incorrect freq" << endl;
  else cout<< "correct freq of harry" <<endl;
  dt.insert("harry",19273);
  freq = dt.getFreq("harry");
  if(freq != 19273)
	cout << "Incorrect freq" << endl;
  else cout<< "correct freq re-inserted harry"<<endl;
  freq = dt.getFreq("ritardo");
  if(freq != 250) cout<< "incorrect freq" <<endl;
  else cout<<"correct freq ritardo"<<endl;
  freq = dt.getFreq("ahahah");
  if(freq != 76476) cout<<"incorrect freq ahahah"<<endl;
  else cout<<"correct freq ahahah"<<endl;


  
/*You are supposed to add more test cases in this file */
  //test autocomplete
  /*if(argc != 2){
	cout << "Incorrect number of arguments" << endl;
	return -1;
  }*/
  DictionaryTrie dt2;
  ifstream wordIn;
  wordIn.open("shuffled_unique_freq_dict.txt", ifstream::in);
  unsigned int numWord = 40000;
  Utils::load_dict(dt2, wordIn, numWord);
  /*findWord = dt2.find("a");
 
  //more tests for find
  if (findWord!=true) cout << "Incorrect find"<< endl;
  else cout<<"find a correct"<< endl;
  findWord = dt2.find("a baby");
  if (findWord!=true) cout << "Incorrect find" << endl;
  else cout <<"find a baby correct" <<endl;
  */
  //tests for auto-completion
  std::vector<std::string> result = dt2.predictCompletions("bu",12);
  unsigned int i;
  for(i=0; i<result.size();i++){
	cout << i+1 << ": " << result[i] << endl; 
  } 
   


  return 0;
}
