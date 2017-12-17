#include <stdio.h>
#include <stdlib.h>
#include <cstring>

// A structure to represent an adjacency list node
struct AdjListNode
{
    int dest;
    struct AdjListNode* next;
};

// A structure to represent an adjacency list
struct AdjList
{
    struct AdjListNode *head;// pointer to head node of list
    int isVisited = 0;
    int color = -1;
};

// A structure to represent a graph. A graph is an array of adjacency lists.
// Size of array will be V (number of vertices in graph)
struct Graph
{
    int V;
    struct AdjList* array;
};

// A utility function to create a new adjacency list node
struct AdjListNode* newAdjListNode(int dest)
{
    struct AdjListNode* newNode =
            (struct AdjListNode*) malloc(sizeof(struct AdjListNode));
    newNode->dest = dest;
    newNode->next = NULL;
    return newNode;
}

// A utility function that creates a graph of V vertices
struct Graph* createGraph(int V)
{
    struct Graph* graph = (struct Graph*) malloc(sizeof(struct Graph));
    graph->V = V;

    // Create an array of adjacency lists.  Size of array will be V
    graph->array = (struct AdjList*) malloc(V * sizeof(struct AdjList));

    // Initialize each adjacency list as empty by making head as NULL
    int i;
    for (i = 0; i < V; ++i)
        graph->array[i].head = nullptr;

    return graph;
}

// Adds an edge to an undirected graph
void addEdge(struct Graph* graph, int src, int dest)
{
    // Add an edge from src to dest.  A new node is added to the adjacency
    // list of src.  The node is added at the begining
    struct AdjListNode* newNode = newAdjListNode(dest);
    newNode->next = graph->array[src].head;
    graph->array[src].head = newNode;
    // Since graph is undirected, add an edge from dest to src also
    newNode = newAdjListNode(src);
    newNode->next = graph->array[dest].head;
    graph->array[dest].head = newNode;
}

// A utility function to print the adjacency list representation of graph
void printGraph(struct Graph* graph)
{
    int v;
    for (v = 0; v < graph->V; ++v)
    {
        struct AdjListNode* pCrawl = graph->array[v].head;
        
        printf("\n Adjacency list of vertex %d\n head ", v);
        while (pCrawl)
        {
            printf("-> %d", pCrawl->dest);
            pCrawl = pCrawl->next;
        }
        printf("\n");
    }
}

int findSmallestUnvisitedNode(struct Graph* graph,char *coursesNamesList[6]){

    int v;
    char starterPointString[16] ;
    strcpy(starterPointString,"ZZZZZZZZZZZZZZZ");
    int starterPoint= 0;


    for (v = 0; v < graph->V; v++)
    {

        if (strcmp(coursesNamesList[v],starterPointString)  < 0  && graph->array[v].isVisited != 1 ){ //We are trying to find the smallest course name value to set the starting point.

            strcpy(starterPointString,coursesNamesList[v]);
            starterPoint = v;


        }

    }
    return starterPoint;



}

int* sortedListGraphNodes(struct Graph* graph,char *coursesNamesList[6]){

    int sortedGraphNodesList[6];
    int colors[3];
    colors[0]=0;
    colors[1]=1;
    colors[2]=2;

    int v;
    for ( v = 0; v < graph->V; v++) {//Find the list of nodes that contains sorted indexes of graph.

        int smallestUnvisitedNodeIndex = findSmallestUnvisitedNode(graph,coursesNamesList);
        graph->array[smallestUnvisitedNodeIndex].isVisited = 1;
        sortedGraphNodesList[v] = smallestUnvisitedNodeIndex;
        printf("\n%s\n",coursesNamesList[sortedGraphNodesList[v]]);

    }
    for (int v = 0; v < graph->V; ++v) {//Re-assign the isVisited variable to the 0 to use in the future.
        graph->array[v].isVisited = 0;
    }
    return sortedGraphNodesList;

}

void GraphColoring(struct Graph* graph,char *coursesNamesList[6]){

    int sortedGraphNodesList[6];
    int colors[3];
    colors[0]=0;
    colors[1]=1;
    colors[2]=2;

    int v;
    for ( v = 0; v < graph->V; v++) {//Find the list of nodes that contains sorted indexes of graph.

        int smallestUnvisitedNodeIndex = findSmallestUnvisitedNode(graph,coursesNamesList);
        graph->array[smallestUnvisitedNodeIndex].isVisited = 1;
        sortedGraphNodesList[v] = smallestUnvisitedNodeIndex;
        printf("\n%s\n",coursesNamesList[sortedGraphNodesList[v]]);

    }
    for (int v = 0; v < graph->V; ++v) {//Re-assign the isVisited variable to the 0 to use in the future.
        graph->array[v].isVisited = 0;
    }







    for (int v = 0; v < graph->V; ++v) {//We will try to travers the list that we created earlier and try to find out adjecent nodes colors and assign a different color.
        if(graph->array[sortedGraphNodesList[v]].isVisited != 1){

            struct AdjListNode* pCrawl = graph->array[sortedGraphNodesList[v]].head;
            int adjacentColors[3];
            int adjacentColorsIndex = 0 ;
            while (pCrawl){

                if (graph->array[pCrawl->dest].color >= 0){//If there is a color assigned to the adjacent before.
                    adjacentColors[adjacentColorsIndex] = graph->array[pCrawl->dest].color;

                }else{

                }



                pCrawl = pCrawl->next;



            }

            graph->array[sortedGraphNodesList[v]].isVisited = 1;

        }

    }

//        graph->array->isVisited = 1;
//
//        struct AdjListNode* pCrawl = graph->array[v].head;
//
//        printf("\n Adjacency list of vertex %d\n head ", v);
//        while (pCrawl)
//        {
//            printf("-> %d", pCrawl->dest);
//            pCrawl = pCrawl->next;
//        }
//        printf("\n");




}






// Driver program to test above functions
int main()
{


    char *studentNameList[4] ;
    studentNameList[0] = "Ayse Kara";
    studentNameList[1] = "Efe Anil";
    studentNameList[2] = "Suat Ali Barut";
    studentNameList[3] = "Nil Girgin";


    char *coursesNamesList[6] ;
    coursesNamesList[0] = "MATH101";
    coursesNamesList[1] = "CSE100";
    coursesNamesList[2] = "MATH259";
    coursesNamesList[3] = "BLAW203";
    coursesNamesList[4] = "STAT253";
    coursesNamesList[5] = "HIST111";







    // create the graph given in above figure
    int V = 6;
    struct Graph* graph = createGraph(V);
    addEdge(graph, 0, 1);
    addEdge(graph, 0, 2);
    addEdge(graph, 1, 2);
    addEdge(graph, 0, 3);
    addEdge(graph, 2, 5);
    addEdge(graph, 2, 4);
    addEdge(graph, 4, 5);

    // print the adjacency list representation of the above graph
    printGraph(graph);

    int *sortedGraphNodesList ;
    sortedGraphNodesList = (int*) malloc(sizeof(coursesNamesList));
    sortedGraphNodesList = sortedListGraphNodes(graph,coursesNamesList);
    printf("\n%d",sortedGraphNodesList[0]);
    printf("\n%d",sortedGraphNodesList[1]);
    printf("\n%d",sortedGraphNodesList[2]);
    printf("\n%d",sortedGraphNodesList[3]);
    printf("\n%d",sortedGraphNodesList[4]);
    printf("\n%d",sortedGraphNodesList[5]);




    for (int i = 0; i < 6; i++) {


        printf("%d",sortedGraphNodesList[i]);

    }
//    GraphColoring(graph,coursesNamesList);

    return 0;
}