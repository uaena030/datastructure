#include <stdio.h>
#include <stdlib.h>
void initial_npath(int node, int *array);
void add(struct node* q, int value);
int findParent(int i, int *parent);
void Unionset(int i, int j, int *parent);

struct node{
    struct node *next;
    int value;
};

void initial_npath(int node, int *array){//initialize route
    for(int i = 0; i < node; i ++){
        scanf("%d", &array[i]);
    }
}

void add(struct node* q, int value){ // push the value to the end of queue
    struct node *temp = q;
    while(temp->next!=NULL){ // traverse to the end
        temp=temp->next;
    }
    temp->next = (struct node*)malloc(sizeof(struct node)); // malloc new node
    temp->next->value = value;
    temp->next->next = NULL;
}

int findParent(int i, int *parent){
    return (parent[i] == i) ? i : findParent(parent[i], parent);
}

void Unionset(int i, int j, int *parent){
    parent[findParent(j, parent)] = findParent(i, parent);
}

int main(){
    int node;
    scanf("%d\n",&node);
    int *parent = (int)malloc(sizeof(int) * node);
    int *initial = (int )malloc(sizeof(int) * node);
    int *final = (int)malloc(sizeof(int) * node);
    struct node *end = (struct node*)malloc(sizeof(struct node) * node);

    initial_npath(node, initial);
    initial_npath(node, final);
    int change_new = 0, comflict = 0, print_count = 0;
    add(end, -10);

    //dsu part
    for(int i = 0; i < node; i++){//initial dsu array
        parent[i] = i;
    }
    for(int i = 0; i < node; i++){
        if(initial[i] == -1 && final[i] != -1){
            add(end , i);
            Unionset(findParent(i, parent), i, parent);
            change_new = 1;
        }
        if(initial[i] != final[i]){
            comflict++;
        }
    }
    if(change_new == 1){
        add(end, -10);
        print_count++;
    }
}