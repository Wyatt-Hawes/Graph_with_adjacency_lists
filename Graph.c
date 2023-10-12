#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<assert.h>
#include<stdbool.h>
#include "List.h"
#include "Graph.h"


//Helper Functions
typedef int ListElement;

//GraphObj constructor
typedef struct GraphObj{

    List* vertexes;
    int* color;
    int* parents;
    int* distances;

    int count;

    //order= num of vertices
    int order;

    //size = num of edges
    int size;
    
    //source, most recent
    int source;


} GraphObj;

#define black 3
#define gray 2
#define white 1


static void append_ascending(Graph g, List L, int val){
    
    if(index(L) == -1 && length(L) == 0){
        append(L, val);
        g->size++;
        return;
    }
    moveFront(L);
    while(index(L) != -1){

        if(get(L) == val){
            return;
        }

        if(get(L) > val){
            insertBefore(L, val);
            g->size++;
            return;
        }
        moveNext(L);
    }
    g->size++;
    append(L, val);

}
//creates new empty graph with N vertices
Graph newGraph(int n){
    Graph g = malloc(sizeof(GraphObj));
    assert(g != NULL);
    g->count = n+1;
    g->vertexes = calloc(n + 1, sizeof(List));

    for(int i = 0; i < g->count; i++){
        //initialize all the lists
        g->vertexes[i] = newList();
    }

    g->color = calloc(g->count, sizeof(int));
    for(int i = 0; i < g->count; i++){
        //all nodes undiscovered
        g->color[i] = white;
    }

    g->parents = calloc(g->count, sizeof(int));
    for(int i = 0; i < g->count; i++){
        //all nodes have no BFS parent yet
        g->parents[i] = NIL;
    }

    g->distances = calloc(g->count,sizeof(int));
    for(int i = 0; i < g->count; i++){
        //all nodes distance start infinity
        g->distances[i] = INF;
    }

    g->order = n;
    g->size = 0;
    g->source = NIL;

    return g;
}

//free graph memory
void freeGraph(Graph *g){
    
    //Free individual vertex Lists
    for(int i = 0; i < (*g)->count; i++){
        //printf("i:%d\n",i);
        freeList(&((*g)->vertexes[i]));
    }
    //free the array of those lists
    free((*g)->vertexes);

    //free various arrays
    free((*g)->color);
    free((*g)->parents);
    free((*g)->distances);

    //finally free the struct
    free((*g));

    (*g) = NULL;
    return;
}

int getOrder(Graph g){
    if( g==NULL ){
      printf("Graph Error: calling getOrder() on NULL GRAPH reference\n");
      exit(EXIT_FAILURE);
   }
   return g->order;
}

int getSize(Graph g){
    if( g==NULL ){
      printf("Graph Error: calling getSize() on NULL GRAPH reference\n");
      exit(EXIT_FAILURE);
   }
   return g->size;
}

int getSource(Graph g){
    if( g==NULL ){
      printf("Graph Error: calling getSource() on NULL GRAPH reference\n");
      exit(EXIT_FAILURE);
   }
   return g->source;
}

int getParent(Graph g, int u){
    if( g==NULL ){
      printf("Graph Error: calling getParent() on NULL GRAPH reference\n");
      exit(EXIT_FAILURE);
    }
    if(u < 1 || u > getOrder(g)){
        printf("Graph Error: calling getParent() on invalid u (%d)\n", u);
      exit(EXIT_FAILURE);
    }

   return g->parents[u];
}

int getDist(Graph g, int u){
    if( g==NULL ){
      printf("Graph Error: calling getDist() on NULL GRAPH reference\n");
      exit(EXIT_FAILURE);
   }
   if(u < 1 || u > getOrder(g)){
        printf("Graph Error: calling getDist() on invalid u (%d)\n", u);
      exit(EXIT_FAILURE);
    }
   return g->distances[u];
}

