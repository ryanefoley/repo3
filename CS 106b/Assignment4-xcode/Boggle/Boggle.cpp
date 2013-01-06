/*
 * File: Boggle.cpp
 * ----------------
 * Name: Ryan Foley
 * Section: Brett Wines
 * This file is the main starter file for Assignment #4, Boggle.
 * This is a script to run Boggle!
 */
 
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

//Defining coordinate as a structure type with two fields, row and col, both of type int. These will be used to indicate coordinates on the board.
struct coordinate{
    int row;
    int col;
};

//Ask the user whether he would like to play Big Boggle or Standard and return the corresponding game type.
string getGameType(){
        string gameType;
        while(true){
            string usersChoice = toLowerCase(getLine("You can play either Big Boggle (5x5) or Standard(4x4).\nWould you like to play Big Boggle? "));
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

//validLetters checks that each letter inputted is truly a letter. If not return false.
bool validLetters(string letters){
    foreach(char ch in letters){
        if(!isalpha(ch)) return false;
    }
    return true;
}

//presetLetters asks the user whether they would like to set the letters for the board.
string presetLetters(string gameType){
    string letters;
    while(true){
        string response = toLowerCase(getLine("Would you like to set the board letters? "));
        if(response == "no" || response == "n") 
            return letters;
        if(response == "yes" || response == "y")
            break;
        else cout<<"Please enter either yes or no.\n";
    }
    while(true){
        letters = getLine("Please enters you would like for the board: ");
        if(validLetters(letters)){
            if(gameType == "big"){
                if(letters.length() >= 25) break;
                else cout<<"Please enter atleast 25 letters.\n";
            }
            if(gameType =="stan"){
                if(letters.length() >= 16) break;
                else cout<<"Please enter atleast 16 letters.\n";
            }
        }else cout<<"Please only enter actual letters in the alphabet.\n";
    } 
    return letters;
}

//This function takes random letters from the appropriate Boggle blocks, given the game type, and returns the letters that will be used to fill the game board.
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

//This function fills the appropriate game board with the given letters. It returns cube, which is type grid, to represent the game board.
Grid<char> makeBoardWithLetters(string letters, string gameType){ 
    letters = toUpperCase(letters);
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
    for(int row = 0; row < numRows; row++){ //filling in the grid with letters
        for(int col = 0; col < numCols; col++){ 
            labelCube(row, col, letters[i]);
            cube[row][col] = letters[i];
            i++;
        }
    }
    return cube;
}

//This function is used with findWord to find whether the given word is on the board.
bool findRestOfWord(string word, Grid<char> cube, Vector<coordinate>& coordinates){
    if(word == "") return true;
    coordinate pos = coordinates[coordinates.size()-1];//getting the coordinate of the current letter
    cube[pos.row][pos.col] = '0'; //marking the position of letter with 0 denotes that it has already been used in the word. 
    
    coordinate newPos;
    for(int i = -1; i < 2; i++){ //double for loop for trying each each letter around the current letter.
        for(int j = -1; j < 2; j++){
            newPos = pos;
            newPos.row += i;
            newPos.col += j;
            Vector<coordinate> newCoordinates = coordinates;
            if(cube.inBounds(newPos.row,newPos.col)){ //making sure that row and column within dimensions of the grid
                if(cube[newPos.row][newPos.col] == word[0]){ //checking if letter in cube matches that of the word
                    newCoordinates += newPos;
                    if(findRestOfWord(word.substr(1), cube, newCoordinates)){ 
                        coordinates = newCoordinates;
                        return true;
                    }
                }
            }
        }
    } return false;
}

//This function checks if the given word is on the board. It begins by finding the first letter and then uses findRestOfWord to find the remaining letters in the word. If the word is found, it is highlighted and a point is given to the player.
bool findWord(string word, Grid<char> cube){
    word = toUpperCase(word);
    for(int row = 0; row < cube.numRows(); row++){ //Looking through the grid for the first letter of the word.
        for(int col = 0; col < cube.numCols(); col++){
            if(cube[row][col] == word[0]){
                coordinate pos;
                pos.row = row;
                pos.col = col;
                Vector<coordinate> coordinates;
                coordinates.add(pos);
                if(findRestOfWord(word.substr(1), cube, coordinates)){ //If word is found, highlight and add to score.
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

//This function checks that the given word is valid - in that is has 4 or more characters and it is in the dictionary.
bool checkWordValid(string word, Lexicon& english){
    if(word.length() < 4){
        cout<<"Sorry, word length must be atleast 4 letters.\n";
        return false;
    }
    if(!english.contains(word)){
        cout<<"Sorry, that is not a word.\n";
        return false;
    }
    return true;
}

//This function is for the human player's turn. It asks the player for words adn keeps score.
void humanTurn(Lexicon& english, Grid<char> cube){
    Set<string> wordsPlayed;
    while(true){
        string word = getLine("Enter word: ");
        if(word == "") break;
        if(checkWordValid(word, english)){
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
}

//allWords finds all of the words formed from a given starting row and column.
Set<string> allWords(Lexicon& english, Grid<char> cube, string prefix, int row, int col){
    Set<string> result;
    if(!english.containsPrefix(prefix)) return result; //quick check if the current prefix is in the dictionary.
    if(english.contains(prefix) && prefix.size() > 3) result += prefix; //if prefix in dictionary and long enough, add to result.
    int newRow = 0;
    int newCol = 0;
    Grid<char> newCube = cube;
    newCube[row][col] = '0'; //marking used letter in grid as 0
    for(int i = -1; i < 2; i++){ //looking at each letter surrounding current letter
        for(int j = -1; j < 2; j++){
            newRow = row + i;
            newCol = col + j;
            if(cube.inBounds(newRow,newCol)){//making sure position in bounds of the grid
                string newPrefix = prefix + newCube[newRow][newCol]; 
                result += allWords(english, newCube, newPrefix, newRow, newCol); //adding all valid words from the next letter to result. 
            }
        }
    } return result;
}

//Function represents the computers turn. It looks for all valid words in the grid and adds them to the computer players score.
void computerTurn(Lexicon& english, Grid<char> cube){
    string prefix = "";
    Set<string> words; //initializing the set of all words on the board.
    for(int row = 0; row < cube.numRows(); row++){ //for each letter on the board, finding all words that extend from it.
        for(int col = 0; col < cube.numCols(); col++){
            words += allWords(english, cube, prefix, row, col);
        }
    }
    foreach(string word in words){
        recordWordForPlayer(word, COMPUTER);
    }
}

//This function asks the user if they would like to play again. The program ends if the user replies with No or N.
bool playAgain(){
    while(true){
        string playAgain = getLine("Would you like to play again: ");
        if(toLowerCase(playAgain) == "no" || toLowerCase(playAgain) == "n") 
            return false;
        if(toLowerCase(playAgain) == "yes" || toLowerCase(playAgain) == "y")
            return true;
        else cout<<"Please enter either yes or no.\n";
    }
}

//The Boggle function represnts the primary function of the game given the game type. 
void boggle(string gameType){
    while(true){ //Continue playing until the user says they do not want to play again.
        string letters = presetLetters(gameType);  
        if(letters == "") //presetLetters returns the empty string if the user indicates that they don't want to set them. 
            letters = shuffle(gameType); //letters is set to random letters from the preset boggle cubes.
        Grid<char> cube = makeBoardWithLetters(letters, gameType);
        Lexicon englishWords("EnglishWords.dat");
        humanTurn(englishWords, cube);
        computerTurn(englishWords, cube);
        if(!playAgain()) break; //if the user does not want to play again then break.
    }
}
            
/* Main program */

int main() {
    initGraphics(BOGGLE_WINDOW_WIDTH, BOGGLE_WINDOW_HEIGHT);
    welcome();
    giveInstructions();
    string gameType = getGameType(); //getting game type which corresponds to board size.
    boggle(gameType);
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











