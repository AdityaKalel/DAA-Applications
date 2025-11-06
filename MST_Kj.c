#include <stdio.h>
#include <stdlib.h>

#define V 5 // Number of vertices

// Structure to represent an edge
struct Edge {
    int src, dest, weight;
};

// Structure to represent a graph
struct Graph {
    int V, E;
    struct Edge* edges;
};

// Creates a graph with V vertices and E edges
struct Graph* createGraph(int V, int E) {
    struct Graph* graph = (struct Graph*)malloc(sizeof(struct Graph));
    graph->V = V;
    graph->E = E;
    graph->edges = (struct Edge*)malloc(graph->E * sizeof(struct Edge));
    return graph;
}

// A structure to represent a subset for union-find
struct subset {
    int parent;
    int rank;
};

// Find operation
int find(struct subset subsets[], int i) {
    if (subsets[i].parent != i)
        subsets[i].parent = find(subsets, subsets[i].parent);
    return subsets[i].parent;
}

// Union operation
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

// Compare function for sorting edges
int compareEdges(const void* a, const void* b) {
    struct Edge* a1 = (struct Edge*)a;
    struct Edge* b1 = (struct Edge*)b;
    return a1->weight - b1->weight;
}

void KruskalMST(struct Graph* graph) {
    int V = graph->V;
    struct Edge result[V]; // Stores the resultant MST
    int e = 0;             // Index for result[]
    int i = 0;             // Index for sorted edges

    qsort(graph->edges, graph->E, sizeof(struct Edge), compareEdges);

    struct subset* subsets = (struct subset*)malloc(V * sizeof(struct subset));
    for (int v = 0; v < V; v++) {
        subsets[v].parent = v;
        subsets[v].rank = 0;
    }

    while (e < V - 1 && i < graph->E) {
        struct Edge next_edge = graph->edges[i++];
        int x = find(subsets, next_edge.src);
        int y = find(subsets, next_edge.dest);

        if (x != y) {
            result[e++] = next_edge;
            Union(subsets, x, y);
        }
    }

    printf("Following are the edges in the constructed MST\n");
    for (i = 0; i < e; ++i)
        printf("%d -- %d == %d\n", result[i].src, result[i].dest, result[i].weight);

    free(subsets);
}

int main() {
    int V = 5; // Number of vertices
    int E = 7; // Number of edges (example)
    struct Graph* graph = createGraph(V, E);

    // Add edges (example for a connected graph)
    graph->edges[0].src = 0; graph->edges[0].dest = 1; graph->edges[0].weight = 2;
    graph->edges[1].src = 0; graph->edges[1].dest = 3; graph->edges[1].weight = 6;
    graph->edges[2].src = 1; graph->edges[2].dest = 2; graph->edges[2].weight = 3;
    graph->edges[3].src = 1; graph->edges[3].dest = 4; graph->edges[3].weight = 5;
    graph->edges[4].src = 1; graph->edges[4].dest = 3; graph->edges[4].weight = 8;
    graph->edges[5].src = 2; graph->edges[5].dest = 4; graph->edges[5].weight = 7;
    graph->edges[6].src = 3; graph->edges[6].dest = 4; graph->edges[6].weight = 9;

    KruskalMST(graph);
    free(graph->edges);
    free(graph);
    return 0;
}