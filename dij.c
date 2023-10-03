#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

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

void dijkstra(int srcx, int srcy, int dstx, int dsty, int **maze, int size)
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
    for (int i = 0; i < distance[dstx][dsty]; i++)
    {
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
    for (int i = distance[dstx][dsty] - 1; i >= 0; i--)
    {
        printf("%d", route[i]);
    }
    printf("\n");
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
    int src1[2], src2[2], dst1[2], dst2[2];
    scanf("%d %d %d %d", &src1[0], &src1[1], &src2[0], &src2[1]);
    scanf("%d %d %d %d", &dst1[0], &dst1[1], &dst2[0], &dst2[1]);

    dijkstra(n - 1 - src1[1], src1[0], n - 1 - dst1[1], dst1[0], maze, n);
    /* need to move src2 to new space */
    // dijkstra(n - 1 - src2[1], src2[0], n - 1 - dst2[1], dst2[0], maze);

    // test
    // printf("---------------------------\n");
    // print_maze(maze, n);
}