//pre-con getSource != NIL
void getPath(List L, Graph g, int u){
    if( g==NULL ){
      printf("Graph Error: calling getPath() on NULL GRAPH reference\n");
      exit(EXIT_FAILURE);
    }
     if( L==NULL ){
      printf("List Error: calling getPath() on NULL LIST reference\n");
      exit(EXIT_FAILURE);
    }
    if (getSource(g) == NIL){
        printf("Graph Error: calling getPath() on GRAPH with no source\n");
      exit(EXIT_FAILURE);
    }
    if(u < 1 || u > getOrder(g)){
        printf("Graph Error: calling getPath() on invalid u (%d)\n", u);
      exit(EXIT_FAILURE);
    }



    int vert = u;
    if(getDist(g,u) == INF){
        append(L, NIL);
        //printf("appending NIL\n");
        return;
    }

    
    append(L,vert);
    //printf("appending:%d\n",vert);
    moveBack(L);
    //printf("v:%d\n",vert);
   

    while(getParent(g, vert) != NIL){
        vert = getParent(g, vert);
        insertBefore(L, vert);
        moveFront(L);
        //printf("insb4:%d\n",vert);
        
    }
    //append(L, vert);
    return;
}

void makeNull(Graph g){
    if( g==NULL ){
      printf("Graph Error: calling makeNULL() on NULL GRAPH reference\n");
      exit(EXIT_FAILURE);
    }
    for(int i = 0; i < g->count; i++){
        clear(g->vertexes[i]);
    }
    return;
}

void addEdge(Graph g, int u, int v){
    if(g == NULL ){
      printf("Graph Error: calling addEdge() on NULL GRAPH reference\n");
      exit(EXIT_FAILURE);
    }
    if(u == v || u == 0){
        return;
    }
    
    if(u < 1 || u > getOrder(g)){
        printf("Graph Error: calling addEdge() on invalid u (%d) order:%d\n", u, getOrder(g));
      exit(EXIT_FAILURE);
    }
    if(v < 1 || v > getOrder(g)){
        printf("Graph Error: calling getEdge() on invalid v (%d)\n", u);
      exit(EXIT_FAILURE);
    }

    
    //g->size+=2;
    append_ascending(g,g->vertexes[u], v);
    append_ascending(g,g->vertexes[v], u);
    g->size--;

    return;
}


void addArc(Graph g, int u, int v){
    if(g == NULL ){
      printf("Graph Error: calling addEdge() on NULL GRAPH reference\n");
      exit(EXIT_FAILURE);
    }
    if(u < 1 || u > getOrder(g)){
        printf("Graph Error: calling addEdge() on invalid u (%d)\n", u);
      exit(EXIT_FAILURE);
    }
    if(v < 1 || v > getOrder(g)){
        printf("Graph Error: calling getEdge() on invalid v (%d)\n", u);
      exit(EXIT_FAILURE);
    }
    
    append_ascending(g,g->vertexes[u], v);

    return;
}

void BFS(Graph g, int s){
    //reset graph
    for(int i = 0; i < g->count; i++){
        g->color[i] = white;
        g->distances[i] = INF;
        g->parents[i] = NIL;
    }

    g->color[s] = gray;
    g->distances[s] = 0;
    g->parents[s] = NIL;
    g->source = s;

    List QUEUE = newList();
    append(QUEUE, s);

    int x;
    while(length(QUEUE) > 0){
        x = front(QUEUE);
        deleteFront(QUEUE);

        moveFront(g->vertexes[x]);
        int y;
        for(int i = 0; i < length(g->vertexes[x]); i++){
            y=get(g->vertexes[x]);
                if(g->color[y] == white){
                    g->color[y] = gray;
                    g->distances[y] = g->distances[x] + 1;
                    g->parents[y] = x;
                    append(QUEUE, y);
                }
            moveNext(g->vertexes[x]);
        }
        g->color[x] = black;


    }
    freeList(&QUEUE);
}

void printGraph(FILE* out, Graph g){

    for(int i = 1; i < g->count; i++){
        fprintf(out, "%d:", i);
        printList(out, g->vertexes[i]);
    }
}
