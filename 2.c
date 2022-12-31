#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#define SEED 35565
int main()
{
	int nt,r,c,i,k,j,count=0;
	r=c=750;
	double t;
	int **a1=(int**)malloc(r*sizeof(int*));
	for(i=0;i<r;i++)
		a1[i] = (int *)malloc(c*sizeof(int));
	int **a2=(int **)malloc(r*sizeof(int *));
	for(i=0;i<r;i++)
		a2[i]=(int*)malloc(c*sizeof(int));
	int **a3=(int **)malloc(r*sizeof(int *));
	for(i=0;i<r;i++)
		a3[i]=(int*)malloc(c*sizeof(int));
	srand(SEED);
	for(i=0;i<r;i++)
		for(j=0;j<c;j++)
		{
			a1[i][j] = rand()%100+count++;
			a2[i][j] = rand()%100+count++;
		}	
	for(nt=1;nt<16;nt*=2)
	{
		t=omp_get_wtime();
		omp_set_num_threads(nt);
		#pragma omp parallel for private(j,k)
		for(i=0;i<r;i++)
		{
			for(j=0;j<c;j++)
			{
				a3[i][j]=0;
				for(k=0;k<r;k++)
					a3[i][j] += a1[i][k]*a2[k][j];
			}	
		} 
		t=omp_get_wtime()-t;
		printf("\ninput size : %d time=%lf threads=%d",r,t,nt);
	}
	free(a1);
	free(a2);
	free(a3);
	return 0;	
} 
