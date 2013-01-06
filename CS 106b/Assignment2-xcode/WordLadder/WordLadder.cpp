/*
 * File: WordLadder.cpp
 * --------------------
 * Name: Ryan Foley
 * Section: Brett Wines
 * This file is the starter project for the word ladder problem
 * on Assignment #2.
 * Program gets from user input a starting word and destination word. The program then finds the shortest word ladder (chain of words in the English lexicon differing by one letter from word to word) from the starting word to the destination word. 
 */

#include <iostream>
#include "console.h"
#include "lexicon.h"
#include "queue.h"
#include "simpio.h"
#include "vector.h"
#include <string>

#include "foreach.h" //included to us foreach function.
using namespace std;

//checking to see if word is already contained in vector, ladder.

bool foundInLadder(string word, Vector <string> ladder){
    
    for(int i = 0; i < ladder.size(); i++){
        if(ladder[i] == word){
            return true;
        }
    }
    return false;
}

//Function to obtain set of all possibe words that are one letter away from start word and in the English Lexicon.

Set <string> wordsOneAway(string startWord, Lexicon& englishWords){
    
    string alpha = "abcdefghijklmnopqrstuvwxyz"; //string containing the english alphabet.
    string newWord;
    Set <string> setOfWords;

    for(int i = 0; i < startWord.length(); i++){ //Looping through each position of the start word.
        for(int j = 0; j < alpha.length(); j++){ //looping through each letter of the alphabet.
           
            newWord = startWord;
            newWord.replace(i,1,string()+alpha[j]); //replacing a letter with a new letter.
            
            //if the new word, one letter away, is in the English lexicon then insert into set.
            if(newWord != startWord){ 
                if(englishWords.contains(newWord)) setOfWords.add(newWord); 
            }
        }
    }
    
    return setOfWords; //returning all words one letter away from start word.
    
}

//Primary function that constructs the shortest possible word ladder from the start word to the destination word.

Vector <string> wordLadder(string startWord, string destWord, Lexicon& englishWords) {
    
    Queue <Vector<string> > myQueue; //create queue of vectors to contain ladders.
    Vector <string> startVector;
    startVector.add(startWord);
    myQueue.enqueue(startVector); //adding start word as a vector to initialize the queue.
    Lexicon usedWords; //creating lexicon of words already in other laddders.
    usedWords.add(startWord);
    
    //looping through the queue until no ladders left or return resulting ladder.
    while(myQueue.size() != 0){ 
        
        Vector <string> ladder = myQueue.dequeue();
        
        if(ladder.get(ladder.size()-1) == destWord){ //if ladder ends in destination word, return ladder.
            
            return ladder;
        }
        
        startWord = ladder.get(ladder.size()-1); //get last word in ladder.
        
        foreach(string nextWord in wordsOneAway(startWord, englishWords)){
            
            //if next word is not already in a ladder, then create a new ladder and add it to the queue.
            if(!usedWords.contains(nextWord)){ 
                usedWords.add(nextWord);
                Vector <string> ladderCopy; 
                ladderCopy = ladder;
                ladderCopy.add(nextWord);
                myQueue.enqueue(ladderCopy);
                
            }                
                    
        }
    }
    
    //returning ladder with just zero to signify failure to find a ladder between words.
    Vector <string> result; 
    result.add("0");
    return result;
}



int main() {
    
    Lexicon englishWords("EnglishWords.dat"); //loading the lexicon of English words.
    string startWord = getLine("Enter a start word: "); //prompting user for start and end words.
    string destWord = getLine("Enter a destination word: ");
    
    //checking that both start and destination words exist in English lexicon.
    if(!englishWords.contains(startWord) or !englishWords.contains(destWord)){ 
        cout<<"Both start and destination words must be in the English Lexicon."<<endl;
        return 0;
    }
    Vector <string> ladder = wordLadder(startWord, destWord, englishWords); //create word ladder.
    
    //printing out result:
    if(ladder[0] == "0") cout<<"No ladder exists."<<endl;
    else{
        cout <<"Found Ladder: "<<endl;
    
        for(int i = 0; i < ladder.size(); i++){
            cout<<ladder[i]<<endl;
        }
    }
    
    return 0;
    
}
