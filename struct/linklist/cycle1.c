//判断单链表是否带环，带环返回相遇点的指针
//设置两个指针fast slow,fast一次走两次，slow一次走一次
//如果链表带环则还会再次相遇。如果不带环，则fast一定会走到NULL

void LinkNodeCycle1(LinkNode *phead)
{
    if(phead = NULL)
    {
        //空链表
        return NULL;
    }
    LinkNode* fast = phead;
    LinkNode* slow = phead;
    while(fast!=NULL&&fast->next!=NULL)
    {
    fast=fast->next->next;
    slow=slow->next;
    if(fast==slow)
    {
        //快慢指针再次相遇，则一定带环
        return fast;
    }
    }
    //链表走到这则一定带环
    return NULL;
}
