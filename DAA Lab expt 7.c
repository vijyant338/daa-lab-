//NAME : VIJYANT
//ROLL NO. : 25/DA/063
#include<stdio.h>

//Activity selection problem
void swap(int* a, int* b)
{
	int temp=*a;
	*a=*b;
	*b=temp;
}

int partition(int start[], int finish[], int low, int high)
{
	int pivot=finish[low];
	int i=low+1;
	int j=high;
	while(i<=j)
	{
		while(i<=high && finish[i]<=pivot)
		{
			i++;
		}
		while(j>low && finish[j]>pivot)
		{
			j--;
		}
		if(i<j)
		{
			swap(&finish[i],&finish[j]);
			swap(&start[i],&start[j]);
			i++;
			j--;
		}
	}
	swap(&finish[j],&finish[low]);
	swap(&start[j],&start[low]);
	return j;
}

void quicksort(int start[], int finish[], int low, int high)
{
	if(low<high)
	{
		int index=partition(start,finish,low,high);
		quicksort(start,finish,low,index-1);
		quicksort(start,finish,index+1,high);
	}
}
int activitySelection(int start[], int finish[], int n)
{
	quicksort(start,finish,0,n-1);
	int ans=0;
	int end=finish[0];
	ans+=1;
	for(int i=1; i<n; i++)
	{
		if(start[i]>=end)
		{
			ans++;
			end=finish[i];
		}
		else
		{
			continue;
		}
	}
	return ans;
}

int main()
{
	int n = 6;
	int start[]  = {1, 3, 0, 5, 3, 5};
	int finish[] = {2, 4, 6, 7, 5, 9};
	
	printf("=== Activity Selection Problem ===\n");
	printf("Total activities provided: %d\n", n);
	printf("Maximum number of activities that can be performed: %d\n", activitySelection(start, finish, n));
	printf("==================================\n");
	
	return 0;
}