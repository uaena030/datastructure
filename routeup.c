#include <stdio.h>
#include <stdlib.h>
void initial_npath(int node, int *array);
void update_route(int node, int *ini_array, int *fin_array, int *end_array);
int judge_node(int node, int dst, int val, int *ini_array, int *fin_array, int *end_array);
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
    //trace back and change node at 1st round
    if(dcheck == -1){//debug finished
        for(int i = 0; i < node; i++){
            if(ini_array[i] == -1 && ini_array[i] != fin_array[i]){
                end_array[i] = fin_array[i];
            }
            else
                end_array[i] = ini_array[i];
        }
        for(int i = 0; i < node; i++){
            stack_route[print_count][i] = end_array[i];
        }
        dcheck++;
        print_count++;
        return;
    }
    if(dcheck != -1){//second and after round
        int pri_temp_val = -1;//initial prior point value
        int pri_temp_dst = node - 1;//initial prior point destination
        int current = 0;
        for(int i = current; i < node; i++){
            if(fin_array[i] == pri_temp_dst){//11//6
                pri_temp_dst == i;//6//1
                pri_temp_val == fin_array[i];//11//6
                if(ini_array[pri_temp_dst] != fin_array[pri_temp_dst]){
                    end_array[pri_temp_dst] = fin_array[pri_temp_dst];
                    for (int i = 0; i < node; i++){
                        stack_route[print_count][i] = end_array[i];
                    }
                    print_count++;
                    return;
                }
                i = current;//0
            }
        }
    }
}

int judge_node(int node, int dst, int val, int *ini_array, int *fin_array, int *end_array){

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
    update_route(node, initial, final, end);
    update_route(node, end, final, end);
    printf("%d\n", print_count + 1);
    print_path(node, initial);
    for(int i = 0; i < print_count; i++){
        for(int j = 0; j < node; j++){
            printf("%d ", stack_route[i][j]);
        }
        printf("\n");
    }
    print_path(node, final);
    return 0;
}