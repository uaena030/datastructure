#include <stdio.h>
#include <stdlib.h>
#define R 30
//int check_hole = -1;//1是按原定，不是就是2
int print_check = -1;

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
    int check_rep;
    int flag[map_size][map_size];
    for (i = 0; i < map_size; i++)
    {
        for (j = 0; j < map_size; j++)
        {
            flag[i][j] = 0;
            // 球沒走過是0
        }
    }
    flag[start_x][start_y] = 2;
    // 球(或是走過的路徑)是2
    // flag[end_x][end_y] = 3;
    // 終點是3
    Queue que;
    que.head = NULL;
    que.tail = NULL;
    que.size = 0;

    int **record = malloc(map_size * sizeof(int *));
    for(int i = 0; i < map_size; i++) record[i] = malloc(map_size * sizeof(int));
    for(int i = 0; i < map_size; i++){
        for(int j = 0; j < map_size; j++){
            record[i][j] = -1;
        }
    }

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
        // printf("deQueue x= %d, y= %d, level= %d\n",x,y,level);
        free(target);
        // down
        if ((y - 1 >= 0) && (y < map_size) && (flag[x][y - 1] == 0))
        {

            check_rep = *(array + x * map_size + y - 1);
            // printf("explored down %d, x= %d, y= %d, level= %d\n", check_rep, x,y-1, level+1);
            flag[x][y - 1] = 2;
            if (check_rep == 0)
            {
                // printf("enqueue x= %d, y= %d, level= %d\n",x,y-1,level+1);
                if(record[x][y - 1] == -1){
                    record[x][y - 1] = 2;
                } 
                enQueue(&que, x, y - 1, level + 1);
                
                //walker[walk_num] = 2;
            }
            else if (check_rep == 3){
                if(print_check != -1){
                    int route_x = x;
                    int route_y = y - 1;
                    /*if(x == end_x && y - 1 == end_y){
                        check_hole = 1;
                    }
                    else
                        check_hole = 2;*/
                    int walker[map_size * map_size];
                    int walk_num = -1;
                    record[route_x][route_y] = 2; 
                    while (record[route_x][route_y] != -1)
                    {
                        walk_num++;
                        if (record[route_x][route_y] == 0)
                        {
                            walker[walk_num] = 0;
                            route_y--;
                        }
                        else if (record[route_x][route_y] == 1)
                        {
                            walker[walk_num] = 1;
                            route_x--;
                        }
                        else if (record[route_x][route_y] == 2)
                        {
                            walker[walk_num] = 2;
                            route_y++;
                        }
                        else if (record[route_x][route_y] == 3)
                        {
                            walker[walk_num] = 3;
                            route_x++;
                        }
                    }
                    for(int u = walk_num; u >= 0 ; u--){
                        printf("%d", walker[u]);
                    }
                }
                return level + 1;
            }
        }
        // up
        if ((y + 1 < map_size) && (y >= 0) && (flag[x][y + 1] == 0))
        {
            check_rep = *(array + x * map_size + y + 1);
            // printf("explored up %d, x= %d, y= %d, level= %d\n", check_rep, x, y + 1, level + 1);
            flag[x][y + 1] = 2;
            if (check_rep == 0)
            {
                // printf("enqueue x= %d, y= %d, level= %d\n", x, y + 1, level + 1);
                if (record[x][y + 1] == -1)
                {
                    record[x][y + 1] = 0;
                }
                enQueue(&que, x, y + 1, level + 1);
                //walker[walk_num] = 0;
            }
            else if (check_rep == 3){
                if (print_check != -1){
                    int route_x = x;
                    int route_y = y + 1;
                    /*if (x == end_x && y + 1 == end_y)
                    {
                        check_hole = 1;
                    }
                    else
                        check_hole = 2;*/
                    int walker[map_size * map_size];
                    int walk_num = -1;
                    record[route_x][route_y] = 0;
                    while (record[route_x][route_y] != -1)
                    {
                        walk_num++;
                        if (record[route_x][route_y] == 0)
                        {
                            walker[walk_num] = 0;
                            route_y--;
                        }
                        else if (record[route_x][route_y] == 1)
                        {
                            walker[walk_num] = 1;
                            route_x--;
                        }
                        else if (record[route_x][route_y] == 2)
                        {
                            walker[walk_num] = 2;
                            route_y++;
                        }
                        else if (record[route_x][route_y] == 3)
                        {
                            walker[walk_num] = 3;
                            route_x++;
                        }
                    }
                    for (int u = walk_num; u >= 0; u--)
                    {
                        printf("%d", walker[u]);
                    }
                }
                return level + 1;
            }
        }
        // left
        if (x - 1 >= 0 && x < map_size && (flag[x - 1][y] == 0))
        {
            check_rep = *(array + (x - 1) * map_size + y);
            // printf("explored left %d, x= %d, y= %d, level= %d\n", check_rep, x - 1, y, level + 1);
            flag[x - 1][y] = 2;
            if (check_rep == 0)
            {
                // printf("enqueue x= %d, y= %d, level= %d\n", x - 1, y, level + 1);
                if (record[x - 1][y] == -1)
                {
                    record[x - 1][y] = 3;
                }
                enQueue(&que, x - 1, y, level + 1);
                //walker[walk_num] = 3;
            }
            else if (check_rep == 3){
                if (print_check != -1){
                    int route_x = x - 1;
                    int route_y = y;
                    /*if (x - 1 == end_x && y == end_y)
                    {
                        check_hole = 1;
                    }
                    else
                        check_hole = 2;*/
                    int walker[map_size * map_size];
                    int walk_num = -1;
                    record[route_x][route_y] = 3;
                    while (record[route_x][route_y] != -1)
                    {
                        walk_num++;
                        if (record[route_x][route_y] == 0)
                        {
                            walker[walk_num] = 0;
                            route_y--;
                        }
                        else if (record[route_x][route_y] == 1)
                        {
                            walker[walk_num] = 1;
                            route_x--;
                        }
                        else if (record[route_x][route_y] == 2)
                        {
                            walker[walk_num] = 2;
                            route_y++;
                        }
                        else if (record[route_x][route_y] == 3)
                        {
                            walker[walk_num] = 3;
                            route_x++;
                        }
                    }
                    for (int u = walk_num; u >= 0; u--)
                    {
                        printf("%d", walker[u]);
                    }
                }
                return level + 1;
            }
        }
        // right
        if (x + 1 < map_size && x >= 0 && (flag[x + 1][y] == 0))
        {
            check_rep = *(array + (x + 1) * map_size + y);
            // printf("explored right %d, x= %d, y= %d, level= %d\n", check_rep, x + 1, y, level + 1);
            flag[x + 1][y] = 2;
            if (check_rep == 0)
            {
                // printf("enqueue x= %d, y= %d, level= %d\n", x + 1, y, level + 1);
                if (record[x + 1][y] == -1)
                {
                    record[x + 1][y] = 1;
                }
                enQueue(&que, x + 1, y, level + 1);
                //walker[walk_num] = 1;
            }
            else if (check_rep == 3){
                if (print_check != -1){
                    int route_x = x + 1;
                    int route_y = y;
                    /*if (x + 1 == end_x && y == end_y)
                    {
                        check_hole = 1;
                    }
                    else
                        check_hole = 2;*/
                    int walker[map_size * map_size];
                    int walk_num = -1;
                    record[route_x][route_y] = 1;
                    /*for(int n = 0; n < map_size; n++){
                        for(int m = 0; m < map_size; m++){
                            printf("%2d", record[n][m]);
                        }
                        printf("\n");
                    }*/
                    while (record[route_x][route_y] != -1)
                    {
                        walk_num++;
                        if (record[route_x][route_y] == 0)
                        {
                            walker[walk_num] = 0;
                            route_y--;
                        }
                        else if (record[route_x][route_y] == 1)
                        {
                            walker[walk_num] = 1;
                            route_x--;
                        }
                        else if (record[route_x][route_y] == 2)
                        {
                            walker[walk_num] = 2;
                            route_y++;
                        }
                        else if (record[route_x][route_y] == 3)
                        {
                            walker[walk_num] = 3;
                            route_x++;
                        }
                    }
                    for (int u = walk_num; u >= 0; u--)
                    {
                        printf("%d", walker[u]);
                    }
                }
                return level + 1;
            }
        }
    }
    return -1;
}
int main()
{
    int map_size, i, j, sum[4], total_walk;
    int ball_1[2][2], ball_2[2][2];
    scanf("%d", &map_size);
    int m_array[map_size][map_size];
    for (j = map_size - 1; j >= 0; j--)
    {
        for (i = 0; i < map_size; i++)
        {
            scanf("%d", &m_array[i][j]);
            // 牆壁是1，路是0
        }
    }
    scanf("%d %d %d %d", &ball_1[0][0], &ball_1[0][1], &ball_2[0][0], &ball_2[0][1]);
    scanf("%d %d %d %d", &ball_1[1][0], &ball_1[1][1], &ball_2[1][0], &ball_2[1][1]);
    //m_array[ball_1[1][0]][ball_1[1][1]] = 3;
    //m_array[ball_2[1][0]][ball_2[1][1]] = 3;
    m_array[ball_1[1][0]][ball_1[1][1]] = 3;
    sum[0] = short_path((int *)m_array, ball_1[0][0], ball_1[0][1], map_size, ball_1[1][0], ball_1[1][1]);
    m_array[ball_1[1][0]][ball_1[1][1]] = 0;
    m_array[ball_2[1][0]][ball_2[1][1]] = 3;
    sum[1] = short_path((int *)m_array, ball_1[0][0], ball_1[0][1], map_size, ball_2[1][0], ball_2[1][1]);
    m_array[ball_2[1][0]][ball_2[1][1]] = 0;
    m_array[ball_1[1][0]][ball_1[1][1]] = 3;
    sum[2] = short_path((int *)m_array, ball_2[0][0], ball_2[0][1], map_size, ball_1[1][0], ball_1[1][1]);
    m_array[ball_1[1][0]][ball_1[1][1]] = 0;
    m_array[ball_2[1][0]][ball_2[1][1]] = 3;
    sum[3] = short_path((int *)m_array, ball_2[0][0], ball_2[0][1], map_size, ball_2[1][0], ball_2[1][1]);
    m_array[ball_2[1][0]][ball_2[1][1]] = 0;
    int min = sum[0];
    int temp;
    for(int j = 0 ; j < 4; j++){
        if(sum[j] < min){
            min = sum[j];
            temp = j;
        }
    }
    //check_hole = -1;
    if(temp == 0){
        print_check = 1;
        m_array[ball_1[1][0]][ball_1[1][1]] = 3;
        short_path((int *)m_array, ball_1[0][0], ball_1[0][1], map_size, ball_1[1][0], ball_1[1][1]);
        m_array[ball_1[1][0]][ball_1[1][1]] = 0;
        /*if (check_hole = 2){
            check_hole = -1;
            m_array[ball_1[1][0]][ball_1[1][1]] = 3;
            short_path((int *)m_array, ball_2[0][0], ball_2[0][1], map_size, ball_1[1][0], ball_1[1][1]);
        }*/
        m_array[ball_2[1][0]][ball_2[1][1]] = 3;
        short_path((int *)m_array, ball_2[0][0], ball_2[0][1], map_size, ball_2[1][0], ball_2[1][1]);
        m_array[ball_2[1][0]][ball_2[1][1]] = 0;
    }
    else if(temp == 1){
        print_check = 1;
        m_array[ball_2[1][0]][ball_2[1][1]] = 3;
        short_path((int *)m_array, ball_1[0][0], ball_1[0][1], map_size, ball_2[1][0], ball_2[1][1]);
        m_array[ball_2[1][0]][ball_2[1][1]] = 0;
        m_array[ball_1[1][0]][ball_1[1][1]] = 3;
        short_path((int *)m_array, ball_2[0][0], ball_2[0][1], map_size, ball_1[1][0], ball_1[1][1]);
        m_array[ball_1[1][0]][ball_1[1][1]] = 0;
    }
    else if(temp == 2){
        print_check = 1;
        m_array[ball_1[1][0]][ball_1[1][1]] = 3;
        short_path((int *)m_array, ball_2[0][0], ball_2[0][1], map_size, ball_1[1][0], ball_1[1][1]);
        m_array[ball_1[1][0]][ball_1[1][1]] = 0;
        m_array[ball_2[1][0]][ball_2[1][1]] = 3;
        short_path((int *)m_array, ball_1[0][0], ball_1[0][1], map_size, ball_2[1][0], ball_2[1][1]);
        m_array[ball_2[1][0]][ball_2[1][1]] = 0;
    }
    else if(temp == 3){
        print_check = 1;
        m_array[ball_2[1][0]][ball_2[1][1]] = 3;
        short_path((int *)m_array, ball_2[0][0], ball_2[0][1], map_size, ball_2[1][0], ball_2[1][1]);
        m_array[ball_2[1][0]][ball_2[1][1]] = 0;
        m_array[ball_1[1][0]][ball_1[1][1]] = 3;
        short_path((int *)m_array, ball_1[0][0], ball_1[0][1], map_size, ball_1[1][0], ball_1[1][1]);
        m_array[ball_1[1][0]][ball_1[1][1]] = 0;
    }
    /*if(check_hole = 2){
        check_hole = -1;
        m_array[ball_1[1][0]][ball_1[1][1]] = 0;
        m_array[ball_2[1][0]][ball_2[1][1]] = 0;
        m_array[ball_1[1][0]][ball_1[1][1]] = 3;
        sum2 = short_path((int *)m_array, ball_2[0][0], ball_2[0][1], map_size, ball_1[1][0], ball_1[1][1]);
    }
    else if(check_hole = 1){
        check_hole = -1;
        m_array[ball_1[1][0]][ball_1[1][1]] = 0;
        m_array[ball_2[1][0]][ball_2[1][1]] = 0;
        m_array[ball_2[1][0]][ball_2[1][1]] = 3;
        sum2 = short_path((int *)m_array, ball_2[0][0], ball_2[0][1], map_size, ball_2[1][0], ball_2[1][1]);
    }*/
    /*for(int j = 0; j < sum; j++){
        printf("%d", walker[j]);
    }*/
    //printf("%d", sum);
    /*for (int j = 0; j < sum; j++){
        printf("%d", walker[j]);
    }*/
    //printf("%d", sum);
    return 0;
}