#include <stdio.h>
#include <stdlib.h>
void initial_npath(int node, int *array);
void update_route(int node, int *ini_array, int *fin_array, int *end_array);
void judge_node(int node, int dst, int val, int *ini_array, int *fin_array, int *end_array);
void change_origin_path(int dst, int val, int *end_array);
void print_path(int node, int *end);

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
                if(fin_array[i] == pri_temp_dst){//路線二的點指到該點
                    int dst = pri_temp_dst;
                    int val = pri_temp_val;
                    judge_node(node, dst, val, ini_array, fin_array, end_array);
                    check++;
                }
            }
            /*if (end_array[pri_temp_dst] != -1){ //該點已指向其他點(需更換原路徑)(之後做)
                change_origin_path(pri_temp_dst, pri_temp_val, end_array);
            }*/
            if (ini_array[i] == pri_temp_dst){//無分支，原路徑
                pri_temp_dst = i;
                pri_temp_val = ini_array[i];
                end_array[pri_temp_dst] = pri_temp_val;
                check = 0;
                //printf("dst: %d, val: %d\n",pri_temp_dst,pri_temp_val);
            }
            //printf("%d\n",check);
        }
        print_path(node, end_array);
    }
}

void judge_node(int node, int dst, int val, int *ini_array, int *fin_array, int *end_array){
    while(dst != 0){
        for(int i = 0; i < node; i++){
            if (fin_array[i] == dst){
                dst = i;
                val = fin_array[i];
                if(ini_array[dst] != -1){//該點已指向其他點(需更換原路徑)(之後做)
                    //change_origin_path(dst, val, end_array);
                    break;
                }
                end_array[dst] = val;
                //printf("dst: %d, val: %d\n",dst,val);
            }
        }
    }
}

/*void change_origin_path(int dst, int val, int *end_array){
    end_array[dst] = val;
}*/

void print_path(int node, int *end){
    for(int i = 0; i < node; i++){
        printf("%d ", end[i]);
    }
    printf("\n");
}

int main(){
    int node, time = 2;
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
    //print_path(node, initial);
    update_route(node, initial, final, end);
    //print_path(node, final);
    return 0;
}