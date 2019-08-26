#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include <cstdlib>
#include <Windows.h>
#pragma warning(disable:4996)
#define INPUT_FILE_NAME "input_array_1026.bin"
#define CHECK_TIME_START QueryPerformanceFrequency((_LARGE_INTEGER*) &freq); QueryPerformanceCounter((_LARGE_INTEGER*)&start);
#define CHECK_TIME_END(a) QueryPerformanceCounter((_LARGE_INTEGER*)&end); a = (float)((float) (end - start)/freq);
__int64 start, freq, end;
float resultTime;
int swap_temp;

void swap(int *x, int *y)
{
	int temp;
	temp = *x;
	*x = *y;
	*y = temp;
}
int Validation(int* data, int left, int right) {
	for (int i = left; i < right - 1; i++) {
		if (data[i] > data[i + 1]) return -1;
	}
	return 1;
}

void Quick_Sort_P(int *data, int left, int right)
{
	if (left >= right) return;	int pivot = data[left];
	if (right - left >= 4)
	{
	int i = left + 1;
	int j = right;
	while (1)
	{
		for (i = left + 1; data[i] <= pivot; i++);
		for (j = right; data[j] > pivot; j--);
		if (i > j) break;
		swap(&data[i], &data[j]);
	}
	swap(&data[left], &data[j]);
	Quick_Sort_P(data, left, j - 1);
	Quick_Sort_P(data, j + 1, right);
}
	else // 직접비교
	{
		int i, j, temp;
		for (i = left; i <= right - 1; i++)
		{
			temp = i;
			for (j = i + 1; j <= right; j++)
				if (data[temp] > data[j]) temp = j;
			swap(&data[i], &data[temp]);
		}
	}
}

void main()
{
	FILE * f;
	int i, n;
	f = fopen(INPUT_FILE_NAME, "rb");
	fread(&n, sizeof(int), 1, f);
	printf("[%d] size of data sort\n", n);
	int* data = (int*)malloc(sizeof(int)*n);
	for (i = 0; i < n; i++)
		fread(&data[i], sizeof(int), 1, f);
	fclose(f);
	CHECK_TIME_START;
	Quick_Sort_P(data, 0, n);
	CHECK_TIME_END(resultTime);
	printf("Total Time is [ %f (ms)]\n", resultTime*1000.0f);
	if (Validation(data, 0, n) == 1)
		printf("Well Done\n");
	else printf("Try Again!");
	//for (i = 0; i < n; i++)
		   //printf("%d\n", data[i]);
	free(data);
}