/** Peiran Li; Ziang Jing
 * PA2
 * Date: 2/2/2017
 * This is a file to test runtime of two hash functions
 */


#include <iostream>
#include <string>
#include <fstream>
#include <vector>


using std::cout;
using std::endl;
using std::string;
//from stackoverflow url:http://stackoverflow.com/questions/8567238/hash-function-in-c-for-string-to-int
unsigned int hashfunction1( const string &key, int tableSize) {
   int hashVal = 0;

   for(unsigned int i = 0; i<key.length();  i++)
     hashVal = 37*hashVal+key[i];

   hashVal %= tableSize;

   if(hashVal<0)
     hashVal += tableSize;

   return (unsigned)hashVal;
 }


// from class material of CSE12	
unsigned int hashStringBase256(const string& key,unsigned int tableSize){
    unsigned int hashValue = 0;
    
    unsigned int BYTE_WIDTH = 8;   
    for (string::const_iterator i = key.begin();  i != key.end();  i++)
	{
		hashValue = (hashValue << BYTE_WIDTH) + (unsigned)*i;

		hashValue %= tableSize;
	}

    return hashValue;
    
}

int main(int argc, char** argv){
    
    std::string string1 = "rido";
    std::string string2 = "zhuru";
    std::string string3 = "jiz";
    int tablesize = 10;
    
    //test hash function value with expected value   
    unsigned int test1of1 = hashfunction1(string1, tablesize);
    unsigned int test2of1 = hashfunction1(string2, tablesize);
    unsigned int test3of1 = hashfunction1(string3, tablesize);
    
    unsigned int test1of2 = hashStringBase256(string1, tablesize);
    unsigned int test2of2 = hashStringBase256(string2, tablesize);
    unsigned int test3of2 = hashStringBase256(string3, tablesize);

    cout<< test1of1<<endl;

    cout<< test2of1<<endl;

    cout<< test3of1<<endl;

    cout<< test1of2<<endl;

    cout<< test2of2<<endl;
    
    cout<< test3of2<<endl;

    //open file stream
    std::ifstream dictFile;
	dictFile.open(argv[1]);
    
    unsigned int num_words = atoi(argv[2]);

    unsigned int table_size = 2000;
   
    //test for the first hash function
    std::vector<int> table(2000, 0);
    
    //record the number of elements in each slot
    string line = "";
    for (unsigned int i = 0; i < num_words; i++) {
        getline(dictFile, line);
        unsigned int hashVal = hashfunction1(line, table_size);
        table[hashVal]++; 
        if (dictFile.eof()) {
            std::cout << "Warning!  Only " << i << " words read from file." << endl;
            break;
        }
	}
    //close stream
    dictFile.close();

    //collect hits result
	std::vector<int> result(table_size, 0);
    for(unsigned int i = 0; i < table_size; i++){
			result[table[i]]++;
    }
    
    //print statistics
    cout << "Printing the statistics for hashFunction1 with hash table size " << table_size << endl;
    cout << "#hits    #slots receiving the #hits" << endl;
	for(unsigned int i=0; i < result.size(); i++){
		if(result[i] != 0)
			cout << i << "\t" << result[i] << endl;
    }
    //compute the average steps
	double sum = 0;
    for(unsigned int i=0; i< result.size(); i++){
        double innerSum =0;
        for(unsigned int j=i; j < result.size(); j++){
            innerSum += result[j];
        }
        sum += i*innerSum;

    }

    double ave = (double)sum/(double)num_words;
    cout << "The average number of steps for a successful search for hash function 1 would be "<< ave << endl;
    int max = 0;
    for(int i = 1; i<2000; i++){
		if(result[i]!=0 && i>max)
	    	max = i;		
	}
	cout << "The worst case steps that would be needed to find a word is " << max << endl;
 

    //tests for second hash function
    std::vector<int> table2(2000, 0);


    
    line = "";
	dictFile.open(argv[1]);
   
    //collect hits
    for (unsigned int i = 0; i < num_words; i++) {
        getline(dictFile, line);
        unsigned int hashVal = hashStringBase256(line, table_size);
        table2[hashVal]++;
        if (dictFile.eof()) {
            std::cout << "Warning!  Only " << i << " words read from file." << endl;
            break;
        }
    }
    dictFile.close();

    //collect number of slots
    std::vector<int> result2(table_size, 0);
    for(unsigned int i = 0; i < table_size; i++){
        result2[table2[i]]++;
    }

    cout << "Printing the statistics for hashFunction2 with hash table size " << table_size << endl;
    cout << "#hits    #slots receiving the #hits" << endl;
    for(unsigned int i=0; i < result2.size(); i++){
        if(result2[i] != 0)
            cout << i << "\t" << result2[i] << endl;
    }
    sum = 0;
    for(unsigned int i=0; i< result2.size(); i++){
		double innerSum =0;
		for(unsigned int j=i; j < result2.size(); j++){
			innerSum += result2[j];
		}
		sum += i*innerSum;
 			
    }
    double ave2 = (double)sum/(double)num_words;
    cout << "The average number of steps for a successful search for hash function 2 would be "<< ave2 << endl;
    max = 0;
    for(int i = 1; i< 2000; i++){
		if(result2[i]!=0 && i>max)
			max = i;
	}
    cout << "The worst case steps that would be needed to find a word is " << max << endl;
    dictFile.close();
}
