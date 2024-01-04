#ifndef HUFFMAN_LOGIC_HPP
#define HUFFMAN_LOGIC_HPP

#include <iostream>
#include<queue>
#include<vector>
#include<string>
#include<unordered_map>
#include<fstream>
#include<bitset>
#include "charfreqpair.hpp"
#include "scanner.hpp"
using namespace std;
class huffman_logic{
    void TraversethroughTree1(CFpair* , unordered_map<char,string>&, string);
    void TraversethroughTree2(CFpair* , unordered_map<string,char>&, string);
    CFpair* READ(ifstream&);
    void writePreorderTree(ofstream&,CFpair*);
    void PRINT(string );
    void print(int);
    void printSep();
int FindPos(string);
public:

string compressLog(string, string);
string decompressfile(string,string);

};
//defining metthods

int  huffman_logic:: FindPos(string filename){
    int pos = -1;
    for(unsigned int i=0;i<filename.length();i++){
        if(filename[i]=='/')
        pos=i;
    }
    return pos;

}
//character to huffmand code mapping
void huffman_logic::TraversethroughTree1(CFpair* head,  unordered_map<char, string>&charkeymapping,string s){
if(head->left==NULL&& head->right==NULL){
//base case 
charkeymapping[head->getchar()]=s;
return ;
}

TraversethroughTree1(head->left,charkeymapping,s+"0");
TraversethroughTree1(head->right,charkeymapping,s+"1");


}

//huffman code to charater mapping
void huffman_logic::TraversethroughTree2(CFpair* head,  unordered_map<string, char>&keycharmapping,string s){
if(head->left==NULL&& head->right==NULL){
//base case 
// charkeymapping[head->getchar()]=s;
keycharmapping[s]=head->getchar();
return ;
}
TraversethroughTree2(head->left,keycharmapping,s+"0");
TraversethroughTree2(head->right,keycharmapping,s+"1");


}

void huffman_logic::writePreorderTree(ofstream &writer,CFpair* head){
if(head->left==NULL&&head->right==NULL){
    writer<<"1";
    writer<<head->getchar();
}
writer<<'0';
writePreorderTree(writer,head->left);
writePreorderTree(writer,head->right);

}
CFpair* huffman_logic:: READ(ifstream &reader){
char nodetyp;
reader>>noskipws>>nodetyp;
if(nodetyp=='1'){
    char ch;
    reader>>noskipws>>ch;
    CFpair* head=new CFpair(ch,0);
}//nodtyp ==0  leafnode
//nodetyp==1 internal node
CFpair* head=new CFpair('\0',0);
head->left=READ(reader);
head->right=READ(reader);
return head;



}
string huffman_logic::compressLog(string inputfile, string compressedfile) {
    cout<<"WOrking>>>"<<endl;
    if (compressedfile == "") {  
        cout<<"Hello kunal"<<endl;// naming compressedfile if name isn't given to it
        int pos = FindPos(inputfile);
        compressedfile = inputfile;
            cout<<"WOrking>>>"<<endl;
    }
    cout<<"Working";
    ifstream reader(inputfile);  // Open the file here
    if (!reader.is_open()) {
        cout<<"Hello kunal"<<endl;
        cerr << "ERROR IN OPENING FILE " << inputfile << endl;
        return "";
    }
        cout<<"Working";

    //now reading the file and counting freqency 
    unordered_map<char,int>* indexing=new unordered_map<char, int>;//dynamically alocate the map
    vector<CFpair*>FREQ;
    char ch;
    int numChar=0;
        cout<<"Working";

    while(reader>>noskipws>>ch){ //cheartors read using i/p streasm extreacter  operator>> here: reader 
    //and noskipwns ensures no whitespace is skipped // and stored extracted char from inp stream strored in var
    numChar++;
    cout<<"Hello kunal"<<endl;
    //if char is already present in the map frequency is updated
    //if not present then new entrey added and new cfpair object created and added to the freqpair 
if (indexing->count(ch) > 0) {
    int I = indexing->at(ch);
    // Use first or second based on whether the character is present or not
    FREQ[I]->setFreq(FREQ[I]->getfreq() + 1);
}
else {
    indexing->insert({
        ch, FREQ.size()
    });
}



    }
        cout<<"Working";

    reader.close();
    
    if(FREQ.size()<=1){
        cout<<"no need for encryption"<<endl;
        return inputfile;
            cout<<"Working";

    }



    reader.close();
    delete indexing;
    cout<<"Working";

    //now creating a min priority queue of cfpair objects
priority_queue<CFpair*,vector<CFpair*>,pairCompare>Freq_Sorter;
for (auto i:FREQ){  //based on frequency of chars they r pushed in prior q
    Freq_Sorter.push(i);
}
CFpair* head;
    cout<<"Working";

//now creating huffman tree
while(!Freq_Sorter.empty()){
CFpair* first =Freq_Sorter.top();
Freq_Sorter.pop();
CFpair* second=Freq_Sorter.top();
CFpair* newpair=new CFpair('\0', first->getfreq()+second->getfreq()); //ggetting two nodes with least freq  
//and creating a new node with freq as sum of freq of the two nodes
//and pushing it back in the priority queue tilloonly one rootremains in prior q
//head ptr is set to the root of the tree
newpair->left=first;
newpair->right=second;
if(Freq_Sorter.size()==1){
    head=newpair;
    break;
}

}
    cout<<"Working";

//creating a mapping between char and theri hufman code
unordered_map<char,string>keycharmapping;
TraversethroughTree1(head,keycharmapping, "");

//read from fileand writing the compressed file
ofstream writer;
writer.open(compressedfile,ios::out| ios::trunc);//createing o/p file stream and opens file in op mode
//trunc flag trucates the file if it already exists
reader.open(inputfile,ios::in);
//input file stream reader opens the file by source file
//writeing a treeto the compress file in preorder form 
writePreorderTree(writer,head); 
delete head;
    cout<<"Working";





return compressedfile;
}


