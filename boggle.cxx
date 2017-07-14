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
    dictLookup checks if word is in hashtable
    checkPrefix checks if the hashtable contains a word with the given prefix
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
    std::string result = *prefix;
    bool test = false;
    if (result.length() >= word.length())
    {
        result = result.substr(0, word.length());
        test = (0 == result.compare(word));
    }
    return test;
}


/*************************************
    Data Structure for Cubies
        Individual cell to comprise Cube
        Methods to initialize Cubie
*************************************/
class Cubie
{
    public:
        bool used;
        int neighbors;
        char letter;
        Cubie ** nextTo;
   
        Cubie();
        void setChar(char);       
        void addNeighbor(Cubie *);
        void printConnections();
        void trashCubie();
};

Cubie::Cubie()
{
    int neighbors = 0;
    bool used = false;
    this->nextTo = new Cubie*[26];
}

void Cubie::setChar(char inLetter)
{
    letter = inLetter;
}

void Cubie::addNeighbor(Cubie * cell)
{
    nextTo[neighbors] = cell;
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

void Cubie::trashCubie()
{
    delete[] this->nextTo;
}

/*************************************
    Data Structure for Cube
        3D array of Cubies
        Methods to initialize Cube
*************************************/
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

    // Create sizeXsizeXsize cubies for the cube
    for (int c = 0; c < pow(size, 3); c++)
    {
        this->Cubies[c] = new Cubie();
    }
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
                if (i > 0) front = false;
                else front = true;
                if (i < this->size-1) back = false; 
                else back = true;
                if (j > 0) top = false;
                else top = true;
                if (j < this->size-1) bottom = false;
                else bottom = true;
                if (k > 0) left = false;
                else left = true;
                if (k < this->size-1) right = false;
                else right = true;


                //  Six faces to cube
                if (!top) Cubies[(i*16)+(j*4)+k]->addNeighbor(Cubies[(i*16)+((j-1)*4)+k]);
                if (!bottom) Cubies[(i*16)+(j*4)+k]->addNeighbor(Cubies[(i*16)+((j+1)*4)+k]);
                if (!front) Cubies[(i*16)+(j*4)+k]->addNeighbor(Cubies[((i-1)*16)+(j*4)+k]);
                if (!back) Cubies[(i*16)+(j*4)+k]->addNeighbor(Cubies[((i+1)*16)+(j*4)+k]);
                if (!left) Cubies[(i*16)+(j*4)+k]->addNeighbor(Cubies[(i*16)+(j*4)+k-1]);
                if (!right) Cubies[(i*16)+(j*4)+k]->addNeighbor(Cubies[(i*16)+(j*4)+k+1]);

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
    for (int i = 0; i < pow(size, 3); i++)
    {
        Cubies[i]->setChar(cubeLetters[i]);
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
    for (int c = 0; c < pow(size, 3); c++)
    {
        Cubies[c]->trashCubie();
        delete this->Cubies[c];
    }
    delete[] this->Cubies;
}

/*************************************
    Method for word search
    Traverses cube comparing to hashtable
*************************************/
int Traverse(Cubie * cell, std::string word, std::unordered_set<std::string> * dictionary, std::set<std::string> * prefixDictionary)
{
    int total = 0;

    //  Check if word is in dictionary
    if (dictLookup(word, *dictionary))
    {
        total++;
        dictionary->erase(word);
        prefixDictionary->erase(word);
    }

    //  Check if prefix exists
    if (checkPrefix(word, *prefixDictionary))
    {
        cell->used = true;
        for (int i = 0; i < cell->neighbors; i++)
        {
            word = word + std::string(1, cell->nextTo[i]->letter);
            if (cell->nextTo[i]->used == false)
                total += Traverse(cell->nextTo[i], word, dictionary, prefixDictionary);
            word.pop_back();        
        }
        cell->used = false;
    }

    else
    {
        cell->used = false;
    }
    return total;
}


/*************************************
    Main: 
    Creates dictionary
    Then creates cubes and traverses them
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
    //  Upload cube
    std::ifstream infile(argv[1]);
    std::string s;
    int cubeSize;
    int cubeCount = 0;
    while (std::getline(infile, s))
    {
        try
        {
            std::unordered_set<std::string> gameDict = dictionary;
            std::set<std::string> gamePreDict = prefixDictionary;
            
            cubeSize = (int) cbrt(s.length());
            Cube game (cubeSize);
     
            cubeCount++;
            game.setConnections();

            game.setLetters(s);
 
            //game.printCube();

            int wordCount = 0;

            for (int i = 0; i < (pow(cubeSize, 3)); i++)
            {
                std::string word = std::string(1, game.Cubies[i]->letter);
                wordCount = wordCount + Traverse(game.Cubies[i], word, &gameDict, &gamePreDict);
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

    // Print # of cubes and time
    duration = (std::clock() - start ) / (double) CLOCKS_PER_SEC;
    std::cout << "Scored " << cubeCount << " cubes in " << duration << " seconds." << std::endl;

}
