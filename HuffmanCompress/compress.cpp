#include <iostream>
#include <fstream>
#include <vector>
#include <iomanip>
#include "HCTree.h"

/** This compress using the efficient header takes a little bit long
 * about 11 minutes, but the uncompress is very fast, no more than 
 * 1 minute. In total the whole process will take less than 12 minutes
 */
using namespace std;
int main(int argc, char** argv){
    //Open the input file for reading
    ifstream in;
    in.open(argv[1],ios_base::binary);
     
    vector<int> vecNum(256, 0);
    unsigned char nextChar;
    while(1){
        //read bytes
        nextChar = in.get();
        //in >> nextChar;
        if(in.eof()) break;
        //count freq
        vecNum[nextChar]++;
    }
    in.close();

    HCTree myHTree;
    myHTree.build(vecNum);

    ofstream out;
    out.open(argv[2]);
    BitOutputStream bitOut(out);
    /*for(int i=0; i < vecNum.size(); i++){
        out.put(vecNum[i]);
        out.put('\n');
        //out << vecNum[i] << endl;
    }*/
    
    //write header
    myHTree.writeHeader(bitOut);

    //open again
    in.open(argv[1],ios_base::binary);
    while(1){
        //read bytes
        nextChar = in.get();
        if(in.eof()) break;
        myHTree.encode((byte)nextChar, bitOut);
    }
    bitOut.flush();
    in.close();
    out.close();

    return 0;
}


