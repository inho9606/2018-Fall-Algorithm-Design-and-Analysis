#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable:4996)
#include <stdio.h>
#include <stdlib.h>

struct Edge {
	int src, dest, root;
	long long int weight;
};

struct Graph {
	int V, E;
	struct Edge *edge;
};

char input_file[128], output_file[128];

struct Graph* createGraph(int V, int E) {
	struct Graph* graph = (struct Graph*)malloc(sizeof(struct Graph));
	graph->V = V;
	graph->E = E;
	graph->edge = (struct Edge*)malloc((graph->E) * sizeof(struct Edge));
	return graph;
}

struct subset {
	int parent;
	int rank;
};

int find(struct subset subsets[], int i) {
	if (subsets[i].parent != i)
		subsets[i].parent = find(subsets, subsets[i].parent);

	return subsets[i].parent;
}

void Union(struct subset subsets[], int x, int y) {
	int xroot = find(subsets, x);
	int yroot = find(subsets, y);

	if (subsets[xroot].rank < subsets[yroot].rank)
		subsets[xroot].parent = yroot;
	else if (subsets[xroot].rank > subsets[yroot].rank)
		subsets[yroot].parent = xroot;
	else {
		subsets[yroot].parent = xroot;
		subsets[xroot].rank++;
	}
}

int comparing(const void* a, const void* b) {
	struct Edge *a1 = (struct Edge*)a;
	struct Edge *b1 = (struct Edge*)b;
	return a1->weight - b1->weight;
}

int comparing2(const void* a, const void* b) {
	struct Edge *a1 = (struct Edge*)a;
	struct Edge *b1 = (struct Edge*)b;
	return a1->root - b1->root;
}

void MST(struct Graph* graph) {
	int V = graph->V;
	int E = graph->E;
	struct Edge *result;
	result = (struct Edge*)malloc((V - 1) * sizeof(struct Edge));

	int e = 0, i = 0, n = 0;
	qsort(graph->edge, graph->E, sizeof(graph->edge[0]), comparing);

	struct subset *subsets = (struct subset*)malloc(V * sizeof(struct subset));

	for (int v = 0; v < V; v++) {
		subsets[v].parent = v;
		subsets[v].rank = 0;
	}

	for (e = 0; e < E; e++) {
		struct Edge next_edge = graph->edge[i++];

		int x = find(subsets, next_edge.src);
		int y = find(subsets, next_edge.dest);

		if (x != y) {
			Union(subsets, x, y);
			result[n++] = next_edge;
		}
	}

	for (int i = 0; i < n; i++) result[i].root = find(subsets, result[i].src);
	qsort(result, n, sizeof(result[0]), comparing2);

	int cnum = 1, vnum = 0, isolated = 0;
	long long int weight = 0;
	for (int i = 0; i < n - 1; i++) {
		if (result[i].root != result[i + 1].root) cnum++;
	}

	for (int i = 0; i < V; i++) {
		if (subsets[i].parent == i && subsets[i].rank == 0) isolated++;
	}

	FILE *fp = fopen(output_file, "w");

	cnum += isolated;
	fprintf(fp, "%d\n", cnum);
	for (i = 0; i < n; i++) {
		if (i > 0 && result[i].root != result[i - 1].root) {
			fprintf(fp, "%d %lld\n", vnum + 1, weight);
			vnum = 0;
			weight = 0;
		}
		vnum++;
		weight += result[i].weight;
	}
	fprintf(fp, "%d %lld\n", vnum + 1, weight);

	for (i = 0; i < isolated; i++) fprintf(fp, "1 0\n");
	fclose(fp);
}

int main(void) {
	FILE *fp;
	fp = fopen("commands.txt", "r");
	int V, E, max;
	long long int m;

	fscanf(fp, "%s", input_file);
	fscanf(fp, "%s", output_file);
	fclose(fp);
	fp = fopen(input_file, "r");
	fscanf(fp, "%d %d %d", &V, &E, &max);
	struct Graph* graph = createGraph(V, E);

	for (int i = 0; i < E; i++) {
		fscanf(fp, "%d %d %d", &(graph->edge[i].src), &(graph->edge[i].dest), &(graph->edge[i].weight));
	}
	fclose(fp);

	MST(graph);
	return 0;
}