#pragma once
#include<stddef.h>
#define SeqListMaxSize  100
#define SeqListType char
typedef struct SeqList{
    SeqListType data[SeqListMaxSize];
    size_t size;//当前的有效数据个数
}SeqList;
