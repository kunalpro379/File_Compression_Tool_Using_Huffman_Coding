#ifndef SCANNER_HPP
#define SCANNER_HPP

#include <fstream>//for file handling
#include<iostream>
#include<string>
using namespace std;
// using namespace ios;

class Scanner{
    private:
ifstream reader;//for reading file 
//private member reader varible instance of ifstream

    public: 
   
    int getfilesize(string filename){
         try{ reader.open( filename, ios::binary|ios::ate);  //opening file in binarymode and 
         //setting up a file pointer to the end of the file ios.ate
        if(!reader.is_open()) throw "unable to open "+filename;

        reader.seekg(0, ios::end);  //if file opened file pointer end me lagjayega using seekg
        //determing size of file
        int size=reader.tellg();// getting position of file pointer 
        reader.close();
        return size;
        }
        catch (string err)
        {
            cerr<<err<<endl;
            return -1;
        }
       
    }

};
#endif

