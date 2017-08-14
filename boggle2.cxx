/***********************************************
    3D Boggle Solver
    for Connected Signals hiring process
    
    Samantha Mintzmyer
***********************************************/
#include <iostream>
#include <string>
#include <fstream>
#include <unordered_set>
#include <unordered_map>
#include <map>
#include <math.h>
#include <cstdio>
#include <ctime>
#include <set>

/*************************************
    Methods for dictionary:
    dictLookup checks if word is in hashtable
    checkPrefix checks if the hashtable contains a word with the given prefix
*************************************/

class WordWizard
{
    //  Data types
    protected:
        //  Prefix Dictionary
        std::set<std::string> PrefixDict;
        //  Word Dictionary
        std::unordered_set<std::string> WordDict;
        //  Lookup History
        std::unordered_multimap<std::string, bool> History;

    //  Methods 
    public:
        //  Prefix Dictionary and Checker
        void buildHash(std::string);
        bool dictLookup(std::string);
        //  Word Dictionary and Checker
        void buildSet(std::string);
        bool checkPrefix(std::string);
        //  History checker
        bool checkHistory(std::string);
};

//  buildHash: accepts dictionary file, returns hashtable of words
void WordWizard::buildHash(std::string dictName)
{
    //  Read words into hashtable
    std::ifstream infile(dictName);
    std::string s;
    while (std::getline(infile, s))
    {
        this->PrefixDict.insert (s);
    }
}

//  buildSet: accepts dictionary file, returns hashtable of words
void WordWizard::buildSet(std::string dictName)
{
    //  Read words into hashtable
    std::ifstream infile(dictName);
    std::string s;
    while (std::getline(infile, s))
    {
        WordDict.insert (s);
    }
}

//  dictLookup: accepts word and dictionary, returns true/false
bool WordWizard::dictLookup(std::string word)
{
    return this->WordDict.count(word) > 0;
}

//  checkPrefix: accepts word and dictionary, returns if prefix exists
bool WordWizard::checkPrefix(std::string word)
{
    if (checkHistory(word)) return true;
    std::set<std::string>::iterator prefix;
    prefix = PrefixDict.lower_bound(word);
    std::string result = *prefix;
    bool test = false;
    if (result.length() >= word.length())
    {
        result = result.substr(0, word.length());
        test = (0 == result.compare(word));
    }
    std::pair<std::string, bool> prefixResult (word, test);
    this->History.insert(prefixResult);
    return test;
}

//  checkHistory: accepts word, returns true/false
bool WordWizard::checkHistory(std::string word)
{
    return this->History.count(word) > 0;
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
        std::string letter;
        std::multimap<std::string*,Cubie*> nextTo;
        //Cubie ** nextTo;
   
        Cubie();
        void setLetter(std::string);       
        void addNeighbor(Cubie *);
        void printConnections();
        void trashCubie();
};

Cubie::Cubie()
{
    this->neighbors = 0;
    this->used = false;
//    this->nextTo = new Cubie*[26];
}

void Cubie::setLetter(std::string inLetter)
{
    letter = inLetter;
}

void Cubie::addNeighbor(Cubie * cell)
{
//    std::cout << "Index: " << this->neighbors << std::endl;
//  Should this really be Cubie**? Maybe Cubie*...
    std::pair<std::string*, Cubie*> neighbor (&(cell->letter), cell);
    this->nextTo.insert (neighbor);
}

void Cubie::printConnections()
{
    for (int i = 0; i < neighbors; i++)
    {
        //std::cout << nextTo[i]->letter << " ";
    }
    std::cout << std::endl;
}

void Cubie::trashCubie()
{
    //delete[] this->nextTo;
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
        int totalWords = 0;
        Cubie ** Cubies;
        std::unordered_set<std::string> wordsFound;

        Cube(int);
        void setConnections();
        void setLetters(std::string);
        bool checkWordsFound(std::string);
        void printCube();
        void garbage();
        void traverse(Cubie*, std::string, WordWizard*);
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
    this->size = inSize;
    this->Cubies = new Cubie*[size*size*size];

    // Create sizeXsizeXsize cubies for the cube
    for (int c = 0; c < pow(size, 3); c++)
    {
        this->Cubies[c] = new Cubie();
//        std::cout << "New: " << this->Cubies[c]->neighbors << std::endl;
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
        Cubies[i]->setLetter( std::string(1, cubeLetters[i]) );
    }
}

//  checkWordsFound: accepts word, returns true/false
bool Cube::checkWordsFound(std::string word)
{
    return this->wordsFound.count(word) > 0;
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
void Cube::traverse(Cubie * cell, std::string word, WordWizard* library)
{

    //  Check if word is in dictionary
    if ( (!checkWordsFound(word)) && ((*library).dictLookup(word) ))
    {
        this->totalWords++;
        this->wordsFound.insert(word);
    }

    cell->used = true;

    //  Search unique elements of nextTo multimap for valid prefix
    std::string letter;
    for (std::multimap<std::string*, Cubie*>::iterator Neighbor = cell->nextTo.begin(); Neighbor != cell->nextTo.end(); ) 
    {
        letter = *(Neighbor->first);
        word = word + letter;
        //  Traverse all unused valid prefix elements
        if ((*library).checkPrefix(word))
        {
            do
            {
                this->traverse(Neighbor->second, word, library);
            } while (Neighbor != cell->nextTo.end() && letter.compare(*(Neighbor->first)));
        }
        else
        {
            do 
            {
                ++Neighbor;
            } while (Neighbor != cell->nextTo.end() && letter.compare(*(Neighbor->first)));
        }
        word.pop_back();
    }

    cell->used = false;
    return;
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

//  Make new dictionary object
    WordWizard* reference = new WordWizard;
    reference->buildHash(argv[2]);
    reference->buildSet(argv[2]);
    
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
            cubeSize = (int) cbrt(s.length());
            Cube game (cubeSize);
     
            cubeCount++;
            game.setConnections();

            game.setLetters(s);
 
            //game.printCube();

            int wordCount = 0;

            for (int i = 0; i < (pow(cubeSize, 3)); i++)
            {
                std::string word = game.Cubies[i]->letter;
                game.traverse(game.Cubies[i], word, reference);
            }
            std::cout << game.totalWords << std::endl;
            game.garbage();
        }
        catch (int e)
        {
        std::cout << "Exception! Check each cube has the correct number of letters. Exception #" << e << std::endl;
        }
    }

    // Print # of cubes and time
    duration = (std::clock() - start ) / (double) CLOCKS_PER_SEC;
    std::cout << "Scored " << cubeCount << " cubes in " << duration << " seconds." << std::endl;

}
