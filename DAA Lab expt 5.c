//Name : vijyant
//Roll no. : 25/DA/063

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MIN(a, b) ((a) < (b) ? (a) : (b))

// Node structure for Adjacency List
struct AdjListNode {
    int dest;
    struct AdjListNode* next;
};

// Graph structure
struct Graph {
    int V;
    struct AdjListNode** array;
};

// Function to create a new adjacency list node
struct AdjListNode* newAdjListNode(int dest) {
    struct AdjListNode* newNode = (struct AdjListNode*)malloc(sizeof(struct AdjListNode));
    newNode->dest = dest;
    newNode->next = NULL;
    return newNode;
}

// Function to create a graph of V vertices
struct Graph* createGraph(int V) {
    struct Graph* graph = (struct Graph*)malloc(sizeof(struct Graph));
    graph->V = V;
    graph->array = (struct AdjListNode**)malloc(V * sizeof(struct AdjListNode*));
    for (int i = 0; i < V; ++i) {
        graph->array[i] = NULL;
    }
    return graph;
}

// Function to add an edge to an undirected graph
void addEdge(struct Graph* graph, int src, int dest) {
    struct AdjListNode* newNode = newAdjListNode(dest);
    newNode->next = graph->array[src];
    graph->array[src] = newNode;

    newNode = newAdjListNode(src);
    newNode->next = graph->array[dest];
    graph->array[dest] = newNode;
}

// Recursive function to find articulation points using DFS
void DFS_AP(struct Graph* graph, int u, bool visited[], int disc[], int low[], int parent[], bool isAP[], int* time) {
    int children = 0;
    visited[u] = true;
    disc[u] = low[u] = ++(*time);

    struct AdjListNode* pCrawl = graph->array[u];
    while (pCrawl != NULL) {
        int v = pCrawl->dest;

        if (!visited[v]) {
            children++;
            parent[v] = u;
            DFS_AP(graph, v, visited, disc, low, parent, isAP, time);

            // Check if the subtree rooted with v has a connection to one of the ancestors of u
            low[u] = MIN(low[u], low[v]);

            // Case 1: u is root of DFS tree and has two or more children.
            if (parent[u] == -1 && children > 1) {
                isAP[u] = true;
            }

            // Case 2: u is not root and low value of its child is more than or equal to discovery value of u.
            if (parent[u] != -1 && low[v] >= disc[u]) {
                isAP[u] = true;
            }
        } 
        // Update low value of u for parent function calls.
        else if (v != parent[u]) {
            low[u] = MIN(low[u], disc[v]);
        }
        pCrawl = pCrawl->next;
    }
}

// Function to initialize structures and find Articulation Points
void findArticulationPoints(struct Graph* graph) {
    int V = graph->V;
    int* disc = (int*)malloc(V * sizeof(int));
    int* low = (int*)malloc(V * sizeof(int));
    int* parent = (int*)malloc(V * sizeof(int));
    bool* visited = (bool*)malloc(V * sizeof(bool));
    bool* isAP = (bool*)malloc(V * sizeof(bool));

    int time = 0;

    // Initialize arrays
    for (int i = 0; i < V; i++) {
        parent[i] = -1;
        visited[i] = false;
        isAP[i] = false;
    }

    // Call recursive helper function for all unvisited vertices (handles disconnected graphs)
    for (int i = 0; i < V; i++) {
        if (!visited[i]) {
            DFS_AP(graph, i, visited, disc, low, parent, isAP, &time);
        }
    }

    // Print the articulation points
    printf("Articulation Points in the graph: \n");
    bool found = false;
    for (int i = 0; i < V; i++) {
        if (isAP[i]) {
            printf("%d ", i);
            found = true;
        }
    }
    if (!found) {
        printf("None");
    }
    printf("\n");

    // Clean up memory
    free(disc);
    free(low);
    free(parent);
    free(visited);
    free(isAP);
}

int main() {
    // Example Graph setup
    int V = 5;
    struct Graph* graph = createGraph(V);
    
    addEdge(graph, 1, 0);
    addEdge(graph, 0, 2);
    addEdge(graph, 2, 1);
    addEdge(graph, 0, 3);
    addEdge(graph, 3, 4);

    findArticulationPoints(graph);

    return 0;
}
