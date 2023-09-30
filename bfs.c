#include <stdio.h>
#include <stdlib.h>
#define R 30

int walker[10000000];
struct _node
{
    int level;
    int x;
    int y;
    struct _node *next;
};
typedef struct _node Node;

struct _queue
{
    Node *head;
    Node *tail;
    int size;
};
typedef struct _queue Queue;

void enQueue(Queue *que, int x, int y, int level)
{
    Node *p;
    p = (Node *)malloc(sizeof(Node));
    p->x = x;
    p->y = y;
    p->level = level;
    p->next = NULL;
    if (que->size == 0)
    {
        que->head = p;
        que->tail = p;
    }
    else
    {
        que->tail->next = p;
        que->tail = p;
    }
    que->size += 1;
}

int short_path(int *array, int start_x, int start_y, int map_size, int end_x, int end_y)
{
    Node *head, *tail, *p, *target;
    int x, y, level, i, j, walk_num = -1;
    int check_rep;
    int flag[map_size][map_size];
    for (i = 0; i < map_size; i++)
    {
        for (j = 0; j < map_size; j++)
        {
            flag[i][j] = 0;
            //球沒走過是0
        }
    }
    flag[start_x][start_y] = 2;
    //球(或是走過的路徑)是2
    flag[end_x][end_y] = 3;
    //終點是3
    Queue que;
    que.head = NULL;
    que.tail = NULL;
    que.size = 0;
    enQueue(&que, start_x, start_y, 0);
    while (que.size > 0)
    {
        walk_num++;
        // deqQueue
        target = que.head;
        x = target->x;
        y = target->y;
        level = target->level;
        que.head = target->next;
        que.size -= 1;
        free(target);
        // down
        if ((y - 1 >= 0) && (y < map_size) && (flag[x][y - 1] == 0))
        {
            
            check_rep = *(array + x * map_size + y - 1);
            flag[x][y - 1] = 2;
            walker[walk_num] = 2;
            if (check_rep == 0){
                enQueue(&que, x, y - 1, level + 1);
            }
            else if (check_rep == 3)
                return level + 1;
        }
        // up
        if ((y + 1 < map_size) && (y >= 0) && (flag[x][y + 1] == 0))
        {
            check_rep = *(array + x * map_size + y + 1);
            flag[x][y + 1] = 2;
            walker[walk_num] = 0;
            if (check_rep == 0){
                enQueue(&que, x, y + 1, level + 1);
            }
            else if (check_rep == 3)
                return level + 1;
        }
        // left
        if (x - 1 >= 0 && x < map_size && (flag[x - 1][y] == 0))
        {
            check_rep = *(array + (x - 1) * map_size + y);
            flag[x - 1][y] = 2;
            walker[walk_num] = 3;
            if (check_rep == 0){
                enQueue(&que, x - 1, y, level + 1);
            }
            else if (check_rep == 3)
                return level + 1;
        }
        // right
        if (x + 1 < map_size && x >= 0 && (flag[x + 1][y] == 0))
        {
            check_rep = *(array + (x + 1) * map_size + y);
            flag[x + 1][y] = 2;
            walker[walk_num] = 1;
            if (check_rep == 0){
                enQueue(&que, x + 1, y, level + 1);
            }
            else if (check_rep == 3)
                return level + 1;
        }
    }
    return -1;
}
int main()
{
    int map_size, i, j, sum = 0;
    int ball_1[2][2], ball_2[2][2]; 
    scanf("%d", &map_size);
    int m_array[map_size][map_size];
    for (j = map_size - 1; j >= 0 ; j--){
        for (i = 0; i < map_size; i++){
            scanf("%d", &m_array[i][j]);
            //牆壁是1，路是0
        }
    }
    scanf("%d %d %d %d", &ball_1[0][0], &ball_1[0][1], &ball_2[0][0], &ball_2[0][1]);
    scanf("%d %d %d %d", &ball_1[1][0], &ball_1[1][1], &ball_2[1][0], &ball_2[1][1]);
    sum += short_path((int *)m_array, ball_1[0][0], ball_1[0][1], map_size, ball_1[1][0], ball_1[1][1]);
    for(int j = 0; j < sum; j++){
        printf("%d", walker[j]);
    }

    printf("%d\n", sum);
    sum = 0;
    sum += short_path((int *)m_array, ball_2[0][0], ball_2[0][1], map_size, ball_2[1][0], ball_2[1][1]);
    for (int j = 0; j < sum; j++){
        printf("%d", walker[j]);
    }
    return 0;
}
