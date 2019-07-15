#include <iostream>
#include <fstream>
#include <vector>
#include <iomanip>
#include "HCNode.h"
#include "HCTree.h"

/**Compress using the efficient header takes a little bit long
 * about 11 minutes, but the uncompress is very fast, no more than 
 * 1 minute. In total the whole process will take less than 12 minutes
 */

using namespace std;

int main(int argc, char** argv){
    //Open the input file for reading
    ifstream in;
    in.open(argv[1],ios_base::binary);
    vector<int> vecNum(256,0);
    int size = 0;
    BitInputStream bitIn(in);
    /*int next;
    int newLineChar;
    for(int i=0; i < vecNum.size(); i++){
        next = in.get();
        newLineChar = in.get();
        vecNum[i] = next;
        //in >> vecNum[i];
        size += vecNum[i];
    }*/

    //cout << "size: " << size << endl;
    HCTree myHTree;
    //myHTree.build(vecNum);
  
    myHTree.readHeader(bitIn);
    ofstream out;
    out.open(argv[2],ios_base::binary);
    BitOutputStream bitOut(out);
    int count=0;
    for(;count<myHTree.getNumSize();count++)
    {
        if(in.eof())
            break;
        unsigned char symbol = myHTree.decode(bitIn);
        out.put(symbol);
        //out << symbol;
    }
    in.close();
    out.close();

    return 0;
}

