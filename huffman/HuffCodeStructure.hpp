#include<iostream>
#include "readbmp.hpp"
#include "BuildHuffTree.hpp"
#ifndef HUFFCODESTRUCTURE_HPP
#define HUFFCODESTRUCTURE_HPP
using namespace std;

class HuffmanStructure{
    public:


//defining structures for pix frequecny and hufcode
struct pixfreq {
    int pix;
    float freq;
    struct pixfreq* left;
    struct pixfreq* right;
    char code[maxcodelen];
};

struct huffcode {
    char code[maxcodelen];
    int pix,arr;
    int freq;
};
struct tree {
int pix;
int LeftArr, RightArr;
float freq;
char code[maxcodelen];

};

//declaring structs
struct pixfreq *pix_freq;
struct huffcode *huff_code;
//each element in arr is node in huffman tree
//pix_freq and huffcode--> will cointain info of all the leaf nodes in huffman tree

// pix_freq-> all nodes in huffman tree
// huffcode-> to store sorted tree 

// when we combine two nodes of lowest frequency, new updated node will be appended
// to the end of pix freq and also huffcodes but note that only huffcodes will sort again according to
//probablity of occurrance after new node added 

//also pos of neew node in array pix_freq will be stored in the arrloc,

struct tree* huffman_tree;

//if n number of leaf node -> 2n-1 nodes in huffman tree

//so
int TostalNodes= 2*nodeNo-1;
int TotalPixels=height*width;
pix_freq=(struct pixfreq*)malloc(sizeof(struct pixfreq)*TotalPixels);
huffman_tree=(struct tree*)malloc(sizeof(struct tree)*TotalNodes);
huff_code=(struct hufcode*)malloc(sizeof(struct huffcode)*nodeNo);


//creating pix_freq array
float TempFrq;
for(int i=0;i<256;i++){
if(hist[i]!=0)
{
    
}



}



};
#endif