//单链表的逆序
//每次取下一个节点放到头结点前边并将头指针前移
void LinkListReverse(LinkNode **phead)
{

    if(phead==NULL)
    {
        //非法输入
        return;
    }
    if(*phead==NULL)
    {
        //空链表
        return;
    }
    if((*phead)->next=NULL)
    {
        //只有一个节点
        return;
    }
    LinkNode *cur=*phead;
    while(cur->next!=NULL)
    {
        LinkNode *to_delete=cur->next;
        cur->next=to_delete->next;
        to_delete->next=*phead;
        *phead=to_delete;
    }
    return;
}
