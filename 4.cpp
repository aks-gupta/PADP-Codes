#include <iostream>
#include <math.h>
#include <string.h>
#include <omp.h>
using namespace std;
double t1,t2;
inline long strike(bool *composite,long i,long stride,long limit)
{
	for(;i<=limit;i+=stride)
		composite[i]=true;
	return i;
}
long Friendly(long n)
{
	long m = (long)sqrt((double)n);
	long w,limit,i,count=0;
	bool *composite = new bool[n+1];
	memset(composite,0,n+1);
	long *striker=new long[m];
	long *factor=new long[m];
	long nfactor=0;
	t1=omp_get_wtime();
	for(i=2;i<=m;i++)
	{
		if(!composite[i])
		{
			count++;
			striker[nfactor]=strike(composite,2*i,i,m);
			factor[nfactor++]=i;
		}	
	}
	for(w=m+1;w<=n;w+=m)
	{
		limit=min(w+m-1,n);
		for(long k=0;k<nfactor;k++)
			striker[k]=strike(composite,striker[k],factor[k],limit);
		for(i=w;i<=limit;i++)
			if(!composite[i])
				count++;
	}
	t1=omp_get_wtime()-t1;	
	delete[]composite;
	delete[]striker;
	delete[]factor;
	return count;
}
long Parallel(long n)
{
	long m = (long)sqrt((double)n);
	long *factor = new long[m];
	long count=0;
	long nfactor=0;
	t2=omp_get_wtime();
	#pragma omp parallel
	{
		bool *composite=new bool[m+1];
		long *striker=new long[m];
		#pragma omp single
		{
			memset(composite,0,m);
			for(long i=2;i<=m;++i)
				if(!composite[i])
				{
					++count;
					strike(composite,2*i,i,m);
					factor[nfactor++]=i;
				}	
				
		} 
		long base = -1;
		#pragma omp for reduction (+:count) 
		for(long w=m+1;w<=n;w+=m)
		{	
			memset(composite,0,m);
			if(base!=w)
			{
				base=w;
				for(long k=0;k<nfactor;++k)
					striker[k]=(base+factor[k]-1)/factor[k]*factor[k]-base;
			}
			long limit = min(w+m-1,n)-base;
			for(long k=0;k<nfactor;++k)
				striker[k]=strike(composite,striker[k],factor[k],limit)-m;
			for(long i=0;i<=limit;++i)
				if(!composite[i])
					++count;
			base+=m;				
		}
		delete[]composite;
		delete[]striker;	
	}
	t2=omp_get_wtime()-t2;
	delete[]factor;
	return count;
}
int main()
{
	long size,count;
	cout<<endl<<" number of threads : 4\n";
	for(int i=2;i<=8;i++)
	{
		size=pow(10,i);
		count=Friendly(size);
		cout<<endl<<size<<"\t\t"<<t1<<"\t"<<count;
		omp_set_num_threads(4);
		count=Parallel(size);
		cout<<"\t"<<t2<<"\t"<<count;
	}
	/* long count = Parallel(100000000);
    cout << count << " Time : " << t2 <<endl;
	
	long count1 =Friendly(100000000);
	cout << count1<< "Time :" << t1 << endl;*/	

	return 0;
}
