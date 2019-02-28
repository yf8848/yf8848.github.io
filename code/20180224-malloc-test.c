/*****************************
**
**测试环境：minGw gcc 5.1.0
**测试int * p = malloc(0);p是否指向NULL
**
*****************************/
#include<stdio.h>
#include<stdlib.h>
int main(void){
    int * p = (int *)malloc(0);
    printf("%d,%d\n",*(p),*(p+1024));
    free(p);
    
    //int * q = NULL;
    //printf("%d,%d\n",*(q),*(q+1024));
    return 0;
}
