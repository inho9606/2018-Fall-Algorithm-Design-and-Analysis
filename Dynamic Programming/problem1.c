#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#pragma warning(disable:4996)
#define INPUT_FILE_NAME "input.txt"

void gap_info(FILE * fp, int ** table, int m, int n) {
	int xgapcount = 0, ygapcount = 0, i, j, k=0, l=0;
	for (i = m-1, j = n-1; i >= 0 && j >= 0; ) {
		if (table[i][j] == 0) {
			i--;
			j--;
		}
		else if (table[i][j] == 1) {
			ygapcount++;
			i--;
		}
		else {
			xgapcount++;
			j--;
		}
	}
	fprintf(fp, "%d\n", m + xgapcount);
	int * xgap = (int*)malloc(sizeof(int)*xgapcount);
	int * ygap = (int*)malloc(sizeof(int)*ygapcount);
		for (i = m-1, j = n-1; i >= 0 && j >= 0;) {
			if (table[i][j] == 0) {
				i--;
				j--;
			}
			else if (table[i][j] == 1) {
				ygap[l] = i;
				i--;
				l++;
			}
			else {
				xgap[k] = j;
				j--;
				k++;
			}
}
		fprintf(fp, "%d\n", xgapcount);
		for (i = xgapcount-1; xgapcount >= 1 && i >= 0; i--) fprintf(fp, "%d\n", xgap[i]);
		fprintf(fp, "%d\n", ygapcount);
		for (i = ygapcount - 1; ygapcount >= 1 && i >= 0; i--) fprintf(fp, "%d\n", ygap[i]);
		free(xgap);
		free(ygap);

}

void main() {
	int m, n, s, f, p, i, j, max;
	char filename[30];
	FILE * fp = fopen(INPUT_FILE_NAME, "r");
	if (fp != NULL)
	{
		fscanf(fp, "%s", filename);
		fscanf(fp, "%d %d %d", &s, &f, &p);
		fclose(fp);
		fp = fopen(filename, "rb");
		fread(&m, sizeof(int), 1, fp);
		fread(&n, sizeof(int), 1, fp);
		char * x = (char*)malloc(sizeof(char)*(m+1));
		fread(x, sizeof(char), m, fp);
		x[m] = '\0';
		char * y = (char*)malloc(sizeof(char)*(n+1));
		fread(y, sizeof(char), n, fp);
		y[n] = '\0';
		fclose(fp);
		int **record = (int**)malloc(sizeof(int)*m);
		for (i = 0; i < m; i++)
			record[i] = (int*)malloc(sizeof(int)*n);
		int **S = (int**)malloc(sizeof(int*)*(m+1));
		for (i = 0; i <= m; i++)
			S[i] = (int*)malloc(sizeof(int)*(n+1));
		for (i = 0; i <= m; i++) {
			for (j = 0; j <= n; j++) {
				if (i == 0) S[i][j] = -p*j;
				else if (j == 0) S[i][j] = -p * i;
				else {
					if (x[i - 1] == y[j - 1]) max = S[i - 1][j - 1] + s;
					else max = S[i - 1][j - 1] - f;
					if (max < S[i][j - 1] - p) max = S[i][j - 1] - p;
					if (max < S[i - 1][j] - p) max = S[i - 1][j] - p;
					S[i][j] = max;
					if (S[i - 1][j - 1] > S[i][j-1] && S[i-1][j-1] > S[i-1][j]) record[i-1][j-1] = 0;
					else if (S[i - 1][j] > S[i-1][j-1] && S[i-1][j] > S[i][j-1]) record[i-1][j-1] = 1;
					else if (S[i][j-1] > S[i-1][j-1] && S[i][j-1] > S[i-1][j]) record[i-1][j-1] = 2;
					else record[i - 1][j - 1] = 0;
				}
			}
		}
		free(x);
		free(y);
		fp = fopen("output.txt", "w");
		fprintf(fp, "%d\n", S[m][n]);
		gap_info(fp, record, m, n);
		free(record);
		fclose(fp);
	}


}