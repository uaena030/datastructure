#include <stdio.h>
#include <stdlib.h>
void initial_npath(int node, int *array);
void update_route(int node, int *ini_array, int *fin_array, int *end_array);
int judge_node(int node, int dst, int val, int *ini_array, int *fin_array, int *end_array);
void change_origin_path(int dst, int val, int *fin_array, int *end_array);
void print_path(int node, int *end);
int dcheck = -1; // 確認是否為新增節點後的step
int print_count = 0;
int stack_route[100][100];

void initial_npath(int node, int *array){//初始化
    for(int i = 0; i < node; i ++){
        scanf("%d", &array[i]);
    }
}
void update_route(int node, int *ini_array, int *fin_array, int *end_array){//新增節點
    int pri_temp_val = -1;//initial prior point value
    int pri_temp_dst = node - 1;//initial prior point destination
    int check = 0;
    while(pri_temp_dst != 0){//起點前沒東西，break//首先先只考慮第二個路線有沒有跟第一個路線重複，沒有就新增

    }
}
int judge_node(int node, int dst, int val, int *ini_array, int *fin_array, int *end_array){//新增不重複路線(對路線1)，換句話說就是自己跑路線
    while (val == -1){ // 前個點沒有指到別的點
        for (int i = 0; i < node; i++){
            if (fin_array[i] == dst){ // 路線2有其他點指到該點(有分支)
                dst = i;
                val = fin_array[i]; // 往前找(根據路徑2)
                end_array[dst] = val; // 更換end路徑
                break;//再次判斷前一個有沒有指到別的點
            }
        }
    }
    return 0;
}
void change_origin_path(int dst, int val, int *fin_array, int *end_array){ // 原路徑1改為路徑2
    end_array[dst] = fin_array[dst];
}

void print_path(int node, int *end){
    for (int i = 0; i < node; i++){
        printf("%d ", end[i]);
    }
    printf("\n");
}

int main()
{
    int node;
    scanf("%d\n", &node);
    // initialize path1 and path2
    int initial[node], final[node], end[node];
    for (int i = 0; i < node; i++){
        end[i] = -1;
    }
    initial_npath(node, initial);
    initial_npath(node, final);
    update_route(node, initial, final, end);
    dcheck++;
    update_route(node, end, final, end);
    printf("%d\n", print_count + 2);
    print_path(node, initial);
    for (int i = 0; i < print_count; i++){
        for (int j = 0; j < node; j++){
            printf("%d ", stack_route[i][j]);
        }
        printf("\n");
    }
    print_path(node, final);
    return 0;
}