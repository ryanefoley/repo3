/*
 * File: Boggle.cpp
 * ----------------
 * Name: Ryan Foley
 * Section: Brett Wines
 * This file is the main starter file for Assignment #4, Boggle.
 * [TODO: extend the documentation]
 */

///////////////check prefixes in lexicon? fast end? reread instructs. user define board chars. fix highlighting
 
#include <iostream>
#include "gboggle.h"
#include "graphics.h"
#include "grid.h"
#include "lexicon.h"
#include "random.h"
#include "simpio.h"
using namespace std;

/* Constants */

const int BOGGLE_WINDOW_WIDTH = 650;
const int BOGGLE_WINDOW_HEIGHT = 350;

const string STANDARD_CUBES[16]  = {
   "AAEEGN", "ABBJOO", "ACHOPS", "AFFKPS",
   "AOOTTW", "CIMOTU", "DEILRX", "DELRVY",
   "DISTTY", "EEGHNW", "EEINSU", "EHRTVW",
   "EIOSST", "ELRTTY", "HIMNQU", "HLNNRZ"
};
 
const string BIG_BOGGLE_CUBES[25]  = {
   "AAAFRS", "AAEEEE", "AAFIRS", "ADENNN", "AEEEEM",
   "AEEGMU", "AEGMNN", "AFIRSY", "BJKQXZ", "CCNSTW",
   "CEIILT", "CEILPT", "CEIPST", "DDLNOR", "DDHNOT",
   "DHHLOR", "DHLNOR", "EIIITT", "EMOTTT", "ENSSSU",
   "FIPRSY", "GORRVW", "HIPRRY", "NOOTUW", "OOOTTU"
};

/* Function prototypes */

void welcome();
void giveInstructions();

struct coordinate{
    int row;
    int col;
};

string getGameType(){
        string gameType;
        while(true){
            string usersChoice = toLowerCase(getLine("You can play either big boggle or standard. Would you like to play big? "));
            if(usersChoice == "y" || usersChoice == "yes"){
                gameType = "big";
                return gameType;
            }            
            if(usersChoice == "n" || usersChoice == "no"){
                gameType = "stan";
                return gameType;
            }
            else
                cout<<"Sorry, please respond with either yes or no.\n";
        }
}

string shuffle(string gameType){
    string letters;
    if(gameType == "big"){
        for (int i = 0; i < 25; i++) {
            string block = BIG_BOGGLE_CUBES[i];
            letters += block.substr(randomInteger(0, 5),1);
        }
    }else{
        for (int i = 0; i < 16; i++) {
            string block = STANDARD_CUBES[i];
            letters += block.substr(randomInteger(0, 5),1);
        }
    }
    return letters;
}

Grid<char> makeBoardWithLetters(string letters, string gameType){ //note need to make sure caps in letters
    
    int numRows = 0;
    int numCols = 0;
    
    if(gameType == "big"){
        numRows = 5;
        numCols = 5;
    }else{
        numRows = 4;
        numCols = 4;
    }
    drawBoard(numRows, numCols);
    Grid<char> cube(numRows, numCols);
    int i = 0;
    for(int row = 0; row < numRows; row++){
        for(int col = 0; col < numCols; col++){ 
            labelCube(row, col, letters[i]);
            cube[row][col] = letters[i];
            i++;
        }
    }
    return cube;
}

bool findRestOfWord(string word, Grid<char> cube, int row, int col, Vector<coordinate>& coordinates){
    if(word == "") return true;
    cube[row][col] = '0'; //marking the position of letter with 0 denotes that it has already been used in the word. 
    coordinate pos;
    pos.row = row;
    pos.col = col;
    coordinates += pos;
    
    int newRow = 0;
    int newCol = 0;
    for(int i = -1; i < 2; i++){
        for(int j = -1; j < 2; j++){
            newRow = row + i;
            newCol = col + j;
            Vector<coordinate> newCoordinates = coordinates;
            coordinate newPos;
            newPos.row = newRow;
            newPos.col = newCol;
            newCoordinates += newPos;
            if(cube.inBounds(newRow,newCol)){
                if(cube[newRow][newCol] == word[0]){
                    if(findRestOfWord(word.substr(1), cube, newRow, newCol, newCoordinates)){
                        coordinates = newCoordinates;
                        return true;
                    }
                }
            }
        }
    } return false;
}

bool findWord(string word, Grid<char> cube){
    word = toUpperCase(word);
    for(int row = 0; row < cube.numRows(); row++){
        for(int col = 0; col < cube.numCols(); col++){
            if(cube[row][col] == word[0]){
                Vector<coordinate> coordinates;
                if(findRestOfWord(word.substr(1), cube, row, col, coordinates)){
                    coordinate pos;
                    foreach(pos in coordinates){
                        highlightCube(pos.row, pos.col, true);
                    }
                    pause(300);
                    foreach(pos in coordinates){
                        highlightCube(pos.row, pos.col, false);
                    }
                    return true;
                }
            }
        }
    } 
    return false;
}

