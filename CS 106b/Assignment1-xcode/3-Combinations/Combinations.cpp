/*
 * File: Combinations.cpp
 * ----------------------
 * Name: Ryan Foley
 * Section: Brent Wines
 * This file is the starter project for the recursive combinations problem.
 * This program is for the third problem of the first assignment and it calculates combinations.
 */

#include <iostream>
#include "console.h"
#include "simpio.h"
using namespace std;

int c(int n, int k);

int main() {
    
    int n = getInteger("Enter value for N: ");
    
    if (n < 0 ){    //check to make sure N is non negative
        cout << "Invalid entry. N and K must be non negative integers." << endl;
        return 0;
    }
    int k = getInteger("Enter value for K: ");
    
    if (k < 0 ){    //check that k is non negative
        cout << "Invalid entry. N and K must be non negative integers." << endl;
        return 0;
    }
    
    if (k > n){     //check that n is larger than k
        cout << "Invalid entry. K must be less than or equal to n." << endl;
        return 0;
    }
    
    int value = c(n,k); //send n and k to function c to calculate combination and return value
    
    cout << n << " choose " << k << " is equal to " << value << endl;
    
    
   return 0;
}

int c(int n, int k){ //calculating the combination for n choose k
    if (n < k or k < 0){ 
        return 0;
    } else {
        if (n == 0 && k == 0){
            return 1;
        }
        else {
            return c(n-1,k-1) + c(n-1, k);
        }
    }
}
    