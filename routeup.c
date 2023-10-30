#include <stdio.h>
#include <stdlib.h>
void initial_npath(int node, int *array);
void update_route(int node, int *ini_array, int *fin_array, int *end_array);
int judge_node(int node, int dst, int val, int *ini_array, int *fin_array, int *end_array);
void change_origin_path(int dst, int val, int *fin_array, int *end_array);
void print_path(int node, int *end);
int dcheck = -1;//確認是否為新增節點後的step
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
    while(pri_temp_dst != 0){//起點前沒東西，break
        for (int i = 0; i < node; i++)
        {
            if(check == 0){//沒做過(加新路線)這個步驟
                if(fin_array[i] == pri_temp_dst){//路線2有其他點指到該點(有分支)(有問題，因為有可能位元比ini後面)
                    judge_node(node, pri_temp_dst, pri_temp_val, ini_array, fin_array, end_array);
                    int dst_how = 0;
                    for(int j = i; j < node; j++){
                        if(fin_array[j] == pri_temp_dst || ini_array[j] == pri_temp_dst){dst_how++;}
                    }
                    if(dst_how == 1){//fin或ini之後會有其他點指向該點
                        check++;//bug:>=1以上的點指向該點
                    }
                    else{//只有ini指向該點
                        dst_how--;
                    }
                }
            }
            if(i == node - 1){
                if (ini_array[i] == pri_temp_dst){//無分支，原路徑
                        pri_temp_dst = i;
                        pri_temp_val = ini_array[i];
                        end_array[pri_temp_dst] = pri_temp_val;
                        check = 0;
                    //printf("dst: %d, val: %d\n",pri_temp_dst,pri_temp_val);
                }
            }
            //printf("%d\n",check);
        }
        //printf("\n");
    }
}

int judge_node(int node, int dst, int val, int *ini_array, int *fin_array, int *end_array){
    while(dst != 0){//沒跑到起點
        for(int i = 0; i < node; i++){
            if (fin_array[i] == dst){//路線2有其他點指到該點(有分支)
                dst = i;
                val = fin_array[i];//往前找(根據路徑2)
                if(ini_array[dst] != -1){//新的點在路徑1已指向其他點(非新路徑)(更換原路徑)
                    if(dcheck != -1){//第二次輸出路徑之後(已新增完所有新結點)
                        if(end_array[dst] == fin_array[dst]){//沒有更改到end路徑
                            return 0;
                        }
                        change_origin_path(dst, val, fin_array, end_array); // 按理來說每次change path都能輸出新的路徑
                        for(int j = 0; j < node; j++){
                            stack_route[print_count][j] = end_array[j];
                        }
                        print_count++;
                        //print_path(node, end_array);
                        //printf("k\n");
                        return 0;       
                    }
                    break;
                }
                end_array[dst] = val;//更換end路徑
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
    update_route(node, initial, final, end);
    //print_path(node, end);
    //printf("1st\n");
    dcheck++;
    update_route(node, end, final, end);
    printf("%d\n", print_count + 2);
    print_path(node, initial);
    for(int i = 0; i < print_count; i++){
        for(int j = 0; j < node; j++){
            printf("%d ", stack_route[i][j]);
        }
        printf("\n");
    }
    //print_path(node, end);
    print_path(node, final);
    return 0;
}