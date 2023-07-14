#include <time.h>
#include <stdlib.h>
#include <stdio.h>

int extraMemoryAllocated;

// implements heap sort
// extraMemoryAllocated counts bytes of memory allocated
void swap(int *a,int *b){
	int tmp=*a;
	*a=*b;
	*b=tmp;
}
void heapSort(int arr[], int n){

}


// implement merge sort
void merge(int pData[], int l, int m, int r){
	int a,b,c;
	int v1=m-l+1;
	int v2=r-m;
	//the temporary arrays
	int *L=(int*)malloc(v1*sizeof(int));
	for (a=0;a<v1;a++){
		L[a]=pData[l+a];}
	int *R=(int*)malloc(v2*sizeof(int));
	for (b=0;b<v2;b++){
		R[b]=pData[m+1+b];}
	a=0;
	b=0;
	c=l;
	while(a<v1&&b<v2){
		if(L[a]<=R[b]){
			pData[c]=L[a];
			a++;
		}else{
			pData[c]=R[b];
			b++;
		}
		c++;
	}
	while (a<v1) {
		pData[c]=L[a];
		a++;
		c++;
	}
	while (b<v2){
		pData[c]=R[b];
		b++;
		c++;
	}
	free(L);
	free(R);
}
// extraMemoryAllocated counts bytes of extra memory allocated
void mergeSort(int pData[], int l, int r){
	if (l<r){
		//get the mid point
		int m=(l+r)/2;
		//sort first and second halves
		mergeSort(pData,l,m);
		mergeSort(pData,m+1,r);
		printf("TEsting l=%d r=%d m=%d. \n",l,r,m);
		merge(pData,l,m,r);
	}
}

// parses input file to an integer array
int parseData(char *inputFileName, int **ppData)
{
	FILE* inFile = fopen(inputFileName,"r");
	int dataSz = 0;
	int i, n, *data;
	*ppData = NULL;
	
	if (inFile)
	{
		fscanf(inFile,"%d\n",&dataSz);
		*ppData = (int *)malloc(sizeof(int) * dataSz);
		// Implement parse data block
		if (*ppData == NULL)
		{
			printf("Cannot allocate memory\n");
			exit(-1);
		}
		for (i=0;i<dataSz;++i)
		{
			fscanf(inFile, "%d ",&n);
			data = *ppData + i;
			*data = n;
		}

		fclose(inFile);
	}
	
	return dataSz;
}

// prints first and last 100 items in the data array
void printArray(int pData[], int dataSz)
{
	int i, sz = dataSz - 100;
	printf("\tData:\n\t");
	for (i=0;i<100;++i)
	{
		printf("%d ",pData[i]);
	}
	printf("\n\t");
	
	for (i=sz;i<dataSz;++i)
	{
		printf("%d ",pData[i]);
	}
	printf("\n\n");
}

int main(void)
{
	clock_t start, end;
	int i;
    double cpu_time_used;
	char* fileNames[] = { "input1.txt", "input2.txt", "input3.txt", "input4.txt" };
	
	for (i=0;i<4;++i)
	{
		int *pDataSrc, *pDataCopy;
		int dataSz = parseData(fileNames[i], &pDataSrc);
		
		if (dataSz <= 0)
			continue;
		
		pDataCopy = (int *)malloc(sizeof(int)*dataSz);
	
		printf("---------------------------\n");
		printf("Dataset Size : %d\n",dataSz);
		printf("---------------------------\n");
		
		printf("Heap Sort:\n");
		memcpy(pDataCopy, pDataSrc, dataSz*sizeof(int));
		extraMemoryAllocated = 0;
		start = clock();
		heapSort(pDataCopy, dataSz);
		end = clock();
		cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
		printf("\truntime\t\t\t: %.1lf\n",cpu_time_used);
		printf("\textra memory allocated\t: %d\n",extraMemoryAllocated);
		printArray(pDataCopy, dataSz);
		
		printf("Merge Sort:\n");
		memcpy(pDataCopy, pDataSrc, dataSz*sizeof(int));
		extraMemoryAllocated = 0;
		start = clock();
		mergeSort(pDataCopy, 0, dataSz - 1);
		end = clock();
		cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
		printf("\truntime\t\t\t: %.1lf\n",cpu_time_used);
		printf("\textra memory allocated\t: %d\n",extraMemoryAllocated);
		printArray(pDataCopy, dataSz);
		
		free(pDataCopy);
		free(pDataSrc);
	}
	
}