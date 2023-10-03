#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
//int check_point = -1;
int check = -1;

void print_maze(int **maze, int n)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            printf("%d ", maze[i][j]);
        }
        printf("\n");
    }
}

typedef struct node
{
    int x;
    int y;
} node;


void dijkstra(int srcx, int srcy, int dstx, int dsty, int **maze, int size, int* src_otx, int* src_oty)
{
    // printf("Hello, world!\n");
    // print_maze(maze, size);
    // initialize the distance table
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
    // printf("BFS\n");
    // bfs
    while (head != tail)
    {
        node_x = queue[head].x;
        node_y = queue[head].y;
        if (node_x == dstx && node_y == dsty)
            break;

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
        // printf("Head %d\n", head);
    }

    // printf("Route\n");
    // generate route
    int *route = calloc(distance[dstx][dsty], sizeof(int));
    int now_x = dstx;
    int now_y = dsty;
    //int count = 0;
    for (int i = 0; i < distance[dstx][dsty]; i++)
    {
        //count++;
        if (distance[now_x + 1][now_y] == distance[now_x][now_y] - 1)
        {
            route[i] = 0;
            now_x++;
        }
        else if (distance[now_x][now_y - 1] == distance[now_x][now_y] - 1)
        {
            route[i] = 1;
            now_y--;
        }
        else if (distance[now_x - 1][now_y] == distance[now_x][now_y] - 1)
        {
            route[i] = 2;
            now_x--;
        }
        else if (distance[now_x][now_y + 1] == distance[now_x][now_y] - 1)
        {
            route[i] = 3;
            now_y++;
        }
        // else printf("---------\nError\n--------\n");
    }
    /*
    if(check_point == -1){
        return count;
    }*/
    //if(check_point != -1){
        for (int i = distance[dstx][dsty] - 1; i >= 0; i--)
        {
            printf("%d", route[i]);
            if(check == -1){
                if(route[i] == 0 && distance[(*src_otx)--][*src_oty] != -2){
                    (*src_otx)--;
                }
                else if (route[i] == 1 && distance[*src_otx][(*src_oty)++] != -2){
                    (*src_oty)++;
                }
                else if (route[i] == 2 && distance[(*src_otx)++][*src_oty] != -2)
                {
                    (*src_otx)++;
                }
                else if (route[i] == 3 && distance[*src_otx][(*src_oty)--] != -2)
                {
                    (*src_oty)--;
                }
            }
        }
    //}
}

int main()
{
    // input the size
    int n;
    scanf("%d", &n);

    // initialize the maze
    int **maze = malloc(n * sizeof(int *));
    for (int i = 0; i < n; i++)
    {
        maze[i] = (int *)calloc(n, sizeof(int));
    }

    // input the maze
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            scanf("%d", &maze[i][j]);
        }
    }

    // input start & end point
    int src1[2], src2[2], dst1[2], dst2[2]; //compare[4];
    scanf("%d %d %d %d", &src1[0], &src1[1], &src2[0], &src2[1]);
    scanf("%d %d %d %d", &dst1[0], &dst1[1], &dst2[0], &dst2[1]);
    int src_otx = src2[0];
    int src_oty = src2[1];

    dijkstra(n - 1 - src1[1], src1[0], n - 1 - dst1[1], dst1[0], maze, n, &src_otx, &src_oty);
    check = 1;
    dijkstra(n - 1 - src2[1], src2[0], n - 1 - dst2[1], dst2[0], maze, n, 0, 0);

    /* need to move src2 to new space */
    /*compare[0] = dijkstra(n - 1 - src1[1], src1[0], n - 1 - dst1[1], dst1[0], maze, n);
    compare[1] = dijkstra(n - 1 - src1[1], src1[0], n - 1 - dst2[1], dst2[0], maze, n);
    compare[2] = dijkstra(n - 1 - src2[1], src2[0], n - 1 - dst2[1], dst2[0], maze, n);
    compare[3] = dijkstra(n - 1 - src2[1], src2[0], n - 1 - dst1[1], dst1[0], maze, n);

    int min = compare[0], temp = 0;
    for(int j = 0; j < 4; j++){
        if(compare[j] < min){
            min = compare[j];
            temp = j;
        }
    }
    check_point = 2;
    switch (temp){
    case 0:{
        dijkstra(n - 1 - src1[1], src1[0], n - 1 - dst1[1], dst1[0], maze, n);
        dijkstra(n - 1 - src2[1], src2[0], n - 1 - dst2[1], dst2[0], maze, n);
        break;
    } 
    case 1:{
        dijkstra(n - 1 - src1[1], src1[0], n - 1 - dst2[1], dst2[0], maze, n);
        dijkstra(n - 1 - src2[1], src2[0], n - 1 - dst1[1], dst1[0], maze, n);
        break;
    }
    case 2:{
        dijkstra(n - 1 - src2[1], src2[0], n - 1 - dst2[1], dst2[0], maze, n);
        dijkstra(n - 1 - src1[1], src1[0], n - 1 - dst1[1], dst1[0], maze, n);
        break;
    }
    case 3:{
        dijkstra(n - 1 - src2[1], src2[0], n - 1 - dst1[1], dst1[0], maze, n);
        dijkstra(n - 1 - src1[1], src1[0], n - 1 - dst2[1], dst2[0], maze, n);
        break;
    }
    default:
        break;
    }
    */
    return 0;
    // test
    // printf("---------------------------\n");
    // print_maze(maze, n);
}