/***********************************************
    3D Boggle Solver
    for Connected Signals hiring process
    
    Samantha Mintzmyer
***********************************************/
#include <iostream>
#include <string>
#include <fstream>
#include <unordered_set>


/*************************************
    Method for dictionary
    buildHash uploads words to hashtable
    dictLookup checks if word is in hashtable
*************************************/

//  buildHash: accepts dictionary file, returns hashtable of words
std::unordered_set<std::string> buildHash(std::string dictName)
{
    std::unordered_set<std::string> dictHash;

    //  Read words into hashtable
    std::ifstream infile(dictName);
    std::string s;
    while (std::getline(infile, s))
    {
        dictHash.insert (s);
    }

    // Testing dictHash hashtable
    std::cout << "Dictionary contains: ";
    for (const std::string& x: dictHash) std::cout << " " << x;
    std::cout << std::endl;

    return dictHash;
}

//  dictLookup: accepts word, returns true/false
bool dictLookup(std::string word, std::unordered_set<std::string> dictHash)
{
    return dictHash.count(word) > 0;
}

/*************************************
    Data Structure for Cubies and Cube
    Class for Cubies and Cube
*************************************/



/*************************************
    Method for word search
    Traverses cube comparing to hasht
*************************************/



/*************************************
    Main: 
    Calls dictUp, Calls travCube
*************************************/
int main(int arc, char* argv[])
{
//  Check usage
    if (arc != 3) std::cout << "usage: boggle.cxx cube-file word-file" << std::endl;

//  Call method for dictionary
    std::unordered_set<std::string> dictionary = buildHash(argv[2]);

//  Testing dictLookup
    if (dictLookup("xyz", dictionary)) std::cout << "Found xyz in dictionary" << std::endl;
    if (dictLookup("assassin", dictionary)) std::cout << "Found assassin in dictionary" << std::endl;
    if (dictLookup("virtual", dictionary)) std::cout << "Found virtual in dictionary" << std::endl;
    if (dictLookup("irrelevancy", dictionary)) std::cout << "Found irrelevancy in dictionary" << std::endl;

//  Iterate over list of cubes

    //  Upload cube

    //  Traverse cube

// Print # of cubes and time
}


