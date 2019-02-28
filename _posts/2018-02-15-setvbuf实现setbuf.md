---
layout:     	post
title:      	setvbuf实现setbuf
subtitle:   	apue习题setbuf
date:       	2018-02-15
author:     	abra
#header-img: 	img/post-ccp-logo.png
catalog: 	true
tags:
    - apue
    - setbuf
    - 标准IO
---



#### 题目

​	用setvbuf实现setbuf。

#### 标准库原型

```c
#include <stdio.h>
void setbuf(FILE *restrict fp, char* restrict buf);
int setvbuf(FILE *restrict fp, char* restrict buf, int mode, size_t size);
// 返回值：成功，返回0；否则，返回非0.
```

#### 思路

考虑缓存的三种类型：

- 不带缓存：buf为空或fp为stderr
- 行缓存：fp为stdin和stdout
- 全缓存：其他情况



#### 实现

```c
#include "apue.h"

/*
    apue prictise 5-1
    用setvbuf实现setbuf;
*/

void setbuf_test(FILE* restrict fp, char* restrict buf)
{
    if(fp==stderr || buf == NULL)
    {
        if(0!=setvbuf(fp,buf,_IONBF,BUFSIZ))
        {
            perror("setvbuf error.");
            exit(-1);
        }
        printf("no buf\n");
    }else{
        if(fp == stdin ||fp=stdout)
        {
            if(0!=setvbuf(fp,buf,_IOLBF,BUFSIZ)){
                perror("setvbuf error");
                exit(-1);
            }
            printf("line buff\n");
        }else{
            if(0!=setvbuf(fp,buf,_IOFBF,BUFSIZ)){
                perror("setvbuf error");
                exit(-1);
            }
            printf("Fill buff\n");
        }
    }
}

```

