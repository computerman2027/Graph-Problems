#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef enum
{
    WHITE,
    GRAY,
    BLACK
} Color;

typedef struct Vertex
{
    int id;
    Color color;
    int d;             // discovery time
    int f;             // finish time
    struct Vertex *pi; // predecessor
} Vertex;

typedef struct Graph
{
    int V;
    Vertex *vertices;
    int **adj;
} Graph;

int dfs_time = 0; 

Graph *createGraph(int V)
{
    Graph *G = (Graph *)malloc(sizeof(Graph));
    G->V = V;
    G->vertices = (Vertex *)malloc(V * sizeof(Vertex));
    G->adj = (int **)malloc(V * sizeof(int *));
    for (int i = 0; i < V; i++)
    {
        G->vertices[i].id = i;
        G->adj[i] = (int *)calloc(V, sizeof(int));
    }
    return G;
}

void DFS_Visit(Graph *G, Vertex *u)
{
    printf("%d ", u->id);
    int v;
    dfs_time++;
    u->d = dfs_time;
    u->color = GRAY;
    for (v = 0; v < G->V; v++)
    {
        if (G->adj[u->id][v] && G->vertices[v].color == WHITE)
        {
            G->vertices[v].pi = u;
            DFS_Visit(G, &G->vertices[v]);
        }
    }
    u->color = BLACK;
    dfs_time++;
    u->f = dfs_time;
}

void DFS(Graph *G)
{
    for (int i = 0; i < G->V; i++)
    {
        G->vertices[i].color = WHITE;
        G->vertices[i].pi = NULL;
    }
    dfs_time = 0;
    for (int i = 0; i < G->V; i++)
    {
        if (G->vertices[i].color == WHITE)
        {
            DFS_Visit(G, &G->vertices[i]);
        }
    }
}

void freeGraph(Graph *G)
{
    for (int i = 0; i < G->V; i++)
    {
        free(G->adj[i]);
    }
    free(G->adj);
    free(G->vertices);
    free(G);
}

int main()
{
    int v, i, j;
    printf("Enter number of vertices: ");
    scanf("%d", &v);
    Graph *G = createGraph(v);

    printf("Enter Adjacency Matrix:\n");
    for (i = 0; i < v; i++)
    {
        for (j = 0; j < v; j++)
        {
            scanf("%d", &G->adj[i][j]);
        }
    }

    clock_t start = clock();
    DFS(G);
    clock_t end = clock();

    double timetaken = ((double)(end - start)) / CLOCKS_PER_SEC;

    printf("\nDFS Discovery and Finish Times:\n");
    for (i = 0; i < v; i++)
    {
        printf("Vertex %d: d = %d, f = %d\n", i, G->vertices[i].d, G->vertices[i].f);
    }

    printf("Time taken = %lf seconds\n", timetaken);

    freeGraph(G);
    return 0;
}
