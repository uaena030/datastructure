#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
int step;

typedef struct node{
    int x;
    int y;
} node;

typedef struct{
    int data_front, data_rear, Time;
    tree *Lchild, *Rchild;
}tree;

int* BFS(int src, int end, int **maze, int size){
    int **distance = malloc(size * sizeof(int *));
    for (int i = 0; i < size; i++)
        distance[i] = malloc(size * sizeof(int));
    for (int i = 0; i < size; i++)// i is starting point and j is ending point
    {
        for (int j = 0; j < size; j++)
        {
            if (maze[i][j] == false)
                distance[i][j] = -2; // use -2 to represent no linked
            else
                distance[i][j] = -1; // -1 to represent linked
        }
    }
    distance[src][src] = 0;// starting point
    distance[end][end] = -1;// ending point

    node queue[size * size + 1];
    int head = 0, tail = 1;
    queue[0].x = src;
    queue[0].y = src;//(src, src) is starting point
    int node_x, node_y;
    // bfs
    while (head != tail)
    {
        node_x = queue[head].x;
        node_y = queue[head].y;
        if (node_x == end && node_y == end){
            break;
        }
        for(int i = 0; i < size; i++){
            if(distance[node_y][i] == -1){
                //node_x = 0 0
                queue[tail].x = node_y;//0 1
                queue[tail].y = i;//1
                distance[node_y][i] = distance[node_x][node_y] + 1;//00 01 12
                node_x = node_y;
                node_y = i;
                tail++;
            }
        }
        head++;
        //printf("node_x = %d, node_y = %d\n", node_x, node_y);
    }
    // generate route
    int *route = malloc((1000000) * sizeof(int));
    int now_x = end;
    int now_y = end;
    //printf("total step is : %d\n", distance[end][end]);
    step = distance[end][end];
    for (int i = 0; i < step; i++){
        for(int j = 0; j < size; j++){
            if(distance[j][now_x] == distance[now_x][now_y] - 1){
                route[i] = now_x;
                now_y = now_x;
                now_x = j;
                break;
            }
        }
    }
    return route;
    /*for (int i = step - 1; i >= 0; i--){
        printf("%d ", route[i]);
    }
    printf("\n");*/
}
tree* CBT(int front, int rear, int*route, int Nodemem, tree *curNode, int Time){
    int mid = (front + rear + 1) / 2;
    tree *newnode = (tree *)malloc(sizeof(tree));
    newnode -> data_front = front;
    newnode -> data_rear = rear;
    newnode -> Time = Time;
    newnode -> Lchild = NULL;
    newnode -> Rchild = NULL;
    if(curNode == NULL){
        return newnode;
    }
    if(mid - 1 != front){//insert left leaf(not bottom of tree)
        if(curNode -> Lchild == NULL){
            curNode -> Lchild = newnode;
        }
        else{

            CBT(front, mid, route, Nodemem, curNode->Lchild, Time);
        }
    }
    else if(mid + 1 != rear){//insert right leaf(not bottom of tree)
        if(curNode -> Rchild == NULL){
            curNode -> Rchild = newnode;
        }
        else{

            CBT(mid, rear, route, Nodemem, curNode->Rchild, Time);
        }
    }
    else if(mid - 1 == front){//entangle(bottom of tree, left leaf)
        
    }
    else if(mid + 1 == rear){//brfore entangle(bottom of tree, right leaf)

    }
    return curNode;

}

int main(){
    int Nodes, Links, TimeSlots, Req;
    int trash, st, ed;
    scanf("%d %d %d %d", &Nodes, &Links, &TimeSlots, &Req);

    int Nodemem[Nodes];
    for(int i = 0; i < Nodes; i++){
        scanf("%d %d", &trash, &Nodemem[i]);
    }

    int **Linkmem = malloc(Nodes * sizeof(int *));
    for (int i = 0; i < Nodes; i++)
    {
        Linkmem[i] = (int *)calloc(Nodes, sizeof(int));
    }
    for(int i = 0; i < Links; i++){
        scanf("%d %d %d", &trash, &st, &ed);
        Linkmem[st][ed] = true;
    }
    int Reqmem[Nodes][Nodes];
    for(int i = 0; i < Req; i++){
        scanf("%d %d %d", &trash, &st, &ed);
        Reqmem[st][ed] = true;
    }
    for(int i = 0; i < Nodes; i++){
        for( int j = 0; j < Nodes; j++){
            if(Reqmem[i][j] == true){
                int* BFSresult = BFS(i, j, Linkmem, Nodes);
                tree *root = (tree *) malloc(sizeof(tree));
                (*root) = (tree){.data_front = 0, .data_rear = 0, .Lchild = NULL, .Rchild = NULL};
                int temptime = TimeSlots;
                CBT(0, step - 1, BFSresult, Nodemem, root, temptime);
            }
        }
    }
        
}