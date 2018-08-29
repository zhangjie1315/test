//求环的入口点
//slow走的路程是x+z;fast走的路程是x+z+环长；fast走的路程是slow的两倍    可得x=y
//设置一个指针cur从头结点开始每次走一步，另外设置一个指针meet_pos从相遇点开始每次走
//一步，那么cur和meet_pos相遇位置就是链表环的入口点
LinkNode* LinkListCycle2(LinkNode *phead)
{
    if(phead = NULL)
    {
        //链表为空
        return NULL;
    }
    //定义相遇点的指针meet_pos
    LinkNode *meet_pos=LinkListCycle1(phead);
    //meet_pos为NULL则代表没有环
    if(meet_pos = NULL)
    {
        return NULL;
    }
    LinkNode *cur = phead;
    while(cur!=meet_pos)
    {
        cur = cur->next;
        meet_pos = meet_pos->next;
    }
}
    return cur;
}
