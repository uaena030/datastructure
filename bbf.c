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

int short_path(char *array, int start_x, int start_y, int row, int col)
{
    Node *head, *tail, *p, *target;
    int x, y, level, i, j;
    char chr;
    int flag[row][col];
    for (i = 0; i < row; i++)
    {
        for (j = 0; j < col; j++)
        {
            flag[i][j] = 0;
        }
    }
    flag[start_x][start_y] = 1;
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
        // left
        if ((y - 1 >= 0) && (y < col) && (flag[x][y - 1] == 0))
        {
            chr = *(array + x * col + y - 1);
            // printf("explored left %c, x= %d, y= %d, level= %d\n", chr, x,y-1, level+1);
            flag[x][y - 1] = 1;
            if (chr == '.')
            {
                // printf("enqueue x= %d, y= %d, level= %d\n",x,y-1,level+1);
                enQueue(&que, x, y - 1, level + 1);
            }
            else if (chr == 'E')
                return level + 1;
        }
        // right
        if ((y + 1 < col) && (y >= 0) && (flag[x][y + 1] == 0))
        {
            chr = *(array + x * col + y + 1);
            // printf("explored right %c, x= %d, y= %d, level= %d\n", chr, x,y+1, level+1);
            flag[x][y + 1] = 1;
            if (chr == '.')
            {
                // printf("enqueue x= %d, y= %d, level= %d\n",x,y+1,level+1);
                enQueue(&que, x, y + 1, level + 1);
            }
            else if (chr == 'E')
                return level + 1;
        }
        // up
        if (x - 1 >= 0 && x < row && (flag[x - 1][y] == 0))
        {
            chr = *(array + (x - 1) * col + y);
            // printf("explored up %c, x= %d, y= %d, level= %d\n", chr, x-1,y, level+1);
            flag[x - 1][y] = 1;
            if (chr == '.')
            {
                // printf("enqueue x= %d, y= %d, level= %d\n",x-1,y,level+1);
                enQueue(&que, x - 1, y, level + 1);
            }
            else if (chr == 'E')
                return level + 1;
        }
        // down
        if (x + 1 < row && x >= 0 && (flag[x + 1][y] == 0))
        {
            chr = *(array + (x + 1) * col + y);
            // printf("explored down %c, x= %d, y= %d, level= %d\n", chr, x+1,y, level+1);
            flag[x + 1][y] = 1;
            if (chr == '.')
            {
                // printf("enqueue x= %d, y= %d, level= %d\n",x+1,y,level+1);
                enQueue(&que, x + 1, y, level + 1);
            }
            else if (chr == 'E')
                return level + 1;
        }
    }
    return 0;
}
int main()
{
    int m, n, i, j, strt_x, strt_y, test_num, k, sum = 0;
    scanf("%d", &test_num);
    for (k = 0; k < test_num; k++)
    {
        scanf("%d %d\n", &m, &n);
        char array[m][n];
        for (i = 0; i < m; i++)
        {
            gets(array[i]);
            for (j = 0; j < n; j++)
            {
                if (array[i][j] == 'S')
                {
                    strt_x = i;
                    strt_y = j;
                }
            }
        }
        sum += short_path((char *)array, strt_x, strt_y, m, n);
    }

    /*
    array[0][0]='.';array[0][1]='.'; array[0][2]='.';array[0][3]='.';array[0][4]='.';array[0][5]='.';
    array[1][0]='.';array[1][1]='S'; array[1][2]='.';array[1][3]='.';array[1][4]='X';array[1][5]='.';
    array[2][0]='X';array[2][1]='X'; array[2][2]='X';array[2][3]='.';array[2][4]='.';array[2][5]='.';
    array[3][0]='.';array[3][1]='.'; array[3][2]='.';array[3][3]='.';array[3][4]='X';array[3][5]='.';
    array[4][0]='.';array[4][1]='X'; array[4][2]='.';array[4][3]='.';array[4][4]='X';array[4][5]='X';
    array[5][0]='.';array[5][1]='E'; array[5][2]='X';array[5][3]='.';array[5][4]='.';array[5][5]='.';
    strt_x = 1;
    strt_y = 1;
    */
    /*

    */
    //
    // printf("x: %d, y= %d\n", strt_x, strt_y);

    printf("%d", sum);

    /*
    for(i=0;i<m;i++)
    {
        printf("%c %c %c %c %c\n",array[i][0],array[i][1],array[i][2],array[i][3],array[i][4]);
    }*/
    return 0;
}

