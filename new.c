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

void dijkstra(int srcx, int srcy, int dstx, int dsty, int **maze, int size, int *src_otx, int *src_oty, int ot_dst_x, int ot_dst_y)
{
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
        if (node_x == dstx && node_y == dsty){
            pause++;
            break;
        }
        else if (node_x == ot_dst_x && node_y == ot_dst_y && check == -1)
        {
            //printf("evoke 1\n");
            pause++;
            break;
        }

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
        // for(int i = 0; i < size; i++){
        //     for(int j = 0; j < size; j++){
        //         printf("%d ", distance[i][j]);
        //     }
        //     printf("\n");
        // }
        // printf("-------------------------------------------------------\n");
    }

    // generate route
    int *route = malloc((1000000)*sizeof(int));
    int now_x = dstx;
    int now_y = dsty;
    int end_x = dstx;
    int end_y = dsty;
    if (pause == 0 && check == -1)
    {
        //printf("evoke 2\n");
        now_x = ot_dst_x;
        now_y = ot_dst_y;
        end_x = ot_dst_x;
        end_y = ot_dst_y;
    }
    int step = distance[end_x][end_y];
    for (int i = 0; i < step; i++){
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
    }
    int temp_x = ot_dst_x;
    int temp_y = ot_dst_y;
    for (int i = step - 1; i >= 0; i--)
    {
        printf("%d", route[i]);
        if (check == -1)
        {
            //printf("Evoke ball2 route\n");
            if (route[i] == 0 && maze[*src_otx - 1][*src_oty] != 1)
            {
                src_otx--;
            }
            else if (route[i] == 1 && maze[*src_otx][*src_oty + 1] != 1)
            {
                src_oty++;
            }
            else if (route[i] == 2 && maze[*src_otx + 1][*src_oty] != 1)
            {
                src_otx++;
            }
            else if (route[i] == 3 && maze[*src_otx][*src_oty - 1] != 1)
            {
                src_oty--;
            }
            printf("x = %d y = %d\n", *src_otx, *src_oty);
            if(temp_x == *src_otx && temp_y == *src_oty){
                break;
            }
        }
    }
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
    int second_x = n - 1 - src1[1];
    int second_y = src1[0];

    
    dijkstra(n - 1 - src1[1], src1[0], n - 1 - dst1[1], dst1[0], maze, n, &new_x, &new_y, n - 1 - dst2[1], dst2[0]);
    // printf("1\n");
    check = 1;
    printf("nx = %d ny = %d\n", 10 - new_y, new_x);
    if(pause == -1){
        dijkstra(new_x, new_y, n - 1 - dst2[1], dst2[0], maze, n, &second_x, &second_y, -100, -100);
    }
    else if(pause == 0){
        dijkstra(new_x, new_y, n - 1 - dst1[1], dst1[0], maze, n, &second_x, &second_y, -100, -100);
    }
    return 0;
}