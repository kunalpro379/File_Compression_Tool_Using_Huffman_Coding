#include<iostream>
#include<stdio.h>
#include<vector>
#include<time.h>
#include<cstring>
using namespace std;
float p=1.0;

struct pixfreq {
    int pix,LeftArrLoc,RightArrLoc;
    float freq;
    struct pixfreq* left;
    struct pixfreq* right;

    vector<char>code;


};

struct huffcode {
   
    int pix, arrlocation;
    float freq;


};
struct tree
	{
		int pix, LeftArrLoc,RightArrLoc;
		float freq;
		vector<char>code;
	};
int codelen(char *code)
{
	int l=0;
	while(*(code+l)!='\0')
		l++;
	return l;
}

void strconcat(vector<char>& str, const vector<char>& parentcode, char add) {
    for (char ch : parentcode) {
        str.push_back(ch);
    }
    if (add != '2') {
        str.push_back(add);
    }
}







int fib(int n) {
    if (n <= 1)
        return n;
    return fib(n - 1) + fib(n - 2);
}



int main(){


int i, j;
int hist[256];
int width, height;
int nodeNo;
int maxcodelen;

clock_t start;
clock_t end;



   int data = 0, hbytes;
    int offset;
    int bpp = 0;
    long bmpsize = 0, bmpdataoff = 0;
    int** imageArr;
    int temp = 0;

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
    std::cout<<"BMP header..."<<endl;

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
/*


*/
//Creating Image arrya  2d arry  
//imageArr[height][width]



//bmpsize-->total size of of the bmp file in the bytes including pixels metadata and headers 
//bmpdataoff-->offset of the pixel data from the start of the file
//numbytes-->total number of bytes in the pixel data
//3-->number of bytes per pixel
		printf("Creating Image array...\n\n");
		imageArr = (int **)malloc(height*sizeof(int *));
		for(i=0;i<height;i++)
		{
			imageArr[i] = (int *)malloc(width*sizeof(int));
		}
		//int image[height][width];
		int numbytes = (bmpsize - bmpdataoff)/3;
		printf("Number of bytes: %d \n\n",numbytes);
		printf("Reading the BMP File into Image Array...\n\n");
        // Assuming imageArr is a 2D array representing the image
// and hist is an array to store the histogram
		for(i=0;i<height;i++)
		{
			for(j=0;j<width;j++)
			{
				fread(&temp,3,1,image_file);
				temp = temp&0x0000FF;
				imageArr[i][j] = temp;
			}
		}
		printf("Image array allocated...\n\n");
		end = clock();






}//else
	time_taken = ((double)(end-start))/CLOCKS_PER_SEC;
	printf("Time taken for reading BMP Image:: %f seconds\n\n",time_taken);
	fclose(image_file);
	//Image
	for(i=0;i<height;i++){
		for(j=0;j<width;j++)
				printf("%d ",imageArr[i][j]);
		printf("\n");
}
std::cout << "\nPress any key to continue.." << std::endl;
        // Finding the probability of occurrence
        // Creating pixel intensity histogram
        // Values of pixel intensity range from 0 to 255

        for ( i = 0; i < 256; i++)
            hist[i] = 0;

        for ( i = 0; i < height; i++)
            for ( j = 0; j < width; j++)
                hist[imageArr[i][j]] += 1;

        cout << "Histogram" << endl << endl;

        for ( i = 0; i < 256; i++) {
            if (hist[i] != 0)
                nodeNo += 1;
        }

        // Print the histogram
        for ( i = 0; i < 256; i++) {
            if (hist[i] != 0) {
                cout << "Pixel intensity " << i << ": " << hist[i] << " occurrences" << endl;
            }
        }

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


 float ptemp;
    for ( i = 0; i < 256; i++) {
        ptemp = static_cast<float>(hist[i]) / (height * width);
        if (ptemp > 0 && ptemp <= p)
            p = ptemp;
    }

i=0;
    while ((1 / p) > fib(i))
        i++;
    maxcodelen = i - 3;
    cout << endl << "maxcodelen :: " << maxcodelen << endl;

    int codeLength = maxcodelen;





//declaring structs ///////////////////////////////////////



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

//initializing pix-freq and hufff_code//////////////////////////////////////////

//info about leaf nodes
 float TempFrqProbablity;
    for (int i = 0; i < 242; i++) {
        if (hist[i] != 0) {
            // Pixel intensity values
            huff_code[j].pix = i;
            pix_freq[j].pix = i;
            huffman_tree[j].pix = i;
            huffman_tree[j].LeftArrLoc = -1;
            huffman_tree[j].RightArrLoc = -1;

            huff_code[j].arrlocation = j;

            // Probability of occurrence
            TempFrqProbablity = static_cast<float>(hist[i]) / TotalPixels;
            pix_freq[j].freq = TempFrqProbablity;
            huff_code[j].freq = TempFrqProbablity;
            huffman_tree[j].freq = TempFrqProbablity;

            pix_freq[j].left = NULL;
            pix_freq[j].right = NULL;

            pix_freq[j].code.clear();  // Clear the vector before using it
            huffman_tree[j].code.clear();  // Clear the vector before using it

            j++;
        }
    }
