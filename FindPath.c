#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>
#include "List.h"
#include "Graph.h"

int main(int argc, char* argv[]){

    if (argc != 3){
        fprintf(stderr, "Please enter 2 arguments.\n Ex: Lex <input file> <output file>\n");
        return 1;
    }

    FILE* input = fopen(argv[1], "r");
    FILE* output = fopen(argv[2], "w");

    if (input == NULL){

        fprintf(stderr, "Input file does not exist.\n");
        return 1;
    }

    int a,b = -1;
    fscanf(input,"%d\n", &a);

    //printf("%d\n",a);
    int n = a;
    Graph g = newGraph(n);

    while (a != 0 && b != 0){
        fscanf(input,"%d %d\n", &a, &b);

        if(a == 0 && a == b){break;}
        addEdge(g, a, b);
    }
    printGraph(output,g);
    //fprintf(output,"\n");
    fscanf(input,"%d %d\n", &a, &b);
    List path = newList();
    while (a != 0 && b != 0){
        
        //printf("processing: %d %d\n", a, b);
        //if(a == 0 && a == b){break;}
        
        BFS(g, a);
        clear(path);
        getPath(path, g, b);

        //printf("---%d-%d----\n",a,b);
        //printList(output,path);
        //printf("--------\n");
        if(getDist(g, b) == INF){
            fprintf(output, "The distance from %d to %d is infinity\nNo %d-%d path exists\n",a,b,a,b);
            fscanf(input,"%d %d\n", &a, &b);
            //printf("read %d %d\n",a ,b);
            continue;
        }
        //printf("bot\n");
        int dis = getDist(g,b);
        fprintf(output, "\nThe distance from %d to %d is %d\nA shortest %d-%d path is:",a,b,dis,a,b);
        printList(output, path);
        //fprintf(output,"\n");
        fscanf(input,"%d %d\n", &a, &b);
        //printf("read %d %d\n",a ,b);
        continue;
    }


    //Time to free all the memory
    freeList(&path);
    freeGraph(&g);
}