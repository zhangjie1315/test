LinkNode* LinkListMerge(LinkNode* phead1,LinkNode* phead2)
{

    if(phead1==NULL)
    {
        return phead2;
    }
    if(phead2==NULL)
    {
        return phead1;
    }
    LinkNode* cur1=phead1;
    LinkNode* cur2=phead2;
    LinkNode* new_head=NULL;
    LinkNode* new_tail=NULL;
    while(cur1!=NULL&&cur2!=NULL)
    {
        if(cur1->data<cur2->data)
        {
            if(new_head==NULL)
            {
                new_head=new_tail=cur1;
            }
            else {

                new_tail->next=cur1;
                new_tail=new_tail->next;
            }
            cur1=cur1->next;
        }
        if(cur1>cur2)
        {
            if(new_head==NULL)
            {
                new_head=new_tail=cur2;
            }
            else
            {
                new_tail->next=cur2;
                new_tail=new_tail->next;
            }
            cur2=cur2->next;
        }
    if(cur1!=NULL)
    {
        new_tail->next=cur1;
    }
    if(cur2!=NULL)
    {
        new_tail->dext=cur2;
    }
    return new_head;
}
}
