#include<iostream>
#include "HuffCodeStructure.hpp"  // Include the header file where maxcodelen is declared

using namespace std;


int i, j;
int hist[256];
int width, height;
int maxcodelen;
#include <iostream>

struct pixfreq {
    int pix;
    float freq;
    struct pixfreq* left;
    struct pixfreq* right;
    char* code;

    // Constructor 
    pixfreq(int codeLength) : code(new char[maxcodelen ]) {}  

    // Destructor 
    ~pixfreq() {
        delete[] code;
    }
};

struct huffcode {
    char* code;
    int pix, arrlocation;
    int freq;

    // Constructor 
    huffcode(int codeLength) : code(new char[maxcodelen]) {} 

    // Destructor 
    ~huffcode() {
        delete[] code;
    }
};
struct tree {
    
    int pix;
    int LeftArr, RightArr;
    float freq;
    char* code;

    // Constructor 
    tree(int codeLength) : code(new char[maxcodelen ]) {}  

    // Destructor 
    ~tree() {
        delete[] code;
    }
};



int MaxCodeLen() {
    float p = 1.0, ptemp;
    for (int i = 0; i < 256; i++) {
        ptemp = (hist[i] / (float)(height * width));
        if (ptemp > 0 && ptemp <= p)
            p = ptemp;
    }
    i = 0;
    while ((1 / p) > fib(i))
        i++;
    maxcodelen = i - 3;
    return maxcodelen;
}

int fib(int n) {
    if (n <= 1)
        return n;
    return fib(n - 1) + fib(n - 2);
}



