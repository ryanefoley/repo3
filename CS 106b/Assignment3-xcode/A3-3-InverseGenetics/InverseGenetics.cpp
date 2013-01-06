/* File: InverseGenetics.cpp
 * Name: Ryan Foley
 * Section Leader: Brett Wines
 * A program that, given a sequence of amino acids, returns all possible
 * RNA strands that could encode that amino acid sequence.
 */
#include <iostream>
#include <string>
#include <fstream>
#include "set.h"
#include "map.h"
#include "console.h"
#include "simpio.h"
#include "lexicon.h"
using namespace std;

/* Function: allRNAStrandsFor(string protein,
 *                            Map<char, Set<string> >& codons);
 * Usage: foreach (string rna in allRNAStrandsFor("PARTY", codons);
 * ==================================================================
 * Given a protein and a map from amino acid codes to the codons for
 * that code, returns all possible RNA strands that could generate
 * that protein.
 */
Set<string> allRNAStrandsFor(string protein, Map<char, Set<string> >& codons);

/* Function: loadCodonMap();
 * Usage: Map<char, Lexicon> codonMap = loadCodonMap();
 * ==================================================================
 * Loads the codon mapping table from a file.
 */
Map<char, Set<string> > loadCodonMap();

int main() {

    
    
    
	/* Load the codon map. */
	Map<char, Set<string> > codons = loadCodonMap();
    string protein = getLine("Enter protein as amino acid squence: ");
    foreach(char c in protein){ //checking to make sure each char entered is a codon.
        if(!codons.containsKey(c)){
        cout<<c<<" is not a codon. Please enter only codons."<<endl;
        return 0;
        }
    }
    //Get RNA strands from inputted codons and print them out.
    Set<string> RNAStrands = allRNAStrandsFor(protein, codons);
    cout<<"RNA strands encoding protein are: "<<endl;
    foreach(string RNA in RNAStrands){
        cout<<RNA<<endl;
    }

	return 0;
}

Set<string> allRNAStrandsFor(string protein, Map<char, Set<string> >& codons) {
	
    Set<string> RNAStrands;
    string strand;
    string nextStrand;
    
    if(protein == ""){ 
        
        RNAStrands += "";
    }
    else{
        //for each strand corresponding to first protein get every possible strand of the remaining proteins.
        foreach(strand in codons[protein[0]]){ //codons[protein[0]] returns set of rna strands associated with char.
            foreach(nextStrand in allRNAStrandsFor(protein.substr(1, protein.length()), codons)){
                strand += nextStrand;
                RNAStrands += strand;
                strand = strand.substr(0,3);
            }
        }
    }
    return RNAStrands;
}

/* You do not need to change this function. */
Map<char, Set<string> > loadCodonMap() {
	ifstream input("codons.txt");
	Map<char, Set<string> > result;
    
	/* The current codon / protein combination. */
	string codon;
	char protein;
	
	/* Continuously pull data from the file until all data has been
	 * read.  We did not cover this syntax in class, but it means
	 * "while reading a codon/protein pair succeeds, add the pair to
	 * the map."
	 */
	while (input >> codon >> protein) {
		result[protein] += codon;
	}
	
	return result;
}

