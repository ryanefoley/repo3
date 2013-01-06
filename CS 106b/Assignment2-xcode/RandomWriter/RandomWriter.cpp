/*
 * File: RandomWriter.cpp
 * ----------------------
 * Name: Ryan Foley
 * Section: Brett Wines
 * This file is the starter project for the random writer problem
 * on Assignment #2.
 * This program takes in a selected source text and generates 2000 random characters based on probabilities calculated by frequencies at which some indicated number, or order, of characters appear in the source. 
 */

#include <fstream>
#include <iostream>
#include <string>
#include "simpio.h" //for getLine
#include "console.h"
#include "map.h"
#include "random.h"
#include "strlib.h"
#include "vector.h"
#include "strlib.h" //for upper and lowercase functions
using namespace std;


//Function to prompt user for a filename and confirm that it exists.
string promptUserForFile(ifstream & sourceText, string prompt) {
    while (true) {
        //get filename from user and open the file.
        cout << prompt;
        string filename;
        getline(cin, filename); 
        sourceText.open(filename.c_str());
        
        //send an error if cannot open the file and try again.
        if (!sourceText.fail()) return filename;
        sourceText.clear();
        cout << "Unable to open that file.  Try again." << endl;
    } }

//Function that makes a map from all potential seeds of length specified by order to a vector of all characters that follow the after the seed in the text.
void makeMap(ifstream& sourceText, int order, Map<string, Vector<char> >& possibleNextChars){
    char ch;
    string seed;
    
    //Get the first letters of number equal to order from the text.
    for(int i = 0; i < order; i++){ 
        ch = sourceText.get();
        seed += ch;
    }
    
    seed = toLowerCase(seed);
    
    //Get every other possible seed in text and map them to vector of chars that follow them.
    while(true){
        int next = sourceText.get();
        if(next == EOF) break;
        ch = next;
        seed = toLowerCase(seed);
        possibleNextChars[seed] += ch;
        seed = seed.substr(1,seed.length()-1) + ch;
    }

}

//Function to find the initial seed of a specified order.
string findSeed(ifstream& sourceText, int order, Map<string, Vector<char> >& possibleNextChars){
    string seed;
    int seedFreq = 0;
    
    //loop through all order length strings in text and find combination with highest frequency.
    foreach(string key in possibleNextChars){
        if(possibleNextChars[key].size() > seedFreq){
            seed = key;
            seedFreq = possibleNextChars[key].size();
                    }
    }
    return seed; //returning seed with highest frequency in the text.
}

//Function to randomly select the next character given a seed based on the frequency at which characters appear in the text after the seed.
string nextChar(string seed, ifstream& sourceText, Map<string, Vector<char> >& possibleNextChars){
    
    Vector<char> chs = possibleNextChars[seed];
    
    //choose a random char from the list of chars following the seed. 
    //Casting it to type string and making sure it is in lower case also.
    return toLowerCase(string() + chs[randomInteger(0,chs.size()-1)]);
    
}

//Primary function that writes the random written output.
string randomWriter(ifstream& sourceText, int order){
    
    Map <string, Vector<char> > possibleNextChars;
    
    makeMap(sourceText, order, possibleNextChars); //creating map of seeds with associated chars after them.
    
    string seed = findSeed(sourceText, order, possibleNextChars); //find intitial seed.
    string output = seed; //start output with initial seed.

    //writing output until length is 2000 or seed is not a key in possibleNextChars.
    int i = 1;
    while(output.length() < 2000 && possibleNextChars.containsKey(seed)){
        string ch = nextChar(seed, sourceText, possibleNextChars);
        output += ch;
        seed = output.substr(i,order);
        i++;
    }
    return output; //returning random written output.
}


int main() {
    
    ifstream sourceText;
    promptUserForFile(sourceText, "Please enter filename containing source text: ");
    
    int order = getInteger("What order of analysis (1 to 10): "); //get order from user
    
    cout<<"Analyzing ... please wait."<<endl; //inform user that it might take a while
    
    cout<<randomWriter(sourceText, order)<<endl; //output from random writer.
    
	return 0;
}
