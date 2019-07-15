#include "BitOutputStream.h"


/** Send the buffer to the output, and clear it */
void BitOutputStream::flush() {
    out.put(buf);
    out.flush();
    buf = nbits = 0;
}

/** Write the least significant bit of the argument to
 * the bit buffer, and increment the bit buffer index.
 * But flush the buffer first, if it is full.
 */
void BitOutputStream::writeBit(int i) {
    // Is the bit buffer full? Then flush it.
    if(nbits == 8){
         flush();
    }   

    //Write the least significant bit of i into the buffer
    //at the current index
   
    buf = buf | (i << (7-nbits));
    // Increment the index
    nbits++;
}

/** Write one byte of the argument*/
void BitOutputStream::writeByte(int i) {
    out.put((unsigned char)i);
}

/** Write 4-byte int of the argument*/
void BitOutputStream::writeInt(int i) {
    int mask = 0xFF;
    unsigned char nextChar;
    //wirte the 4 byte integer in seperate bytes
    for(int j=3; j>=0; j--){
        nextChar = (unsigned char)((i >> j*8) & mask);
        out.put(nextChar);
    }
}
