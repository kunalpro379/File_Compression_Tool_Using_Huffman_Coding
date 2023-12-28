#include<iostream>
#include<stdio.h>
#include <stdlib.h>
int main(){
int i,j;
char InputFile[]="input.bmp";
int data=0;
int offset;
int bpp=0;
int width,height;
long bmpsize=0, bmpdataoff=0;
int **image;
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


fseek();
fseek();




}




}