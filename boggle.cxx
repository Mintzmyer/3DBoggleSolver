/***********************************************
    3D Boggle Solver
    for Connected Signals hiring process
    
    Samantha Mintzmyer
***********************************************/
#include <iostream>
#include <string>
#include <fstream>
#include <unordered_set>
#include <math.h>
#include <cstdio>
#include <ctime>
#include <set>

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

    return dictHash;
}

//  buildSet: accepts dictionary file, returns hashtable of words
std::set<std::string> buildSet(std::string dictName)
{
    std::set<std::string> dictHash;

    //  Read words into hashtable
    std::ifstream infile(dictName);
    std::string s;
    while (std::getline(infile, s))
    {
        dictHash.insert (s);
    }

    return dictHash;
}

//  dictLookup: accepts word and dictionary, returns true/false
bool dictLookup(std::string word, std::unordered_set<std::string> dictHash)
{
    return dictHash.count(word) > 0;
}

//  checkPrefix: accepts word and dictionary, returns if prefix exists
bool checkPrefix(std::string word, std::set<std::string> dictHash)
{
    std::set<std::string>::iterator prefix;
    prefix = dictHash.lower_bound(word);
    //std::cout << "Prefix: " << *prefix;
    std::string result = *prefix;
    bool test;
    if (result.length() >= word.length())
    {
        result = result.substr(0, word.length());
        test = (0 == result.compare(word));
    }
//    if (!test) std::cout << " !";
//    else if (test) std::cout << " =";
    //std::cout << "= " << word << std::endl;
    return test;
}


/*************************************
    Data Structure for Cubies and Cube
    Class for Cubies and Cube
*************************************/
class Cubie
{
    public:
        bool used;
        int neighbors;
        char letter;
        Cubie * nextTo[26];
   
        Cubie();
        void setChar(char);       
        void addNeighbor(Cubie *);
        void printConnections();
};

Cubie::Cubie()
{
    int neighbors = 0;
    bool used = false;
}

void Cubie::setChar(char inLetter)
{
    letter = inLetter;
}

void Cubie::addNeighbor(Cubie * cell)
{
    nextTo[neighbors] = cell;
    //std::cout << cell->letter;
    //std::cout << nextTo[neighbors]->letter;
    this->neighbors++;
}

void Cubie::printConnections()
{
    for (int i = 0; i < neighbors; i++)
    {
        std::cout << nextTo[i]->letter << " ";
    }
    std::cout << std::endl;
}



class Cube
{
    public:
        int size;
        Cubie ** Cubies;

        Cube(int);
        void setConnections();
        void setLetters(std::string);
        void printCube();
        void garbage();
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
    this->Cubies = new Cubie*[size*size*size];

    //std::cout << "Cube initalized with " << size << " dimensions" << std::endl;
    //std::cout << "Now creating cubies for the cube" << std::endl;
    // Create sizeXsizeXsize cubies for the cube
    for (int c = 0; c < size*size*size; c++)
    {
        this->Cubies[c] = new Cubie();
    }
    //std::cout << "Completed cubies for the cell" << std::endl;
}

