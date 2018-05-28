#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

// Program "Utilities"
void fillArray(int *a, int size)
{
	for (int i = 0; i < size; ++i)
		a[i] = (rand() % 90) + 10;
}

void printArray(int *a, int size)
{
	for (int i = 0; i < size; ++i)
		cout << a[i] << " ";

	cout << endl;
}

// A function to merge the two half into a sorted data.
void Merge(int *a, int low, int high, int mid)
{
	// We have low to mid and mid+1 to high already sorted.
	int i, j, k, temp[high-low+1];
	i = low;
	k = 0;
	j = mid + 1;

	// Merge the two parts into temp[].
	while (i <= mid && j <= high)
	{
		if (a[i] < a[j])
		{
			temp[k] = a[i];
			++k;
			++i;
		}
		else
		{
			temp[k] = a[j];
			++k;
			++j;
		}
	}

	// Insert all the remaining values from i to mid into temp[].
	while (i <= mid)
	{
		temp[k] = a[i];
		++k;
		++i;
	}

	// Insert all the remaining values from j to high into temp[].
	while (j <= high)
	{
		temp[k] = a[j];
		++k;
		++j;
	}


	// Assign sorted data stored in temp[] to a[].
	for (i = low; i <= high; ++i)
		a[i] = temp[i-low];
}

// A function to split array into two parts.
void MergeSort(int *a, int low, int high)
{
	int mid;
	if (low < high)
	{
		mid=(low+high)/2;
		// Split the data into two half.
		MergeSort(a, low, mid);
		MergeSort(a, mid+1, high);

		// Merge them to get sorted output.
		Merge(a, low, high, mid);
	}
}

// iterative partition for select-kth 2
int partitionI(int* a, const int& low, const int& high)
{
	int i = low - 1;

	for (int j = low; j < high; ++j)
	{
		if (a[j] < a[high])
		{
			++i;
			swap(a[i], a[j]);
		}
	}

	swap(a[i+1], a[high]);
	return (i + 1);
}

int selectKth1(int* a, int size, const int& k)
{
	MergeSort(a, 0, size-1);
	return a[k];
}

int selectKth2(int* a, int size, const int& k)
{
	int low = 0, high = size-1;
	int pivotPosition = partitionI(a, low, high);

	while (k != pivotPosition)
	{
		if (k < pivotPosition)
			high = pivotPosition - 1;
		else if (k > pivotPosition)
			low = pivotPosition + 1;

		pivotPosition = partitionI(a, low, high);
	}

	return a[k];
}

int main(int argc, char** argv)
{
	// srand(time(0));

	int arraySize = atoi(argv[1]);
    int array[arraySize];

	fillArray(array, arraySize);
	printArray(array, arraySize);

	cout << "The kth element is " << selectKth2(array, arraySize, 7) << endl;
    return 0;
}
