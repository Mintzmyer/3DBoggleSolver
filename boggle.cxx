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
        bool used;
        int neighbors = 0;
        char letter;
        Cubie * nextTo[26];
   
        void setChar(char);       
        void addNeighbor(Cubie *);
        void printConnections();
};

void Cubie::setChar(char inLetter)
{
    letter = inLetter;
}

void Cubie::addNeighbor(Cubie * cell)
{
    nextTo[neighbors] = cell;
    neighbors++;
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
        Cubie * Cubies;

        Cube(int);
//        void setConnections();
        void setLetters(std::string);
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
/*
}

void Cube::setConnections()
{
*/
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

                //  Six faces to cube
                if (!top) Cubies[(i*16)+(j*4)+k].addNeighbor(&Cubies[(i*16)+((j-1)*4)+k]);
                if (!bottom) Cubies[(i*16)+(j*4)+k].addNeighbor(&Cubies[(i*16)+((j+1)*4)+k]);
                if (!front) Cubies[(i*16)+(j*4)+k].addNeighbor(&Cubies[((i-1)*16)+(j*4)+k]);
                if (!back) Cubies[(i*16)+(j*4)+k].addNeighbor(&Cubies[((i+1)*16)+(j*4)+k]);
                if (!left) Cubies[(i*16)+(j*4)+k].addNeighbor(&Cubies[(i*16)+(j*4)+k-1]);
                if (!right) Cubies[(i*16)+(j*4)+k].addNeighbor(&Cubies[(i*16)+(j*4)+k+1]);

                //  Twelve edges to cube
                if (!top && !left) Cubies[(i*16)+(j*4)+k].addNeighbor(&Cubies[((i)*16)+((j-1)*4)+k-1]);
                if (!top && !right) Cubies[(i*16)+(j*4)+k].addNeighbor(&Cubies[((i)*16)+((j-1)*4)+k+1]);
                if (!bottom && !left) Cubies[(i*16)+(j*4)+k].addNeighbor(&Cubies[((i)*16)+((j+1)*4)+k-1]);
                if (!bottom && !right) Cubies[(i*16)+(j*4)+k].addNeighbor(&Cubies[((i)*16)+((j+1)*4)+k+1]);

                if (!top && !front) Cubies[(i*16)+(j*4)+k].addNeighbor(&Cubies[((i-1)*16)+((j-1)*4)+k]);
                if (!top && !back) Cubies[(i*16)+(j*4)+k].addNeighbor(&Cubies[((i+1)*16)+((j-1)*4)+k]);
                if (!bottom && !front) Cubies[(i*16)+(j*4)+k].addNeighbor(&Cubies[((i-1)*16)+((j+1)*4)+k]);
                if (!bottom && !back) Cubies[(i*16)+(j*4)+k].addNeighbor(&Cubies[((i+1)*16)+((j+1)*4)+k]);

                if (!right && !front) Cubies[(i*16)+(j*4)+k].addNeighbor(&Cubies[((i-1)*16)+((j)*4)+k+1]);
                if (!right && !back) Cubies[(i*16)+(j*4)+k].addNeighbor(&Cubies[((i+1)*16)+((j)*4)+k+1]);
                if (!left && !front) Cubies[(i*16)+(j*4)+k].addNeighbor(&Cubies[((i-1)*16)+((j)*4)+k-1]);
                if (!left && !back) Cubies[(i*16)+(j*4)+k].addNeighbor(&Cubies[((i+1)*16)+((j)*4)+k-1]);

                //  Eight corners to cube
                if (!top && !front && !right) Cubies[(i*16)+(j*4)+k].addNeighbor(&Cubies[((i-1)*16)+((j-1)*4)+k+1]);
                if (!top && !back && !right) Cubies[(i*16)+(j*4)+k].addNeighbor(&Cubies[((i+1)*16)+((j-1)*4)+k+1]);
                if (!bottom && !front && !right) Cubies[(i*16)+(j*4)+k].addNeighbor(&Cubies[((i-1)*16)+((j+1)*4)+k+1]);
                if (!bottom && !back && !right) Cubies[(i*16)+(j*4)+k].addNeighbor(&Cubies[((i+1)*16)+((j+1)*4)+k+1]);

                if (!top && !front && !left) Cubies[(i*16)+(j*4)+k].addNeighbor(&Cubies[((i-1)*16)+((j-1)*4)+k-1]);
                if (!top && !back && !left) Cubies[(i*16)+(j*4)+k].addNeighbor(&Cubies[((i+1)*16)+((j-1)*4)+k-1]);
                if (!bottom && !front && !left) Cubies[(i*16)+(j*4)+k].addNeighbor(&Cubies[((i-1)*16)+((j+1)*4)+k-1]);
                if (!bottom && !back && !left) Cubies[(i*16)+(j*4)+k].addNeighbor(&Cubies[((i+1)*16)+((j+1)*4)+k-1]);
            }
        }
    }
}

void Cube::setLetters(std::string cubeLetters)
{
    for (int i = 0; i < size*size*size; i++)
    {
        Cubies[i].setChar(cubeLetters[i]);
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
    std::cout << std::endl;
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
    if (arc != 3)
    {
        std::cout << "usage: boggle.cxx cube-file word-file" << std::endl;
        return 0;
    }

//  Call method for dictionary
    std::unordered_set<std::string> dictionary = buildHash(argv[2]);

//  Iterate over list of cubes

    //  Upload cube
    std::ifstream infile(argv[1]);
    std::string s;
    int cubeSize;
    while (std::getline(infile, s))
    {
        try
        {
            cubeSize = (int) cbrt(s.length());
            Cube game (cubeSize);
            game.setLetters(s);
//            game.setConnections();
            game.printCube();


            for (int i = 0; i < 64; i++)
            {
                game.Cubies[i].printConnections();
            }

        }
        catch (int e)
        {
        std::cout << "Exception! Check each cube has the correct number of letters. Exception #" << e << std::endl;
        }
    }


    //  Traverse cube

// Print # of cubes and time
}


