#ifndef BUILDHUFFTREE_HPP
#define BUILDHUFFTREE_HPP

#include "readbmp.hpp"
#include<iostream>
//#include "HuffCodeStructure.hpp"

class HuffmanTree {
public:
    float SumProb;
    int SumPix;
    int n = 0, k = 0, l = 0;
    int nextnode = nodeNo; 
    
    // Constructor or other member functions can go here

    // Example member function
    void printNodeNo() {
        std::cout << "nodeNo :: " << nodeNo << std::endl;
    }
/*

while(n<nodeNo-1)
{
//adding lowest Two probablities

sumProb=huff_code[].freq+huff_code[].freq;







}

*/






};

#endif