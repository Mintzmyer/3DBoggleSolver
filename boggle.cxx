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
    Methods for dictionary:
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

//  dictLookup: accepts word and dictionary, returns true/false
bool dictLookup(std::string word, std::unordered_set<std::string> dictHash)
{
    return dictHash.count(word) > 0;
}

/*************************************
    Data Structure for Cubies and Cube
    Class for Cubies and Cube
*************************************/
class Cubie
{
    public:
        int neighbors;
        char letter;
        int** nextTo;
    
        void setChar(char);       
        void setNeighbors(int);
};

void Cubie::setChar(char inLetter)
{
    letter = inLetter;
}

void Cubie::setNeighbors(int inNeighbors)
{ 
    neighbors = inNeighbors;
    int* array[neighbors];
    nextTo = array;
}

class Cube
{
    int size;
    Cubie * Cubies;

    public:
        Cube(int);
        void printCube();
};

/*****************************************
    Initialize Cube
    4 Cubie 'types' to consider:
    Central    -     26 Connections
    Side       -     17 Connections
    Edge       -     11 Connections
    Corner     -     7 Connections
*****************************************/
Cube::Cube(int inSize)
{
    size = inSize;
    Cubie array[size*size*size];
    Cubies = array;

    // Create sizeXsizeXsize cubies for the cube
    for (int c = 0; c < size*size*size; c++)
    {
        Cubie cell;
        Cubies[c] = cell;
    }

    //  Populate cubie nextTo array with pointer to all cubies neighboring
    //  Iterate through the ith layer of the cube
    for (int i = 0; i < size; i++)
    {
        //  Iterate through the jth cubie of the ith layer
        for (int j = 0; j < size*size; j++)
        {
            //  If layer is 'front' or 'back' face of cube
       	    if (i == 0 || i == size-1)
            {
                //  If cubie is on top row of front/back face
                if (j < size)
                {
                    if (j % size == 0)
                    {
                    //  Top Left Corner Found!
                    }
                    if (j+1 % size == 0)
                    {
                    //  Top Right Corner Found!
                    }
                    else
                    {
                    //  Top Edge Found!
                    }
                }
                //  If cubie is on bottom row of front/back face
                else if (j >= size*(size-1))
                {
                    if (j % size == 0)
                    {
                    //  Bottom Left Corner Found!
                    }
                    if (j+1 % size == 0)
                    {
                    //  Bottom Right Corner Found!
                    }
                    else
                    {
                    //  Bottom Edge Found!
                    }
                }
                else
                {
                //  If cubie is on middle side of front/back face
                    if (j % size == 0)
                    {
                    //  Left Edge Found!
                    }
                    if (j+1 % size == 0)
                    {
                    //  Right Edge Found!
                    }
                    else
                    {
                    //  Side Found!
                    }
                }
            }
            //  If layer is 'middle' faces of cube sandwich
            else
            {
                //  If cubie is on top row of middle faces
                if (j < size)
                {
                    if (j % size == 0)
                    {
                    //  Top Left Edge Found!
                    }
                    if (j+1 % size == 0)
                    {
                    //  Top Right Edge Found!
                    }
                    else
                    {
                    //  Top Side Found!
                    }
                }
                //  If cubie is on bottom row of middle faces
                else if (j >= size*(size-1))
                {
                    if (j % size == 0)
                    {
                    //  Bottom Left Edge Found!
                    }
                    if (j+1 % size == 0)
                    {
                    //  Bottom Right Edge Found!
                    }
                    else
                    {
                    //  Bottom Side Found!
                    }
                }
                else
                {
                //  If cubie is on middle side of middle faces
                    if (j % size == 0)
                    {
                    //  Left Side Found!
                    }
                    if (j+1 % size == 0)
                    {
                    //  Right Side Found!
                    }
                    else
                    {
                    //  Central Found!
                    }
                }
            }
        }
    }
}

void Cube::printCube()
{
    std::cout << "Cube contents:\n" << std::endl;
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            for (int k = 0; k < size; k++)
            {
                std::cout << Cubies[(4*i)+(16*j)+k].letter << " ";

            }
            std::cout << "    ";
        }
        std::cout << std::endl;
    }
}

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


