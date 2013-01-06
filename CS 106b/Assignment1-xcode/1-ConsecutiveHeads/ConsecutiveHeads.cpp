/*
 * File: ConsecutiveHeads.cpp
 * --------------------------
 * Name: Ryan Foley 
 * Brett Wines
 * This file is the starter project for the coin-flipping problem.
 * This script is for the first problem of the first assignment. It prints either heads or tails with equal probability simulating flips of a fair coin. When 3 consecutive heads have occurred it stops and reports the total number of flips that occurred.
 */

#include <iostream>
#include <string>
#include "console.h"
#include "foreach.h"
#include "random.h" //included to use the randomChance() function.
#include <iostream>
#include "console.h"
#include "lexicon.h"
#include "queue.h"
#include "simpio.h"
#include "vector.h"
#include <string>
using namespace std;

/*Set <string> permuts(string prefix, string rest){
    Set<string> result;
    if (rest == ""){
        return result += prefix;
    }else{
        for(int i = 0; i < rest.length(); i++){

        }
    }

*/    
    
    
    
    

/*Set <string> generateAllPerms(string str, Set<string> perms){
    Set<string> result;
    if (str=="") return result;
    if(perms.size() == 0){
        for(int i  = 0; i<str.length(); i++){
            perms += string() + str[i];
            string newStr = str;
            result += generateAllPerms(newStr.erase(i,1), perms); 
        }
    } else {
        for(int i  = 0; i<str.length(); i++){
            foreach(string perm in perms){
                perms += perm + str[i];
                 //perms.remove(perm);
                
            }
            string newStr = str;
            result += generateAllPerms(newStr.erase(i,1), perms);
        }
    }
    return result;
}*/

/* File: permutations.cpp
 *
 * A program to generate all permutations of a string.
 */
Set<string> permutationsOf(string s) {
    Set<string> result;
    /* Base case: There is just one permutation of the empty string, namely "". */
    if (s == "") {
        result += "";
    }
    /* Recursive case: For each character, permute everything but that character,
     * then prepend the character.
     */
    else {
        for (int i = 0; i < s.length(); i++) {
            string iRemoved = s.substr(0, i) + s.substr(i + 1);
            foreach (string permutation in permutationsOf(iRemoved)) {
                result += s[i] + permutation;
            }
        }
    }
    return result;
}




int main() {

    string word = "word";
    cout<<word.substr(3,4)<<"END"<<endl;
    
    
    
    Lexicon english;
    english.add("word");
    string str = "theword";
    foreach(char ch in str){
        cout<<ch<<endl;
    }
    if(english.contains(str.substr(3))){ cout<<"derka derka"<<endl;}
    
    
    
    int headsInARow = 0;
    int numberOfFlips = 0;
    
    while(headsInARow < 3){ //repeat until 3 consecutive heads occur.
        
        if (randomChance(.5) == true){ //with probability .5, true outputted by randomChance indicating head flipped.
            headsInARow++; //increment consecutive heads by one.
            numberOfFlips++;   //increment number of flips.
            cout<<"heads"<<endl;
        
        } else{                 //Here reset the number of heads to zero and report tail flipped.
            headsInARow = 0; 
            numberOfFlips++;
            cout<<"tails"<<endl;
        }
    }
    
    cout<<"It took " << numberOfFlips << " flips to get 3 consecutive heads." << endl;
        
    return 0;
}


