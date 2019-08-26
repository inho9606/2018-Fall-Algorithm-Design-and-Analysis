#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include <cstdlib>
#include <Windows.h>
#pragma warning(disable:4996)
#define FILE_NAME "input_array_1026.bin"
#define CHECK_TIME_START QueryPerformanceFrequency((_LARGE_INTEGER*) &freq); QueryPerformanceCounter((_LARGE_INTEGER*)&start);
#define CHECK_TIME_END(a) QueryPerformanceCounter((_LARGE_INTEGER*)&end); a = (float)((float) (end - start)/freq);
__int64 start, freq, end;
float resultTime;
int swap_temp;

int Validation(int* data, int left, int right) {
	for (int i = left; i < right - 1; i++) {
		if (data[i] > data[i + 1]) return -1;
	}
	return 1;
}

int insertion_sort(int *data, int left, int right)
{
	CHECK_TIME_START;
	int i, j, current;
	for (i = 1; i < right; i++) {
		current = data[i];
		for (j = i; j >= 1 && current < data[j - 1]; j--)
			data[j] = data[j - 1];
		data[j] = current;
	}
		CHECK_TIME_END(resultTime);
		return Validation(data, left, right);
	}

	void main()
	{
		FILE * f;
		int i, n;
		f = fopen(FILE_NAME, "rb");
		fread(&n, sizeof(int), 1, f);
		printf("[%d] size of data sort\n", n);
		int* data = (int*)malloc(sizeof(int)*n);
		for (i = 0; i < n; i++)
			fread(&data[i], sizeof(int), 1, f);
		fclose(f);
		if (insertion_sort(data, 0, n) == 1)
			printf("Well Done\n");
		else printf("Try Again!");
		// for (i = 0; i < n; i++)
			// printf("%d\n", data[i]);
		free(data);
		printf("Total Time is [ %f (ms)]\n", resultTime*1000.0f);
	}