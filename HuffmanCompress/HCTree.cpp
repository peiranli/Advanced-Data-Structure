#include "HCTree.h"
#include <fstream>
#include <vector>
#include <iostream>
#include <stack>


/** Use the Huffman algorithm to build a Huffman coding trie.
    *  PRECONDITION: freqs is a vector of ints, such that freqs[i] is 
    *  the frequency of occurrence of byte i in the message.
    *  POSTCONDITION:  root points to the root of the trie,
    *  and leaves[i] points to the leaf node containing byte i.
    */
void HCTree::build(const vector<int>& freqs){
    priority_queue<HCNode*, vector<HCNode*>, HCNodePtrComp> pq;
    //add the non-zero freq symbols in to leave[] and pq
    for(int i=0; i<freqs.size(); i++){
        if(freqs[i]==0) continue;
        leaves[i]= new HCNode(freqs[i], i);
        //increase the amount of distinct leaves
        numSymbol++;
        //increase the amount of total leaces
        numSize+=freqs[i];
        pq.push(leaves[i]);
    }
    //build the tree from bot to top
    while(pq.size()>1){
        HCNode* n1 = pq.top();
        pq.pop();
        HCNode* n2 = pq.top();
        pq.pop();
        HCNode *parent  = new HCNode(n1->count+n2->count, n1->symbol, n1, n2,0);
        n1->p = parent;
        n2->p = parent;
        pq.push(parent);
    }
    //empty tree corner case
    if(pq.size() == 0){
        root = nullptr;
    }
    else root = pq.top();
	
}


 /** Write to the given BitOutputStream
     *  the sequence of bits coding the given symbol.
     *  PRECONDITION: build() has been called, to create the coding
     *  tree, and initialize root pointer and leaves vector.
     */
void HCTree::encode(byte symbol, BitOutputStream& out) const{
    HCNode* curr = leaves[symbol];
    //use the stack structure to encode
    stack<int> temp;
    while(curr != root){
        if(curr->p->c0 == curr)
            temp.push(0);
        else if(curr->p->c1 == curr)
            temp.push(1);
        curr = curr->p;

    }
    //pop stack and encode with BitOut
    while(!temp.empty()){
        int code = temp.top();
        temp.pop();
        out.writeBit(code);
    }
}

 /** Write to the given ofstream
     *  the sequence of bits (as ASCII) coding the given symbol.
     *  PRECONDITION: build() has been called, to create the coding
     *  tree, and initialize root pointer and leaves vector.
     *  THIS METHOD IS USEFUL FOR THE CHECKPOINT BUT SHOULD NOT 
     *  BE USED IN THE FINAL SUBMISSION.
     */
void HCTree::encode(byte symbol, ofstream& out) const {
    HCNode* curr = leaves[symbol];
    //use stack structure to encode
    stack<int> temp;
    while(curr != root){
        if(curr->p->c0 == curr)
            temp.push(0);
        else if(curr->p->c1 == curr)
            temp.push(1);
        curr = curr->p;
    }
    //pop stack and encode with ostream   
    while(!temp.empty()){
        int code = temp.top();
        temp.pop();
        out << code;
    }
}

/** Return symbol coded in the next sequence of bits from the stream.
     *  PRECONDITION: build() has been called, to create the coding
     *  tree, and initialize root pointer and leaves vector.
     */
int HCTree::decode(BitInputStream& in) const{
    HCNode* curr = root;
    int nextBit;
    //find the position of the BitInput in the Huffman tree
    while(curr->c0 != nullptr && curr->c1 != nullptr){
        nextBit = in.readBit();
        if(nextBit == 1) {
            curr = curr->c1;
        }else if(nextBit == 0) {
            curr = curr->c0;
        }
    }
    return curr->symbol;
}

 /** Return the symbol coded in the next sequence of bits (represented as 
     *  ASCII text) from the ifstream.
     *  PRECONDITION: build() has been called, to create the coding
     *  tree, and initialize root pointer and leaves vector.
     *  THIS METHOD IS USEFUL FOR THE CHECKPOINT BUT SHOULD NOT BE USED
     *  IN THE FINAL SUBMISSION.
     */
int HCTree::decode(ifstream& in) const {
    HCNode* curr = root;
    unsigned char nextChar;
    //find the position of the istream in the Huffman tree
    while(curr->c0 != nullptr && curr->c1 != nullptr){
        in >> nextChar;
        if(nextChar == '1'){
            curr = curr->c1;
        }else if(nextChar == '0'){
            curr = curr->c0;
        }
    }
    return curr->symbol;
}

/** destructor*/
HCTree::~HCTree(){
    deleteAll(root);
}

/** helper method for destructor to delete all of the HCNode in the tree*/
void HCTree::deleteAll(HCNode* node){
    if(node != nullptr ){
        if(node->c0)
            deleteAll(node->c0);
        if(node->c1)
            deleteAll(node->c1);
        delete(node);
    }
}

/** write the efficient header use BitOuputStream*/
void HCTree::writeHeader(BitOutputStream& out) {
    //write the amount of distinct leaves and the amount of the total 
    //freqs in the front of the header
    out.writeInt(this->numSymbol);
    out.writeInt(this->numSize);
    //node information part
    writeNode(root, out);
}

/** recursively loop through the tree and write the information in the node
      * with BitIO
      */
void HCTree::writeNode(HCNode* node, BitOutputStream& out) {
    if(isLeaf(node)){
        out.writeByte('0');//mark for leaf node
        out.writeByte(node->symbol);
    }else{
        out.writeByte('1');//mark for medium node
        writeNode(node->c0, out);
        writeNode(node->c1, out);
    }
}

/** read the efficient header bitwisely with BitInputStream
     * there are numSymbol, numSize and the node information in the header
     */
void HCTree::readHeader(BitInputStream& in) {
   //read the two numbers first
   this->numSymbol = in.readInt(); 
   this->numSize = in.readInt();
   root = readNode(root, in);
}

/** read the part of node information in the efficient header
     * use the information to build a tree
     */
HCNode* HCTree::readNode(HCNode* node,BitInputStream& in) {
    if(this->symbolRead == this->numSymbol)
        return node;
    unsigned char nextByte = in.readByte();
    //base case for leaf node
    if(nextByte == '0'){
        unsigned char symbol  = in.readByte();
        node = new HCNode(0, symbol,0,0,0);
        this->symbolRead++;}
    //recursively create medium node
    else if(nextByte == '1'){
        node = new HCNode(0,0,0,0,0);
        node->c0 = readNode(node->c0,in);
        node->c1 = readNode(node->c1,in);
        node->c0->p = node;
        node->c1->p = node;
    }
    return node;
}

/** return the sum of the total freqs*/
int HCTree::getNumSize(){
    return numSize;
}

/** method to determine whether a node in the tree is a leaf or not
      * return true if it is a leaf
      * return false if it is not
      */
bool HCTree::isLeaf(HCNode* node) const{
    return (node->c0 == nullptr && node->c1 == nullptr);
}
