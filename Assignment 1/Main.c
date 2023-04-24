#include <stdio.h>
#include <stdlib.h> // in order to use rand()
#include <time.h> // in order to randomize rand()

int Search1(int V[], int m, int x, int* iterations)
{
	int i = 0;
	while (V[i] != 0)
	{
		if (V[i] == x)
		{
			*iterations = i;
			return i;
		}
		i++;
	}
	*iterations = i;
	return -1;
}

int Search2(int V[], int m, int x, int* iterations)
{
	int count = 0;
	int left = 0;
	int right = m - 1;
	while (left <= right)
	{
		int mid = left + (right - left) / 2;
		count++;
		if (V[mid] == x)
		{
			*iterations = count;
			return mid;
		}
		if (V[mid] < x && V[mid] != 0)
			left = mid + 1;
		else // V[mid] > x || V[mid] == 0
			right = mid - 1;
	}
	*iterations = count;
	return -1;
}

int FindLastNatural(int V[], int left, int right, int* iterations)
{
	int count = 0;
	while (left <= right)
	{
		int mid = left + (right - left) / 2;
		count++;
		if (V[mid] != 0 && V[mid + 1] == 0)
		{
			*iterations += count;
			return mid;
		}
		if (V[mid] == 0)
			right = mid - 1;
		else // V[mid] < 0 || V[mid] != 0 && V[mid + 1] != 0
			left = mid + 1;
	}
}

int Search3(int V[], int m, int x, int* iterations)
{
	int count = 0;
	int range_left = 1, range_right = 1;
	int mult = 2;

	while (V[range_right] != 0 && range_right < m)
	{
		count++;
		range_left = range_right; // save the previous location of the right range, which is the left range
		range_right += mult; // increase the right range by a number in the  form of 2^k keeping it O(log n) (k is number of iterations) 
		mult *= 2;
	}
	*iterations = count;

	if (range_right > m - 1)
		range_right = m - 1;

	int last_natural_index = FindLastNatural(V, range_left, range_right, iterations); // finding last natural number using binary search which is O(logn)

	int target_index = Search2(V, last_natural_index, x, &count); // finding x using binary search which is O(logn)
	*iterations += count;

	return target_index;
}

void BubbleSort(int V[], int size)
{
	for (int i = 0; i < size - 1; i++)
	{
		for (int j = 0; j < size - i - 1; j++)
		{
			if (V[j] > V[j + 1])
			{
				int temp = V[j];
				V[j] = V[j + 1];
				V[j + 1] = temp;
			}
		}
	}
}

int main()
{
	// number of iterations in each search
	int iterations_search1 = 0; 
	int iterations_search2 = 0;
	int iterations_search3 = 0;
	// sum of iteration in order to calculate the average
	int sum_search1 = 0;
	int sum_search2 = 0;
	int sum_search3 = 0;
	// sum of n in order to calculate average
	int n_sum = 0;

	srand(time(NULL));

	for (int i = 0; i < 500; i++)
	{
		int arr[1000] = {0};
		int arr_size = sizeof(arr) / sizeof(arr[0]);

		int n = rand() % (300 - 200 + 1) + 200; // making a random n between 200 and 300
		n_sum += n;

		for (int i = 0; i < n; i++)
		{
			arr[i] = rand() + 1; // random number that is not 0
		}
	
		BubbleSort(arr, n);

		int x = rand() + 1; // random number that is not 0

		Search1(arr, arr_size, x, &iterations_search1);
		Search2(arr, arr_size, x, &iterations_search2);
		Search3(arr, arr_size, x, &iterations_search3);
		
		sum_search1 += iterations_search1;
		sum_search2 += iterations_search2;
		sum_search3 += iterations_search3;

	}
	printf("200 <= %d <= 300\n", n_sum / 500);
	printf("Search1: %d\n", sum_search1 / 500); // O(n)
	printf("Search2: %d\n", sum_search2 / 500); // O(log m)
	printf("Search3: %d\n", sum_search3 / 500); // O(log n)
}
