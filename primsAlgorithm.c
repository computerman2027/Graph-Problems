#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<limits.h>
#include<stdbool.h>

typedef struct AdjListNode{
    int dest;
    int weight;
    struct AdjListNode* next;
}AdjListNode;

typedef struct AdjList{
    AdjListNode* head;
}AdjList;

typedef struct Graph{
    int V;
    AdjList* array;
}Graph;


AdjListNode* newAdjListNode(int dest, int weight) {
    AdjListNode* node = (AdjListNode*) malloc(sizeof(AdjListNode));
    node->dest = dest;
    node->weight = weight;
    node->next = NULL;
    return node;
}

Graph* createGraph(int V)
{
    Graph* graph= (Graph*)malloc(sizeof(Graph));
    graph->V=V;
    graph->array=(AdjList*)malloc(V*sizeof(AdjList));

    int i;
    for(i=0;i<V;i++)
    {
        graph->array[i].head=NULL;
    }
    return graph;
}

void addEdge(Graph* graph, int src, int dest, int weight)
{
    AdjListNode* node = newAdjListNode(dest, weight);
    node->next = graph->array[src].head;
    graph->array[src].head = node;

    // For undirected graph
    node = newAdjListNode(src, weight);
    node->next = graph->array[dest].head;
    graph->array[dest].head = node;
}

int minKey(int key[], bool inMST[], int V) 
{
    int min = INT_MAX, min_index = -1;
    for (int v = 0; v < V; v++) 
    {
        printf("inMST[%d] = %d key[%d] = %d min = %d\n",v,inMST[v],v,key[v],min);
        if (!inMST[v] && key[v] < min) 
        {
            min = key[v];
            min_index = v;
        }
    }
    return min_index;
}

void primMST(Graph* graph)
{
    int V =graph->V;
    int* parent = (int*)malloc(V*sizeof(int));
    int* key = (int*)malloc(V*sizeof(int));
    bool* inMST = (bool*)malloc(V*sizeof(int));

    int i;
    for(i=0;i<V;i++)
    {
        key[i]=INT_MAX;
        inMST[i]=false;
    }

    key[0]=0;
    parent[0]=-1;

    int count,u,v;

    for(count=0;count<V-1;count++)
    {
        u=minKey(key, inMST,V);
        printf("u = %d\n",u);
        inMST[u]=true;

        AdjListNode* crawl = graph->array[u].head;

        while(crawl!=NULL)
        {
            v = crawl->dest;
            printf("v = %d\n",v);
            printf("inMST[%d] = %d crawl->weight = %d key[%d] = %d\n",v,inMST[v],crawl->weight,v,key[v]);
            if(!inMST[v] && crawl->weight<key[v])
            {
                key[v]=crawl->weight;
                parent[v]=u;
            }
            crawl=crawl->next;
        }
    }

    printf("Edge \t Weight\n");
    for(i=1;i<V;i++)
    {
        printf("%d - %d \t%d \n",parent[i],i,key[i]);
    }
}

int main()
{
    int V,E;
    printf("Enter number of vertices : ");
    scanf("%d",&V);
    printf("Enter number of edges : ");
    scanf("%d",&E);

    int src,dest,weight,i;
    Graph* graph= createGraph(V);

    for(i=0;i<E;i++)
    {
        printf("Enter src, dest, weight : ");
        scanf("%d %d %d",&src,&dest,&weight);
        addEdge(graph,src,dest,weight);
    }

    primMST(graph);

    return 0;
}