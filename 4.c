#include <stdio.h>
#include <error.h>
#include<omp.h>
#include <gd.h>
#include<string.h>
int main(int argc, char **argv)
{
	FILE *fp,*fp1 = {0};
	gdImagePtr img;
	char *iname = NULL;
	char *oname = NULL;
	int color, x, y, w, h,i=0;
	int red, green, blue,tmp,tid;
	color = x = y = w = h = 0;
	red = green = blue = 0;
	if(argc != 3)
	  error(1, 0, "Usage: ./a.out input.png output.png");
	else
	{
	  iname = argv[1];
	  oname = argv[2];
	}
	if((fp = fopen(iname, "r")) == NULL)
	  error(1, 0, "Error - fopen(): %s", iname);
	else
		//img = gdImageCreateFromJpeg(fp);
		img = gdImageCreateFromPng(fp);
	w = gdImageSX(img);
	h = gdImageSY(img);
	double t = omp_get_wtime();
	printf("%d%d",w,h);
	#pragma omp static parallel for private(y,color,red,green,tmp)
	for(x = 0; x < w; x++){
		for(y = 0; y < h; y++){
			tid=omp_get_thread_num();
			color=gdImageGetPixel(img, x, y);
			red   = gdImageRed(img, color);
			green = gdImageGreen(img, color);
			blue  = gdImageBlue(img, color);
			tmp = (red+green+blue)/ 3;
			red = green = blue = tmp;
			if(tid == 0 || tid == 1 || tid == 2 || tid == 3){
				color = gdImageColorAllocate(img, red, green, blue);
				gdImageSetPixel(img, x, y, color);
			}
	 	}
	}
	 fp1=fopen(oname,"w");
	gdImagePng(img, fp1);
	fclose(fp1);
	       t = omp_get_wtime() - t;
	gdImageDestroy(img);
	printf("Time taken = %g\n",t);
	return 0;
}

