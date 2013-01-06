/*************************************************************************
 * File: ReferenceHuffmanEncoding.h
 *
 * Header file containing links into our reference implementations used
 * during testing.  You should not modify this header file, nor should
 * you use these functions in your code; they're for our testing harness
 * only.
 */

#include "HuffmanEncoding.h"

/* Reference solution for getFrequencyTable. */
Map<ext_char, int> referenceGetFrequencyTable(istream & file);

/* Reference solution for buildEncodingTree. */
Node *referenceBuildEncodingTree(Map<ext_char, int> frequencies);

/* Returns true if chars are unsigned and false if they are signed */
bool referenceCharUnsignedTest();