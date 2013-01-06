/**********************************************************
 * File: HuffmanEncoding.cpp
 *
 * Implementation of the functions from HuffmanEncoding.h.
 * Most (if not all) of the code that you write for this
 * assignment will go into this file.
 */

#include "HuffmanEncoding.h"
#include "HuffmanPQueue.h"
#include "HuffmanTypes.h"
#include "foreach.h"
#include "map.h"
#include "strlib.h"
#include <iostream>


/* Function: getFrequencyTable
 * Usage: Map<ext_char, int> freq = getFrequencyTable(file);
 * --------------------------------------------------------
 * Given an input stream containing text, calculates the
 * frequencies of each character within that text and stores
 * the result as a Map from ext_chars to the number of times
 * that the character appears.
 *
 * This function will also set the frequency of the PSEUDO_EOF
 * character to be 1, which ensures that any future encoding
 * tree built from these frequencies will have an encoding for
 * the PSEUDO_EOF character.
 */
Map<ext_char, int> getFrequencyTable(istream& file) {
	Map<ext_char, int> freqTable;
    while(true){
        ext_char next = file.get();
        if(next == EOF){ //If next is pseudo eof, then add 1 in table for Pseudo EOF and break.
            freqTable[PSEUDO_EOF] = 1; 
            break;
        }
        if(next != NOT_A_CHAR){ //make sure ext_char is a character
            if(freqTable.containsKey(next))
                freqTable[next]++;
            else freqTable[next] = 1;
        }
    }
	return freqTable;	
}

/* This is function to Recursively build the Encoding Tree. It is called the function 
 * following after, buildEncodingTree. */

void recBuildTree(HuffmanPQueue& nodes){
    //Base Case: if nodes is empty or equal to 1 return.
    if(nodes.size() <= 1) return;
    
    //Take two nodes with lowest weights and combine them under the same node.
    Node* zero = nodes.dequeueMin();
    Node* one = nodes.dequeueMin();
    
    Node* newNode = new Node;
    newNode->character = NOT_A_CHAR;
    newNode->weight = zero->weight + one->weight;
    newNode->zero = zero;
    newNode->one = one;
    nodes.enqueue(newNode);

    //Repeat until only one node in the queue, representing the root node of the tree.
    recBuildTree(nodes);
}

/* Function: buildEncodingTree
 * Usage: Node* tree = buildEncodingTree(frequency);
 * --------------------------------------------------------
 * Given a map from extended characters to frequencies,
 * constructs a Huffman encoding tree from those frequencies
 * and returns a pointer to the root.
 *
 * This function can assume that there is always at least one
 * entry in the map, since the PSEUDO_EOF character will always
 * be present.
 */
Node* buildEncodingTree(Map<ext_char, int>& frequencies) {
	
    //Fill priority queue of nodes with each char:
    HuffmanPQueue nodes;
    
    foreach(ext_char chr in frequencies){ //for each chr, create a new node. 
        Node* newNode = new Node;   
        newNode->character = chr;
        newNode->weight = frequencies[chr];
        newNode->zero = NULL;
        newNode->one = NULL;
        nodes.enqueue(newNode);
    }
    recBuildTree(nodes);
    
    //if there are no nodes in the pqueue then must return NULL
    if(nodes.isEmpty()) return NULL;
    //otherwise there should only be one node in the queue so return it.
    else return nodes.dequeueMin();
}

/* Function: freeTree
 * Usage: freeTree(encodingTree);
 * --------------------------------------------------------
 * Deallocates all memory allocated for a given encoding
 * tree.
 */
void freeTree(Node* root) {
	if(root == NULL) return;
    freeTree(root->zero);
    freeTree(root->one);
    delete root;
}

/* This is a function to build tables used in encoding and decoding. */
void fillTables(Node* encodingTree, Map<ext_char, string>& encodingTable, Map<string, ext_char>& decodingTable,  string bits){
    if(encodingTree == NULL) return;
    if(encodingTree->character != NOT_A_CHAR){
        encodingTable[encodingTree->character] = bits;
        decodingTable[bits] = encodingTree->character;
    } else{
        fillTables(encodingTree->zero, encodingTable, decodingTable, bits + "0");
        fillTables(encodingTree->one, encodingTable, decodingTable, bits + "1");
    }
}


