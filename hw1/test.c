#include <stdio.h>

int main(){
    int a[4][4];
    for(int i = 0; i < 4; i++){
        for(int k = 0; k < 4; k++){
            scanf("%d",&a[i][k]);
        } 
    }
    for(int j = 0 ; j < 4; j++){
        for(int n = 0; n < 4; n++){
            printf("%d",a[j][n]);
        }
    }
    return 0;
}