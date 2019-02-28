# include<stdio.h>
# include<stdlib.h>
int num1;/*BSS段*/
int num2 = 2;/*全局区*/
char * str1 = "str1";/*文字常量区*/
int main(void){
    printf("%d\n",getpid());/*获取当前进程id号*/

    int num3 = 3;/*栈区*/
    static int num4 = 4;/*全局区*/
    const int num5 = 5;/*栈区*/
    char * str2 = "str2";/*文字常量区*/
    char str3[] = "str3";/*栈区*/
    int * p = malloc(sizeof(0));/*&p在栈区，p在堆区*/

    printf("num1:%p\nnum2:%p\nnum3:%p\nnum4:%p\nnum5:%p\n",&num1,&num2,&num3,&num4,&num5);
    printf("str1:%p\nstr2:%p\nstr3:%p\n",str1,str2,str3);
    printf("&p:%p\np:%p\n",&p,p);

    while(1){}/*死循环以保证进程不会结束，方便查看/proc/pid/maps文件*/

    free(p);

    return 0;
}

//build: gcc 20180224-maps.c -o 20180224-maps
