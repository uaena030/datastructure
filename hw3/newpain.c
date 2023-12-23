#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
int step, bruh = 0;
int level, max = 0;

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
    node queue[size * size + 1];
    int head = 0, tail = 1;
    queue[0].x = src;
    queue[0].y = src;//(src, src) is starting point
    int node_x, node_y;
    int visited[size], ancient[10000];
    for(int i = 0; i < size; i++){
        visited[i] = false;
    }
    visited[0] = true;
    // bfs
    while (head != tail){
        node_x = queue[head].x;
        node_y = queue[head].y;
        if (node_x == end && node_y == end){
            break;
        }
        for(int i = 0; i < size; i++){
            if(maze[node_y][i] == 1 && visited[i] == false){
                ancient[i] = node_y;
                //node_x = 0 0
                queue[tail].x = node_y;//0 1
                queue[tail].y = i;//1
                visited[i] = true;
                tail++;
            }
        }
        head++;
        //printf("node_x = %d, node_y = %d\n", node_x, node_y);
    }
    // generate route
    int rroute[10000];
    for(int i = 0; i < 10000; i++){
        rroute[i] = -1;
    }
    int i = end, j = 0;
    while(i != src){
        rroute[j] = i;
        j++;
        i = ancient[i];
    }
    rroute[j] = i;
    int *route = malloc((j + 1) * sizeof(int));
    for(int i = 0; i < j + 1; i++){
        route[i] = rroute[j - i];
    }
    /*for (int i = 0; i < j + 1; i++){
        printf("%d ", route[i]);
    }
    printf("\n");*/
    step = j + 1;
    return route;//第0元素是起點
}
tree* CBT(int front, int rear, int*route, tree *curNode){
    int mid = (front + rear + 1) / 2;
    int check = 0;
    tree *newnode = (tree *)malloc(sizeof(tree));
    newnode -> data_front = route[front];
    newnode -> data_rear = route[rear];
    newnode -> Lchild = NULL;
    newnode -> Rchild = NULL;
    if(curNode == NULL){
        return newnode;
    }
    if(front + 1 != rear){
        if(curNode -> Lchild == NULL){//insert Lchild
            curNode -> Lchild = newnode;
            CBT(front, mid, route, curNode->Lchild);
        }
        curNode = curNode -> Lchild;
        bruh = true;
        if(curNode -> Rchild == NULL){//insert Rchild
            tree *newnode = (tree *)malloc(sizeof(tree));
            newnode->data_front = route[mid];
            newnode->data_rear = route[rear];
            newnode->Lchild = NULL;
            newnode->Rchild = NULL;
            curNode -> Rchild = newnode;
            // deal with capacity
            CBT(mid, rear, route, curNode->Rchild);
        }
    }
    if(front + 1 == rear && check != true){//before entangle
        int choose = -1;
        if (curNode->Lchild == NULL && bruh != true){
            curNode->Lchild = newnode;
            choose = 0;
        }
        else if(curNode -> Rchild == NULL){
            choose = 1;
        }
        tree *newnode = (tree *)malloc(sizeof(tree));
        newnode->data_front = route[front];
        newnode->data_rear = route[rear];
        newnode->Lchild = NULL;
        newnode->Rchild = NULL;
        if(choose == 0)
            curNode -> Lchild -> Lchild = newnode;
        else if(choose == 1)
            curNode -> Lchild = newnode;
        check = true;
    }
    //entangle統一建在Lchild node
    return curNode;
}

int judgemem(tree *route, int level, int Timesl, int** Nodemem){
    if(route != NULL){
        judgemem(route->Lchild, level + 1, Timesl, Nodemem);
        judgemem(route->Rchild, level + 1, Timesl, Nodemem);
        route->Time = Timesl - level;
        if(Nodemem[route->Time][route->data_front] - 1 >= 0 || Nodemem[route->Time][route->data_rear] - 1 >= 0){
            Nodemem[route->Time][route->data_front]--;
            Nodemem[route->Time][route->data_rear]--;
        }
        else
            return 0;
    }
    return 1;
}

void flo(tree *route, int level){
    if(route != NULL){
        flo(route->Lchild, level + 1);
        flo(route->Rchild, level + 1);
        if(level > max){
            max = level;
        }
    }
}

void Postorder(tree *route){
    // deal with entangle(should not be printed)
    if(route != NULL){
        Postorder(route -> Lchild);
        Postorder(route -> Rchild);
        if(route -> Lchild == NULL && route -> Rchild == NULL){//entangle
            printf("%d %d %d\n", route -> data_front, route -> data_rear, (route -> Time) + 2);
        }
        //print child
        if(route -> Lchild != NULL && route -> Rchild != NULL){
            printf("%d %d %d %d %d %d %d\n", route -> data_front, route -> data_rear\
            , route -> Lchild -> data_front, route -> Lchild -> data_rear, route -> Rchild -> data_front, route -> Rchild -> data_rear, (route -> Time) + 1);
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
    int **tempmem = malloc(TimeSlots * sizeof(int *));
    for (int i = 0; i < TimeSlots; i++)
    {
        tempmem[i] = (int *)calloc(Nodes, sizeof(int));
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
        Linkmem[ed][st] = true;
    }
    int Reqmem[Nodes][Nodes];
    for(int i = 0; i < Req; i++){
        scanf("%d %d %d", &trash, &st, &ed);
        Reqmem[st][ed] = true;
    }
    int k = -1;
    int accepted = 0, acce[Req];
    for(int i = 0; i < Req; i++){
        acce[i] = false;
    }
    tree* root[Req];
    int finalroute[Req][10000];
    int stepcount[Req];
    for(int i = 0; i < Nodes; i++){
        for( int j = 0; j < Nodes; j++){
            if(Reqmem[i][j] == true){
                k++;
                int* BFSresult = BFS(i, j, Linkmem, Nodes);
                stepcount[k] = step;
                for(int mu = 0; mu < step; mu++){
                    finalroute[k][mu] = BFSresult[mu];
                }
                root[k] = (tree *) malloc(sizeof(tree));
                root[k]->data_front = 0;
                root[k]->data_rear = 0;
                root[k]->Time = 0;
                root[k]->Lchild = NULL;
                root[k]->Rchild = NULL;
                for (int m = 0; m < TimeSlots; m++){
                    for (int n = 0; n < Nodes; n++){
                        tempmem[m][n] = Nodemem[m][n];
                    }
                }
                CBT(0, step - 1, BFSresult, root[i]);
                root[k] = root[k] -> Lchild;
                level = 0;
                flo(root[k], level);
                level = max;
                if(judgemem(root[k], 0, level, tempmem) != 0){
                    for (int m = 0; m < TimeSlots; m++){
                        for (int n = 0; n < Nodes; n++){
                            Nodemem[m][n] = tempmem[m][n];
                        }
                    }
                    accepted++;
                    acce[accepted - 1] = true;//accessible request
                }         
            }
        }
    }
    printf("%d\n", accepted);
    for(int i = 0; i < Req; i++){
        if(acce[i] == true){
            printf("%d ", i);
            for(int j = 0; j < stepcount[i]; j++){
                printf("%d ",finalroute[i][j]);
            }
            printf("\n");
            Postorder(root[i]);
            deleteTree(root[i]);
        }
    }
}