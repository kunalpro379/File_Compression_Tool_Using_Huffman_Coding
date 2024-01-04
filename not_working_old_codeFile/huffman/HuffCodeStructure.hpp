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
    int pix,arrlocation;
    int freq;
};
struct huffcode TempHuff;

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

//initializing pix-freq and hufff_code
//info about leaf nodes
float TempFrqProbablity;

for(int i=0;i<256;i++){
if(hist[i]!=0)
{
    //pixel intensityr vals
    huff_code[j].pix=i;
    pix_freq[j].pix=i;
    //frequency


    huffman_tree[j].pix=i;
    huffman_tree[j].LeftArr=-1;
    huffman_tree[j].RightArr=-1;

    huff_code[j].arrlocation=j;

    TempFrqProbablity=(float)hist[i]/TotalPixels; //----> probablity of occurrance of for  the frequencey of pixels at some intensity that is historgram by dividing total number of pixels in the image 
    pix_freq[j].freq=TempFrqProbablity;
    huff_code[j].freq=TempFrqProbablity;
    huffman_tree[j].freq=TempFrqProbablity;
    
    pix_freq[j].left=NULL:
    pix_freq[j].right=NULL;

    pix_freq[j].code[0]='\0';
    huffman_tree[j].code[j]='\0';
    j++;



}

//sorting the histogram is done in sorting work 

void sortHuffCode(){
        for(int i=0;i<nodeNo;i++){
            for(int j=i+1;j<nodeNo;j++){
                if(huff_code[i].freq<huff_code[j].freq){
                    TempHuff=huff_code[i];
                    huff_code[i]=huff_code[j];
                    huff_code[j]=TempHuff;
                }
            }
        }
    }

//now huffman tree is builded in hufmantree.hpp


}

};






#endif