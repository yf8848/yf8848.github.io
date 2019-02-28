---
layout:     post
title:      Mysql中varchar类型长度问题
subtitle:   mysql、数据库、varchar
date:       2017-12-04
author:     abra
#header-img: img/post-mysql.jpg
catalog: true
tags:
    - varchar
    - mysql
---

> 今天在设计一个简单，但是value值可能会很长的数据库表时；考虑到`varchar`类型长度问题。遇到了一个有意思的问题。

#### 1. 库表字段

库表的字段很简单，基本就是key，value类型。`Fvalue`字段的值可能很长，所以需要将varchar字段的值设置为比较大的值。库表创建语句如下：

```mysql
CREATE TABLE check_acc.t_system(
Fbkid bigint(20) NOT NULL AUTO_INCREMENT,
Fkey varchar(64)  NOT NULL DEFAULT '',
Fvalue varchar(?)  NOT NULL DEFAULT '',
Fmodify_time datetime DEFAULT NULL,
Fcreate_time datetime DEFAULT NULL,
PRIMARY KEY (Fbkid),
KEY k2key (Fkey)
)ENGINE=InnoDB AUTO_INCREMENT=0 DEFAULT CHARSET=latin1;
```

不考虑其他字段，聚焦到`Fvalue`字段
#### 2. `varchar(?)` 的值会自动扩展吗
做一个简单的测试。

- 版本如下：

  ```mysql
  mysql> select version();
  +------------+
  | version()  |
  +------------+
  | 5.7.15-log |
  +------------+
  1 row in set (0.00 sec)
  ```

  ​


- 将`Fvalue`字段长度设定为8，建表语句如下：

  ``` mysql
  CREATE TABLE check_acc.t_system(
   Fbkid bigint(20) NOT NULL AUTO_INCREMENT,
   Fkey varchar(64)  NOT NULL DEFAULT '',
   Fvalue varchar(8)  NOT NULL DEFAULT '',
   Fmodify_time datetime DEFAULT NULL,
   Fcreate_time datetime DEFAULT NULL,
   PRIMARY KEY (Fbkid),
   KEY k2key (Fkey)
  )ENGINE=InnoDB AUTO_INCREMENT=0 DEFAULT CHARSET=latin1;
  ```

  ​

- 插入一条记录，如下：

  ```mysql
  insert into check_acc.t_system(Fkey,Fvalue,Fmodify_time,Fcreate_time) values('exclude_uids','931810|931812',now(),now());
  ```

- 查看插入的值:

  ```mysql
  mysql> select * from check_acc.t_system;
  +-------+--------------+----------+---------------------+---------------------+
  | Fbkid | Fkey         | Fvalue   | Fmodify_time        | Fcreate_time        |
  +-------+--------------+----------+---------------------+---------------------+
  |     1 | exclude_uids | 931810|9 | 2017-12-04 11:59:58 | 2017-12-04 11:59:58 |
  +-------+--------------+----------+---------------------+---------------------+
  1 row in set (0.00 sec)
  ```

> **结论：** 在5.7的mysql上，当实际长度大于我们设定的值时，我们的测试结果是varchar()的设定的长度是不会自动增长的。如果实际长度小于设定的值，会存储实际的长度值+1。而char(M)是固定M个字长。



#### 3. `varchar` 还是 `TEXT` ####

1. 存储字符长度比较大可选的有`varchar`和`TEXT`两种数据类型。具体长度如下：

| 字符串类型      |         描述及存储要求          |
| :--------- | :----------------------: |
| varchar(M) | M为0~65535之间的整数，值的长度+1个字节 |
| TEXT       | 允许的长度0~65535字节，值的长度+2个字节 |



​	从上面的图标可以看到`varchar`和`TEXT` 两种类型的最大长度都是65535，对于我们的需求，大部分值都不会超过65535。考虑到检测效率，大小范围的变化，避免用`TEXT`类型。我们采用`varchar`类型.

> 避免用`TEXT`类型：
>
> - 检测效率：`cahr` > `varchar` > `TEXT`。
> - 性能问题：`TEXT`会性能问题，当表执行delete操作，会造成很大的‘空洞’，对插入的性能影响和内存浪费影响都很大，需要用 `OPTIMIZE TABLE` 对这类表进行碎片整理。



2. 接下来，让我们按预想的方式更改库表，看看发生了什么.

   ```mysql
   mysql> alter table check_acc.t_system change Fvalue  Fvalue varchar(65534)  NOT NULL DEFAULT '';
   ERROR 1118 (42000): Row size too large. The maximum row size for the used table type, not counting BLOBs, is 65535. This includes storage overhead, check the manual. You have to change some columns to TEXT or BLOBs
   ```

   错误！说行大小超过65535，建议采用`TEXT` or `BLOB` 类型。 可是上面命名说最大是65535，怎么会超呢？

3. 字符集不同导致的字母、汉字张勇的字节数不同

   > - latin1:
   >
   >   1character=1byte, **1汉字=2character**,
   >
   >   也就是说一个字段定义成 `varchar(200)`，则它可以存储100个汉字或者200个字母。
   >
   >   这一点要注意，尤其是当字段内容是字母和汉字组成时，尽量假设字段内容都是由汉字组成，据此来设置字段长度
   >
   >
   > - utf8:
   >
   >   1character=3bytes, 1汉字=1character
   >
   >   也就是说一个字段定义成 `varchar(200)`，则它可以存储200个汉字或者200个字母。
   >
   >
   > - gbk:
   >
   >   1character=2bytes,1汉字=1character
   >
   >   也就是说一个字段定义成`varchar(200)`，则它可以存储200个汉字或者200个字母。

各种不同字符集下`Fvalue varchar(M)` 字段长度计算方式如下：

 -  utf8:

     -  $$
        M= (65535-1-2-2-8-8-8-64)/3=65442/3=21814
        $$

        - 减1：实际行存储从第二个字节开始
        - 减2：`varchar` 头部的两个字节标示长度。两个`varchar`类型字段，减两次
        - 减8：
          - `datatime` 字段长度占用8字节。减两次；
          - `bigint` 字段长度为8字节。

- gbk:
  $$
  M=(65535-1-2-2-8-8-8-64)/2=65442/2=32721
  $$

- latin1:
  $$
  M=(65535-1-2-2-8-8-8-64)/1=65442
  $$





4. 更新库表`Fvalue`字段长度：

   ```mysql
   mysql> alter table check_acc.t_system change Fvalue  Fvalue varchar(65442)  NOT NULL DEFAULT '';
   Query OK, 1 row affected (0.06 sec)
   Records: 1  Duplicates: 0  Warnings: 0
   ```

   ​

#### 4. 长度够用吗 ####

说点题外话，这个库表里面我们的`Fvalue`字段最终长度设定为65442，可以存储`65442`个字母或者`65442/2`个汉字；但是这个长度不能保证长度够不够用。在库表设计的时候，我们设定了一个自增主键`Fbkid`字段，用来区分每条记录。当`Fvalue` 长度不够用时，可以以同名key重新插入一条记录。
