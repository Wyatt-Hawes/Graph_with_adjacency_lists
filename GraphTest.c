#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<assert.h>
#include<stdbool.h>

#include "List.h"
#include "Graph.h"

static void append_ascending(List L, int val){
    
    if(index(L) == -1 && length(L) == 0){
        append(L, val);
        //printList(stdout,L);
        return;
    }
    moveFront(L);
    //printf("C:%d\n", index(L));
    while(index(L) != -1){

        if(get(L) > val){
            insertBefore(L, val);
            //printList(stdout,L);
            return;
        }
        moveNext(L);
    }
    append(L, val);
    //printList(stdout,L);
}

int main(){
    
    //printf("---------\n");
    Graph g = newGraph(6);
    List L = newList();
    append_ascending(L,3);
    //append_ascending(L,2);
    //append_ascending(L,5);
    
    addEdge(g,1,2);
    addEdge(g,1,3);
    addEdge(g,2,4);
    addEdge(g,2,5);
    addEdge(g,2,6);
    addEdge(g,3,4);
    addEdge(g,4,5);
    addEdge(g,5,6);
    addEdge(g,0,0);
    
    addEdge(g,1,5);
    addEdge(g,3,6);
    addEdge(g,2,3);
    addEdge(g,4,4);
    addEdge(g,0,0);
    
    //printGraph(stdout,g);
    makeNull(g);
    printGraph(stdout,g);
    printList(stdout, L);
    freeGraph(&g);
    freeList(&L);
    return 0;
}