/* Function: encodeFile
 * Usage: encodeFile(source, encodingTree, output);
 * --------------------------------------------------------
 * Encodes the given file using the encoding specified by the
 * given encoding tree, then writes the result one bit at a
 * time to the specified output file.
 *
 * This function can assume the following:
 *
 *   - The encoding tree was constructed from the given file,
 *     so every character appears somewhere in the encoding
 *     tree.
 *
 *   - The output file already has the encoding table written
 *     to it, and the file cursor is at the end of the file.
 *     This means that you should just start writing the bits
 *     without seeking the file anywhere.
 */ 
void encodeFile(istream& infile, Node* encodingTree, obstream& outfile) {
	Map<ext_char, string> encodingTable;
    Map<string, ext_char> decodingTable;
    fillTables(encodingTree, encodingTable, decodingTable, "");
    
    //read from the infile ext_chars and encode them into the outfile.
    while(true){
        ext_char next = infile.get();
        if(encodingTable.containsKey(next)){
            string bits = encodingTable[next];
            //take each 1 or 0 and write to outfile:
            for(int i = 0; i < bits.size(); i++){
                int bit = stringToInteger(string() + bits[i]); //converting char in bits to an integer bit because writeBit take in type int.
                outfile.writeBit(bit);      
            }
        }
        //if next is the EOF then output the bits associated with the PSEUDO_EOF.
        if(next == EOF){
            string bits = encodingTable[PSEUDO_EOF];
            for(int i = 0; i < bits.size(); i++){
                int bit = stringToInteger(string() + bits[i]); //converting char in bits to an integer bit because writeBit take in type int.
                outfile.writeBit(bit);      
            }
            break;
        }   
    }
}

/* Function: decodeFile
 * Usage: decodeFile(encodedFile, encodingTree, resultFile);
 * --------------------------------------------------------
 * Decodes a file that has previously been encoded using the
 * encodeFile function.  You can assume the following:
 *
 *   - The encoding table has already been read from the input
 *     file, and the encoding tree parameter was constructed from
 *     this encoding table.
 *
 *   - The output file is open and ready for writing.
 */
void decodeFile(ibstream& infile, Node* encodingTree, ostream& file) {
   
    Map<ext_char, string> encodingTable;
    Map<string, ext_char> decodingTable;
    fillTables(encodingTree, encodingTable, decodingTable, "");
    
    //Read bits from the infile. When they match those of a key in the map, output the associated ext_char.
    string bits = "";
    while(true){
        int bit = infile.readBit();
        bits += integerToString(bit); //add the integer bit to the string bits
        if(decodingTable.containsKey(bits)){
            if(decodingTable[bits] == PSEUDO_EOF) break;
            file.put(decodingTable[bits]);
            bits = ""; //reset bits to empty string
        }
    }
}


/* NOTE!: Here I wrote the above decodeFile method using the encoding tree at each step. Logically, I
 * didn't think that it would be faster and Zach said that using the map would be better. However, when 
 * I tested this method usign the auto test given, it seemed to perform a little faster! Not entirely sure why 
 * this was.
 */

/*void decodeFile(ibstream& infile, Node* encodingTree, ostream& file) {
    Node* root = encodingTree;
    while (true) {
        int bit = infile.readBit(); 
        if(bit == EOF) break;
        
        if(bit == 0){
            root = root->zero;
        } else if(bit == 1) {
            root = root->one;
        } 
         
        if(root->character != NOT_A_CHAR) {
            if(root->character != PSEUDO_EOF){
                file.put(root->character);
                root = encodingTree;
            }else break;
        }
    }
}*/
 
 
/* Function: writeFileHeader
 * Usage: writeFileHeader(output, frequencies);
 * --------------------------------------------------------
 * Writes a table to the front of the specified output file
 * that contains information about the frequencies of all of
 * the letters in the input text.  This information can then
 * be used to decompress input files once they've been
 * compressed.
 *
 * This function is provided for you.  You are free to modify
 * it if you see fit, but if you do you must also update the
 * readFileHeader function defined below this one so that it
 * can properly read the data back.
 */
