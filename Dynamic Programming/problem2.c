#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#pragma warning(disable:4996)
#define INPUT_FILE_NAME "input.txt"

int check_mixed_card(int * a, int * b, int m, int n) {
	int i, j,max;
	int ** S = (int**)malloc(sizeof(int)*m);
	for (i = 0; i < m; i++)
		S[i] = (int*)malloc(sizeof(int)*n);
	for (i = 0; i < m; i++) {
		for (j = 0; j < n; j++) {
			if (a[i] == b[j]) {
				if (i == 0 || j == 0) max = 1;
				else max = S[i - 1][j - 1] + 1;
			}
			else {
				if (i == 0 && j == 0) max = 0;
				else if (i == 0) max = S[i][j - 1];
				else if (j == 0) max = S[i - 1][j];
				else {
					if (S[i - 1][j] >= S[i][j - 1]) max = S[i - 1][j];
					else max = S[i][j - 1];
				}
			}
			S[i][j] = max;
		}
	}
			return S[m-1][n-1];
	free(S);
}

void main() {
	int i, j, lengtha, lengthb, lengthc, lengthd;
	FILE * fp = fopen(INPUT_FILE_NAME, "r");
	fscanf(fp, "%d", &lengtha);
	int * a = (int*)malloc(sizeof(int)*lengtha);
	for (i = 0; i < lengtha; i++) {
		fscanf(fp, "%d", &a[i]);
		if (a[i] < 1 || a[i] > 1000) {
			printf("카드의 숫자는 1부터 1000 사이의 숫자이어야 합니다. 프로그램을 종료합니다.");
			return;
		}
	}
	fscanf(fp, "%d", &lengthb);
	int * b = (int*)malloc(sizeof(int)*lengthb);
	for (i = 0; i < lengthb; i++) {
		fscanf(fp, "%d", &b[i]);
		if (b[i] < 1 || b[i] > 1000) {
			printf("카드의 숫자는 1부터 1000 사이의 숫자이어야 합니다. 프로그램을 종료합니다.");
			return;
		}
	}
	if (lengtha < 1 || lengtha > 1000 || lengthb < 1 || lengthb > 1000) {
		printf("카드의 개수는 각 손에 1장에서 1000장 사이로 들고 있어야 합니다. 프로그램을 종료합니다.");
		return;
	}
	fscanf(fp, "%d", &lengthc);
	int * c = (int*)malloc(sizeof(int)*lengthc);
	for (i = 0; i < lengthc; i++) fscanf(fp, "%d", &c[i]);
	fscanf(fp, "%d", &lengthd);
	int * d = (int*)malloc(sizeof(int)*lengthd);
	for (i = 0; i < lengthd; i++) fscanf(fp, "%d", &d[i]);
	fclose(fp);
	fp = fopen("output.txt", "w");
	if (check_mixed_card(a, c, lengtha, lengthc) == lengtha && check_mixed_card(b, c, lengthb, lengthc) == lengthb) fprintf(fp, "%d", 1);
	else fprintf(fp, "%d", 0);
	if (check_mixed_card(a, d, lengtha, lengthd) == lengtha && check_mixed_card(b, d, lengthb, lengthd) == lengthb) fprintf(fp, "%d", 1);
	else fprintf(fp, "%d", 0);
	fclose(fp);
	free(a);
	free(b);
	free(c);
	free(d);
}