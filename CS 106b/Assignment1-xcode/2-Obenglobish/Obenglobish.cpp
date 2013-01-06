/*
 * File: Obenglobish.java
 * ----------------------
 * Ryan Foley
 * Brett Wines
 * This file is the starter project for the Obenglobish problem.
 * This is the script for the second problem on the first assignment. It takes a string as input and inserts "ob" before vowels that do not follow directly after another vowel and not before e's at the end of a word.
 */

#include <iostream>
#include <string> //included for functions like length() and find() on a string
#include "console.h" 
#include "simpio.h" //included for getLine function
#include "strlib.h" 
using namespace std;

/* Main program */

string obenglobish(string str);

int main() {
    while (true) {
        string word = getLine("Enter a word: "); //prompt user for a word
        if (word == "") break;
        string trans = obenglobish(word); //send word to obenglobish function for translation and return result
        cout << word << " -> " << trans << endl;
    }
    return 0;
    
}

string obenglobish(string str){
    
    string vowels = "eaiou"; //creating string of vowels to use in checking their existence in str
    
    for(int i = 0; i < str.length();){
    
        if (str[i] == 'e' && i < str.length()-1 && vowels.find(str[i-1],0) == string::npos){ //str[i] is character so comparing to 'e' instead of "e"
            str = str.insert(i, "ob");
            i += 3;
        } else {
            if (vowels.find(str[i],0) != string::npos  && i == 0){ //if a vowel other than e and in the first position
                str = str.insert(i, "ob"); //insert "ob"
                i += 3;
            } else {
                if (vowels.find(str[i],0) != string::npos && vowels.find(str[i-1],0) == string::npos){
                    str = str.insert(i, "ob"); //checking if vowel and no vowel before, then insert "ob"
                    i +=3;
                } else {
                    i++;
                }
            }
        }
    }
   
    return str;
    }

