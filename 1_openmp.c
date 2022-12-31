#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <math.h>
#define SEED 3954556
int main()
{
	double pi,x,y,z;
	long i,niter,count=0;
	int j,nt;
	niter=pow(10,7);
	printf("\ninput: %ld",niter);
	double t;
	srand(SEED);
	for(j=1;j<16;j*=2)
	{
		count =0;
		t=omp_get_wtime();
		omp_set_num_threads(j);
		#pragma omp parallel for private(x,y,z) reduction(+:count)
		for(i=0;i<niter;i++)
		{
			
			x=(double)rand()/RAND_MAX;
			y=(double)rand()/RAND_MAX;
			z=x*x+y*y;
			if(z<=1)
				count++;
		}
		t=omp_get_wtime()-t;
		pi=(double)count/niter *4;
		printf("\nTime : %lf threads : %d pi: %lf",t,j,pi);	
	}	
	return 0;
}
