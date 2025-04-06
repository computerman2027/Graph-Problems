#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int **G;
int noOfVertices;
int *visited;
int *stack;
int top = -1;

void push(int val)
{
    stack[++top] = val;
}

void dfs(int v)
{
    visited[v] = 1;
    int i;
    for (i = 0; i < noOfVertices; i++)
    {
        if (G[v][i] && !visited[i])
        {
            dfs(i);
        }
    }
    push(v);
}

void topologicalSort()
{
    int i;

    for (i = 0; i < noOfVertices; i++)
    {
        if (!visited[i])
        {
            dfs(i);
        }
    }

    printf("Topological Sort Order:\n");
    while (top != -1)
    {
        printf("%d ", stack[top--]);
    }
    printf("\n");
}

int main()
{
    int i, j;
    printf("Enter number of vertices : ");
    scanf("%d", &noOfVertices);

    G = (int **)malloc(noOfVertices * sizeof(int *));
    for (i = 0; i < noOfVertices; i++)
    {
        G[i] = (int *)calloc(noOfVertices, sizeof(int));
    }

    printf("Enter the Adjacency Matrix : \n");
    for (i = 0; i < noOfVertices; i++)
    {
        for (j = 0; j < noOfVertices; j++)
        {
            scanf("%d", &G[i][j]);
        }
    }

    visited = (int *)calloc(noOfVertices, sizeof(int));
    stack = (int *)calloc(noOfVertices, sizeof(int));

    topologicalSort();

    return 0;
}