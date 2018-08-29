//查找单链表倒数第k个节点（只能一次链表）
//设置两个指针分别为fast,slow,先让fast走k步，然后fast和slow同时向后走
//当fast指向NULL时，此时slow指向的就是倒数第k个位置
LinkNode* LinkListFindK(LinkNode* phead,size_t k){
    if(phead = NULL)
    {
        //空链表
        return NULL;
    }
    LinkNode* fast = phead;
    LinkNode* slow = phead;
    size_t i = 0;
    for(i=0;i<k;i++)
    {
        if(fast==NULL)
        {
            break;
        }
        fast = fast->next;
    }
    while(fast!=NULL)
    {
        slow = slow->next;
        fast = fast->next;
    }
    return slow;
}
