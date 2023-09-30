#include <stdio.h>
#include <stdlib.h>
#define R 30
/* run this program using the console pauser or add your own getch, system("pause") or input loop */
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
    int x, y, level, i, j;
    int chr;
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
    //球是2
    flag[end_x][end_y] = 3;
    //終點是3
    Queue que;
    que.head = NULL;
    que.tail = NULL;
    que.size = 0;
    enQueue(&que, start_x, start_y, 0);
    while (que.size > 0)
    {
        // deqQueue
        target = que.head;
        x = target->x;
        y = target->y;
        level = target->level;
        que.head = target->next;
        que.size -= 1;
        // chr = *(array+x*col+y);
        // printf("deQueue x= %d, y= %d, level= %d\n",x,y,level);
        free(target);
        // down
        if ((y - 1 >= 0) && (y < map_size) && (flag[x][y - 1] == 0))
        {
            
            chr = *(array + x * map_size + y - 1);
            // printf("explored left %c, x= %d, y= %d, level= %d\n", chr, x,y-1, level+1);
            flag[x][y - 1] = 1;

            if (chr == 0 || chr == 3)
            {
                // printf("enqueue x= %d, y= %d, level= %d\n",x,y-1,level+1);
                enQueue(&que, x, y - 1, level + 1);
                if (chr == 3)
                    return level + 1;
            }
            
        }
        // up
        if ((y + 1 < map_size) && (y >= 0) && (flag[x][y + 1] == 0))
        {
            chr = *(array + x * map_size + y + 1);
            // printf("explored right %c, x= %d, y= %d, level= %d\n", chr, x,y+1, level+1);
            flag[x][y + 1] = 1;
            if (chr == 0 || chr == 3)
            {
                // printf("enqueue x= %d, y= %d, level= %d\n",x,y+1,level+1);
                enQueue(&que, x, y + 1, level + 1);
                if (chr == 3)
                    return level + 1;
            }
        }
        // left
        if (x - 1 >= 0 && x < map_size && (flag[x - 1][y] == 0))
        {
            chr = *(array + (x - 1) * map_size + y);
            // printf("explored up %c, x= %d, y= %d, level= %d\n", chr, x-1,y, level+1);
            flag[x - 1][y] = 1;
            if (chr == 0 || chr == 3)
            {
                // printf("enqueue x= %d, y= %d, level= %d\n",x-1,y,level+1);
                enQueue(&que, x - 1, y, level + 1);
                if (chr == 3)
                    return level + 1;
            }
        }
        // right
        if (x + 1 < map_size && x >= 0 && (flag[x + 1][y] == 0))
        {
            chr = *(array + (x + 1) * map_size + y);
            // printf("explored down %c, x= %d, y= %d, level= %d\n", chr, x+1,y, level+1);
            flag[x + 1][y] = 1;
            if (chr == 0 || chr == 3)
            {
                // printf("enqueue x= %d, y= %d, level= %d\n",x+1,y,level+1);
                enQueue(&que, x + 1, y, level + 1);
                if (chr == 3)
                    return level + 1;
            }
        }
    }
    return -1;
}
int main()
{
    int map_size, i, j, sum = 0;
    int ball_1[2][2], ball_2[2][2]; 
    scanf("%d", &map_size);
    //printf("%d\n", map_size);
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
    
    //printf("x: %d, y= %d\n", ball_1[0][0], ball_1[0][1]);

    printf("%d\n", sum);
    sum = 0;
    sum += short_path((int *)m_array, ball_2[0][0], ball_2[0][1], map_size, ball_2[1][0], ball_2[1][1]);
    printf("%d", sum);
    /*
    for(i=0;i<m;i++)
    {
        printf("%c %c %c %c %c\n",array[i][0],array[i][1],array[i][2],array[i][3],array[i][4]);
    }*/
    return 0;
}
