#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
// int check_point = -1;
int check = -1;
int runtime = 0;

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

int dijkstra(int srcx, int srcy, int dstx, int dsty, int **maze, int size, int src_otx, int src_oty, int ot_dst_x, int ot_dst_y)
{
    // printf("Hello, world!\n");
    // print_maze(maze, size);
    // initialize the distance table
    // printf("%d %d %d %d\n", (*src_otx)-1, (*src_oty)-1, (*src_oty)+1, (*src_otx)+1);
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
        //球1提前入球2洞
        if(runtime == 0){
            if(node_x == ot_dst_x && node_y == ot_dst_y){
                // printf("face 1 sucess\n");
                return 1;
            }
        }
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
    // int count = 0;
    for (int i = 0; i < distance[dstx][dsty]; i++)
    {
        // count++;
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
    int temp_x = src_otx;
    int temp_y = src_oty;
    //printf("x = %d ,y = %d\n", src_otx, src_oty);
    for (int i = distance[dstx][dsty] - 1; i >= 0; i--)
    {
        //printf("src1_x = %d, src1_y = %d\n", src_otx, src_oty);
        printf("%d", route[i]);
        if (check == -1)
        {
            //printf("check in\n");
            //printf("src2_x = %d, src2_y = %d\n", src_oty, 9 - src_otx);
            //球2提前入球1洞
            if(runtime == 0){
                if(maze[src_otx][src_oty] == maze[dstx][dsty] && i != 0){
                    //printf("face 2 sucess\n");
                    src_otx = temp_x;
                    src_oty = temp_y;
                    //printf("src2_x = %d, src2_y = %d\n", src_otx, src_oty);
                    return 2;
                }
            }
            if (route[i] == 0 && maze[src_otx - 1][src_oty] != 1)
            {
                src_otx--;
            }
            else if (route[i] == 1 && maze[src_otx][src_oty + 1] != 1)
            {
                //printf("Yaro\n");
                src_oty++;
            }
            else if (route[i] == 2 && maze[src_otx + 1][src_oty] != 1)
            {
                //printf("Baka\n");
                src_otx++;
            }
            else if (route[i] == 3 && maze[src_otx][src_oty - 1] != 1)
            {
                src_oty--;
            }
        }
        //printf("x = %d ,y = %d\n", src_oty, 10 - src_otx);
    }
    return 0;
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
    int src1[2], src2[2], dst1[2], dst2[2]; // compare[4];
    scanf("%d %d %d %d", &src1[0], &src1[1], &src2[0], &src2[1]);
    scanf("%d %d %d %d", &dst1[0], &dst1[1], &dst2[0], &dst2[1]);
    int new_x = n - 1 - src2[1];
    int new_y = src2[0];

    int first = dijkstra(n - 1 - src1[1], src1[0], n - 1 - dst1[1], dst1[0], maze, n, new_x, new_y, n - 1 - dst2[1], dst2[0]);
    //printf("src1_x = %d, src1_y = %d\n", new_x, new_y);
    if (first == 1){
        //printf("1\n");
        //printf("x = %d,y = %d\n", new_y, 10 - new_x);
        runtime ++;
        dijkstra(n - 1 - src1[1], src1[0], n - 1 - dst2[1], dst2[0], maze, n, new_x, new_y, n - 1 - dst2[1], dst2[0]);
        //printf("ball1 second success\n");
        //printf("x = %d,y = %d\n", new_x, new_y);
        check = 1;
        dijkstra(new_x, new_y, n - 1 - dst1[1], dst1[0], maze, n, n - 1 - src1[1], src1[0], -100, -100);
        return 0;
    }
    else if (first == 2){
        //printf("2\n");
        runtime++;
        dijkstra(n - 1 - src2[1], src2[0], n - 1 - dst1[1], dst1[0], maze, n, n - 1 - src1[1], src1[0], n - 1 - dst2[1], dst2[0]);
        check = 1;
        dijkstra(n - 1 - src1[1], src1[0], n - 1 - dst2[1], dst2[0], maze, n, n - 1 - src1[1], src1[0], -100, -100);
        return 0;
    }
    runtime++;
    check = 1;
    dijkstra(new_x, new_y, n - 1 - dst2[1], dst2[0], maze, n, n - 1 - src1[1], src1[0], -100, -100);
    //printf("src1_x = %d, src1_y = %d\n", new_x, new_y);
    //check = 1;
    //dijkstra(new_x, new_y, n - 1 - dst2[1], dst2[0], maze, n, src2[0], src2[1]);
    return 0;
    // test
    // printf("---------------------------\n");
    // print_maze(maze, n);
}