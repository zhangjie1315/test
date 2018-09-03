//不允许遍历链表
//在pos节点前插入数据
//在pos节点后创建一个和pos一样的节点，然后将把要插入的值给pos所指向的数据
void LinkListInsertSp(LinkNode **phead,LinkNode *pos,LinkListType value)
{
    if(phead==NULL||pos==NULL)
    {

        //非法输入
        return;
    }
    if(*phead==NULL)
    {
        //链表为空
        return;
    }
    LinkNode *p =CreateNode(pos->data);
    p->next = pos->next;

    pos->next = p;
    pos->data = value;
    return;
}
