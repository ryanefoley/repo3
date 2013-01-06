/* File: UniversalHealthCoverage.cpp
 * Name: Ryan Foley
 * A program that determines whether or not it is possible to provide
 * coverage to everyone using a fixed number of hospitals.
 *
 * This is an example in Recursive Backtracking!
 *
 */
#include <iostream>
#include <string>
#include "set.h"
#include "vector.h"
#include "console.h"
using namespace std;

/* Function: canOfferUniversalCoverage(Set<string>& cities,
 *                                     Vector< Set<string> >& locations,
 *                                     int numHospitals,
 *                                     Vector< Set<string> >& result);
 * Usage: if (canOfferUniversalCoverage(cities, locations, 4, result)
 * ==================================================================
 * Given a set of cities, a list of what cities various hospitals can
 * cover, and a number of hospitals, returns whether or not it's
 * possible to provide coverage to all cities with the given number of
 * hospitals.  If so, one specific way to do this is handed back in the
 * result parameter.
 */
bool canOfferUniversalCoverage(Set<string>& cities,
                               Vector< Set<string> >& locations,
                               int numHospitals,
                               Vector< Set<string> >& result);

struct  Node {
    string value;
    Node* next;
};

string test(Node* node){
    string output = "";
    if(node == NULL) return "";
    return output += node->value + " " + test(node->next);
}

int main() {
    
    Node* node1 = NULL; //don't know that I need these initialized as NULL
    Node* node2 = NULL;
    
    string str1 = "a";
    string str2 = "b";
    
    node1->value = str1;
    node1->next = node2;
    node2->value = str2;
    node2->next = NULL;
    
    cout<<test(node1)<<endl;
    
    
    
    // creating a test set of cities
    string a = "a", b = "b", c = "c", d = "d", e = "e", f = "f";
    
	Set<string> cities;
    cities += a,b,c,d,e,f;
    Vector< Set<string> > locations;
    
    //creating test set of locations
    Set<string> testSet1;
    testSet1 += a;
    Set<string> testSet2;
    testSet2 += a,b,c;
    Set<string> testSet3;
    testSet3 += c,d,e;
    Set<string> testSet4;
    testSet4 += c,d,e,f;
    
    locations += testSet1, testSet2, testSet3, testSet4;
    int numHospitals = 4; //setting number of potential hospitals
    Vector< Set<string> > result;
    
    //determine whether Universal Coverage is possible.
    if(canOfferUniversalCoverage(cities, locations, numHospitals, result)){
        cout<<"Universal Healthcare is possible!"<<endl;
        return 0;
    } else {
        cout<<"Universal Healthcare is not possible!"<<endl;
        return 0;
    }
}

bool canOfferUniversalCoverage(Set<string>& cities,
                               Vector< Set<string> >& locations,
                               int numHospitals,
                               Vector< Set<string> >& result) {
    
    if(cities.isEmpty()) return true; 
    Set<string> citiesCovered;
    foreach(Set<string> covered in result) citiesCovered += covered; //adding all cities in result to cities covered.
    if(cities.isSubsetOf(citiesCovered)) return true; //if cities covered includes all cities, return true.
    if(numHospitals == 0) return false; //Given that not all cities are covered and there are no potential hospitals return false.
    
    /* for each location, add that location to result if it is not in it already. Then make recursive call to the function. If function does not return true, remove location from result. Continue by trying each possible location. This is an example of recursive backtracking in that we try one route all the way to the bottom and then backtrack by trying each possible step from the bottom up.*/
    foreach(Set<string> location in locations){
        if(result.isEmpty()){
            result += location;
            if(canOfferUniversalCoverage(cities, locations, numHospitals-1, result)) return true;
            else{
                result.removeAt(0);
            }
        }else{
        foreach(Set<string> coveredLocation in result){
            if(location != coveredLocation){
                result += location;
                if(canOfferUniversalCoverage(cities, locations, numHospitals-1, result)) return true;
                else {
                    result.removeAt(result.size()-1);
                    }
                }
            }
        } 
    }
    return false;
}
