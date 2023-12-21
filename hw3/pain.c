#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
int step;

typedef struct node{
    int x;
    int y;
} node;

typedef struct tree{
    int data_front, data_rear, Time;
    struct tree *Lchild, *Rchild;
} tree;
void deleteTree(tree* curNode){
    if(curNode == NULL)return;
    deleteTree(curNode->Lchild);
    deleteTree(curNode->Rchild);
    free(curNode);
}
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
    for (int i = step - 1; i >= 0; i--){
        for(int j = 0; j < size; j++){
            if(distance[j][now_x] == distance[now_x][now_y] - 1){
                route[i] = now_x;
                now_y = now_x;
                now_x = j;
                break;
            }
        }
    }
    return route;//第0元素是起點
    /*for (int i = 0; i < step>; i++){
        printf("%d ", route[i]);
    }
    printf("\n");*/
}
tree* CBT(int front, int rear, int*route, int** Nodemem, tree *curNode, int Time){//目前是無窮迴圈狀態
    int mid = (front + rear + 1) / 2;
    int TT = Time -  1;
    int check, type_a;
    tree *newnode = (tree *)malloc(sizeof(tree));
    newnode -> data_front = route[front];
    newnode -> data_rear = route[rear];
    newnode -> Time = Time;
    newnode -> Lchild = NULL;
    newnode -> Rchild = NULL;
    if(curNode == NULL){
        return newnode;
    }
    if(mid == rear && check != true){//brfore entangle(brfore bottom of tree)
        if(type_a == 1){
            newnode -> Time = TT;
            curNode -> Lchild = newnode;
            goto jump;
        }
        curNode -> Lchild = newnode;
        tree *newnode = (tree *)malloc(sizeof(tree));
        newnode->data_front = route[front];
        newnode->data_rear = route[rear];
        newnode->Time = Time - 1;
        newnode->Lchild = NULL;
        newnode->Rchild = NULL;
        curNode -> Lchild -> Lchild = newnode;
        check = true;
    }
    jump:
    if(mid != front){//insert left leaf(not bottom of tree)
        if(curNode -> Lchild == NULL){//insert Lchild
            curNode -> Lchild = newnode;
            Nodemem[Time][front]--;
            Nodemem[Time][rear]--;
            //deal with capacity
            if(Nodemem[Time][front]-- < 0 || Nodemem[Time][mid]-- < 0 || Time - 1 < 0){//reach edge
                deleteTree(curNode);
                return 0;
            }
            //Time < 0 is invalid
            CBT(front, mid, route, Nodemem, curNode->Lchild, TT);
        }
    }
    if(mid != rear){//insert right leaf(not bottom of tree)
        type_a = 1;
        curNode = curNode -> Lchild;//這行有問題
        if(curNode -> Rchild == NULL){//insert Rchild
            newnode->data_front = route[mid];
            newnode->data_rear = route[rear];
            newnode->Time = TT;
            curNode -> Rchild = newnode;
            Nodemem[TT][front]--;
            Nodemem[TT][rear]--;
            // deal with capacity
            if(Nodemem[TT][mid]-- < 0 || Nodemem[TT][rear]-- < 0 || TT - 1 < 0){//reach edge
                deleteTree(curNode);
                return 0;
            }
            CBT(mid, rear, route, Nodemem, curNode->Rchild, TT);
        }
    }
    //entangle統一建在Lchild node
    return curNode;
}
void Postorder(tree *route, int Time){
    int initial = Time;
    // deal with entangle(should not be printed)
    if(route != NULL){
        Postorder(route -> Lchild, Time--);
        Postorder(route -> Rchild, Time--);
        if(route -> Lchild == NULL && route -> Rchild == NULL){//entangle
            printf("%d %d %d\n", route -> data_front, route -> data_rear, Time);
        }
        //print child
        if(route -> Lchild != NULL && route -> Rchild != NULL){
            printf("%d %d %d %d %d %d %d\n", route -> data_front, route -> data_rear\
            , route -> Lchild -> data_front, route -> Lchild -> data_rear, route -> Rchild -> data_front, route -> Rchild -> data_rear, Time);
        }
    }
}

int main(){
    int Nodes, Links, TimeSlots, Req;
    int trash, st, ed;
    scanf("%d %d %d %d", &Nodes, &Links, &TimeSlots, &Req);
    int **Nodemem = malloc(TimeSlots * sizeof(int *));
    for (int i = 0; i < TimeSlots; i++)
    {
        Nodemem[i] = (int *)calloc(Nodes, sizeof(int));
    }
    for(int i = 0; i < Nodes; i++){
        scanf("%d %d", &trash, &Nodemem[0][i]);
    }
    for(int i = 1; i < TimeSlots; i++){
        for(int j = 0; j < Nodes; j++){
            Nodemem[i][j] = Nodemem[0][j];
        }
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
                (*root) = (tree){.data_front = 0, .data_rear = 0, .Time = 0, .Lchild = NULL, .Rchild = NULL};
                int temptime = TimeSlots - 1;
                CBT(0, step - 1, BFSresult, Nodemem, root, temptime);
                Postorder(root, temptime);
                deleteTree(root);
            }
        }
    }
}