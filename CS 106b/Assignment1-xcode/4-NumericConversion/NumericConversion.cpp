/*
 * File: NumericConversion.cpp
 * ---------------------------
 * Name: Ryan Foley
 * Section: Brent Wines
 * This file is the starter project for the numeric-conversion problem
 * in which you implement the functions intToString and stringToInt.
 * This program is for the Numeric Conversion problem of the first assignment. It converts a numerical int and a string to a string and an int respectively.
 */

#include <iostream>
#include <string>
#include "console.h"
#include "simpio.h" // included simpio.h to use getInteger and getLine functions
#include <cctype> //for isaplha()
using namespace std;

/* Function prototypes */

string intToString(int n);
int stringToInt(string str);
string checkIfNumeric(string str);

/* Main program */

int main() {
    char x = (char)'0'<<endl;
    int n = getInteger("Enter integer to convert to a string: ");
    
    string str = getLine("Enter string to convert to an integer: ");
    
    str = checkIfNumeric(str); // run checkIfNumeric function to make sure that string inputted is only numeric chars.
    
    string nConverted = intToString(n);
    
    int strConverted = stringToInt(str);
    
    cout << "Inputted values have been converted. They are the new string and integer: " << nConverted << " and " <<strConverted << endl;
    
   return 0;
}

 /* checkIfNumeric is checking that each character inputted numeric. If character is a letter, then error message displayed and asks for input again. */

string checkIfNumeric(string str){
    
    for(int i = 0; i < str.length(); i++){            
        if(isalpha(str[i])){      
            cout << "Please only input numerical values. Thank you and try again!" << endl;
            str = getLine("Enter string to convert to an integer: "); 
            return checkIfNumeric(str);
        
        }
    }
    
    return str;

}

string intToString(int n){
    if(n >= 0){ //checking whether the int supplied is positive.
        
        char digit = (char)(((int)'0')+ n%10); //taking last digit of int and converting it to a char.
        
        if (n/10 == 0){ //taking remaining digits and recursively passing them back through the function.
            return string() + digit;
        } else {
            return string() + intToString(n/10) + digit; //combining last digit and recursive solution to the string.
        }
        
    } else {
        n = (-1)*n;                             //convert n to positive integer then procede as before but adding "-" sign.
        char digit = (char)(((int)'0')+ n%10);  //peel off last digit of n
        if (n/10 == 0){                         //check if n is one digit. If so, return true.
            return string("-") + digit;
        } else {
            return string("-") + intToString(n/10) + digit;
        }

        
    }
}

int stringToInt(string str){
    if(str == ""){
        return 0;
    } else {
        if(str[0] != '-'){              //check to see if negative number
            int digit = (int)(str[str.length()-1]) - (int)'0';
            return digit + 10*stringToInt(str.substr(0,str.length()-1));
        } else {                        //Input is negative so must multiply result by negative 1.
            return -1*(stringToInt(str.substr(1,str.length()-1)));
        }
    }
}

    
