#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<time.h>

int codelen(char *code)
{
	int l=0;
	while(*(code+l)!='\0')
		l++;
	return l;
}

void strconcat(char *str, char *parentcode, char add)
{
	int i=0;
	while(*(parentcode+i)!='\0')
	{
		*(str+i)=*(parentcode+i);
		i++;
	}
	if(add!='2')
	{
		str[i]=add;
		str[i+1]='\0';
	}
	else
		str[i]='\0';
}

int fib(int n)
{
    if (n <= 1)
        return n;
    return fib(n - 1) + fib(n - 2);
}

int main()
{
	int i,j,r,c;
	char filename[] = "lenagray88.bmp";
	int data=0,offset,hbytes,width,height;
	long bmpsize=0,bmpdataoff=0,bpp=0;
	int **image;
	int temp=0;
	clock_t  start,end;
	double time_taken;

	//Reading the BMP File
	FILE *image_file;
	image_file = fopen(filename,"rb");
	if(image_file==NULL)
	{
		printf("Error Opening File!!");
		exit(1);
	}
	else
	{
		start = clock();
		//Set file position of the stream to the beginning
		printf("Processing BMP Header...\n\n");
		offset = 0;
		fseek(image_file,offset,SEEK_SET);
		printf("Getting file ID...\n\n");
		for(i=0;i<2;i++)
		{
			fread(&data,1,1,image_file);
			printf("%c",data);
		}
		printf("\n\nGetting size of BMP File...\n\n");
		fread(&bmpsize,4,1,image_file);
		printf("Size of the BMP File:: %ld bytes\n\n",bmpsize);
		printf("Getting offset where the pixel arrray starts...\n\n");
		offset = 10;
		fseek(image_file,offset,SEEK_SET);
		fread(&bmpdataoff,4,1,image_file);
		printf("Bitmap data offset:: %ld\n\n",bmpdataoff);
		printf("DIB Header\n\n");
		fread(&hbytes,4,1,image_file);
		printf("Number of bytes in header:: %d\n\n",hbytes);
		fread(&width,4,1,image_file);
		fread(&height,4,1,image_file);
		printf("Width of Image: %d\n",width);
		printf("Height of image: %d\n\n",height);
		fseek(image_file,2,SEEK_CUR);
		fread(&bpp,2,1,image_file);
		printf("Number of bits per pixel: %ld\n\n",bpp);
		printf("Setting offset to start of pixel data...\n\n");
		fseek(image_file,bmpdataoff,SEEK_SET);
		printf("Creating Image array...\n\n");
		image = (int **)malloc(height*sizeof(int *));
		for(i=0;i<height;i++)
		{
			image[i] = (int *)malloc(width*sizeof(int));
		}
		//int image[height][width];
		int numbytes = (bmpsize - bmpdataoff)/3;
		printf("Number of bytes: %d \n\n",numbytes);
		printf("Reading the BMP File into Image Array...\n\n");
		for(r=0;r<height;r++)
		{
			for(c=0;c<width;c++)
			{
				fread(&temp,3,1,image_file);
				temp = temp&0x0000FF;
				image[r][c] = temp;
			}
		}
		printf("Image array allocated...\n\n");
		end = clock();
	}
	time_taken = ((double)(end-start))/CLOCKS_PER_SEC;
	printf("Time taken for reading BMP Image:: %f seconds\n\n",time_taken);
	fclose(image_file);
	//Image
	for(r=0;r<height;r++){
		for(c=0;c<width;c++)
				printf("%d ",image[r][c]);
		printf("\n");}
	//Finding the probability of occurence
	int hist[256];
	for(i=0;i<256;i++)
	{
		hist[i]=0;
	}
	for(i=0;i<height;i++)
		for(j=0;j<width;j++)
			hist[image[i][j]]+=1;
	
	printf("Histogram\n\n");
	//free(image);
	//image = NULL;
	//Finding number of non-zero occurences
	int nnz=0;
	for(i=0;i<256;i++)
	{
		if(hist[i]!=0)
			nnz+=1;
	}
	 // Calculating max length of code word
	float p = 1.0,ptemp;
	for(i=0;i<256;i++){
		ptemp = (hist[i]/(float)(height*width));
		if (ptemp>0 && ptemp<=p)
			p = ptemp;
	}
    i = 0;
    while ((1 / p) > fib(i))
        i++;
	int maxcodelen = i-3;
	printf("Max Code len : %d\n\n",maxcodelen);
	//Defining Structures pixfreq
	int maxl=maxcodelen;
	struct pixfreq
	{
		int pix,larrloc,rarrloc;
		float freq;
		struct pixfreq *left, *right;
		char code[102020202020220];
	};
	//Defining Structures huffcode
	struct huffcode
	{
		int pix,arrloc;
		float freq;
	};
	//Defining Struct to transmit
	struct tree
	{
		int pix, larrloc,rarrloc;
		float freq;
		char code[1010101010110];
	};
	//Declaring structs
	struct pixfreq *pix_freq;
	struct huffcode *huffcodes;
	struct tree *huffman_tree;
	int totalnnz = 2*nnz-1;
	int totpix = height*width;
	pix_freq = (struct pixfreq *)malloc(sizeof(struct pixfreq)*totalnnz);
	huffcodes = (struct huffcode *)malloc(sizeof(struct huffcode)*nnz);
	huffman_tree = (struct tree *)malloc(sizeof(struct tree)*totalnnz);
	j=0;
	float tempfreq;
	for(i=0;i<256;i++)
	{
		if(hist[i]!=0)
		{
			huffcodes[j].pix = i;
			pix_freq[j].pix = i;
			huffman_tree[j].pix=i;
			huffman_tree[j].larrloc=-1;
			huffman_tree[j].rarrloc=-1;
			huffcodes[j].arrloc = j;
			tempfreq = (float)hist[i]/(float)totpix;
			pix_freq[j].freq = tempfreq;
			huffcodes[j].freq = tempfreq;
			huffman_tree[j].freq = tempfreq;
			pix_freq[j].left = NULL;
			pix_freq[j].right = NULL;
			pix_freq[j].code[0] = '\0';
			huffman_tree[j].code[0]='\0';
			j++;
		}
	}
	//Sorting the histogram
	struct huffcode temphuff;
	//Sorting w.r.to probability of occurence
	for(i=0;i<nnz;i++)
	{
		for(j=i+1;j<nnz;j++)
	  	{
			if(huffcodes[i].freq < huffcodes[j].freq)
	    		{
				temphuff = huffcodes[i];
				huffcodes[i] = huffcodes[j];
				huffcodes[j] = temphuff;
	    		}
	  	}
	}
	/*
	//Sorting w.r.to pixel values
	for(i=0;i<nnz;i++)
	{
		for(j=i+1;j<nnz;j++)
		{
			if(pix_freq[i].freq==pix_freq[j].freq && pix_freq[i].pix>pix_freq[j].pix)
	  	    	{
				temppix = pix_freq[i];
				pix_freq[i] = pix_freq[j];
				pix_freq[j] = temppix;
		    	}
	    	}
	}*/
	//Displaying sorted Histogram
	for(i=0;i<nnz;i++)
		printf("%d --> %f\n",huffcodes[i].pix,huffcodes[i].freq);
	start = clock();
	//Building Huffman Tree
	float sumprob;
	int sumpix;
	int n=0,k=0,l=0;
	printf("nnz:: %d\n",nnz);
	int nextnode = nnz;
	while(n<nnz-1)
	{
		//Adding the lowest two probabilities
		sumprob = huffcodes[nnz-n-1].freq+huffcodes[nnz-n-2].freq;
		sumpix = huffcodes[nnz-n-1].pix+huffcodes[nnz-n-2].pix;
		i=0;
		//New position of the combined node
		while(sumprob<=huffcodes[i].freq)
			i++;
		//Appending to the Heap Array
		pix_freq[nextnode].pix = sumpix;
		huffman_tree[nextnode].pix = sumpix;
		pix_freq[nextnode].freq = sumprob;
		huffman_tree[nextnode].freq = sumprob;
		pix_freq[nextnode].left = &pix_freq[huffcodes[nnz-n-2].arrloc];
		pix_freq[nextnode].right = &pix_freq[huffcodes[nnz-n-1].arrloc];
		huffman_tree[nextnode].larrloc = huffcodes[nnz-n-2].arrloc;
		huffman_tree[nextnode].rarrloc = huffcodes[nnz-n-1].arrloc;
		pix_freq[nextnode].code[0] = '\0';
		huffman_tree[nextnode].code[0]='\0';
		//Sorting the new array		
		for(k=nnz;k>=0;k--)
		{
			if(k==i)
			{
				huffcodes[k].pix=sumpix;
				huffcodes[k].freq=sumprob;
				huffcodes[k].arrloc = nextnode;
			}
			else if(k>i)
			{
				huffcodes[k] = huffcodes[k-1];
			}
		}
		n+=1;
		nextnode+=1;
	}
	end = clock();
	printf("Time taken for Building Huffman code:: %f seconds\n\n",((double)(end-start))/CLOCKS_PER_SEC);
	start = clock();
	//Assigning Code through backtracking
	printf("Assigning Code through backtracking...\n\n");
	char left = '0';
	char right = '1';
	int index;
	for(i=totalnnz-1;i>=nnz;i--)
	{
		if(pix_freq[i].left!=NULL)
		{
			strconcat(pix_freq[i].left->code,pix_freq[i].code,left);
			strconcat(huffman_tree[huffman_tree[i].larrloc].code,huffman_tree[i].code,left);
		}
		if(pix_freq[i].right!=NULL) 
		{
			strconcat(pix_freq[i].right->code,pix_freq[i].code,right);
			strconcat(huffman_tree[huffman_tree[i].rarrloc].code,huffman_tree[i].code,right);
		}
	}
	//naming the last node as ROOT
	strconcat(pix_freq[totalnnz-1].code,"root",'2');
	end = clock();
	printf("Time taken for assigning Huffman code:: %f seconds\n\n",((double)(end-start))/CLOCKS_PER_SEC);
	//Printing Huffman Codes
	printf("Huffmann Codes::\n\n");
	printf("pixel values -> Code\n\n");
	for(i=0;i<nnz;i++)
	{
		if(snprintf(NULL,0,"%d",pix_freq[i].pix)==2)
			printf("     %d      -> %s\n",pix_freq[i].pix,pix_freq[i].code);
		else
			printf("    %d      -> %s\n",pix_freq[i].pix,pix_freq[i].code);
	}
	//Write to text file
	FILE *huffman = fopen("huffmancode88.txt","wb");
	fprintf(huffman,"Huffmann Codes::\n\n");
	fprintf(huffman,"pixel values -> Code\n\n");
	for(i=0;i<nnz;i++)
	{
		if(snprintf(NULL,0,"%d",pix_freq[i].pix)==2)
			fprintf(huffman,"     %d      -> %s\n",pix_freq[i].pix,pix_freq[i].code);
		else
			fprintf(huffman,"    %d      -> %s\n",pix_freq[i].pix,pix_freq[i].code);
	}
	fclose(huffman);

	//Calculating Average Bit Length
	float avgbitnum = 0;
	for(i=0;i<nnz;i++)
		avgbitnum+=pix_freq[i].freq*codelen(pix_freq[i].code);
	printf("\nAverage Number of Bits = %f\n\n",avgbitnum);

	//Writing the Huffman Tree to a File
	printf("Writing to Huffman Tree to a .dat file for simulating Transmission...\n\n");
	FILE *treefile = fopen("hufftree.dat","wb");
	int tree_size = sizeof(struct tree);
	for(i=0;i<totalnnz;i++)
		fwrite(&huffman_tree[i],tree_size,1,treefile);
	fclose(treefile);
	//Encode the Image
	int pix_val;
	printf("Writing the Huffman encoded Image for simulating Transmission...\n\n");
	FILE *imagehuff = fopen("encoded_image.txt","wb");
	for(r=0;r<height;r++)
		for(c=0;c<width;c++)
		{
			pix_val = image[r][c];
			for(i=0;i<nnz;i++)
				if(pix_val == pix_freq[i].pix)
					fprintf(imagehuff,"%s",pix_freq[i].code);
		}
	fclose(imagehuff);
	//Write Information of the Image
	printf("Writing Image information to file...\n\n");
	FILE *image_info = fopen("image_info.dat","wb");
	fwrite(&nnz,4,1,image_info);
	fwrite(&height,4,1,image_info);
	fwrite(&width,4,1,image_info);
	fclose(image_info);
	//Creating Graphical Tree
	printf("Creating DOT file for Huffman Tree visualization...\n\n");
	FILE *fp = fopen("huffman88.dot","wb");
	fprintf(fp,"digraph G {\n rotate = 180;\n ration=\"fill\";\n size = \"8.3,11.7!\";\n minlen=1.5;\n rankdir = LR;\n");
	k=0;
	for(i=totalnnz-1;i>=nnz;i--)
	{
		if(pix_freq[i].left!=NULL)
		{
			fprintf(fp,"%s[color=green,fontcolor=red,labelfontsize=35];\n",pix_freq[i].code);
			fprintf(fp,"%s -> %s [label=%f,color=green, fontcolor=red,labelfontsize=25];\n",pix_freq[i].code,pix_freq[i].left->code,pix_freq[i].left->freq);
		}
		if(pix_freq[i].right!=NULL)
		{
			fprintf(fp,"%s -> %s [label=%f,color=green, fontcolor=red,labelfontsize=35];\n",pix_freq[i].code,pix_freq[i].right->code,pix_freq[i].right->freq);
		}
	}
	for(i=0;i<nnz;i++)
	{
		fprintf(fp,"%s [label = <%d<BR/>%s>,color=green,fontcolor=red,labelfontsize=35];\n",pix_freq[i].code,pix_freq[i].pix,pix_freq[i].code);
	}
	fprintf(fp,"{rank = same; ");
	for(i=0;i<nnz;i++)
		fprintf(fp,"%s; ",pix_freq[i].code);
	fprintf(fp,"}\n");
	fprintf(fp,"}\n");
	fclose(fp);
	printf("DOT File created...\n\nSaving to Image and PDF Files...\n\n");
	//Execute LINUX terminal command to generate png image from dot file
	printf("Saving the dot file as png file...\n\n");
	char commandpng[]="dot huffman88.dot -Tpng -o huffman88.png";
	system(commandpng);
	printf("Saving the dot file as pdf file...\n\n");
	char commandpdf[] = "dot huffman88.dot -Tpdf -o huffman88.pdf";
	system(commandpdf);
	printf("Save Complete...\n\n");

	FILE *encoded_image = fopen("encoded_image.txt","rb");
	int **huffimage;
	char bit;
	huffimage = (int **)malloc(height*sizeof(int *));
	for(i=0;i<height;i++)
	{
		huffimage[i] = (int *)malloc(width*sizeof(int));
	}
	for(i=0;i<totalnnz;i++)
		printf("%d -> %s\n",pix_freq[i].pix,pix_freq[i].code);
	struct pixfreq currnode;
	currnode = pix_freq[totalnnz-1];
	printf("Decoding....\n\n");
	for(r=0;r<height;r++)
		for(c=0;c<width;c++)
		{
			currnode = pix_freq[totalnnz-1];
			while(currnode.left!=NULL && currnode.right!=NULL)
			{
				fscanf(encoded_image,"%c",&bit);
				if(bit==left)
					currnode = *currnode.left;
				else
					currnode = *currnode.right;
				//printf("%d ",currnode.pix);
			}
			//printf("\n");
			if(currnode.left==NULL && currnode.right==NULL)
				huffimage[r][c] = currnode.pix;
		}
	printf("Decoding complete....\n\n");
	fclose(encoded_image);
	FILE *decImage = fopen("decoded_Image.txt","wb");
	for(r=0;r<height;r++){
		for(c=0;c<width;c++)
			fprintf(decImage,"%d ",huffimage[r][c]);
		fprintf(decImage,"\n");}
	fclose(decImage);
	return 0;
}