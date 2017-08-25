# 3DBoggleSolver
Solves a Boggle-ish puzzle with 3D 4x4x4 cube of letters
            Samantha Mintzmyer

    To run:
    * Clone the repository
    * Use cmake to build project
    * Use make to compile project


—-Contents-—

1) Overview of the project

2) Data structures used

3) Explanation of techniques

1-Overview of the Project—
    The game is a n-cube, each with (n^3) individual letters. It is implemented in C++ and developed on a MacBook Pro using Vim.

2-Data structures used—
    I used subtly different dictionaries for two purposes. A standard std::set of strings contained a dictionary that could check if any words had a given prefix, using the ‘lower_bound’ method. A std::unordered_set of strings has a slightly faster lookup time using the ‘count’ method, so I used that to determine if a word was an exact match.

    The game is modeled in c++ classes to utilize OOP. I considered an adjacency matrix for mapping cubies connections, but given another chance I believe an unordered_multimap is faster and more appropriate for this project.

3-Explanation oAAAf techniques—
    My approach was a typical dynamic programming solution. I divided the problem into a base case and a recurrence relation as follows; when a string cannot possibly form a word (that is it is the prefix of no words in the dictionary) we consider that case explored. Until then, recurse to the neighbors of the last letter.

    I believe this problem lends itself well to utilizing optimizations that simulate multithreading. Because each grid and indeed each path is independent, an expansion on my solution will be to traverse the grid with 64 copies, so the processor can work on each starting point and sum the totals together. Similarly, instead of creating and traversing a grid one at a time, iterate over the grids in bunches and let the processor work on groups of grids.

    Rather than store a list of words found and check them against the words being traversed, I opted to remove words that were already found from the dictionaries to save time looking them up. This meant fresh dictionaries had to be copied for each cube, but I believe the design is a net gain in speed.
