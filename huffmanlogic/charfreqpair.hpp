#ifndef CHARFREQPAIR_HPP
#define CHARFREQPAIR_HPP

#include<iostream>
using namespace std;

class CFpair{
char ch;
int freq;
public:

CFpair* left;
CFpair* right;
 //insitiializing 
CFpair(char const &ch, int const &freq) : ch(ch), freq(freq){

    this->left=NULL;
    this->right=NULL;
 }
char getchar(){ return ch;}
int getfreq(){return freq;}
void setFreq(int freq){this->freq=freq;}
~CFpair(){
    delete left;
    delete right;
}

};

class pairCompare{
    public:

    int operator()(CFpair* &a,CFpair* &b){
//it compares the frequencies of cfpair obj pointed to by a and b using getfreq()
return a-> getfreq()>b->getfreq();
    }//declares the function call operator() as member function fof the class object of the claass can be called as if thery were functions 

};

#endif