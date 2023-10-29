#include <stdio.h>
#include <stdlib.h>
void initial_npath(int node, int *array);
void update_route(int node, int *ini_array, int *fin_array, int *end_array);
int judge_node(int node, int dst, int val, int *ini_array, int *fin_array, int *end_array);
void change_origin_path(int dst, int val, int *fin_array, int *end_array);
void print_path(int node, int *end);
int dcheck = -1;//確認是否為新增節點後的step
int print_count = 0;

void initial_npath(int node, int *array){//初始化
    for(int i = 0; i < node; i ++){
        scanf("%d", &array[i]);
    }
}

void update_route(int node, int *ini_array, int *fin_array, int *end_array){//新增節點
    int pri_temp_val = -1;//initial prior point value
    int pri_temp_dst = 11;//initial prior point destination
    int check = 0;
    while(pri_temp_dst != 0){//起點前沒東西，break
        for (int i = 0; i < node; i++)
        {
            if(check == 0){
                if(fin_array[i] == pri_temp_dst){//有其他點指到該點(有分支)
                    judge_node(node, pri_temp_dst, pri_temp_val, ini_array, fin_array, end_array);
                    check++;
                }
            }
            if (ini_array[i] == pri_temp_dst){//無分支，原路徑
                pri_temp_dst = i;
                pri_temp_val = ini_array[i];
                end_array[pri_temp_dst] = pri_temp_val;
                check = 0;
                //printf("dst: %d, val: %d\n",pri_temp_dst,pri_temp_val);
            }
            //printf("%d\n",check);
        }
        //printf("\n");
    }
}

int judge_node(int node, int dst, int val, int *ini_array, int *fin_array, int *end_array){
    while(dst != 0){
        for(int i = 0; i < node; i++){
            if (fin_array[i] == dst){
                dst = i;
                val = fin_array[i];
                if(ini_array[dst] != -1){//該點在路徑1已指向其他點(非新路徑)(更換原路徑)
                    if(dcheck != -1){
                        if(end_array[dst] == fin_array[dst]){
                            return 0;
                        }
                        change_origin_path(dst, val, fin_array, end_array); // 按理來說每次change path都能輸出新的路徑
                        print_count++;
                        print_path(node, end_array);
                        //printf("k\n");
                        return 0;       
                    }
                    break;
                }
                end_array[dst] = val;
                //printf("dst: %d, val: %d\n",dst,val);
            }
        }
    }
    return 0;
    //print_path(node, end_array);
    //printf("\n");
}

void change_origin_path(int dst, int val, int *fin_array, int *end_array){//原路徑1改為路徑2
    end_array[dst] = fin_array[dst];
}

void print_path(int node, int *end){
    for(int i = 0; i < node; i++){
        printf("%d ", end[i]);
    }
    printf("\n");
}

int main(){
    int node;
    scanf("%d\n", &node);
    //initialize path1 and path2
    int initial[node], final[node], end[node];
    for(int i = 0; i < node; i++){
        end[i] = -1;
    }
    initial_npath(node, initial);
    initial_npath(node, final);
    /*
    for(int i = 0; i < node; i ++){
        printf("%d ", initial[i]);
    }
    printf("\n");
    for (int i = 0; i < node; i++)
    {
        printf("%d ", final[i]);
    }
    */
    //printf("6\n");
    print_path(node, initial);
    update_route(node, initial, final, end);
    //print_path(node, end);
    //printf("1st\n");
    dcheck++;
    update_route(node, end, final, end);
    //print_path(node, end);
    print_path(node, final);
    printf("%d\n", print_count + 2);
    return 0;
}