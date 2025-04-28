#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define INF INT_MAX // A value to represent infinity

// Function to print the solution matrix
void printSolution(int **dist, int V)
{
    printf("\nShortest distances between every pair of vertices:\n");
    for (int i = 0; i < V; i++)
    {
        for (int j = 0; j < V; j++)
        {
            if (dist[i][j] == INF)
                printf("%7s\t", "INF");
            else
                printf("%7d\t", dist[i][j]);
        }
        printf("\n");
    }
}

// Function to implement Floyd-Warshall algorithm
void floydWarshall(int **graph, int V)
{
    int **dist;

    // Dynamic allocation of dist matrix
    dist = (int **)malloc(V * sizeof(int *));
    for (int i = 0; i < V; i++)
        dist[i] = (int *)malloc(V * sizeof(int));

    // Initialize dist matrix
    for (int i = 0; i < V; i++)
        for (int j = 0; j < V; j++)
            dist[i][j] = graph[i][j];

    // Floyd-Warshall algorithm
    for (int k = 0; k < V; k++)
    {
        for (int i = 0; i < V; i++)
        {
            for (int j = 0; j < V; j++)
            {
                if (dist[i][k] != INF && dist[k][j] != INF)
                {
                    if (dist[i][k] + dist[k][j] < dist[i][j])
                        dist[i][j] = dist[i][k] + dist[k][j];
                }
            }
        }
    }

    // Print the final shortest distance matrix
    printSolution(dist, V);

    // Free dynamically allocated memory
    for (int i = 0; i < V; i++)
        free(dist[i]);
    free(dist);
}

int main()
{
    int V;
    printf("Enter the number of vertices: ");
    scanf("%d", &V);

    // Dynamic allocation of graph matrix
    int **graph = (int **)malloc(V * sizeof(int *));
    for (int i = 0; i < V; i++)
        graph[i] = (int *)malloc(V * sizeof(int));

    printf("Enter the adjacency matrix (use %d for INF):\n", INF);
    for (int i = 0; i < V; i++)
    {
        for (int j = 0; j < V; j++)
        {
            scanf("%d", &graph[i][j]);
            if (graph[i][j] == 0 && i != j)
            {
                graph[i][j] = INF;
            }
        }
    }

    floydWarshall(graph, V);

    // Free dynamically allocated memory
    for (int i = 0; i < V; i++)
        free(graph[i]);
    free(graph);

    return 0;
}
