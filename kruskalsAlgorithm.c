#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct edge
{
    int source;
    int destination;
    int weight;
} Edge;

typedef struct subset
{
    int parent;
    int rank;
} Subset;

int compareEdges(const void *a, const void *b)
{
    return (((Edge *)a)->weight) - (((Edge *)b)->weight);
}

int find(Subset subsets[], int i)
{
    if (subsets[i].parent != i)
    {
        subsets[i].parent = find(subsets, subsets[i].parent);
    }
    return subsets[i].parent;
}

void Union(Subset subsets[], int x, int y)
{
    int xroot = find(subsets, x);
    int yroot = find(subsets, y);

    if (subsets[xroot].rank < subsets[yroot].rank)
    {
        subsets[xroot].parent = yroot;
    }
    else if (subsets[xroot].rank > subsets[yroot].rank)
    {
        subsets[yroot].parent = xroot;
    }
    else
    {
        subsets[yroot].parent = xroot;
        subsets[xroot].rank++;
    }
}

void kruskalsMST(Edge edges[], int V, int E)
{
    Edge *result = (Edge *)malloc((V - 1) * sizeof(Edge));

    int e = 0;
    int i = 0;
    int v;

    qsort(edges, E, sizeof(edges[0]), compareEdges);

    Subset *subsets = (Subset *)malloc(V * sizeof(Subset));

    for (v = 0; v < V; v++)
    {
        subsets[v].parent = v;
        subsets[v].rank = 0;
    }

    while (e < V - 1 && i < E)
    {
        Edge nextEdge = edges[i++];
        int x = find(subsets, nextEdge.source);
        int y = find(subsets, nextEdge.destination);

        if (x != y)
        {
            result[e++] = nextEdge;
            Union(subsets, x, y);
        }
    }

    printf("Edges in the MST:\n");
    for (i = 0; i < e; ++i)
        printf("%d -- %d == %d\n", result[i].source, result[i].destination, result[i].weight);

    free(subsets);
}

int main()
{
    int V, E;
    printf("Enter no of Vertices : ");
    scanf("%d", &V);
    printf("Enter no of Edges : ");
    scanf("%d", &E);

    Edge *edges = (Edge *)malloc(E * sizeof(Edge));
    int v, e, wt, i;
    for (i = 0; i < E; i++)
    {
        printf("Enter Source : ");
        scanf("%d", &edges[i].source);
        printf("Enter Destination : ");
        scanf("%d", &edges[i].destination);
        printf("Enter Weight : ");
        scanf("%d", &edges[i].weight);
    }

    kruskalsMST(edges, V, E);

    return 0;
}