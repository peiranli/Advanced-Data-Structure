/** Peiran Li; Ziang Jing
 * PA2
 * Date:2/2/2017
 * This is a file of examining runtime of three data structures
 */



#include <iostream>
#include <fstream>
#include <sstream>
#include "util.h"
#include "DictionaryTrie.h"
#include "DictionaryBST.h"
#include "DictionaryHashtable.h"

int main(int argc, char**argv){
   if(argc != 5){
       std::cout << "Incorrect number of arguments" << std::endl;
       return -1;
   }
   
   std::ifstream dictFile;

   Timer t;
   //parse the input
   int min_size = atoi(argv[1]);
   int step_size = atoi(argv[2]);
   int num_iterations = atoi(argv[3]);
   int test_size = 100;

   //test the runtime of BST
   std::cout << "BST" << std::endl;
   for(int i = 0; i<num_iterations; i++){
      dictFile.open(argv[4]);
      DictionaryBST * dictBST = new DictionaryBST();
      std::vector<std::string> wordsToFind;
      Utils::load_dict(*dictBST, dictFile, min_size+ i*step_size);
      Utils::load_vector(wordsToFind, dictFile, test_size);
   
      t.begin_timer();
      for(std::string w : wordsToFind)
         dictBST->find(w);
      long long time  = t.end_timer();

      std::cout << min_size+i*step_size << "\t" << time <<std::endl;

      delete dictBST;
      dictFile.close();
   }


   //test the runtime of hash table
   std::cout << "Hashtable"<<std::endl;
   for(int i = 0; i<num_iterations; i++){
      dictFile.open(argv[4]);
      DictionaryHashtable * dictHT = new DictionaryHashtable();
      std::vector<std::string> wordsToFind;
      Utils::load_dict(*dictHT, dictFile, min_size+ i*step_size);
      Utils::load_vector(wordsToFind, dictFile, test_size);

      t.begin_timer();
      for(std::string w : wordsToFind)
         dictHT->find(w);
      long long time  = t.end_timer();

      std::cout << min_size+i*step_size << "\t" << time <<std::endl;

      delete dictHT;
      dictFile.close();
   }
   
   //test the runtime of TST
   std::cout << "TST" << std::endl;
   for(int i = 0; i<num_iterations; i++){
      dictFile.open(argv[4]);
      DictionaryTrie * dictTST = new DictionaryTrie();
      std::vector<std::string> wordsToFind;
      Utils::load_dict(*dictTST, dictFile, min_size+ i*step_size);
      Utils::load_vector(wordsToFind, dictFile, test_size);

      t.begin_timer();
      for(std::string w : wordsToFind)
         dictTST->find(w);
      long long time  = t.end_timer();

      std::cout << min_size+i*step_size << "\t" << time <<std::endl;

      delete dictTST;
      dictFile.close();
   }







    return 0;
}

