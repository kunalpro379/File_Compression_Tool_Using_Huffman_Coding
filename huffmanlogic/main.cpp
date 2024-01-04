// #include<iostream>
// #include<string>
// //#include <huffmanlogic/Huffman_Logic.hpp>
// #include "huffman_logic.hpp"

// using namespace std;
// void displayconsole(const string &name){
//     cerr << "Usage: " << name << " <option(s)> SOURCES\n"
//          << "Options:\n"
//          << "\t-h,--help\t\tShow this help message\n"
//          << "\tbenchmark\t\tBenchmark\n"
//          << "compress <source file> [destination file]\t\tCompress source file\n"
//          << "decompress <source file> [destination file]\t\tDecompress source file\n"
//          << endl;



// }

// int main(int argc, char const *argv[]){
// huffman_logic ht;


// if(argc<2||argc>4){displayconsole(argv[0]);}

// else {

//     string arg1=argv[1];
//     string arg2=argv[2];


//     ///compress
//     if(arg1=="compress"){
//         string output;
//         if(argc==3){
//             output=ht.compressLog(arg2);
//             cout<<"Compressed file is "<<output<<endl;
//         }
//         else{
//             string arg3=argv[3];
//             output=ht.compressLog(arg2,arg3);
//         }
//         if (output != "")
//             {
//                 cout << "Output file: " << output << "\n";
//             }
//     }//decomprress
//     else if(arg1=="decompress"){
//             string output;
//             if (argc == 3)
//                 output = ht.decompressfile(arg2,"");
//             else
//             {
//                 string arg3 = argv[3];
//                 output = ht.decompressfile(arg2, arg3);
//             }
//             if (output != "")
//             {
//                 cout << "Output file: " << output << "\n";
//             }


//     }
//     else{
//         displayconsole(argv[0]);
//     }
// }
// return 0;
// }
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <queue>
#include <unordered_map>
#include <bitset>
// #include <filesystem>  // Add this for current_path
#include "charfreqpair.hpp"
#include "scanner.hpp"
#include "huffman_logic.hpp"

using namespace std;



int main() {
    huffman_logic ht;

    // Example: Compression
    std::string inputFileName = "input.bmp";
    std::string compressedFileName = "compressed_output.bmp";
    std::string decompressedFileName = "decompressed_output.bmp";

    cout << "Compressing file: " << inputFileName << endl;
    std::string compressedFile = ht.compressLog(inputFileName, compressedFileName);
    if (!compressedFile.empty()) {
        cout << "Compressed file: " << compressedFile << endl;

        // Example: Decompression
        cout << "Decompressing file: " << compressedFile << endl;
        std::string decompressedFile = ht.decompressfile(compressedFile, decompressedFileName);
        if (!decompressedFile.empty()) {
            cout << "Decompressed file: " << decompressedFile << endl;
        }
    }

    return 0;
}