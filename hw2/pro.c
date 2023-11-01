#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int *new, *old, *updated, *backward, *unionSet;
int updateCounter=0, roundCounter=1, operation=0, n, current, temp; // updateCounter stores the time we've updated, roundCounter stores the round we need to perform, operation counts the maximum step we need to update all the nodes
typedef struct Queue{ // implement the queue by linked list
    struct Queue *next;
    int n;
}queue;
queue **ans, **prune, **shortcut;


int dsuFind(int a){ // implement dsu and find the root
    if(a==unionSet[a]){
        return a;
    }
    else{
        unionSet[a]=dsuFind(unionSet[a]);
        return unionSet[a];
    }
}

void dsuUnion(int a, int b){ // union two element and update their values
    int temp1=dsuFind(a);
    int temp2=dsuFind(b);
    unionSet[temp2]=temp1;
}

void push(queue** q, int value){ // push the value to the end of queue
    queue* temp=*q;
    while(temp->next!=NULL){ // traverse to the end
        temp=temp->next;
    }
    temp->next=(queue*)malloc(sizeof(queue)); // malloc new node
    temp->next->n=value;
    temp->next->next=NULL;
    return;
}

int top(queue** q){
    if((*q)->next==NULL){
        return INT_MIN;
        printf("top empty\n");
    }
    else{
        return (*q)->next->n; //return top value
    }
}

void pop(queue** q){
    queue* temp;
    if((*q)->next==NULL){
        printf("pop empty\n");
        return;
    }
    else{
        temp=(*q)->next;
        (*q)->next=(*q)->next->next; // link to the next node of next node
        free(temp); // free the top mode 
        return;
    }
}

int isEmpty(queue** q){ // check if the queue is empty
    if((*q)->next==NULL){
        return 1;
    }
    else{
        return 0;
    }
}

int findDestination(int i){ // find the node that's not updated on the new path
    while(updated[i]==1){
        i=new[i];
    }
    return i;
}

int skipCount(int i){// return the number that will skip on the new path
    int count=0, current=i, dest=new[i];
    dest=findDestination(new[i]);// store the desination on the new path
    do{
        current=old[current];
        if(old[current]!=-1&&new[current]!=-1&&current!=dest&&updated[current]!=1){
            count++;// count adds if limit satisfies
        }
    }while(current!=dest);
    return count;
}

void checkBackward(void){ //check if this new path is backward, which will induce cycle
    int current, dest;
    for(int i=0;i<n;i++){
        current=i;
        dest=findDestination(new[i]);// find the destination first
        if(updated[i]==1||old[i]==-1||new[i]==-1){ // nodes that doesn't matter
            backward[i]=-1;
            continue;
        }
        else{
            backward[i]=1;
            do{
                current=old[current];
                if(dsuFind(dest)==dsuFind(current)){// find old path counters new path with same dsu value
                    backward[i]=0;
                    break;
                }
            }while(current!=n-1);
        }
    }
}

void addShortcut(int node){// add node to 'shortcut queue'
    push(shortcut, node);
    updated[node]=1;
    dsuUnion(node, findDestination(node)); // renew the dsu value
    push(ans, node);
    updateCounter++;
}

void pruneFunction(void){// update the nodes that're on the skipped shortcut
    while(!isEmpty(shortcut)){
        int current=top(shortcut);
        pop(shortcut);
        int dest=findDestination(new[current]);
        current=old[current];
        while(current!=dest){
            if(old[current]!=-1&&new[current]!=-1&&updated[current]==0){
                push(prune, current); //push the node into 'prune queue'
            }
            current=old[current];
        }
    }
    if(isEmpty(prune)){ //no need to add roundCounter
        return;
    }
    while(!isEmpty(prune)){
        int temp=top(prune);
        pop(prune);
        dsuUnion(temp, findDestination(temp));// combine two set components(group)
        push(ans, temp);
        updated[temp]=1;
        updateCounter++;
    }
    push(ans, -1);
    roundCounter++;   
}


int main(){
    scanf("%d",&n);
    new=(int*)calloc(n,sizeof(int));// malloc new, old, update, backward, unionSet arrays
    old=(int*)calloc(n,sizeof(int));
    updated=(int*)calloc(n,sizeof(int));
    backward=(int*)calloc(n,sizeof(int));
    unionSet=(int*)calloc(n,sizeof(int));

    ans=(queue**)malloc(sizeof(queue*));// initialize ans, prune, shortcut queues
    *ans=(queue*)malloc(sizeof(queue));
    (*ans)->next=NULL;
    prune=(queue**)malloc(sizeof(queue*));
    *prune=(queue*)malloc(sizeof(queue));
    (*prune)->next=NULL;
    shortcut=(queue**)malloc(sizeof(queue*));
    *shortcut=(queue*)malloc(sizeof(queue));
    (*shortcut)->next=NULL;

    for(int i=0;i<n;i++){// input
        scanf("%d",&old[i]);
    }
    for(int i=0;i<n;i++){// input
        scanf("%d",&new[i]);
    }
    for(int i=0;i<n;i++){// initialize union set
        unionSet[i]=i;
    }

    roundCounter=1;
    push(ans,-1); // the output should start with inital state
    temp=0;


    for(int i=0;i<n;i++){
        if(new[i]!=-1&&old[i]==-1){
            push(ans,i); //update nodes that are not on old path and on new path
            dsuUnion(i, findDestination(i));
            updateCounter++;
            updated[i]=1;
            temp=1;
        }
        if(new[i]!=old[i]){
            operation++;
        }
    }
    if(temp==1){ // this flag checks if there's any node pushed to ans, if so, then roundCounter++
        push(ans,-1);
        roundCounter++;
    }

    while(updateCounter!=operation){
        int maxIndex=-1, maxValue=INT_MIN;
        checkBackward();// check all the nodes if they're pointing backward
        for(int i=0;i<n;i++){
            if(updated[i]==0&&new[i]!=-1&&backward[i]!=1){
                temp=skipCount(i);
                if(temp>maxValue){
                    maxValue=temp; // find the shortcut with maximum skipCount value
                    maxIndex=i;
                }
            }
        }
        if(maxIndex==-1){ // if no shortcut found
            break;
        }
        addShortcut(maxIndex); //update that node
        roundCounter++;
        push(ans, -1);
        pruneFunction();

    }

    temp=0;
    for(int i=0;i<n;i++){
        if(old[i]!=-1&&new[i]==-1){//update nodes that are on old path and not on new path
            temp=1;
            push(ans,i);
            updateCounter++;
            updated[i]=1;
        }
    }

    if(temp==1){ // this flag checks if there's any node pushed to ans, if so, then roundCounter++
        push(ans,-1);
        roundCounter++;
    }

    printf("%d\n",roundCounter);
    for(int i=0;i<roundCounter;i++){ //print the answer
        while(1){
            int temp=top(ans);
            pop(ans);
            if(temp==-1){
                break;
            }
            else{
                old[temp]=new[temp];
            }
        }
        for(int j=0;j<n;j++){
            printf("%d",old[j]);
            if(j!=n-1){
                printf(" ");
            }
        }
        if(i!=roundCounter-1){
            printf("\n");
        }
    }
}