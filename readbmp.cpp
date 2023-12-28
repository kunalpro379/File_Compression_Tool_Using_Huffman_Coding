#include<iostream>
#include<stdio.h>
#include <stdlib.h>
using namespace std;
int main(){
int i,j;
char InputFile[]="input.bmp";
int data=0;
int offset;
int bpp=0;
int width,height;
long bmpsize=0, bmpdataoff=0;
int **imageArr;
int temp=0;

//reading BMP file
FILE* image_file;
image_file=fopen(InputFile,"rb");
if (image_file == NULL)
{
    printf("Error Opening File");
    exit(1);
}
else
{
    offset=0;  //setting cursur at starting pos

offset=2;
fseek(image_file,offset,SEEK_SET); //fseek() is used to move the file pointer associated with a given file to a specific position.
//SEEK_END: It denotes the end of the file.
//SEEK_SET: It denotes starting of the file.
//SEEK_CUR: It denotes the file pointer’s current position. 

//size of BMP file
fread(&bmpsize, 4,1,image_file);// fread function reads the amout of data acc to parameters set by us
//here, bmpsize is the address where the size will be stored
//4 is the number of bytes to read and 1 is itemcout

offset=10;

fseek(image_file, offset, SEEK_SET);
fread(&bmpdataoff, 4,1,image_file);
fseek(image_file,18,SEEK_SET);


fread(&width,4,1,image_file);
fread(&height,4,1,image_file);
//here i got the height and width of image each of 4 bytes 
///height at 18 and width at 22

//  numbers of bits pers pixels used in img
fseek(image_file,2, SEEK_CUR);  //2 bytes read
//thsese 16 b its data will contain info about how many bits are used to repersent each pixel int htbe image
//it will be stored in bpp address  item cout=1
fread(&bpp,2,1,image_file);

///////
fseek(image_file,bmpdataoff,SEEK_SET);//settimg up the file position to the offset by bmpdataoff
//represent thes start of the pixel data in the BMP file


//Creating Image arrya  2d arry  
//imageArr[height][width]
imageArr=(int **)malloc(height*sizeof(int*));

for(int i=0;i<height    ;i++    ){

imageArr[i]=(int*)malloc(width* sizeof(int*));                                                                                                                           
}
int numbytes =(bmpsize-bmpdataoff)/3;
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
        //end=clock();

}
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
int hist[256];
for(int i=0;i<256;i++)
hist[i]=0;

for(int i=0;i<height;i++)
  for(int j=0;j<width;j++)
    hist[imageArr[i][j]]=+1;

    cout<<"Histogrm"<<endl<<endl;
//finding no. of non zero occurrances of
int NzO=0;
for(int i=0;i<256;i++){
if(hist[i]!=0)
NzO+=1;

} 
//max length of code?
float p,ptemp;
for()
    ptemp=(hist[i]/height*width);













	return EXIT_SUCCESS;



}