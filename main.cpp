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

int main(int argc, char** argv)
{
	srand(time(0));

	int arraySize = atoi(argv[1]);
    int array[arraySize];
	fillArray(array, arraySize);

    cout << "Array unsorted:  ";
    for (int i = 0; i < arraySize; ++i)
        cout << array[i] << " ";

    MergeSort(array, 0, arraySize-1);

    cout << endl << "Array sorted:  ";
    for (int i = 0; i < arraySize; ++i)
        cout << array[i] << " ";

    cout << endl;

    return 0;
}