void Cube::setConnections()
{

    //  Populate cubie nextTo array with pointer to all cubies neighboring
    //  Iterate through the ith layer of the cube
    bool front, back, top, bottom, left, right;

    for (int i = 0; i < size; i++)
    {
        //  Iterate through the jth row of the ith layer
        for (int j = 0; j < size; j++)
        {
            //  Iterate through the kth column of the jth row of the ith layer
            for (int k = 0; k < size; k++)
            {
                //std::cout << "Setting initial values for booleans" << std::endl;
                if (i > 0) front = false;
                else front = true;
                if (i < size-1) back = false; 
                else back = true;
                if (j > 0) top = false;
                else top = true;
                if (j < size-1) bottom = false;
                else bottom = true;
                if (k > 0) left = false;
                else left = true;
                if (k < size-1) right = false;
                else right = true;

         //      std::cout << (i*16)+(j*4)+k << "th Cubie" << std::endl;
           //     std::cout << "Setting 6 faces of cube" << std::endl;
                //  Six faces to cube
                if (!top) Cubies[(i*16)+(j*4)+k]->addNeighbor(Cubies[(i*16)+((j-1)*4)+k]);
                if (!bottom) Cubies[(i*16)+(j*4)+k]->addNeighbor(Cubies[(i*16)+((j+1)*4)+k]);
                if (!front) Cubies[(i*16)+(j*4)+k]->addNeighbor(Cubies[((i-1)*16)+(j*4)+k]);
                if (!back) Cubies[(i*16)+(j*4)+k]->addNeighbor(Cubies[((i+1)*16)+(j*4)+k]);
                if (!left) Cubies[(i*16)+(j*4)+k]->addNeighbor(Cubies[(i*16)+(j*4)+k-1]);
                if (!right) Cubies[(i*16)+(j*4)+k]->addNeighbor(Cubies[(i*16)+(j*4)+k+1]);

           //     std::cout << "Setting 12 edges of cube" << std::endl;
                //  Twelve edges to cube
                if (!top && !left) Cubies[(i*16)+(j*4)+k]->addNeighbor(Cubies[((i)*16)+((j-1)*4)+k-1]);
                if (!top && !right) Cubies[(i*16)+(j*4)+k]->addNeighbor(Cubies[((i)*16)+((j-1)*4)+k+1]);
                if (!bottom && !left) Cubies[(i*16)+(j*4)+k]->addNeighbor(Cubies[((i)*16)+((j+1)*4)+k-1]);
                if (!bottom && !right) Cubies[(i*16)+(j*4)+k]->addNeighbor(Cubies[((i)*16)+((j+1)*4)+k+1]);

                if (!top && !front) Cubies[(i*16)+(j*4)+k]->addNeighbor(Cubies[((i-1)*16)+((j-1)*4)+k]);
                if (!top && !back) Cubies[(i*16)+(j*4)+k]->addNeighbor(Cubies[((i+1)*16)+((j-1)*4)+k]);
                if (!bottom && !front) Cubies[(i*16)+(j*4)+k]->addNeighbor(Cubies[((i-1)*16)+((j+1)*4)+k]);
                if (!bottom && !back) Cubies[(i*16)+(j*4)+k]->addNeighbor(Cubies[((i+1)*16)+((j+1)*4)+k]);

                if (!right && !front) Cubies[(i*16)+(j*4)+k]->addNeighbor(Cubies[((i-1)*16)+((j)*4)+k+1]);
                if (!right && !back) Cubies[(i*16)+(j*4)+k]->addNeighbor(Cubies[((i+1)*16)+((j)*4)+k+1]);
                if (!left && !front) Cubies[(i*16)+(j*4)+k]->addNeighbor(Cubies[((i-1)*16)+((j)*4)+k-1]);
                if (!left && !back) Cubies[(i*16)+(j*4)+k]->addNeighbor(Cubies[((i+1)*16)+((j)*4)+k-1]);

          //      std::cout << "Setting 8 corners of cube" << std::endl;
                //  Eight corners to cube
                if (!top && !front && !right) Cubies[(i*16)+(j*4)+k]->addNeighbor(Cubies[((i-1)*16)+((j-1)*4)+k+1]);
                if (!top && !back && !right) Cubies[(i*16)+(j*4)+k]->addNeighbor(Cubies[((i+1)*16)+((j-1)*4)+k+1]);
                if (!bottom && !front && !right) Cubies[(i*16)+(j*4)+k]->addNeighbor(Cubies[((i-1)*16)+((j+1)*4)+k+1]);
                if (!bottom && !back && !right) Cubies[(i*16)+(j*4)+k]->addNeighbor(Cubies[((i+1)*16)+((j+1)*4)+k+1]);

                if (!top && !front && !left) Cubies[(i*16)+(j*4)+k]->addNeighbor(Cubies[((i-1)*16)+((j-1)*4)+k-1]);
                if (!top && !back && !left) Cubies[(i*16)+(j*4)+k]->addNeighbor(Cubies[((i+1)*16)+((j-1)*4)+k-1]);
                if (!bottom && !front && !left) Cubies[(i*16)+(j*4)+k]->addNeighbor(Cubies[((i-1)*16)+((j+1)*4)+k-1]);
                if (!bottom && !back && !left) Cubies[(i*16)+(j*4)+k]->addNeighbor(Cubies[((i+1)*16)+((j+1)*4)+k-1]);
            }
        }
    }
}

void Cube::setLetters(std::string cubeLetters)
{
    //std::cout << "In the set letters method" << std::endl;
    for (int i = 0; i < size*size*size; i++)
    {
        //std::cout << i << "th loop" << std::endl;
        Cubies[i]->setChar(cubeLetters[i]);
        //std::cout << Cubies[i].letter;
    }
}

