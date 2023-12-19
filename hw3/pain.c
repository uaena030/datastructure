#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int check = -1;
int pause = -1;

typedef struct node
{
    int x;
    int y;
} node;

void BFS(int srcx, int srcy, int **maze, int size){
    int **distance = malloc(size * sizeof(int *));
    for (int i = 0; i < size; i++)
        distance[i] = malloc(size * sizeof(int));
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            if (maze[i][j] == 1)
                distance[i][j] = -2; // use -2 to represent wall
            else
                distance[i][j] = -1;
        }
    }
    distance[srcx][srcy] = 0;
    // printf("Initialize distance table finished.\n");

    node queue[size * size + 1];
    int head = 0, tail = 1;
    queue[0].x = srcx;
    queue[0].y = srcy;
    int node_x, node_y;
    // bfs
    while (head != tail)
    {
        node_x = queue[head].x;
        node_y = queue[head].y;

        // up
        if (distance[node_x - 1][node_y] == -1)
        {
            queue[tail].x = node_x - 1;
            queue[tail].y = node_y;
            distance[node_x - 1][node_y] = distance[node_x][node_y] + 1;
            tail++;
        }
        // right
        if (distance[node_x][node_y + 1] == -1)
        {
            queue[tail].x = node_x;
            queue[tail].y = node_y + 1;
            distance[node_x][node_y + 1] = distance[node_x][node_y] + 1;
            tail++;
        }
        // down
        if (distance[node_x + 1][node_y] == -1)
        {
            queue[tail].x = node_x + 1;
            queue[tail].y = node_y;
            distance[node_x + 1][node_y] = distance[node_x][node_y] + 1;
            tail++;
        }
        // left
        if (distance[node_x][node_y - 1] == -1)
        {
            queue[tail].x = node_x;
            queue[tail].y = node_y - 1;
            distance[node_x][node_y - 1] = distance[node_x][node_y] + 1;
            tail++;
        }
        head++;
    }
}

int main(){
    int Nodes, Links, TimeSlots, Req;
    int trash, st, ed;
    scanf("%d %d %d %d", &Nodes, &Links, &TimeSlots, &Req);
    int Nodemem[Nodes];
    for(int i = 0; i < Nodes; i++){
        scanf("%d %d", &trash, &Nodemem[i]);
    }
    int Linkmem[Nodes][Nodes];
    for(int i = 0; i < Links; i++){
        scanf("%d %d %d", &trash, &st, &ed);
        Linkmem[st][ed] = true;
    }
    int Reqmem[Nodes][Nodes];
    for(int i = 0; i < Req; i++){
        scanf("%d %d %d", &trash, &st, &ed);
        Reqmem[st][ed] = true;
    }
        
}