void writeFileHeader(obstream& outfile, Map<ext_char, int>& frequencies) {
	/* The format we will use is the following:
	 *
	 * First number: Total number of characters whose frequency is being
	 *               encoded.
	 * An appropriate number of pairs of the form [char][frequency][space],
	 * encoding the number of occurrences.
	 *
	 * No information about PSEUDO_EOF is written, since the frequency is
	 * always 1.
	 */
	 
	/* Verify that we have PSEUDO_EOF somewhere in this mapping. */
	if (!frequencies.containsKey(PSEUDO_EOF)) {
		error("No PSEUDO_EOF defined.");
	}
	
	/* Write how many encodings we're going to have.  Note the space after
	 * this number to ensure that we can read it back correctly.
	 */
	outfile << frequencies.size() - 1 << ' ';
	
	/* Now, write the letter/frequency pairs. */
	foreach (ext_char ch in frequencies) {
		/* Skip PSEUDO_EOF if we see it. */
		if (ch == PSEUDO_EOF) continue;
		
		/* Write out the letter and its frequency. */
		outfile << char(ch) << frequencies[ch] << ' ';
	}
}

/* Function: readFileHeader
 * Usage: Map<ext_char, int> freq = writeFileHeader(input);
 * --------------------------------------------------------
 * Reads a table to the front of the specified input file
 * that contains information about the frequencies of all of
 * the letters in the input text.  This information can then
 * be used to reconstruct the encoding tree for that file.
 *
 * This function is provided for you.  You are free to modify
 * it if you see fit, but if you do you must also update the
 * writeFileHeader function defined before this one so that it
 * can properly write the data.
 */
Map<ext_char, int> readFileHeader(ibstream& infile) {
	/* This function inverts the mapping we wrote out in the
	 * writeFileHeader function before.  If you make any
	 * changes to that function, be sure to change this one
	 * too!
	 */
	Map<ext_char, int> result;
	
	/* Read how many values we're going to read in. */
	int numValues;
	infile >> numValues;
	
	/* Skip trailing whitespace. */
	infile.get();
	
	/* Read those values in. */
	for (int i = 0; i < numValues; i++) {
		/* Get the character we're going to read. */
		ext_char ch = infile.get();
		
		/* Get the frequency. */
		int frequency;
		infile >> frequency;
		
		/* Skip the space character. */
		infile.get();
		
		/* Add this to the encoding table. */
		result[ch] = frequency;
	}
	
	/* Add in 1 for PSEUDO_EOF. */
	result[PSEUDO_EOF] = 1;
	return result;
}

/* Function: compress
 * Usage: compress(infile, outfile);
 * --------------------------------------------------------
 * Main entry point for the Huffman compressor.  Compresses
 * the file whose contents are specified by the input
 * ibstream, then writes the result to outfile.  Your final
 * task in this assignment will be to combine all of the
 * previous functions together to implement this function,
 * which should not require much logic of its own and should
 * primarily be glue code.
 */
void compress(ibstream& infile, obstream& outfile) {
    Map<ext_char, int> frequencies;
    frequencies= getFrequencyTable(infile);
    writeFileHeader(outfile, frequencies);
    
    infile.rewind();
    Node* tree = buildEncodingTree(frequencies);
    encodeFile(infile, tree, outfile);
    
    freeTree(tree);
}

/* Function: decompress
 * Usage: decompress(infile, outfile);
 * --------------------------------------------------------
 * Main entry point for the Huffman decompressor.
 * Decompresses the file whose contents are specified by the
 * input ibstream, then writes the decompressed version of
 * the file to the stream specified by outfile.  Your final
 * task in this assignment will be to combine all of the
 * previous functions together to implement this function,
 * which should not require much logic of its own and should
 * primarily be glue code.
 */
void decompress(ibstream& infile, ostream& outfile) {
    Map<ext_char, int> frequencies = readFileHeader(infile);
    Node* tree = buildEncodingTree(frequencies);
    
    decodeFile(infile, tree, outfile);
    
    freeTree(tree);
}