void humanTurn(Lexicon& english, Grid<char> cube){
    Set<string> wordsPlayed;
    while(true){
        string word = toLowerCase(getLine("Enter word: "));
        if(word == "") break;
        if(word.length() < 4)
            cout<<"Sorry, word length must be atleast 4 letters.\n";
        if(!english.contains(word))
            cout<<"Sorry, that is not a word.\n";
        if(wordsPlayed.contains(word))
            cout<<"You've already played that word!\n";
        else{
            if(findWord(word, cube)){
                recordWordForPlayer(word, HUMAN);
                wordsPlayed += word;
            }
            else cout<<"You can't make that word!\n";
        }
    }
}

//allWords finds all of the words formed from a given starting row and column.
Set<string> allWords(Lexicon& english, Grid<char> cube, string prefix, int row, int col){
    Set<string> result;
    if(!english.containsPrefix(prefix)) return result;
    if(english.contains(prefix) && prefix.size() > 3) result += prefix;
    int newRow = 0;
    int newCol = 0;
    Grid<char> newCube = cube;
    newCube[row][col] = '0';
    for(int i = -1; i < 2; i++){
        for(int j = -1; j < 2; j++){
            newRow = row + i;
            newCol = col + j;
            if(cube.inBounds(newRow,newCol)){
                string newPrefix = prefix + newCube[newRow][newCol]; 
                result += allWords(english, newCube, newPrefix, newRow, newCol);
            }
        }
    } return result;
}

void computerTurn(Lexicon& english, Grid<char> cube){
    string prefix = "";
    Set<string> words;
    for(int row = 0; row < cube.numRows(); row++){
        for(int col = 0; col < cube.numCols(); col++){
            words += allWords(english, cube, prefix, row, col);
        }
    }
    foreach(string word in words){
        recordWordForPlayer(word, COMPUTER);
    }
}

/*oid boggle(){
    while(true){
        
        string gameType = getGameType(); //getting game type which corresponds to board size.
        string letters = shuffle(gameType);
        Grid<char> cube = makeBoardWithLetters(letters, gameType);
        
        Lexicon englishWords("EnglishWords.dat");
        humanTurn(englishWords, cube);
        computerTurn(englishWords, cube);
        string playAgain = getline("Would you like to play again: ");
        
    }
}
*/            
/* Main program */

int main() {
    initGraphics(BOGGLE_WINDOW_WIDTH, BOGGLE_WINDOW_HEIGHT);
    welcome();
    giveInstructions();
    string gameType = getGameType(); //getting game type which corresponds to board size.
    string letters = shuffle(gameType);
    Grid<char> cube = makeBoardWithLetters(letters, gameType);
    Lexicon englishWords("EnglishWords.dat");
    humanTurn(englishWords, cube);
    computerTurn(englishWords, cube);
   return 0;
}

/*
 * Function: welcome
 * Usage: welcome();
 * -----------------
 * Print out a cheery welcome message.
 */

void welcome() {
   cout << "Welcome!  You're about to play an intense game ";
   cout << "of mind-numbing Boggle.  The good news is that ";
   cout << "you might improve your vocabulary a bit.  The ";
   cout << "bad news is that you're probably going to lose ";
   cout << "miserably to this little dictionary-toting hunk ";
   cout << "of silicon.  If only YOU had a gig of RAM..." << endl << endl;
}

/*
 * Function: giveInstructions
 * Usage: giveInstructions();
 * --------------------------
 * Print out the instructions for the user.
 */

void giveInstructions() {
   cout << endl;
   cout << "The boggle board is a grid onto which I ";
   cout << "I will randomly distribute cubes. These ";
   cout << "6-sided cubes have letters rather than ";
   cout << "numbers on the faces, creating a grid of ";
   cout << "letters on which you try to form words. ";
   cout << "You go first, entering all the words you can ";
   cout << "find that are formed by tracing adjoining ";
   cout << "letters. Two letters adjoin if they are next ";
   cout << "to each other horizontally, vertically, or ";
   cout << "diagonally. A letter can only be used once ";
   cout << "in each word. Words must be at least four ";
   cout << "letters long and can be counted only once. ";
   cout << "You score points based on word length: a ";
   cout << "4-letter word is worth 1 point, 5-letters ";
   cout << "earn 2 points, and so on. After your puny ";
   cout << "brain is exhausted, I, the supercomputer, ";
   cout << "will find all the remaining words and double ";
   cout << "or triple your paltry score." << endl << endl;
   cout << "Hit return when you're ready...";
   getLine();
}











