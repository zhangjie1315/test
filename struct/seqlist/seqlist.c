#include <stdio.h>

//初始化
void SeqListInit(SeqList *seqlist)
{
    if(seqlist==NULL){
        return;//非法输入
    }
    seqlist->size=0;
}
