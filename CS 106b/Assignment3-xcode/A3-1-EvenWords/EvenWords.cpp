/* Ryan Foley
 * Section Leader: Brett Wines
 *
 * File: EvenWords.cpp
 *
 * A program that uses recursion to determine which words are
 * even words.
 */
#include <iostream>
#include <string>
#include "console.h"
#include "simpio.h" //for getLine
#include "strlib.h" //for upper and lowercase functions
using namespace std;

/* Function: isEvenWord(string input);
 * Usage: if (isEvenWord("tattletale")) { ... }
 * ==================================================================
 * Returns whether the given word is an "even word;" that is, whether
 * every letter in the word appears an even number of times.
 */
bool isEvenWord(string word); 

int main() {
    string word = getLine("Enter a word: " ); // get a word from the user.
    if(isEvenWord(word)) cout<<word<<" is an even word!"<<endl;
    else cout<<word<<" is not an even word."<<endl;
	return 0;
}

//Function determines if the word inputted is an even word.
bool isEvenWord(string word) {
	if(word == "") return true; 
    
    //search for the first letter of the word in the rest of the word.
    if(word.find(word[0], 1) == string::npos) return false; //if not found, return false.
    
    else{   //otherwise, delete both matching letters and make recursive call with remaining string.
        word = word.erase(word.find(word[0],1),1);
        word = word.erase(0,1);
        return isEvenWord(word);
    }
}
