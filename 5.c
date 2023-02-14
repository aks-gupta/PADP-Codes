#include <stdio.h>
#include <string.h>
#include <mpi.h>
#define BUFSIZE 32
char m[4][20]={"\nHello","\nRVCE","\nCSE","\n7th Sem"};
int main(int argc,char **argv)
{
	char mess[32];
	int root=0;
	int tag =0;
	int rank,size;
	int temp=1;
	MPI_Init(&argc,&argv);
	MPI_Status status;
	MPI_Comm_rank(MPI_COMM_WORLD,&rank);
	MPI_Comm_size(MPI_COMM_WORLD,&size);
	if(rank==0)
	{
		for(temp=1;temp<size;temp++)
		{
			strcpy(mess,m[temp-1]);
			MPI_Send(&mess,BUFSIZE,MPI_CHAR,temp,tag,MPI_COMM_WORLD);
		}	
	}
	else
	{
		MPI_Recv(&mess,BUFSIZE,MPI_CHAR,root,tag,MPI_COMM_WORLD,&status);
		printf("%s is message process of rank %d sent to process of rank %d",mess,rank,root);
	}
	printf("\n");	
	MPI_Finalize();
	return 0;
}