string huffman_logic::decompressfile(string compressedFile, string getfile){

if(getfile==""){//empty parameter
    int pos=FindPos(compressedFile);  //finding last occurrance8 of '/'
    getfile=compressedFile.substr(0, pos+1)+"decompressed_";
    if(compressedFile.length()-pos+1>=11&& compressedFile.substr(pos+1,11)=="compressed_"){
        getfile+=compressedFile.substr(pos+12);
    }
    else{
        getfile+=compressedFile.substr(pos+1);
    }
}
ifstream reader;
ofstream writer;
reader.open(compressedFile, ios::in);//opening compressed file for readning
if(!reader.is_open()){       
     std::cerr << "ERROR: No such file exists or cannot open file " + compressedFile;
        return "";
}

//reads the huff tree from file
CFpair* head= READ(reader);
//creating chear map for decompressn by traversing the tree
unordered_map<string,char>keycharmap;
 TraversethroughTree2(head,keycharmap,"");
 delete head;

 int totalchars;
 reader>>std::noskipws>>totalchars;
//getting number of char from copressed file to know how many char to read while decompressing
 writer.open(getfile,ios::out|ios::trunc);
 string key="";
 int readchars=0;
 char ch; 
 while (reader>>std::noskipws>>ch&&readchars!=totalchars){
//while preserving white spaces reads each charconverting into binary representation and appends it into the key string 
//if current key string corrsoponds to huff code in the keychar mapp
//it writes the corrosponidng char in the output file
std:: string binary_read=std::bitset<8>(ch).to_string();//converting char into ist bin and sores as string 
for(unsigned int i=0;i<binary_read.length();i++){


key+=binary_read[i];
if(keycharmap.count(key)>0){
    writer<<keycharmap[key];
    key="";
    readchars++;

if(readchars==totalchars){break;}
}
}

 }
     reader.close();
    writer.close();
    if (readchars != totalchars)
    {
        std::cerr << "ERROR: Compressed file is corrupted\n";
        return "";
    }
 return getfile;
}








#endif  //end