int fib(int n) {
    if (n <= 1)
        return n;
    return fib(n - 1) + fib(n - 2);
}
int main(){
   int codeLength=maxcodelen; 

int nodeNo;


clock_t start,end;



clock_t start,end;
int data=0,hbytes;
int offset;
int bpp=0;

long bmpsize=0, bmpdataoff=0;
int **imageArr;
int temp=0;

double time_taken;


//reading BMP file
FILE* image_file;


    // 23Dec 23
char InputFile[]="input.bmp"; 

image_file=fopen(InputFile,"rb");
if (image_file == NULL)
{
    printf("Error Opening File");
    exit(1);
}
else
{
    start=clock();
    offset=0;  //setting cursur at starting pos
    cout<<"BMP header..."<<endl;

offset=2;
fseek(image_file,offset,SEEK_SET);
cout<<"getting file id...."<<endl;
for(int i=0;i<2;i++){
fread(&data,1,1,image_file);
cout<<data<<endl;
}
cout<<"getting size of Bitmap file"<<endl<<endl;


 //fseek() is used to move the file pointer associated with a given file to a specific position.
//SEEK_END: It denotes the end of the file.
//SEEK_SET: It denotes starting of the file.
//SEEK_CUR: It denotes the file pointer’s current position. 

//size of BMP file
fread(&bmpsize, 4,1,image_file);// fread function reads the amout of data acc to parameters set by us
//here, bmpsize is the address where the size will be stored
//4 is the number of bytes to read and 1 is itemcout
cout<<"  size of Bmp file:: bytes   "<<bmpsize<<endl;
cout<<"  getting offset where the pixel array starts....  "<<endl;
offset=10;

fseek(image_file, offset, SEEK_SET);
fread(&bmpdataoff, 4,1,image_file);
cout<<"Bitmap data offset  :"<<bmpdataoff<<endl<<endl;

fread(&hbytes,4,1,image_file);
cout<<"Number of bytes in header::"<<endl<<hbytes<<endl;
//fseek(image_file,18,SEEK_SET);


fread(&width,4,1,image_file);
fread(&height,4,1,image_file);
//here i got the height and width of image each of 4 bytes 
///height at 18 and width at 22
cout<<"width: "<<width<<endl<<"height: "<<height<<endl;
//  numbers of bits pers pixels used in img
fseek(image_file,2, SEEK_CUR); 

 //2 bytes read
//thsese 16 b its data will contain info about how many bits are used to repersent each pixel int htbe image
//it will be stored in bpp address  item cout=1
fread(&bpp,2,1,image_file);
cout<<"Number of bits per pixel: "<<bpp<<endl;
cout<<"Setting offset for pixel data"<<endl;


///////
fseek(image_file,bmpdataoff,SEEK_SET);//settimg up the file position to the offset by bmpdataoff
//represent thes start of the pixel data in the BMP file
cout<<"Creating IMageArray"<<endl<<endl;

//Creating Image arrya  2d arry  
//imageArr[height][width]
imageArr[i]=(int*)malloc(width* sizeof(int*));                                                                                                                           

int numbytes =(bmpsize-bmpdataoff)/3;
cout<<"Number of bytes : "<<numbytes<<endl;
//bmpsize-->total size of of the bmp file in the bytes including pixels metadata and headers 
//bmpdataoff-->offset of the pixel data from the start of the file
//numbytes-->total number of bytes in the pixel data
//3-->number of bytes per pixel


//reading the data array of a BitMap image
//in array 
for(int i=0;i<height;i++){
    for(int j=0;j<width;j++){
        fread(&temp,3,1,image_file);
        imageArr[i][j]=temp;

    }}

        cout<<"Reading the BMP File into Image Array Completed...\n\n";
        end=clock();


time_taken =(end-start)/CLOCKS_PER_SEC;
cout<<"time_taken_for reading Bpp Image:: "<<"seconds:"<<time_taken<<endl;
fclose(image_file);

//printing the image array
for(int i=0;i<height;i++){
    for(int j=0;j<width;j++){
        printf("%d",imageArr[i][j]);
        printf("\n");

    }
}
//finfing the probablity of occurrance
//creating pixel intensity histogram
//values of pixel intensity ranges from 0 to 255

    for (int i = 0; i < 256; i++)
        hist[i] = 0;

    for (int i = 0; i < height; i++)
        for (int j = 0; j < width; j++)
            hist[imageArr[i][j]] += 1;

    cout << "Histogram" << endl
         << endl;

    // finding no. of non-zero occurrences
    int nodeNo = 0;
    for (int i = 0; i < 256; i++) {
        if (hist[i] != 0)
            nodeNo += 1;
    }

    // 24 DEC 23

    // pixel values 0 to 255
    // not all pixel values are necessarily present in the image so from the histogram
    // and image matrix, we will not have non-zero probability of occurrence,
    // the number of pixel intensity values having non-zero prob will be the number of leaf nodes in the image

    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    // max length of huffman code required?
    // float p = 1.0, ptemp;
    // for (i = 0; i < 256; i++) {
    //     ptemp = (hist[i] / (float)(height * width));
    //     if (ptemp > 0 && ptemp <= p)
    //         p = ptemp;
    // }
    // i = 0;
    // while ((1 / p) > fib(i))
    //     i++;
    // int maxcodelen = i - 3;
    // printf("Max Code len : %d\n\n", maxcodelen);

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////




MaxCodeLen();




    pixfreq pixfreqObj(codeLength);
    huffcode huffcodeObj(codeLength);
    tree treeObj(codeLength);


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
huffman_tree=(struct tree*)malloc(sizeof(struct tree)*TostalNodes);
huff_code=(struct huffcode*)malloc(sizeof(struct huffcode)*nodeNo);

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
    
    pix_freq[j].left=NULL;
    pix_freq[j].right=NULL;

    pix_freq[j].code[0]='\0';
    huffman_tree[j].code[j]='\0';
    j++;



}

//sorting the histogram is done in sorting work 

int TempHuff;
        for(int i=0;i<nodeNo;i++){
            for(int j=i+1;j<nodeNo;j++){
                if(huff_code[i].freq<huff_code[j].freq){
                    TempHuff=huff_code[i];
                    huff_code[i]=huff_code[j];
                    huff_code[j]=TempHuff;
                }
            }
        }


//now huffman tree is builded in hufmantree.hpp


}    
}
}