//sorting the histogram  /////////////////////////////////////////// 

        struct huffcode TempHuff;
        for (int i = 0; i < nodeNo; i++) {
            for (int j = i + 1; j < nodeNo; j++) {
                if (huff_code[i].freq < huff_code[j].freq) {
                    TempHuff = huff_code[i];
                    huff_code[i] = huff_code[j];
                    huff_code[j] = TempHuff;
                }
            }
        }
//   building huffman treee //////////////////////////////////////////////
    float SumProb;
    int SumPix;
    int n = 0, k = 0, l = 0;
    int nextnode = nodeNo; 
 cout<<endl<<nodeNo<<endl<<endl;
 int nxtnode=nodeNo;

//new position of combined node

 while(n<nodeNo-1){
cout<<endl<<endl<<huff_code[i].pix<<endl<<huff_code[i].freq<<endl;

//adding the lowest two probablities st the end (Heap array)
SumPix=huff_code[nodeNo-n-1].freq+huff_code[nodeNo-n-2].freq;
SumProb=huff_code[nodeNo-n-1].pix+huff_code[nodeNo-n-2].pix;

//finding new position  combined node
while(SumProb<=huff_code[i].freq){
//till we get position where new freq is less that at ith position
i++;
}

// now appending the added probablities ito the pix_fre array

//creating new node in pix_freq and huffman_tree arrays  for combinned node
//here shown by sumpix and sumprob 
pix_freq[nextnode].pix=SumPix;
pix_freq[nextnode].freq=SumProb;

huffman_tree[nextnode].pix=SumPix;
huffman_tree[nextnode].freq=SumProb;
//at  the new position of combined node 



//as i know,  huff_code[j].arrlocation=j; 
pix_freq[nextnode].left=&pix_freq[huff_code[nodeNo-n-2].arrlocation];
//pix_freq[nextnode].left assigning the address of node with (nodeNo-n-2)th frequenc 
//connecting SumPix with their left and right child and same with sumprob
pix_freq[nextnode].right=&pix_freq[huff_code[nodeNo-n-1].arrlocation];
//pix_freq[nextnode].left assigning the address of node with (nodeNo-n-1)th frequenc y

huffman_tree[nextnode].LeftArrLoc=huff_code[nodeNo-n-2].arrlocation;
//huffman_tree[nextnode].LeftArr is assigned the array index of node with (nodeNo-n-2)th freq
huffman_tree[nextnode].RightArrLoc=huff_code[nodeNo-1-n].arrlocation;
//  


pix_freq[nodeNo].code[0]='\0';
huffman_tree[nodeNo].code[0]='\0';


//sorting the new array
//updating 
for(k=nodeNo;k>=0;k--){
    if(k==i){

            huff_code[k].pix=SumPix;
            huff_code[k].freq=SumProb;
            huff_code[k].arrlocation=nextnode;

    }
    else if(k>i){
huff_code[k]=huff_code[k-1];

    }


}
n+=1;
nextnode+=1;
end=clock();


start=clock();

//now assigining code 
char Left='0';
char Right='0';
int Index;
//starting from root we assign 0 and 1 to the children and newly formed node will be appended to the arr pix_freq
//root is last eleme nt of arr at index totalNodes-1
//starting from last index iterate over arr and  assigninng 0 or 1 till we reach parent node
//num of steps =totalnodes-nodno-1
/*
for (i = TostalNodes - 1; i > nodeNo; i--)
{
    // nodeNo represents the number of leaf nodes, so we iterate only for internal nodes

    if (pix_freq[i].left != NULL)
    {
        strconcat(pix_freq[i].left->code, pix_freq[i].code, '0');
        //strconcat(huffman_tree[huffman_tree[i].LeftArrLoc].code, huffman_tree[i].code, '0');
    }

    if (pix_freq[i].right != NULL)
    {
        strconcat(pix_freq[i].right->code, pix_freq[i].code, '1');
        //strconcat(huffman_tree[huffman_tree[i].RightArrLoc].code, huffman_tree[i].code, '1');
    }
} 
*/
char left = '0';
char right = '1';
int index;

for (i = TostalNodes - 1; i >= nodeNo; i--) {
    if (pix_freq[i].left != NULL) {
        strconcat(pix_freq[i].left->code, pix_freq[i].code, left);
    }
    if (pix_freq[i].right != NULL) {
        strconcat(pix_freq[i].right->code, pix_freq[i].code, right);
    }
}

// Assuming p is a null-terminated string
const char* p = "R";
// Last node is root
strconcat(pix_freq[TostalNodes - 1].code, vector<char>(p, p + std::strlen(p)), '2');

end = clock();
time_taken = ((double)(end - start)) / CLOCKS_PER_SEC;
cout << "time_taken::::" << time_taken << endl;

// Printing huffcodes
cout << "printing huffman code:::::::" << endl;
cout << "Pixel vals -> code" << endl << endl;
for(i=0;i<nodeNo;i++)
	{
		if(snprintf(NULL,0,"%d",pix_freq[i].pix)==2)
			printf("     %d      -> %s\n",pix_freq[i].pix,pix_freq[i].code);
		else
			printf("    %d      -> %s\n",pix_freq[i].pix,pix_freq[i].code);
	}



    

 }}