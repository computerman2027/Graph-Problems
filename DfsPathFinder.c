#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define WHITE 0
#define GRAY 1
#define BLACK 2
#define NIL -1

typedef struct
{
    int **adjmat;
    int *color;
    int *d;
    int *pi;
    int *f;
    int noOfVertex;
    int time;
} Graph;

void dfsVisit(Graph *G, int u)
{
    G->time++;
    G->d[u] = G->time;
    G->color[u] = GRAY;

    int v;
    for (v = 0; v < G->noOfVertex; v++)
    {
        if (G->adjmat[u][v] == 1 && G->color[v] == WHITE)
        {
            G->pi[v] = u;
            dfsVisit(G, v);
        }
    }

    G->color[u] = BLACK;
    G->time++;
    G->f[u] = G->time;
}

void dfs(Graph *G)
{
    int u;
    for (u = 0; u < G->noOfVertex; u++)
    {
        G->color[u] = WHITE;
        G->pi[u] = NIL;
    }
    G->time = 0;
    for (u = 0; u < G->noOfVertex; u++)
    {
        if (G->color[u] == WHITE)
        {
            dfsVisit(G, u);
        }
    }
}

void printpath(Graph *G, int s, int v)
{
    if (v == s)
    {
        printf("%d ", s);
    }
    else if (G->pi[v] == NIL)
    {
        printf("No path from %d to %d exits\n", s, v);
    }
    else
    {
        printpath(G, s, G->pi[v]);
        printf("%d ", v);
    }
}

int main()
{
    Graph G;
    int i, j, start, end;

    printf("Enter number of vertices: ");
    scanf("%d", &G.noOfVertex);

    G.adjmat = (int **)malloc(G.noOfVertex * sizeof(int *));
    G.color = (int *)malloc(G.noOfVertex * sizeof(int));
    G.d = (int *)malloc(G.noOfVertex * sizeof(int));
    G.f = (int *)malloc(G.noOfVertex * sizeof(int));
    G.pi = (int *)malloc(G.noOfVertex * sizeof(int));

    for (i = 0; i < G.noOfVertex; i++)
    {
        G.adjmat[i] = (int *)malloc(G.noOfVertex * sizeof(int));
    }

    printf("Enter adjacency matrix:\n");
    for (i = 0; i < G.noOfVertex; i++)
    {
        for (j = 0; j < G.noOfVertex; j++)
        {
            scanf("%d", &G.adjmat[i][j]);
        }
    }

    dfs(&G);

    printf("Enter the starting node for dFS: ");
    scanf("%d", &start);

    printf("Enter the destination node to find shortest path: ");
    scanf("%d", &end);

    printf("Path from %d to %d: ", start, end);
    printpath(&G, start, end);
    printf("\n");

    return 0;
}