void Cube::printCube()
{
    //std::cout << "Cube contents:\n" << std::endl;
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            for (int k = 0; k < size; k++)
            {
                std::cout << Cubies[(4*i)+(16*j)+k]->letter << " ";

            }
            std::cout << "    ";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

void Cube::garbage()
{
    for (int c = 0; c < size*size*size; c++)
    {
        delete this->Cubies[c];
    }
    delete this->Cubies;
}

/*************************************
    Method for word search
    Traverses cube comparing to hasht
*************************************/
int Traverse(Cubie * cell, std::string word, std::unordered_set<std::string> * dictionary, std::set<std::string> * prefixDictionary)
{
    //std::cout << "Word: " << word << std::endl;
    //cell->printConnections();
    
    int total = 0;
    //  Check if word is in dictionary
    if (dictLookup(word, *dictionary))
    {
        total++;
        //std::cout << "********** FOUND WORD #" << total << " : " << word << " *************" << std::endl;
        dictionary->erase(word);
        prefixDictionary->erase(word);
    }
    //  Check if prefix exists
    if (checkPrefix(word, *prefixDictionary))
    {
        //std::cout << "In if with: " << word << std::endl;
        cell->used = true;
        for (int i = 0; i < cell->neighbors; i++)
        {
            word = word + std::string(1, cell->nextTo[i]->letter);
            //std::cout << " +1: " << word  << std::endl;
            if (cell->nextTo[i]->used == false)
                total += Traverse(cell->nextTo[i], word, dictionary, prefixDictionary);
            word.pop_back();        
        }
        cell->used = false;
    }
    else
    {
        cell->used = false;
        //std::cout << "Dead End: " << word << std::endl;
    }
    return total;
}


/*************************************
    Main: 
    Calls dictUp, Calls travCube
*************************************/
int main(int arc, char* argv[])
{
//  Check usage
    if (arc != 3)
    {
        std::cout << "usage: boggle.cxx cube-file word-file" << std::endl;
        return 0;
    }

//  The clock is running
    double duration;
    std::clock_t start;

//  Call method for dictionary
    std::unordered_set<std::string> dictionary = buildHash(argv[2]);
    std::set<std::string> prefixDictionary = buildSet(argv[2]);
    
//  Iterate over list of cubes
    //std::cout << "\nBeginning to iterate over list of cubes" << std::endl;
    //  Upload cube
    std::ifstream infile(argv[1]);
    std::string s;
    int cubeSize;
    int cubeCount = 0;
    while (std::getline(infile, s))
    {
        //std::cout << "In while loop, about to initialize cube" << std::endl;
        try
        {
            std::unordered_set<std::string> gameDict = dictionary;
            std::set<std::string> gamePreDict = prefixDictionary;

            cubeSize = (int) cbrt(s.length());
            Cube game (cubeSize);
            cubeCount++;
            //std::cout << "Cube initialized, about to set letters" << std::endl;
            game.setConnections();
            game.setLetters(s);
            //std::cout << "Letters set, about to print" << std::endl;
            //game.printCube();

            for (int i = 0; i < cubeSize*cubeSize*cubeSize; i++)
            {
//                //std::cout << "Inside connections loop: " << i << std::endl;
//                std::cout << game.Cubies[i]->letter << "   ";
//                game.Cubies[i]->printConnections();
            }

            int wordCount = 0;
            //std::cout << "At traverse loop" << std::endl;

            for (int i = 0; i < (cubeSize*cubeSize*cubeSize); i++)
            {
                std::string word = std::string(1, game.Cubies[i]->letter);
                //std::cout << "New Cell: " << word << std::endl;
                wordCount = wordCount + Traverse(game.Cubies[i], word, &gameDict, &gamePreDict);
                //game.printCube();
            }
            std::cout << wordCount << std::endl;
            game.garbage();
            gameDict.clear();
            gamePreDict.clear();
        }
        catch (int e)
        {
        std::cout << "Exception! Check each cube has the correct number of letters. Exception #" << e << std::endl;
        }
    }
    dictionary.clear();
    prefixDictionary.clear();

    duration = (std::clock() - start ) / (double) CLOCKS_PER_SEC;
    std::cout << "Scored " << cubeCount << " cubes in " << duration << " seconds." << std::endl;

// Print # of cubes and time
}
