#include "BitInputStream.h"


/** Fill the buffer from the input */
void BitInputStream::fill() {
    buf = in.get();
    nbits = 0;
}

/** Read the next bit from the bit buffer
 * Fill the buffer from the input stream first if needed
 * Return 1 if the bit read is 1
 * Return 0 if the bit read is 0.
 */
int BitInputStream::readBit() {
    //if all bits in the buffer are read, fill the buffer first
   
    if(nbits == 8){
        if(in.eof())
            return -1;
        fill();
    }


    //Get the bit at the appriopriate location in the bit
    //buffer, and return the appropriate int
    
    int bit = (buf >> 7) & 0x1;
    buf = buf << 1;
    //Increment the index 
    nbits++;
    return bit;
}

/** Read the next byte from the bit buffer
  * Return the byte readed
  */
int BitInputStream::readByte() {
    int byte = in.get();
    //stop when the istream is terminated
    if(in.eof())
        return -1;
    return byte;
}

/** Read the next integer from the bit buffer
  * Return the integer in the form of seperate 4 bytes
  */
int BitInputStream::readInt() {
    int result = 0;
    int nextByte;
    //get the 4 seperate byte of the integer
    for(int i = 3; i>=0; i--){
        nextByte = readByte();
        result |= (nextByte << i*8);
    }
    return result;
}
