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

// recursive partition for select-kth 3
int partitionR(int* a, const int& low, const int& high, const int& k)
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

	if (k < (i+1))
		return partitionR(a, low, i, k);
	else if (k > (i+1))
		return partitionR(a, i + 2, high, k);
	else
		return (i+1);
}

int selectKth1(int* a, const int& size, const int& k)
{
	MergeSort(a, 0, size-1);
	return a[k];
}

int selectKth2(int* a, const int& size, const int& k)
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

int selectKth3(int* a, int size, const int& k)
{
	return a[partitionR(a, 0, size-1, k)];
}

// median of medians
int selectKth4(int *v, const int& n, const int& k) {
    if (n == 1 && k == 0) return v[0];

    int m = (n + 4) / 5;
    int *medians = new int[m];
    for (int i = 0; i < m; ++i)
	{
        if (5*i + 4 < n)
		{
            int *w = v + 5*i;
            for (int j0 = 0; j0 < 3; ++j0)
			{
                int jmin = j0;
                for (int j = j0 + 1; j < 5; ++j)
                    if (w[j] < w[jmin]) jmin = j;

				swap(w[j0], w[jmin]);
            }

            medians[i] = w[2];
        }
		else
            medians[i] = v[5*i];
    }

    int pivot = selectKth4(medians, m, m/2);
    delete [] medians;

    for (int i = 0; i < n; ++i)
	{
        if (v[i] == pivot)
		{
            swap(v[i], v[n-1]);
            break;
        }
    }

    int store = 0;
    for (int i = 0; i < n-1; ++i)
	{
        if (v[i] < pivot)
			swap(v[i], v[store++]);
    }

    swap(v[store], v[n-1]);

    if (store == k)
        return pivot;
	else if (store > k)
        return selectKth4(v, store, k);
    else
        return selectKth4(v + store + 1, n - store - 1, k - store - 1);
}

int main(int argc, char** argv)
{
	/*
	argv[1] => size of array
	argv[2] => k, index of item
	argv[3] => algorithm to use
	*/
	// srand(time(0));

	int arraySize = atoi(argv[1]);
    int array[arraySize];

	fillArray(array, arraySize);

	switch (atoi(argv[3]))
	{
		case 1:
		selectKth1(array, arraySize, atoi(argv[2]));
		break;
		case 2:
		selectKth2(array, arraySize, atoi(argv[2]));
		break;
		case 3:
		selectKth3(array, arraySize, atoi(argv[2]));
		break;
		case 4:
		selectKth4(array, arraySize, atoi(argv[2]));
		break;
	}

    return 0;
}
